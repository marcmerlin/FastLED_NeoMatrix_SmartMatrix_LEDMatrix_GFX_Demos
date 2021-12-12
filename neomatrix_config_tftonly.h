#ifndef neomatrix_config_h
#define neomatrix_config_h

/*
If neomatrix_config.h looks big and scary, this is the same version with all the
backends, but one, removed.
Obviously the file is shorter and looks simpler, but it is now hardcoded for
a single backend. I don't recommend doing this, but I've checked this file in
so that you can have a look if it's easier to read/comprehend, than the big file
*/

#include <Adafruit_GFX.h>
bool init_done = 0;
uint32_t tft_spi_speed;
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

//----------------------------------------------------------------------------
// ILI0341 
#define HAS_TFT

#include <FastLED_ArduinoGFX_TFT.h>


#ifdef ESP32
    // Arduino_ESP32SPI_DMA is faster than Arduino_ESP32SPI, but makes framebuffer::gfx slower at 80Mhz
    Arduino_DataBus *bus2 = new Arduino_ESP32SPI_DMA(TFT_DC, TFT_CS2, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);//60fps ILI9341 at 80Mhz
    // Arduino_DataBus *bus2 = new Arduino_ESP32SPI(TFT_DC, TFT_CS2, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI); // 53fps ILI9341 at 80Mhz
#else
    Arduino_DataBus *bus2 = new Arduino_HWSPI(TFT_DC, TFT_CS2);  // 42fps ILI9341 at 80Mhz
#endif
Arduino_ILI9341 *tft = new Arduino_ILI9341(bus2, TFT_RST, 1 /* rotation */);
// It would be great if we could do this, but many programs use size related variables to
// define static arrays, which required constants
//uint16_t tftw = tft->width();
//uint16_t tfth = tft->height();
const uint16_t tftw = 320;
const uint16_t tfth = 240;
const uint16_t mw =   tftw;


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
        const uint16_t mh = tfth;
    #else
        #pragma message "Compiling for ILI9341 on ESP32 without PSRAM, framebuffer will only be half height"
        const uint16_t mh = tfth/2;
    #endif
#else
    #pragma message "Compiling for ILI9341. Most chips except teensy 3.6 and better, won't have enough RAM"
    const uint16_t mh = tfth;
#endif

// Used by LEDMatrix
// templates prevents being able to get the screen size at runtime. This is why templates must die
const uint16_t MATRIX_TILE_WIDTH =  mw;
const uint16_t MATRIX_TILE_HEIGHT = mh;
const uint8_t MATRIX_TILE_H     = 1; // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 1; // number of matrices arranged vertically
#ifdef LEDMATRIX
cLEDMatrix<-MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,  MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
#endif

// matrixleds is malloced at runtime as there is more memory available once setup runs
CRGB *matrixleds;
uint8_t matrix_brightness = 255;

FastLED_ArduinoGFX_TFT *matrix = new FastLED_ArduinoGFX_TFT(matrixleds, mw, mh, tft);;


//============================================================================
// End Matrix defines (SMARTMATRIX vs NEOMATRIX and size)
//============================================================================

// Compat for some other demos
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
const uint16_t MATRIX_WIDTH  = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t MATRIX_HEIGHT = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;

// If the actual display is bigger than the framebuffer (this is needed
// for TFTs which require more FB RAM than you can get on chips like ESP32)
#ifdef HAS_TFT
uint8_t gfx_scale = (tftw*tfth)/(mw*mh);
#else
// Used by NeoMatrix
const uint16_t mw = MATRIX_WIDTH;
const uint16_t mh = MATRIX_HEIGHT;
#endif

// Used by some demos
const uint32_t NUMMATRIX = mw*mh;
const uint32_t NUM_LEDS = NUMMATRIX;

// Compat with SmartMatrix code that uses those variables
// (but don't redefine for SmartMatrix backend)
#ifndef SMARTMATRIX
const uint16_t kMatrixWidth = mw;
const uint16_t kMatrixHeight = mh;
#endif
#pragma GCC diagnostic pop

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

