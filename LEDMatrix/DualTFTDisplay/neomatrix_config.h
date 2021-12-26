#ifndef neomatrix_config_h
#define neomatrix_config_h

#include <Adafruit_GFX.h>
bool init_done = 0;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

// min/max are complicated. Arduino and ESP32 layers try to be helpful by using
// templates that take specific kinds of arguments, but those do not always work
// with mixed types:
// error: no matching function for call to 'max(byte&, int16_t&)'
// These defines get around this problem.
#define mmin(a,b) ((a<b)?(a):(b))
#define mmax(a,b) ((a>b)?(a):(b))

// The ESP32 FastLED defines below must be defined before FastLED.h is loaded
// They are not relevant if you don't actually use FastLED pixel output but cause
// no harm if we only include FastLED for its CRGB struct.
#ifdef ESP32
    // Allow infrared for old FastLED versions
    #define FASTLED_ALLOW_INTERRUPTS 1
    // Newer Samguyver ESP32 FastLED has a new I2S implementation that can be
    // better (or worse) than then default RMT which only supports 8 channels.
    #define FASTLED_ESP32_I2S
    #pragma message "Please use https://github.com/samguyer/FastLED.git if stock FastLED is unstable with ESP32"
#endif
#include <FastLED.h>

#ifdef LEDMATRIX
// Please use https://github.com/marcmerlin/LEDMatrix/ at least as recent as
// https://github.com/marcmerlin/LEDMatrix/commit/597ce703e924d45b2e676d6558c4c74a8ebc6991
// or https://github.com/Jorgen-VikingGod/LEDMatrix/commit/a11e74c8cd5b933021b6e15eb067280a52691449
// zero copy/no malloc code to work.
#include <LEDMatrix.h>
#endif


//============================================================================
// Ok, if you're doing matrices of displays, there is also a reasonable chance
// you'll be using SPIFFS or FATFS on flash, or an sdcard, so let's define it
// here (NeoMatrix-FastLED-IR actually also uses this to read a config file)
//============================================================================

// control if we decode in 32x32 or 64x64, or something else
#ifdef ESP8266
#define gif_size 32
#else
#define gif_size 64
#endif

// Note, you can use an sdcard on ESP32 or ESP8266 if you really want,
// but if your data fits in built in flash, why not use it?
// Use built in flash via SPIFFS/FATFS
// esp8266com/esp8266/libraries/SD/src/File.cpp
// ESP8266: http://esp8266.github.io/Arduino/versions/2.3.0/doc/filesystem.html#uploading-files-to-file-system
// ESP32: https://github.com/me-no-dev/arduino-esp32fs-plugin
// https://github.com/marcmerlin/esp32_fatfsimage/blob/master/README.md
#if defined(ESP8266)
    #define FS_PREFIX ""
    #include <FS.h>
    #define FSO SPIFFS
    #define FSOSPIFFS
    #if gif_size == 64
        #define GIF_DIRECTORY FS_PREFIX "/gifs64/"
    #else
        #define GIF_DIRECTORY FS_PREFIX "/gifs/"
    #endif
    extern "C" {
        #include "user_interface.h"
    }
#elif defined(ESP32)
    #define FS_PREFIX ""
    //#include <SPIFFS.h>
    //#define FSOSPIFFS
    //#define FSO SPIFFS
    #include "FFat.h"
    #define FSO FFat
    #define FSOFAT
    // Do NOT add a trailing slash, or things will fail
    #if gif_size == 64
        #define GIF_DIRECTORY FS_PREFIX "/gifs64"
    #else
        #define GIF_DIRECTORY FS_PREFIX "/gifs"
    #endif
#elif defined(ARDUINOONPC)
    #define UNIXFS
    #define FS_PREFIX "/root/NM/"
    #define GIF_DIRECTORY FS_PREFIX "gifs/"
