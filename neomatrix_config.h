#ifndef neomatrix_config_h
#define neomatrix_config_h

/* There are 2 major backends
1) SmartMatrix (via SmartMatrix::GFX)
2) Not SmartMatrix (via FastLED::NeoMatrix or FastLED_SPITFT::GFX)

All backends end up using the same Framebuffer::GFX as the base class
but SmartMatrix is sufficiently different to need its own exceptions and handling
(for one, with SmartMatrix, the buffer is actually handled by SmartMatrix whereas
the other libraries define their own FastLED CRGB buffer (RGB888) ).

Backends you should choose from (define 1):
- SMARTMATRIX
- ILI9341
- ST7735_128b160
- ST7735_128b128
- SSD1331 (96x64 TFT)
- Everything below is NeoMatrix in different patterns:
  M24BY24 M32BY8X3 M16BY16T4 M64BY64 are 4 examples of NEOMATRIX defines
  (3 tiled 32x8, 4 tiled 16x16, and a single zigzag 64x64 array)
- ARDUINOONPC is auto defined by https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix
  - On ARM, we assume rPi and define RPIRGBPANEL
  - Elsewhere, we assume rendering on linux/X11
    - LINUX_RENDERER_X11 is the default with ArduinoOnPc-FastLED-GFX-LEDMatrix
    - LINUX_RENDERER_SDL can be defined in ArduinoOnPc-FastLED-GFX-LEDMatrix's Makefile

LEDMATRIX is a separate define you'd set before including this file and
adds the LEDMatrix API if you need it.
The TL;DR is you shouldn't bother with it if you already have the GFX
and FastLED APIs, unless you can use fancy wavy scrolling colored fonts or the
sprite support in LEDMatrix.

You should need to modify this file at all unless you are adding new matrix
definitions and/or changing pin mappings for TFT screens. To choose which backend
to use, set the define before you include the file.
*/

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// README README README README README README README README README README  README README README README
// If you have never used FastLED::NeoMatrix before, please try these 2 examples first
// https://github.com/marcmerlin/FastLED_NeoMatrix/tree/master/examples/matrixtest
// https://github.com/marcmerlin/FastLED_NeoMatrix/tree/master/examples/MatrixGFXDemo
// Then just uncomment this line below (define M24BY24) and fix the matrix definition
// or use one of the other ones if they are closer ot your setup (M32BY8X3 M16BY16T4 M64BY64)
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//#define M24BY24

#if defined(ARDUINOONPC)
    #if defined(__ARMEL__)
	#pragma message "Detected ARDUINOONPC on ARM (guessing rPi), will use FastLED_RPIRGBPanel_GFX"
	#define RPIRGBPANEL
    #else
	#ifndef LINUX_RENDERER_SDL
	    #pragma message "Detected ARDUINOONPC. Using LINUX_RENDERER_X11 FastLED_TFTWrapper_GFX Rendering"
	    #define LINUX_RENDERER_X11
	#else
	    #pragma message "Detected ARDUINOONPC. Using LINUX_RENDERER_SDL FastLED_NeoMatrix Rendering."
	    #pragma message "Comment out LINUX_RENDERER_SDL for X11 rendering instead of SDL. Use + for brighter."
	#endif
    #endif
#endif

#if !defined(M24BY24) && !defined(M32BY8X3) && !defined(M16BY16T4) && !defined(M64BY64) && !defined(SMARTMATRIX) && !defined(SSD1331) && !defined(ST7735_128b128) && !defined(ST7735_128b160) && !defined(ILI9341)
    /*
    For my own benefit, I use some CPU architectures to default to some backends
    in the defines below, but for your own use, you should just set 
    #define SMARTMATRIX or somesuch just before this code block.
    */
    #ifdef ESP8266
    //#define SSD1331
    //#define SSD1331_ROTATE 1
    // ESP8266 shirt with neopixel strips
    #define M32BY8X3
    //#define M16BY16T4
    #endif

    #ifdef ESP32
    //#define ILI9341
    //#define ST7735_128b160
    //#define ST7735_128b128
    //#define SSD1331
    //#define SSD1331_ROTATE 1
    #define SMARTMATRIX
    //#define M64BY64
    #endif

    // Teensy 3.6
    #ifdef __MK66FX1M0__
    #define ILI9341
    #define ILI_ROTATE 1
    #endif
#endif


#include <Adafruit_GFX.h>
bool init_done = 0;
uint32_t tft_spi_speed;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

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
// Please use https://github.com/marcmerlin/LEDMatrix/ at lesat as recent as
// https://github.com/marcmerlin/LEDMatrix/commit/597ce703e924d45b2e676d6558c4c74a8ebc6991
// or https://github.com/Jorgen-VikingGod/LEDMatrix/commit/a11e74c8cd5b933021b6e15eb067280a52691449
// zero copy/no malloc code to work.
#include <LEDMatrix.h>
#endif