// Like XY, but for a mirror image from the top (used by misconfigured code)
int XY2( int x, int y, bool wrap=false) {
    wrap = wrap; // squelch compiler warning
    return matrix->XY(x,MATRIX_HEIGHT-1-y);
}

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
    if (x >= MATRIX_WIDTH) return (MATRIX_WIDTH-1);
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

    // Smartmatrix defines the framebuffers itself. Other methods make their own allocation here
    #if !defined(SMARTMATRIX)
        // ESP32 has more memory available for allocation in setup than in global
        // (if this were a global array), so we use malloc here.
        // https://forum.arduino.cc/index.php?topic=647833
        matrixleds = (CRGB *) mallocordie("matrixleds", sizeof(CRGB) * NUMMATRIX, 1);
        // and then fix the until now NULL pointer in the object.
        matrix->newLedsPtr(matrixleds);
        show_free_mem("After matrixleds malloc");
        #ifdef LEDMATRIX
            Serial.println("ledmatrix.SetLEDArray");
            ledmatrix.SetLEDArray(matrixleds);
        #endif
    #endif


    //============================================================================================
    // ILI9341
    // On my test bench, my ILI9341 doesn't like more than 24Mhz, although when wired properly
    // it should run at 80Mhz
    tft_spi_speed = 40 * 1000 * 1000;
    Serial.println("");
    Serial.println("ILI9341 tft begin");
    // Need to init the underlying TFT SPI engine
    tft->begin(tft_spi_speed);
    #ifdef ADAFRUIT_TFT
        // Seems that filllscreen initializes the tft so that it works (setAddrWindow)
        tft->fillScreen(ILI9341_DARKGREY);
    #endif


    #ifdef HAS_TFT
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
    #endif

    show_free_mem("Before matrix->begin");
    matrix->begin();
    //show_free_mem("After matrix->begin");

    Serial.print("Setting Brightness: ");
    Serial.println(matrix_brightness);
    #if defined(SMARTMATRIX)
        matrixLayer.setBrightness(matrix_brightness);
    #else
        matrix->setBrightness(matrix_brightness);
    #endif
    Serial.print("Gamma Correction: ");
    Serial.println(matrix_gamma);
    // Gamma is used by AnimatedGIFs and others, as such:
    // CRGB color = CRGB(matrix->gamma[red], matrix->gamma[green], matrix->gamma[blue]);
    matrix->precal_gamma(matrix_gamma);

// LEDMatrix alignment is tricky, this test helps make sure things are aligned correctly
    #ifndef DISABLE_MATRIX_TEST
        #ifdef LEDMATRIX
            Serial.println("LEDMatrix Test");
            ledmatrix.DrawLine (0, 0, ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(0, 255, 0));
            ledmatrix.DrawPixel(0, 0, CRGB(255, 0, 0));
            ledmatrix.DrawPixel(ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(0, 0, 255));

            ledmatrix.DrawLine (ledmatrix.Width() - 5, 4, 4, ledmatrix.Height() - 5, CRGB(128, 128, 128));
            ledmatrix.DrawPixel(ledmatrix.Width() - 5, 4,  CRGB(255, 64, 64));
            ledmatrix.DrawPixel(4, ledmatrix.Height() - 5, CRGB(64, 64, 255));
            matrix->show();
            delay(1000);
        #endif
    #endif

    #ifndef DISABLE_SPEED_TEST
        uint32_t before;
        Serial.println("vvvvvvvvvvvvvvvvvvvvvvvvvv Speed vvvvvvvvvvvvvvvvvvvvvvvvvv");
        #ifdef HAS_TFT
            before = millis();
            for (uint8_t i=0; i<5; i++) {
                tft->fillScreen(0);
                tft->fillScreen(0xFFFF);
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

    // At least on teensy, due to some framework bug it seems, early
    // serial output gets looped back into serial input
    // Hence, flush input.
    while(Serial.available() > 0) { char t = Serial.read(); t = t; }
    Serial.println("matrix_setup done");
}
#endif // neomatrix_config_h
// vim:sts=4:sw=4:et