#else
    #define FS_PREFIX ""
    #define FSO SD
    #define FSOSD
    #if defined (ARDUINO)
    #include <SD.h>
    #endif
    // Chip select for SD card on the SmartMatrix Shield or Photon
    // Teensy 3.5/3.6
    #if defined(__MK64FX512__) || defined(__MK66FX1M0__)
        #define SD_CS BUILTIN_SDCARD
    #elif defined(ESP32)
        #define SD_CS 5
    #elif defined (ARDUINO)
        #define SD_CS 15
        //#define SD_CS BUILTIN_SDCARD
    #elif defined (SPARK)
        #define SD_CS SS
    #endif

    // Teensy SD Library requires a trailing slash in the directory name
    #if gif_size == 64
        #define GIF_DIRECTORY FS_PREFIX "/gifs64/"
    #else
        #define GIF_DIRECTORY FS_PREFIX "/gifs/"
    #endif
#endif

// The library now defines default TFT pins, but we override them
#define NO_TFT_SPI_PIN_DEFAULTS
#include <FastLED_ArduinoGFX_TFT.h>

/*  https://pinout.xyz/pinout/spi
SD1331 Pin	    Arduino	ESP8266		ESP32	ESP32	rPi     rPi
1 GND                                       VSPI    HSPI	SPI0    SPI1
2 VCC
3 SCL/SCK/CLK/D0	13	GPIO14/D5	18	14	BC11/22	BC21/40
4 SDA/SDI/MOSI/D1	11	GPIO13/D7	23	13	BC10/19	BC20/38
---- 2 pins above and MISO are HWSPI, pins below are anything
---- RST is not part of SPI, it's an out of band signal to reset a TFT
---- This could be wired to the ESP32 EN(reset) pin
5 RES/RST		9	GPIO15/D8	26	26	BC24
---- Data/Command pin is not part of SPI but used to tell the TFT if incoming SPI
---- data is actually a command, or pixel data.
6 DC/A0/RS (data)	8	GPIO05/D1	25	25	BC23
---- Cable select chooses which SPI device we're talking to, if there is only
---- one, it can be tied to ground. Any pin is fine
7 CS/SS => GND	10	GPIO04/D2	0	2	BC08

CS2: 2 => if you have 2 different screens, need 2 CS pins

---- MISO is not used to talk to TFTs, but is one of the 3 SPI hardware pins
  MISO		12	GPIO12/D6	19	12	BM11/23	BC19/35
*/

// this is the TFT reset pin. Some boards may have an auto-reset
// circuitry on the breakout so this pin might not required but it can
// be helpful sometimes to reset the TFT if your setup is not always
// resetting cleanly. Connect to ground to reset the TFT
#define TFT_RST 26 // Grey
//#define TFT_RST -1 // Grey, can be wired to ESP32 EN to save a pin
#define TFT_DC  25 // Purple
//#define TFT_CS -1 // for display without CS pin
#define TFT_CS  0 // White can be wired to ground if you only have one device
#define TFT_CS2 2 // Orange if you have 2 different screens

#define TFT_MOSI 23 // Blue
#define TFT_CLK  18 // Green
#define TFT_MISO 19 // Yellow
#define TFT_BL 15
#define TFT_SCK TFT_CLK

#define HAS_TFT
#include <Arduino_GFX_Library.h>

#define TFTCNT 2
Arduino_DataBus *bus_[TFTCNT];
Arduino_TFT *tft_[TFTCNT];
CRGB *matrixleds_[TFTCNT];
FastLED_ArduinoGFX_TFT *matrix_[TFTCNT];
uint16_t mw_[TFTCNT];
uint16_t mh_[TFTCNT];
uint16_t tftw_[TFTCNT];
uint16_t tfth_[TFTCNT];
uint8_t gfx_scale_[TFTCNT];
const char *tftname_[TFTCNT];

Arduino_TFT* tft;
CRGB *matrixleds;
FastLED_ArduinoGFX_TFT *matrix;

