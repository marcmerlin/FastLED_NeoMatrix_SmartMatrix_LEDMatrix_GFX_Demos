#ifndef WIFI_SERIAL_OTA_H
#define WIFI_SERIAL_OTA_H

#if 0
How do you find your device after it boots?

sauron:~# avahi-browse -rt _arduino._tcp
+  wlan0 IPv4 P1.825-64BY64                                 _arduino._tcp        local
+  wlan0 IPv4 Marc NFL-3                                    _arduino._tcp        local
+  wlan0 IPv4 P4-64BY32X2                                   _arduino._tcp        local
+  wlan0 IPv4 Marc NFL                                      _arduino._tcp        local
=  wlan0 IPv4 P1.825-64BY64                                 _arduino._tcp        local
   hostname = [P1\.825-64BY64.local]
   address = [192.168.205.187]
   port = [3232]
   txt = ["board=adafruit_matrixportal_esp32s3" "tcp_check=no" "ssh_upload=no" "auth_upload=no"]
=  wlan0 IPv4 Marc NFL-3                                    _arduino._tcp        local
   hostname = [Marc\032NFL-3.local]
   address = [192.168.205.194]
   port = [3232]
   txt = ["board=waveshare_esp32_s3_zero" "tcp_check=no" "ssh_upload=no" "auth_upload=no"]
=  wlan0 IPv4 P4-64BY32X2                                   _arduino._tcp        local
   hostname = [P4-64BY32X2.local]
   address = [192.168.205.203]
   port = [3232]
   txt = ["board=adafruit_matrixportal_esp32s3" "tcp_check=no" "ssh_upload=no" "auth_upload=no"]
=  wlan0 IPv4 Marc NFL                                      _arduino._tcp        local
   hostname = [Marc\032NFL.local]
   address = [192.168.205.218]
   port = [3232]
   txt = ["board=waveshare_esp32_s3_zero" "tcp_check=no" "ssh_upload=no" "auth_upload=no"]
#endif

#include "wifi_secrets.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ArduinoOTA.h>

// you define WIFI_HOSTNAME before doing #include "wifi_serial_ota.h"
// Also define WIFI_SSID and WIFI_PASSWORD before you include
#ifndef WIFI_HOSTNAME
#define WIFI_HOSTNAME "CHANGEME WIFI_HOSTNAME"
#endif

#ifndef WIFI_OTA_PWD
#define WIFI_OTA_PWD` "CHANGEME"
#endif

#ifndef TELNET_PORT
#define TELNET_PORT 23
#endif


template <typename T>
class GenericSerialSplitter : public Stream {
private:
  T* hw;
  WiFiServer* server;
  WiFiClient client;
  bool serverStarted = false; 
  NetworkUDP udpServer;
  bool udpStarted = false;
  uint16_t udpPort;
  
  // Cooldown timer to prevent UDP polling from starving the network stack
  unsigned long lastUdpCheck = 0;
  const unsigned long UDP_COOLDOWN_MS = 100; // 10Hz limit

public:
  GenericSerialSplitter(T& hardwareSerial, uint16_t port = 23) {
    hw = &hardwareSerial;
    server = new WiFiServer(port);
    udpPort = port;
  }

  // Pass the initialization through to the underlying serial interface
  void begin(unsigned long baud) {
    hw->begin(baud);
  }

    // Boolean operator so "if (Serial)" and "while (!Serial)" evaluate cleanly
  operator bool() const {
    return hw ? (bool)(*hw) : false;
  }

  void restart() {
    Serial.println("Inside SerialSplitter.restart()");
    if (serverStarted) {
        server->end();
        serverStarted = false;
        Serial.println("SerialSplitter.restart(): end Splitter");
    }
    if (client) {
        client.stop();
        Serial.println("SerialSplitter.restart(): stop client");
    }
    if (udpStarted) {
        udpServer.stop(); 
        udpStarted = false;
    }
  }