//============================================================================
// Matrix defines (SMARTMATRIX vs NEOMATRIX and size)
// You should #define one and only one of them and if you need to edit it,
// edit both the block below and the 2nd block in setup() at the bottom of this file
//============================================================================
//
#if defined(M24BY24)
    #include <FastLED_NeoMatrix.h>
    #define FASTLED_NEOMATRIX
    
    const uint8_t MATRIXPIN = 13;
    
    uint8_t matrix_brightness = 64;
    // Used by LEDMatrix
    const uint16_t MATRIX_TILE_WIDTH = 24; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 24; // height of each matrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    CRGB *matrixleds;
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    // Unfortunately LEDMatrix has its own matrix definition that isn't as well documented
    // and easy to use. Look for examples if you need to setup a matrix of matrices.
    cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, VERTICAL_ZIGZAG_MATRIX> ledmatrix(false);
    #endif
    
    // MATRIX DECLARATION:
    // Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
    // Parameter 2 = height of each matrix
    // Parameter 3 = number of matrices arranged horizontally
    // Parameter 4 = number of matrices arranged vertically
    // Parameter 5 = pin number (most are valid)
    // Parameter 6 = matrix layout flags, add together as needed:
    //   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
    //     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
    //     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
    //   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
    //     arranged in horizontal rows or in vertical columns, respectively;
    //     pick one or the other.
    //   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
    //     EACH MATRIX proceed in the same order, or alternate lines reverse
    //     direction; pick one.
    //   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
    //     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
    //     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
    //   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
    //     are arranged in horizontal rows or in vertical columns, respectively;
    //     pick one or the other.
    //   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
    //     (tiles) in the OVERALL DISPLAY proceed in the same order for every
    //     line, or alternate lines reverse direction; pick one.  When using
    //     zig-zag order, the orientation of the matrices in alternate rows
    //     will be rotated 180 degrees (this is normal -- simplifies wiring).
    //   See example below for these values in action.
    FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT,
        NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG );
    
//----------------------------------------------------------------------------
#elif defined(M32BY8X3)
    #include <FastLED_NeoMatrix.h>
    #define FASTLED_NEOMATRIX
    
    uint8_t matrix_brightness = 64;
    // Used by LEDMatrix
    const uint16_t MATRIX_TILE_WIDTH = 8; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 32; // height of each matrix
    const uint8_t MATRIX_TILE_H     = 3;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<-MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_ZIGZAG_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    // MATRIX DECLARATION:
    // Parameter 1 = width of EACH NEOPIXEL MATRIX (not total display)
    // Parameter 2 = height of each matrix
    // Parameter 3 = number of matrices arranged horizontally
    // Parameter 4 = number of matrices arranged vertically
    // Parameter 5 = pin number (most are valid)
    // Parameter 6 = matrix layout flags, add together as needed:
    //   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
    //     Position of the FIRST LED in the FIRST MATRIX; pick two, e.g.
    //     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
    //   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs WITHIN EACH MATRIX are
    //     arranged in horizontal rows or in vertical columns, respectively;
    //     pick one or the other.
    //   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns WITHIN
    //     EACH MATRIX proceed in the same order, or alternate lines reverse
    //     direction; pick one.
    //   NEO_TILE_TOP, NEO_TILE_BOTTOM, NEO_TILE_LEFT, NEO_TILE_RIGHT:
    //     Position of the FIRST MATRIX (tile) in the OVERALL DISPLAY; pick
    //     two, e.g. NEO_TILE_TOP + NEO_TILE_LEFT for the top-left corner.
    //   NEO_TILE_ROWS, NEO_TILE_COLUMNS: the matrices in the OVERALL DISPLAY
    //     are arranged in horizontal rows or in vertical columns, respectively;
    //     pick one or the other.
    //   NEO_TILE_PROGRESSIVE, NEO_TILE_ZIGZAG: the ROWS/COLUMS OF MATRICES
    //     (tiles) in the OVERALL DISPLAY proceed in the same order for every
    //     line, or alternate lines reverse direction; pick one.  When using
    //     zig-zag order, the orientation of the matrices in alternate rows
    //     will be rotated 180 degrees (this is normal -- simplifies wiring).
    //   See example below for these values in action.
    FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TILE_H, MATRIX_TILE_V,
      NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
        NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG +
        NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE);
    