//----------------------------------------------------------------------------
// ILI9341 

// It would be great if we could do this, but many programs use size related variables to
// define static arrays, which required constants
//uint16_t tftw1 = tft1->width();
//uint16_t tfth1 = tft1->height();
const uint16_t tftw1 = 320;
const uint16_t tfth1 = 240;
const uint16_t mw1 =   tftw1;

// if you are using ILI9341 on ESP32, the framebuffer does not fit in memory (224KB)
// If PSRAM is available, it will get used. If not, you need to make the framebuffer
// smaller than the TFT. One simple way is to have the framebuffer be half the screen
// size, render what you need in one half, display it, render the other half and then
// render that.
// Before you ask "why would I do this, in that case I can just render to the TFT directly"
// the answer is "yes, you can as long as you are using GFX directly, you can indeed skip
// the framebuffer, but if you use FastLED/LEDMatrix code that requires a CRGB 24bpp buffer
// and does transformations like reading the framebuffer and flipping parts of it, you do
// need the framebuffer and therefore it could make sense to split the screen in two and
// render each half separately.
// In my case, I can use LEDText for fancy font rendering not supported by Adafruit's GFX
// and then display the 24bpp framebuffer on the 16bpp TFT

#ifdef ESP32
    #ifdef BOARD_HAS_PSRAM
        #pragma message "Compiling for ILI9341 on ESP32 with PSRAM"
        const uint16_t mh1 = tfth1;
    #else
        #pragma message "Compiling for ILI9341 on ESP32 without PSRAM, framebuffer will only be half height"
        const uint16_t mh1 = tfth1/2;
    #endif
#else
    #pragma message "Compiling for ILI9341. Most chips except teensy 3.6 and better, won't have enough RAM"
    const uint16_t mh1 = tfth1;
#endif

#ifdef LEDMATRIX
    cLEDMatrix<-mw1, mh1, HORIZONTAL_MATRIX, 1, 1, HORIZONTAL_BLOCKS> ledmatrix1(false);
#endif

//----------------------------------------------------------------------------
// SSD1331

#if SSD1331_ROTATE == 0
    const uint16_t mw2 = 96;
    const uint16_t mh2 = 64;
#else
    const uint16_t mw2 = 64;
    const uint16_t mh2 = 96;
#endif

// Templates suck, we need to define them separately with variable names and they
// cannot be cast to a common type stored in an array
#ifdef LEDMATRIX
    cLEDMatrix<-mw2, mw2, HORIZONTAL_MATRIX, 1, 1, HORIZONTAL_BLOCKS> ledmatrix2(false);
#endif
    

//============================================================================
// End Matrix defines
//============================================================================

#ifdef ESP8266
// Turn off Wifi in setup()
// https://www.hackster.io/rayburne/esp8266-turn-off-wifi-reduce-current-big-time-1df8ae
//
#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}
#endif // ESP8266

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t speed = 255;

float matrix_gamma = 1; // higher number is darker, needed for Neomatrix more than SmartMatrix

// FastLED::colorutils needs a signature with uint8_t
uint16_t XY( uint8_t x, uint8_t y) {
    return matrix->XY(x,y);
}
// but x/y can be bigger than 256
uint16_t XY16( uint16_t x, uint16_t y) {
    return matrix->XY(x,y);
}

int wrapX(int x) {
    if (x < 0 ) return 0;
    if (x >= tft->width()) return (tft->width()-1);
    return x;
}

void show_free_mem(const char *pre=NULL) {
    Framebuffer_GFX::show_free_mem(pre);
}

void die(const char *mesg) {
    Serial.println(mesg);
    while(1) delay((uint32_t)1); // while 1 loop only triggers watchdog on ESP chips
}