  void handle() {
    if (WiFi.status() != WL_CONNECTED && WiFi.getMode() != WIFI_AP && WiFi.getMode() != WIFI_AP_STA) {
        return; 
    }

    if (!serverStarted) {
        Serial.println("SerialSplitter: (re)start");
        server->begin();
        serverStarted = true;
    }

    // Enabling this in the past caused it to eat UDP broadcast from the master
    // hopefully UDP_COOLDOWN_MS will fix this and allow enabling safely
    if (!udpStarted) {
        Serial.println("SerialSplitter: (re)start UDP");
        if (udpServer.begin(udpPort)) {
            udpStarted = true;
        }
    }

    if (server->hasClient()) {
      if (!client || !client.connected()) {
        if (client) client.stop();
        // Fixed Core 3.x deprecation: converted available() to accept()
        client = server->accept(); 
        client.println("\n--- Connected to ESP32 Serial Splitter ---");
      } else {
        // Fixed Core 3.x deprecation: converted available() to accept()
        WiFiClient reject = server->accept();
        reject.stop(); 
      }
    }
  }

  // --- STREAM/PRINT OUTPUT OVERRIDES ---
  
  size_t write(uint8_t c) override {
    size_t n = hw->write(c);         
    if (client && client.connected()) {
      client.write(c);               
    }
    return n;
  }

  size_t write(const uint8_t *buffer, size_t size) override {
    size_t n = hw->write(buffer, size);
    if (client && client.connected()) {
      client.write(buffer, size);
    }
    return n;
  }

  // --- STREAM INPUT OVERRIDES (TWO-WAY COMMS) ---

  int available() override { 
    int total = hw->available();
    if (client) {
      total += client.available();
    }
    if (udpStarted) {
        // RATE LIMITING: Only check for new UDP packets every 100ms
        if (millis() - lastUdpCheck > UDP_COOLDOWN_MS) {
            lastUdpCheck = millis();
            if (udpServer.available() == 0) {
                udpServer.parsePacket();
            }
        }
        total += udpServer.available();
    }
    return total;
  }

  int read() override { 
    if (client && client.available()) {
      return client.read();
    }
    if (udpStarted && udpServer.available()) {
      return udpServer.read();
    }
    return hw->read(); 
  }

  int peek() override { 
    if (client && client.available()) {
      return client.peek();
    }
    if (udpStarted && udpServer.available()) {
      return udpServer.peek();
    }
    return hw->peek(); 
  }

  void flush() override { 
    hw->flush(); 
    // Fixed Core 3.x deprecation: converted flush() to clear()
    if(client) client.clear(); 
  }
};

// 2. Instantiate our splitter using decltype(Serial) to automatically match the architecture
GenericSerialSplitter<decltype(Serial)> Splitter(Serial, TELNET_PORT);

// 3. THE HIJACK: Replace the word "Serial" with our Splitter for the rest of this file
#undef Serial
#define Serial Splitter

void wifi_loop() {
  ArduinoOTA.handle();
  Splitter.handle();
}

void wifi_setup() {
  Serial.begin(115200);
  //while (!Serial) {}
  Serial.println("Start");

  // Wi-Fi Event Callbacks
  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.printf("\n[WiFi] Connected! IP: %s | Hostname: %s.local | Telnet ready port %d (use nc, not telnet)\n", 
                  WiFi.localIP().toString().c_str(), 
                  WIFI_HOSTNAME, TELNET_PORT);
  }, ARDUINO_EVENT_WIFI_STA_GOT_IP);

  WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info) {
    Serial.printf("\n[WiFi] Disconnected. Reason: %d\n", info.wifi_sta_disconnected.reason);
  }, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  Serial.print("Wifi: ");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  // I think this is default now?
  WiFi.setAutoReconnect(true);

  Serial.println("Setup ArduinoOTA. Remote Wifi Updates Supported!");
  ArduinoOTA.setHostname(WIFI_HOSTNAME);
  ArduinoOTA.setPassword(WIFI_OTA_PWD);
  ArduinoOTA.begin();
  Serial.println("OTA Ready");
}
#endif