//----------------------------------------------------------------------------
#elif defined(M16BY16T4)
    #include <FastLED_NeoMatrix.h>
    #define FASTLED_NEOMATRIX
    
    uint8_t matrix_brightness = 64;
    
    const uint16_t MATRIX_TILE_WIDTH = 16; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 16; // height of each matrix
    const uint8_t MATRIX_TILE_H     = 2; // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 2; // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<-MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_ZIGZAG_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, VERTICAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TILE_H, MATRIX_TILE_V,
      NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG +
        NEO_TILE_TOP + NEO_TILE_RIGHT +  NEO_TILE_PROGRESSIVE);
    
    const uint8_t MATRIXPIN = 13;
    
//----------------------------------------------------------------------------
#elif defined(M64BY64) // 64x64 straight connection (no matrices)
    #include <FastLED_NeoMatrix.h>
    #define FASTLED_NEOMATRIX
    
    // http://marc.merlins.org/perso/arduino/post_2018-07-30_Building-a-64x64-Neopixel-Neomatrix-_4096-pixels_-running-NeoMatrix-FastLED-IR.html
    uint8_t matrix_brightness = 128;
    //
    // Used by LEDMatrix
    const uint16_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 64; // height of each matrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    #define NUM_STRIPS 16
    #define NUM_LEDS_PER_STRIP 256
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    CRGB *matrixleds;
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, VERTICAL_ZIGZAG_MATRIX> ledmatrix(false);
    #endif
    FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT,
        NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
        NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG );
    