void *mallocordie(const char *varname, uint32_t req, bool psram=true) {
    // If varname starts with @, show debug for the allocation
    void *mem;

#ifndef BOARD_HAS_PSRAM
    psram = false;
#endif
    if (varname[0] == '@') {
        if (psram) Serial.print("PS");
        Serial.print("Malloc ");
        Serial.print(varname);
        Serial.print(" . Requested bytes: ");
        Serial.println(req);
    }
#ifdef ESP32
    if (psram) {
        mem = ps_malloc(req);
    } else {
        mem = malloc(req);
    }
#else
    mem = malloc(req);
#endif

    if (mem) {
        return mem;
    } else {
        show_free_mem();
        Serial.println("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv");
        Serial.print("FATAL: ");
        if (psram) Serial.print("ps_");
        Serial.print("malloc failed for ");
        Serial.print(varname);
        Serial.print(" . Requested bytes: ");
        Serial.println(req);
        Serial.println("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^");
        while (1); // delay(1);  Adding this seems to cause an ESP32 bug
    }
    return NULL;
}

uint32_t millisdiff(uint32_t before) {
    return((millis()-before) ? (millis()-before): 1);
}

void tft_init(uint8_t tftidx) {
    uint16_t mw = mw_[tftidx];
    uint16_t mh = mh_[tftidx];
    uint16_t tftw = tftw_[tftidx];
    uint16_t tfth = tfth_[tftidx];
    uint16_t gfx_scale = gfx_scale_[tftidx];
    uint32_t NUMMATRIX = mw * mh;
    
    tft = tft_[tftidx];
    matrix = matrix_[tftidx];
    Serial.print("\nMalloc for ");
    Serial.print(tftname_[tftidx]);
    Serial.print(" pixels: ");
    Serial.println(NUMMATRIX);
    // ESP32 has more memory available for allocation in setup than in global
    // (if this were a global array), so we use malloc here.
    // https://forum.arduino.cc/index.php?topic=647833
    matrixleds_[tftidx] = (CRGB *) mallocordie(tftname_[tftidx], sizeof(CRGB) * NUMMATRIX, 1);
    // and then fix the until now NULL pointer in the object.
    matrix->newLedsPtr(matrixleds_[tftidx]);
    show_free_mem("After matrixleds malloc");
    #ifdef LEDMATRIX
        Serial.println("ledmatrix.SetLEDArray");
        // Did I mention templates suck? :)
        if (tftidx==0) ledmatrix1.SetLEDArray(matrixleds_[tftidx]);
        if (tftidx==1) ledmatrix2.SetLEDArray(matrixleds_[tftidx]);
    #endif

    uint32_t tft_spi_speed = 40 * 1000 * 1000;
    Serial.println("");
    Serial.print(tftname_[tftidx]);
    Serial.println(" tft begin");
    Serial.println(">>> If you get no display, try resetting, and removing cross talk between wires or decreasing SPI speed <<<<");
    Serial.println("");
    tft->begin(tft_spi_speed);

    Serial.print("TFT configured, resolution: ");
    Serial.print(tftw);
    Serial.print("x");
    Serial.print(tfth);
    Serial.print(". GFX size:");
    Serial.print(mw);
    Serial.print("x");
    Serial.print(mh);
    Serial.print(". GFX Size Ratio: ");
    Serial.print(gfx_scale);
    Serial.print(". Speed: ");
    Serial.print(tft_spi_speed);
    Serial.println(" (80Mhz is fastest but sometimes unstable)");

    show_free_mem("Before matrix->begin");
    matrix->begin();

    Serial.print("Gamma Correction: ");
    Serial.println(matrix_gamma);
    // Gamma is used by AnimatedGIFs and others, as such:
    // CRGB color = CRGB(matrix->gamma[red], matrix->gamma[green], matrix->gamma[blue]);
    matrix->precal_gamma(matrix_gamma);

    // So this is where things go downhill LEDMatrix uses templates, so it's not really possible
    // to assign them to another variable for templates with different parameters.
    #ifndef DISABLE_MATRIX_TEST
        #ifdef LEDMATRIX
        if (tftidx == 0) {
            Serial.println("LEDMatrix1 Test");
            ledmatrix1.DrawLine (0, 0, ledmatrix1.Width() - 1, ledmatrix1.Height() - 1, CRGB(0, 255, 0));
            ledmatrix1.DrawPixel(0, 0, CRGB(255, 0, 0));
            ledmatrix1.DrawPixel(ledmatrix1.Width() - 1, ledmatrix1.Height() - 1, CRGB(0, 0, 255));

            ledmatrix1.DrawLine (ledmatrix1.Width() - 5, 4, 4, ledmatrix1.Height() - 5, CRGB(128, 128, 128));
            ledmatrix1.DrawPixel(ledmatrix1.Width() - 5, 4,  CRGB(255, 64, 64));
            ledmatrix1.DrawPixel(4, ledmatrix1.Height() - 5, CRGB(64, 64, 255));
        } else {
            Serial.println("LEDMatrix2 Test");
            ledmatrix2.DrawLine (0, 0, ledmatrix2.Width() - 1, ledmatrix2.Height() - 1, CRGB(0, 255, 0));
            ledmatrix2.DrawPixel(0, 0, CRGB(255, 0, 0));
            ledmatrix2.DrawPixel(ledmatrix2.Width() - 1, ledmatrix2.Height() - 1, CRGB(0, 0, 255));

            ledmatrix2.DrawLine (ledmatrix2.Width() - 5, 4, 4, ledmatrix2.Height() - 5, CRGB(128, 128, 128));
            ledmatrix2.DrawPixel(ledmatrix2.Width() - 5, 4,  CRGB(255, 64, 64));
            ledmatrix2.DrawPixel(4, ledmatrix2.Height() - 5, CRGB(64, 64, 255));
        }
        matrix->show();
        delay(1000);
        #endif
    #endif

    #ifndef DISABLE_SPEED_TEST
        uint32_t before;
        Serial.print(tftidx);
        Serial.println(" vvvvvvvvvvvvvvvvvvvvvvvvvv Speed vvvvvvvvvvvvvvvvvvvvvvvvvv");
        #ifdef HAS_TFT
            before = millis();
            // Bypass GFX, write directly to TFT
            for (uint8_t i=0; i<5; i++) {
                tft_[tftidx]->fillScreen(0);
                tft_[tftidx]->fillScreen(0xFFFF);
            }
            Serial.print("TFT SPI Speed: ");
            Serial.print(tft_spi_speed/1000000);
            Serial.print("Mhz (");
            Serial.print(millisdiff(before));
            Serial.print("ms) Resulting fps: ");
            Serial.println(10*1000 / millisdiff(before));

            before = millis();
            for (uint8_t i=0; i<10; i++) {
              matrix->show(0, 0);
              if (gfx_scale != 1) matrix->show(0, mh);
            }
            Serial.print("Matrix->show() Speed Test: ");
            Serial.print(millisdiff(before));
            Serial.print("ms, fps: ");
            Serial.println(10*1000 / (millisdiff(before)));
            // if only one show() command is run and the whole screen 
            // isn't covered, adjust the scale
            //Serial.println(10*1000 / (millisdiff(before)*gfx_scale));

            before = millis();
            for (uint8_t i=0; i<10; i++) {
              matrix->show(0, 0, true);
              if (gfx_scale != 1) matrix->show(0, mh, true);
            }
            // this bypasses accessing PSRAM but also converting, reading, and
            // writing data in the no PSRAM case.
            Serial.print("Matrix->show() BYPASS Speed Test: ");
            Serial.print(millisdiff(before));
            Serial.print("ms, fps: ");
            Serial.println(10*1000 / (millisdiff(before)));
        #endif // HAS_TFT
        before = millis();
        for (uint16_t i=0; i<5; i++) { 
            matrix->fillScreen(0xFC00);
            matrix->show();
            #ifdef HAS_TFT
                if (gfx_scale != 1) matrix->show(0, mh);
            #endif
            matrix->fillScreen(0x003F);
            matrix->show();
            #ifdef HAS_TFT
                if (gfx_scale != 1) matrix->show(0, mh);
            #endif
        }
        Serial.print("Framebuffer::GFX end to end speed test: ");
        Serial.print(millisdiff(before));
        Serial.print("ms, fps: ");
        Serial.println(10*1000 / (millisdiff(before)));
        // Arduino::GFX ILI9314
        //                     tft/gfx/bypass/copy
        // 24Mhz, fps no PSRAM: 14/10/13/ 9       PSRAM: 14/ 8/13/6 (Arduino_HWSPI)
        // 24Mhz, fps no PSRAM: 15/10/13/10  Arduino_ESP32SPI
        // 24Mhz, fps no PSRAM: 21/12/16/12  Arduino_ESP32SPI_DMA
        // 40fhz, fps no PSRAM: 25/15/22/14       PSRAM: 25/11/21/8
        // 80fhz, fps no PSRAM: 42/19/33/18       PSRAM: 40/14/32/9 (Arduino_HWSPI)
        // 80fhz, fps no PSRAM: 53/21/38/20 Arduino_ESP32SPI
        // 80fhz, fps no PSRAM: 60/20/34/18 Arduino_ESP32SPI_DMA
        //
        // Adafruit ILI9314
        // 80Mhz: TFT 40fps, NO PSRAM: 32fps, PSRAM show: 12fps
        // 24Mhz: TFT 14fps, NO PSRAM: 12fps, PSRAM show:  8fps
        //
        // Old Adafruit numbers:
        // ST7735_128b160: 80Mhz: TFT153fps, NO PSRAM:104fps, PSRAM show: 45fps => unstable, no display
        // ST7735_128b160: 60Mhz: TFT 93fps, NO PSRAM: 73fps, PSRAM show: 38fps
        // ST7735_128b160: 60Mhz: TFT 96fps, NO PSRAM: 52fps
        // ST7735_128b160: 40Mhz: TFT 68fps, NO PSRAM: 56fps, PSRAM show: 32fps
        // ST7735_128b160: 20Mhz: TFT 53fps, NO PSRAM: 45fps, PSRAM show: 29fps
        //
        // ST7735_128b128: 60Mhz: TFT117fps, NO PSRAM: 90fps, PSRAM show: 48fps => unstable, garbled
        // ST7735_128b128: 40Mhz: TFT117fps, NO PSRAM: 90fps, PSRAM show: 48fps => unstable, garbled
        // ST7735_128b128: 32Mhz: TFT 84fps, NO PSRAM: 70fps, PSRAM show: 41fps => stable
        // ST7735_128b128: 20Mhz: TFT 66fps, NO PSRAM: 56fps, PSRAM show: 36fps
        //
        // SSD1331: SWSPI: TFT  9fps, NO PSRAM:  9fps, PSRAM show:  8fps => stable
        Serial.println("^^^^^^^^^^^^^^^^^^^^^^^^^^ Speed ^^^^^^^^^^^^^^^^^^^^^^^^^^");
    #endif // DISABLE_SPEED_TEST
    matrix->fillScreen(0x0000);
    matrix->show();
    #ifdef HAS_TFT
        if (gfx_scale != 1) matrix->show(0, mh);
    #endif
}