//----------------------------------------------------------------------------
#elif defined(SMARTMATRIX)
    // CHANGEME, see MatrixHardware_ESP32_V0.h in SmartMatrix/src
    #define GPIOPINOUT 3 // if on ESP32, this selects which wiring is used. Teensy uses the define below
    #include <SmartLEDShieldV4.h>  // if you're using SmartLED Shield V4 hardware on teensy
    #include <SmartMatrix3.h>
    #include <SmartMatrix_GFX.h>
    uint8_t matrix_brightness = 255;
    
    #ifdef ESP32
    #pragma message "SmartMatrix for ESP32 with 64x32 16 scan panel and 64x96 resolution"
    const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
    const uint16_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 96; // height of each matrix
    #elif defined(__MK66FX1M0__) // my teensy 3.6 is connected to a 64x64 panel
    #pragma message "SmartMatrix for Teensy with 64x64 32 scan panel"
    //const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
    const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
    const uint16_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
    const uint16_t MATRIX_TILE_HEIGHT= 64; // height of each matrix
    #else
    #error Unknown architecture (not ESP32 or teensy 3.5/6)
    #endif
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    /// SmartMatrix Defines
    #define COLOR_DEPTH 24         // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
    const uint8_t kMatrixWidth = mw;
    const uint8_t kMatrixHeight = mh;
    const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
    const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
    const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
    const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
    
    SMARTMATRIX_ALLOCATE_BUFFERS(matrixLayer, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
    SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    void show_callback();
    SmartMatrix_GFX *matrix = new SmartMatrix_GFX(matrixleds, mw, mh, show_callback);
    
    // Sadly this callback function must be copied around with this init code
    void show_callback() {
    //    memcpy(backgroundLayer.backBuffer(), matrixleds, kMatrixHeight*kMatrixWidth*3);
    //    backgroundLayer.swapBuffers(false);
        backgroundLayer.swapBuffers(true);
        //matrixleds = (CRGB *)backgroundLayer.getRealBackBuffer());
        matrixleds = (CRGB *)backgroundLayer.backBuffer();
        matrix->newLedsPtr(matrixleds);
    #ifdef LEDMATRIX
        ledmatrix.SetLEDArray(matrixleds);
    #endif
        matrix->showfps();
    }
    
//----------------------------------------------------------------------------
#elif defined(M5STACK)
    #define HASTFT
    
    #include <M5Stack.h>
    #include <FastLED_SPITFT_GFX.h>
    
    uint8_t matrix_brightness = 255;
    const uint16_t MATRIX_TILE_WIDTH = 320;
    const uint16_t MATRIX_TILE_HEIGHT= 240;
    //
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    // M5 gets defined in M5Stack
    FastLED_SPITFT_GFX *matrix = new FastLED_SPITFT_GFX(matrixleds, mw, mh, mw, mh, &M5.lcd, 100);
    
//----------------------------------------------------------------------------
#elif defined(ILI9341)
    #define HASTFT
    
    #include "Adafruit_ILI9341.h"
    #include <FastLED_SPITFT_GFX.h>
    
    uint8_t matrix_brightness = 255;
    #if ILI_ROTATE == 0
    const uint16_t MATRIX_TILE_WIDTH = 320;
    const uint16_t MATRIX_TILE_HEIGHT= 240;
    #else
    const uint16_t MATRIX_TILE_WIDTH = 240;
    const uint16_t MATRIX_TILE_HEIGHT= 320;
    #endif
    //
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    #if defined(__MK66FX1M0__)
    #define TFT_MISO 12
    #define TFT_CLK 13
    #define TFT_MOSI 11
    #define TFT_DC 10
    #define TFT_RST 23
    #define TFT_CS 22
    
    #else
    // HWSPI default    // sparkfun 18 green 23 blue 19 yellow
    #define TFT_MISO 19  // yellow
    #define TFT_MOSI 23  // blue
    #define TFT_CLK 18   // green
    #define TFT_DC 27
    // this is the TFT reset pin. It seems required on my board
    #define TFT_RST 26
    #define TFT_CS 25
    
    #endif
    
    //Adafruit_ILI9341 *tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
    Adafruit_ILI9341 *tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
    
    FastLED_SPITFT_GFX *matrix = new FastLED_SPITFT_GFX(matrixleds, mw, mh, mw, mh, tft, 0);
    
//----------------------------------------------------------------------------
#elif defined(ST7735_128b128) || defined(ST7735_128b160) 
    #define HASTFT
    
    #include <Adafruit_ST7735.h>
    #include <FastLED_SPITFT_GFX.h>
    
    uint8_t matrix_brightness = 255;
    const uint16_t MATRIX_TILE_WIDTH = 128;
    #ifdef ST7735_128b128
    const uint16_t MATRIX_TILE_HEIGHT= 128;
    #else
    const uint16_t MATRIX_TILE_HEIGHT= 160;
    #endif
    
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    /*
    			Arduino	ESP8266		ESP32	ESP32	rPi     rPi
    						VSPI    HSPI	SPI0    SPI1
      VCC
      SCL/SCK/CLK/D0	13	GPIO14/D5	18	14	BC11/22	BC21/40
      SDA/SDI/MOSI/D1	11	GPIO13/D7	23	13	BC10/19	BC20/38
      RES/RST		9	GPIO15/D8	26	26	BC24				
      DC/A0/RS (data)	8	GPIO05/D1	27	27	BC23				
      CS			10	GPIO04/D2	25	25	BC08			
    
      MISO			12	GPIO12/D6	19	12	BM11/23	BC19/35	
    */
    
    #ifdef ESP32
    #define TFT_CS        25
    #define TFT_RST       26
    #define TFT_DC        27
    #elif defined(ESP8266)
    #define TFT_CS         4
    #define TFT_RST       15
    #define TFT_DC         5
    #else
    #define TFT_CS        10
    #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
    #define TFT_DC         8
    #endif
    Adafruit_ST7735 *tft = new Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
    
    FastLED_SPITFT_GFX *matrix = new FastLED_SPITFT_GFX(matrixleds, mw, mh, mw, mh, tft, 0);
    
//----------------------------------------------------------------------------
#elif defined(SSD1331)
    #define HASTFT
    
    #include <Adafruit_SSD1331.h>
    #include <FastLED_SPITFT_GFX.h>
    
    uint8_t matrix_brightness = 255;
    #if SSD1331_ROTATE == 0
    const uint16_t MATRIX_TILE_WIDTH = 96;
    const uint16_t MATRIX_TILE_HEIGHT= 64;
    #else
    const uint16_t MATRIX_TILE_WIDTH = 64;
    const uint16_t MATRIX_TILE_HEIGHT= 96;
    #endif
    //
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    /*  https://pinout.xyz/pinout/spi
    SD1331 Pin	    Arduino	ESP8266		ESP32	ESP32	rPi     rPi
    1 GND                                           VSPI    HSPI	SPI0    SPI1
    2 VCC
    3 SCL/SCK/CLK/D0	13	GPIO14/D5	18	14	BC11/22	BC21/40
    4 SDA/SDI/MOSI/D1	11	GPIO13/D7	23	13	BC10/19	BC20/38
    5 RES/RST		9	GPIO15/D8	26	26	BC24				
    6 DC/A0/RS (data)	8	GPIO05/D1	27	27	BC23				
    7 CS			10	GPIO04/D2	25	25	BC08			
    
      MISO			12	GPIO12/D6	19	12	BM11/23	BC19/35	
    */
    
    #ifdef ESP32
    #define sclk 18
    #define mosi 23
    #define rst  26
    #define dc   27
    #define cs   25
    // Option 1: use any pins but a little slower
    //#pragma message "Using SWSPI"
    Adafruit_SSD1331 *tft  = new Adafruit_SSD1331(cs, dc, mosi, sclk, rst);
    // This hangs the moment it is run
    // https://github.com/adafruit/Adafruit-SSD1331-OLED-Driver-Library-for-Arduino/issues/27
    //Adafruit_SSD1331 *tft  = new Adafruit_SSD1331(cs, dc, rst);
    #else
    // You can use any (4 or) 5 pins
    // hwspi hardcodes those pins, no need to redefine them
    #define sclk 14
    #define mosi 13
    #define rst  15
    #define cs   4
    #define dc   5
    // Option 2: must use the hardware SPI pins
    // (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
    // an output. This is much faster - also required if you want
    // to use the microSD card (see the image drawing example)
    #pragma message "Using HWSPI"
    Adafruit_SSD1331 *tft = new Adafruit_SSD1331(&SPI, cs, dc, rst);
    #endif
    
    #if SSD1331_ROTATE == 0
    FastLED_SPITFT_GFX *matrix = new FastLED_SPITFT_GFX(matrixleds, mw, mh, 96, 64, tft, 0);
    #else
    FastLED_SPITFT_GFX *matrix = new FastLED_SPITFT_GFX(matrixleds, mw, mh, 96, 64, tft, 1);
    #endif
    
//----------------------------------------------------------------------------
#elif defined(LINUX_RENDERER_X11)
    
    #include "TFT_LinuxWrapper.h"
    #include <FastLED_TFTWrapper_GFX.h>
    
    uint8_t matrix_brightness = 255;
    const uint16_t MATRIX_TILE_WIDTH = 64;
    const uint16_t MATRIX_TILE_HEIGHT= 96;
    //
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    TFT_LinuxWrapper *tft = new TFT_LinuxWrapper(MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT);
    FastLED_TFTWrapper_GFX *matrix = new FastLED_TFTWrapper_GFX(matrixleds, mw, mh, tft);

//----------------------------------------------------------------------------
#elif defined(LINUX_RENDERER_SDL)
    #include <FastLED_NeoMatrix.h>
    
    uint8_t matrix_brightness = 128;
    //
    // Used by LEDMatrix
    // All running 1D neopixel code
    #ifdef NEOPIXEL_STRIP
	#pragma message "Neopixel 1D code"
	const uint16_t MATRIX_TILE_WIDTH =  64; // width of EACH NEOPIXEL MATRIX (not total display)
	const uint16_t MATRIX_TILE_HEIGHT=   1; // height of each matrix
    #else
	const uint16_t MATRIX_TILE_WIDTH = 384; // width of EACH NEOPIXEL MATRIX (not total display)
	const uint16_t MATRIX_TILE_HEIGHT= 192; // height of each matrix
    #endif
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    CRGB *matrixleds;
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT,
        NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS );
    
//----------------------------------------------------------------------------
#elif defined(RPIRGBPANEL)
    
    #include <FastLED_RPIRGBPanel_GFX.h>
    // https://github.com/hzeller/rpi-rgb-led-matrix
    // Arduino min/max conflict with g++ math min/max
    #undef min
    #undef max
    #define min(a,b) ((a<b)?(a):(b))
    #define max(a,b) ((a>b)?(a):(b))
    #include <led-matrix.h>
    
    uint8_t matrix_brightness = 255;
    const uint16_t MATRIX_TILE_WIDTH = 384;
    const uint16_t MATRIX_TILE_HEIGHT= 192;
    
    // Used by LEDMatrix
    const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
    const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
    
    // Used by NeoMatrix
    const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
    const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
    
    #ifdef LEDMATRIX
    // cLEDMatrix defines
    cLEDMatrix<MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
        MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix(false);
    #endif
    CRGB *matrixleds;
    
    FastLED_RPIRGBPanel_GFX *matrix = new FastLED_RPIRGBPanel_GFX(matrixleds, mw, mh);
    
    
//============================================================================
#else
    #error "Please write a matrix config or choose one of the definitions above. If you have a FastLED matrix, define M24BY24 at the top of this file"
#endif

//============================================================================
// End Matrix defines (SMARTMATRIX vs NEOMATRIX and size)
//============================================================================

// Compat for some other demos
const uint32_t NUMMATRIX = mw*mh;
const uint32_t NUM_LEDS = NUMMATRIX;
const uint16_t MATRIX_HEIGHT = mh;
const uint16_t MATRIX_WIDTH = mw;

// Compat with SmartMatrix code that uses those variables
// (but don't redefine for SmartMatrix backend)
#ifndef SMARTMATRIX
const uint16_t kMatrixWidth = mw;
const uint16_t kMatrixHeight = mh;
#endif

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

uint16_t XY( uint8_t x, uint8_t y) {
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
    while(1) delay(1); // while 1 loop only triggers watchdog on ESP chips
}