void matrix_setup(bool initserial=true, int reservemem = 40000) {
    reservemem = reservemem; // squelch compiler warning if var is unused.

    if (init_done) {
        Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BUG: matrix_setup called twice");
        return;
    }
    init_done = 1;

    // It's bad to call Serial.begin twice, if your calling script runs it first, make sure
    // you request that it isn't called a 2nd time here.
    if (initserial) {
        Serial.begin(115200);
        Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Serial.begin");
    }

    // Teensy takes a while to initialize serial port.
    // Teensy 3.0, 3.1/3.2, 3.5, 3.6, 4.0+4.1
    // https://docs.platformio.org/en/latest/platforms/teensy.html
    #if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__IMXRT1062__)
        delay(3000);
    #endif
    show_free_mem("Memory after setup() starts");

    uint8_t tftidx=0;

    //----------------------------------------------------------------------------
    // ILI9341 

    tftname_[tftidx] = "ILI9341";

    // Older Arduino::GFX had faster SPI and DMA methods that have been removed now.
    // Arduino_ESP32SPI_DMA is faster than Arduino_ESP32SPI, but makes framebuffer::gfx slower at 80Mhz
    // 60fps ILI9341 at 80Mhz
    // 40Mhz 31fps, 15 show, 22 bypass, 14 GFX fps
    //bus_[tftidx] = new Arduino_ESP32SPI_DMA(TFT_DC, TFT_CS2, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);

    // 53fps ILI9341 at 80Mhz
    // 40Mhz 29fps, 16 show, 24 bypass, 15 GFX fps
    //bus_[tftidx] = new Arduino_ESP32SPI(TFT_DC, TFT_CS2, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);

    // 42fps ILI9341 at 80Mhz
    // 40Mhz 25fps, 15 show, 22 bypass, 14 GFX fps
    // new code: 40Mhz 28fps, 15 show, 23 bypass, 15 GFX fps
    bus_[tftidx] = new Arduino_HWSPI(TFT_DC, TFT_CS2);  
    tft_[tftidx] = new Arduino_ILI9341(bus_[tftidx], TFT_RST, 1 /* rotation */);

    mw_[tftidx] = mw1;
    mh_[tftidx] = mh1;
    tftw_[tftidx] = mw1;
    tfth_[tftidx] = mh1;

    matrix_[tftidx] = new FastLED_ArduinoGFX_TFT(matrixleds_[tftidx], mw_[tftidx], mh_[tftidx], tft_[tftidx]);

    // For bigger TFTs, the framebuffer may have to be smaller than the display size
    gfx_scale_[tftidx] = (tftw1*tfth1)/(mw1*mh1);

    tftidx++;
    
    //----------------------------------------------------------------------------
    // SSD1331

    tftname_[tftidx] = "SSD1331";

    bus_[tftidx] = new Arduino_HWSPI(TFT_DC, TFT_CS);
    // do not add 4th IPS argument, even FALSE. On the multi-board, it is sensitive to
    // tft_spi_speed, maybe 80Mhz only (24 seems unstable)
#if SSD1331_ROTATE == 0
        tft_[tftidx] = new Arduino_SSD1331(bus_[tftidx], TFT_RST, 2 /* rotation */);
#else
        tft_[tftidx] = new Arduino_SSD1331(bus_[tftidx], TFT_RST, 1 /* rotation */);
#endif

    mw_[tftidx] = mw2;
    mh_[tftidx] = mh2;
    tftw_[tftidx] = mw2;
    tfth_[tftidx] = mh2;

    // For bigger TFTs, the framebuffer may have to be smaller than the display size
    // Not an issue here.
    gfx_scale_[tftidx] = 1;

    matrix_[tftidx] = new FastLED_ArduinoGFX_TFT(matrixleds_[tftidx], mw_[tftidx], mh_[tftidx], tft_[tftidx]);

    tftidx++;

    //============================================================================
    // End Matrix defines
    //============================================================================

    for (uint8_t tftidx=0; tftidx<TFTCNT; tftidx++) {
        tft_init(tftidx);
    }

    // At least on teensy, due to some framework bug it seems, early
    // serial output gets looped back into serial input
    // Hence, flush input.
    while(Serial.available() > 0) { char t = Serial.read(); t = t; }
    Serial.println("matrix_setup done");
}
#endif // neomatrix_config_h
// vim:sts=4:sw=4:et