void *mallocordie(const char *varname, uint32_t req, bool psram=true) {
#ifndef BOARD_HAS_PSRAM
    psram = false;
#endif
    if (psram) Serial.print("PS");
    Serial.print("Malloc ");
    Serial.print(varname);
    Serial.print(" . Requested bytes: ");
    Serial.println(req);
    void *mem;
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
	Serial.print("FATAL: ");
	if (psram) Serial.print("ps_");
	Serial.print("malloc failed for ");
	Serial.println(varname);
	show_free_mem();
	while (1); // delay(1);  Adding this seems to cause an ESP32 bug
    }
    return NULL;
}

void matrix_setup(int reservemem = 40000) {
    reservemem = reservemem; // squelch compiler warning if var is unused.
    if (init_done) {
	Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BUG: matrix_setup called twice");
	return;
    }
    init_done = 1;
    // Teensy takes a while to initialize serial port.
// Teensy 3.0, 3.1/3.2, 3.5, 3.6
    #if defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__)
        delay(3000);
    #endif
    Serial.begin(115200);
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Serial.begin");
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
            ledmatrix.SetLEDArray(matrixleds);
        #endif
    #endif
   

    //============================================================================================
    // Matrix Init Start
    //============================================================================================
    #if defined(M24BY24)
        FastLED.addLeds<NEOPIXEL,MATRIXPIN>(matrixleds, NUMMATRIX).setCorrection(TypicalLEDStrip);
        Serial.print("Neomatrix total LEDs: ");
        Serial.print(NUMMATRIX);
        Serial.print(" running on pin: ");
        Serial.println(MATRIXPIN);
    
    //============================================================================================
    // Example of parallel output
    #elif defined(M32BY8X3)
        // Init Matrix
        // Serialized, 768 pixels takes 26 seconds for 1000 updates or 26ms per refresh
        // FastLED.addLeds<NEOPIXEL,MATRIXPIN>(matrixleds, NUMMATRIX).setCorrection(TypicalLEDStrip);
        // https://github.com/FastLED/FastLED/wiki/Parallel-Output
        // WS2811_PORTA - pins 12, 13, 14 and 15 or pins 6,7,5 and 8 on the NodeMCU
        // This is much faster 1000 updates in 10sec
        // See  https://github.com/FastLED/FastLED/wiki/Parallel-Output for pin definitions
        #ifdef ESP8266
        FastLED.addLeds<WS2811_PORTA,3>(matrixleds, NUMMATRIX/MATRIX_TILE_H).setCorrection(TypicalLEDStrip);
        #else
        FastLED.addLeds<WS2811_PORTD,3>(matrixleds, NUMMATRIX/MATRIX_TILE_H).setCorrection(TypicalLEDStrip);
        #endif
        Serial.print("Neomatrix parallel output, total LEDs: ");
        Serial.println(NUMMATRIX);
    
    //============================================================================================
    // Serialized (slow-ish) output
    #elif defined(M16BY16T4)
        FastLED.addLeds<NEOPIXEL,MATRIXPIN>(matrixleds, NUMMATRIX).setCorrection(TypicalLEDStrip);
        Serial.print("Neomatrix total LEDs: ");
        Serial.print(NUMMATRIX);
        Serial.print(" running on pin: ");
        Serial.println(MATRIXPIN);
    
    //============================================================================================
    #elif defined(M64BY64) // 64x64 straight connection (no matrices)
        // https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
        FastLED.addLeds<WS2812B,23, GRB>(matrixleds, 0*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
        #ifdef ESP32
	    FastLED.addLeds<WS2812B,22, GRB>(matrixleds, 1*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,27, GRB>(matrixleds, 2*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);   // was 3
	    FastLED.addLeds<WS2812B,21, GRB>(matrixleds, 3*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
	    FastLED.addLeds<WS2812B,19, GRB>(matrixleds, 4*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
	    FastLED.addLeds<WS2812B,18, GRB>(matrixleds, 5*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B, 5, GRB>(matrixleds, 6*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B, 4, GRB>(matrixleds, 7*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 

	    FastLED.addLeds<WS2812B, 0, GRB>(matrixleds, 8*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B, 2, GRB>(matrixleds, 9*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,15, GRB>(matrixleds,10*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,25, GRB>(matrixleds,11*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,26, GRB>(matrixleds,12*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,14, GRB>(matrixleds,13*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,12, GRB>(matrixleds,14*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
	    FastLED.addLeds<WS2812B,13, GRB>(matrixleds,15*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

	    Serial.print("Neomatrix 16 pin via RMT/I2S 16 way parallel output, total LEDs: ");
	    Serial.println(NUMMATRIX);
        #endif // ESP32
        matrix_gamma = 2.4; // higher number is darker, needed for Neomatrix more than SmartMatrix
    
    //============================================================================================
    #elif defined(SMARTMATRIX)
        matrix_gamma = 1; // SmartMatrix should be good by default.
        matrixLayer.addLayer(&backgroundLayer);
        // SmartMatrix takes all the RAM it can get its hands on. Get it to leave some
        // free RAM so that other libraries can work too.
        #ifdef ESP32
            if (reservemem) matrixLayer.begin(reservemem); else matrixLayer.begin();
        #else
            matrixLayer.begin();
        #endif
        // This sets the neomatrix and LEDMatrix pointers
        show_callback();
        matrixLayer.setRefreshRate(240);
        backgroundLayer.enableColorCorrection(true);
        Serial.print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix GFX output, total LEDs: ");
        Serial.println(NUMMATRIX);
        // Quick hello world test
        #ifndef DISABLE_MATRIX_TEST
            Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix Grey Demo");
            backgroundLayer.fillScreen( {0x80, 0x80, 0x80} );
            // backgroundLayer.swapBuffers();
            show_callback();
            delay(1000);
        #endif
        Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix Init Done");
    
    //============================================================================================
    #elif defined(LINUX_RENDERER_X11)
        // Need to init the underlying TFT SPI engine
        Serial.println("ARDUINOONPC LINUX_RENDERER_X11 tft begin");
        tft->begin();
        matrix->fillScreen(LTDC_BLACK);
    
    //============================================================================================
    #elif defined(LINUX_RENDERER_SDL)
        FastLED.addLeds<SDL, mw, mh>(matrixleds, NUMMATRIX);
        Serial.print("Neomatrix on top of SDL. Please use '+' on numeric keypad for brighter, total LEDs: ");
        Serial.println(NUMMATRIX);
    
    //============================================================================================
    #elif defined(RPIRGBPANEL)
        Serial.println("Using rpi-rgb-led-matrix");
    
        rgb_matrix::RGBMatrix::Options defaults;
        defaults.hardware_mapping = "regular"; // or e.g. "adafruit-hat"
        defaults.rows = 64;
        defaults.cols = 128;
        defaults.chain_length = 3;
        defaults.parallel = 3;
        defaults.pwm_lsb_nanoseconds = 50;
        defaults.pwm_bits = 7;
        defaults.led_rgb_sequence = "RBG";
        defaults.panel_type = "FM6126A";
        
        rgb_matrix::RuntimeOptions ropt;
	ropt.gpio_slowdown = 1;

        rgb_matrix::Canvas *canvas = rgb_matrix::CreateMatrixFromOptions(defaults, ropt);
        while (canvas == NULL) Serial.println("Canvas did not initialize");
        matrix->setCanvas(canvas);
        Serial.println("RGBPanel Canvas initialized");
    
    //============================================================================================
    #elif defined(M5STACK)
        // Need to init the underlying TFT SPI engine
        Serial.println("M5STACK begin");
        M5.begin();
        M5.Power.begin();
        M5.Lcd.fillScreen(BLUE);
    
    //============================================================================================
    #elif defined(ILI9341)
        // Adafruit ILI9341 1.5.4 or better is actually quite fast at 80Mhz: 40fps full frame refresh
        // however it is not stable for the display to work every time. Anything over 24Mhz is not very 
        // stable, so I'm accepting the slower resulting fps (unfortunately 14fps at 24Mhz).
        // See 'ESP32 speed tests' lower down in the file for performance details.
        tft_spi_speed = 24 * 1000 * 1000;
        Serial.println("");
        Serial.println("ILI9341 tft begin");
        Serial.println(">>> If you get no display, try resetting, and removing cross talk between wires or decreasing SPI speed <<<<");
        Serial.println("");
        // Need to init the underlying TFT SPI engine
        tft->begin(tft_spi_speed);
        #if ILI_ROTATE == 0
            tft->setRotation(1);
            // This is very important, or FastLED_SPITFT_GFX::show will not work.
            // Size is hardcoded by TFT size.
            // Doesn't seem to work, but fillscreen below takes care of it
            //tft->setAddrWindow(0, 0, 320, 240);
        #else
            tft->setRotation(0);
            //tft->setAddrWindow(0, 0, 240, 320);
        #endif
        // Seems that filllscreen further initializes the tft so that it works
        tft->fillScreen(ILI9341_DARKGREY);
    
    //============================================================================================
    #elif defined(ST7735_128b160)
        tft_spi_speed = 60 * 1000 * 1000;
        Serial.println("");
        Serial.println("ST7735_128b160 tft begin");
        Serial.println(">>> If you get no display, try resetting, and removing cross talk between wires or decreasing SPI speed <<<<");
        Serial.println("");
        // initR calls begin for us but does not allow setting SPI speed (hardcoded in the file)
        tft->initR(INITR_BLACKTAB);
        tft->setSPISpeed(tft_spi_speed);
        // fillScreen below does the job
        //tft->setAddrWindow(0, 0, 128, 160);
        // This is required for the screen to work
        tft->fillScreen(ST77XX_GREEN);
    
    //============================================================================================
    #elif defined(ST7735_128b128)
        tft_spi_speed = 32 * 1000 * 1000;
        Serial.println("");
        Serial.println("ST7735_128b128 tft begin");
        Serial.println(">>> If you get no display, try resetting, and removing cross talk between wires or decreasing SPI speed <<<<");
        Serial.println("");
        // initR calls begin for us but does not allow setting SPI speed (hardcoded in the file)
        tft->initR(INITR_144GREENTAB);
        tft->setSPISpeed(tft_spi_speed);
        // This is required for the screen to work
        tft->fillScreen(ST77XX_GREEN);
    
    //============================================================================================
    #elif defined(SSD1331)
        // Need to init the underlying TFT SPI engine
        tft_spi_speed = 40 * 1000 * 1000;
        Serial.println("");
        Serial.println("SSD1331 tft begin (HWSPI broken on ESP32)");
        Serial.println(">>> If you get no display, try resetting, and removing cross talk between wires or decreasing SPI speed <<<<");
        Serial.println("");
        tft->begin(tft_spi_speed);
        tft->setSPISpeed(tft_spi_speed);
        // This is very important, or FastLED_SPITFT_GFX::show will not work.
        // Size is hardcoded by TFT size.
        tft->setAddrWindow(0, 0, 96, 64);
    
    //============================================================================================
    #else
        #error "Undefined Matrix"
    #endif
    //============================================================================================
    // Matrix Init End
    //============================================================================================

    show_free_mem("Before matrix->begin");
    matrix->begin();
    //show_free_mem("After matrix->begin");

    Serial.print("Setting Brightness: ");
    Serial.println(matrix_brightness);
    #if defined(SMARTMATRIX)
        matrixLayer.setBrightness(matrix_brightness);
    #else
        FastLED.setBrightness(matrix_brightness);
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

    Serial.println("matrix_setup done");

    // ESP32 speed tests
    // - Adafruit::ILI9341 speed at 80Mhz is 
    // - WROVER at 24Mhz is 25fps, doesn't seem to work any faster
    // - https://github.com/loboris/ESP32_TFT_lib (DMA) at 24Mhz is only 7fps?
    //
    // ILI9314: 80Mhz: TFT 40fps, NO PSRAM: 32fps, PSRAM show: 12ps  => unstable, no display
    // ILI9314: 40Mhz: TFT 25fps, NO PSRAM: 21fps, PSRAM show: 10fps => unstable, no display
    // ILI9314: 39Mhz: TFT 18fps, NO PSRAM: 16fps, PSRAM show:  9fps => unstable, garbled
    // ILI9314: 30Mhz: TFT 18fps, NO PSRAM: 16fps, PSRAM show:  9fps => still a bit unstabled, garbled
    // ILI9314: 24Mhz: TFT 14fps, NO PSRAM: 12fps, PSRAM show:  8fps => stable
    // ILI9314: 20Mhz: TFT 14fps, NO PSRAM: 12fps, PSRAM show:  8fps
    //
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
    uint32_t before;
    #ifdef HASTFT
        before = millis();
        for (uint8_t i=0; i<3; i++) {
    	tft->fillScreen(0);
    	tft->fillScreen(0xFFFF);
        }
        Serial.print("TFT SPI Speed: ");
        Serial.print(tft_spi_speed/1000000);
        Serial.print("Mhz. Resulting fps: ");
        Serial.println((6* 1000/(millis() - before)));
    #endif
    #if defined(BOARD_HAS_PSRAM) && defined(HASTFT)
        before = millis();
        for (uint8_t i=0; i<5; i++) {
          matrix->show(1);
        }
        Serial.print("Matrix->show() PSRAM BYPASS Speed Test fps: ");
        Serial.println((5* 1000/(millis() - before)));
    #endif
    before = millis();
    for (uint8_t i=0; i<5; i++) {
    #if defined(BOARD_HAS_PSRAM) && defined(HASTFT)
          matrix->show(0);
    #else
          matrix->show();
    #endif
    }
    Serial.print("Matrix->show() Speed Test fps: ");
    Serial.println((5* 1000/(millis() - before)));

    // At least on teensy, due to some framework bug it seems, early
    // serial output gets looped back into serial input
    // Hence, flush input.
    while(Serial.available() > 0) { char t = Serial.read(); t = t; }
}
#endif // neomatrix_config_h
//vim:sts=4:sw=4
