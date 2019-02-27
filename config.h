#ifndef neomatrix_config_h
#define neomatrix_config_h

#define M16BY16T4
//#define NEOPIXEL_MATRIX
#ifndef NEOPIXEL_MATRIX
#define SMARTMATRIX
#endif

#include <Adafruit_GFX.h>

//============================================================================ 
// Matrix defines (SMARTMATRIX vs NEOMATRIX and size)
//============================================================================ 

// The ESP32 FastLED defines below must be defined before FastLED.h is loaded
#ifndef SMARTMATRIX
    #ifdef ESP32
        #ifdef ESP32_16PINS
            // This uses https://github.com/hpwit/fastled-esp32-16PINS.git
            // instead of https://github.com/samguyer/FastLED.git
            #define FASTLED_ALLOW_INTERRUPTS 0
            #define FASTLED_SHOW_CORE 0
        #else
            // Allow infrared
            #define FASTLED_ALLOW_INTERRUPTS 1
            #pragma message "Please use https://github.com/samguyer/FastLED.git if stock FastLED is unstable with ESP32"
        #endif // ESP32_16PINS
    #endif

    #if !defined(M16BY16T4)
        #ifdef ESP32
            // 64x64 matrix with optional 16 pin parallel driver
            #define M64BY64
            // 55fps without 16PINS, 110fps with 16PINS
            //#define ESP32_16PINS
        #elif ESP8266
            // ESP8266 shirt with neopixel strips
            #define M32B8X3
        #endif
    #endif
    
    #include <FastLED_NeoMatrix.h>
#else
    #include <SmartLEDShieldV4.h>  // if you're using SmartLED Shield V4 hardware
    #include <SmartMatrix3.h>
    #include <SmartMatrix_GFX.h>
#endif // SMARTMATRIX

#include <FastLED.h>

#ifdef LEDMATRIX
#include <LEDMatrix.h>
#endif

#if defined(SMARTMATRIX)
const uint8_t matrix_brightness = 255;

#ifdef ESP32
#pragma message "Compiling for ESP32 with 64x32 16 scan panel"
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t MATRIX_TILE_HEIGHT= 96; // height of each matrix
#elif defined(__MK66FX1M0__) // my teensy 3.6 is connected to a 64x64 panel
#pragma message "Compiling for Teensy with 64x64 32 scan panel"
const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
const uint8_t MATRIX_TILE_HEIGHT= 64; // height of each matrix
#else
#error Unknown architecture (not ESP32 or teensy 3.5/6)
#endif
// Used by LEDMatrix
const uint8_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically

// Used by NeoMatrix
const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
const uint16_t NUMMATRIX = mw*mh;

// Compat for some other demos
const uint16_t NUM_LEDS = NUMMATRIX; 
const uint8_t MATRIX_HEIGHT = mh;
const uint8_t MATRIX_WIDTH = mw;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

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
    MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix;

// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
CRGB *matrixleds = ledmatrix[0];
#else
CRGB matrixleds[NUMMATRIX];
#endif

// Sadly this callback function must be copied around with this init code
void show_callback() {
    memcpy(backgroundLayer.backBuffer(), matrixleds, kMatrixHeight*kMatrixWidth*3);
    backgroundLayer.swapBuffers(false);
}

SmartMatrix_GFX *matrix = new SmartMatrix_GFX(matrixleds, mw, mh, show_callback);

//---------------------------------------------------------------------------- 
#elif defined(M32B8X3)
const uint8_t matrix_brightness = 64;
// Used by LEDMatrix
const uint8_t MATRIX_TILE_WIDTH = 8; // width of EACH NEOPIXEL MATRIX (not total display)
const uint8_t MATRIX_TILE_HEIGHT= 32; // height of each matrix
const uint8_t MATRIX_TILE_H     = 3;  // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically

// Used by NeoMatrix
const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
const uint16_t NUMMATRIX = mw*mh;

// Compat for some other demos
const uint16_t NUM_LEDS = NUMMATRIX; 
const uint8_t MATRIX_HEIGHT = mh;
const uint8_t MATRIX_WIDTH = mw;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#ifdef LEDMATRIX
// cLEDMatrix defines 
cLEDMatrix<-MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_ZIGZAG_MATRIX,
    MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS> ledmatrix;

// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
CRGB *matrixleds = ledmatrix[0];
#else
CRGB matrixleds[NUMMATRIX];
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
FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TILE_H, MATRIX_TILE_V, 
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG + 
    NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE);

//---------------------------------------------------------------------------- 
#elif defined(M16BY16T4)
const uint8_t matrix_brightness = 64;

const uint8_t MATRIX_TILE_WIDTH = 16; // width of EACH NEOPIXEL MATRIX (not total display)
const uint8_t MATRIX_TILE_HEIGHT= 16; // height of each matrix
const uint8_t MATRIX_TILE_H     = 2; // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 2; // number of matrices arranged vertically

// Used by NeoMatrix
const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
const uint16_t NUMMATRIX = mw*mh;

// Compat for some other demos
const uint16_t NUM_LEDS = NUMMATRIX; 
const uint8_t MATRIX_HEIGHT = mh;
const uint8_t MATRIX_WIDTH = mw;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#ifdef LEDMATRIX
// cLEDMatrix defines 
cLEDMatrix<-MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_ZIGZAG_MATRIX,
    MATRIX_TILE_H, MATRIX_TILE_V, VERTICAL_BLOCKS> ledmatrix;

// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
CRGB *matrixleds = ledmatrix[0];
#else
CRGB matrixleds[NUMMATRIX];
#endif

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TILE_H, MATRIX_TILE_V, 
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG + 
    NEO_TILE_TOP + NEO_TILE_RIGHT +  NEO_TILE_PROGRESSIVE);

#ifdef ESP8266
const uint8_t MATRIXPIN = 5;
#else
const uint8_t MATRIXPIN = 13;
#endif


//---------------------------------------------------------------------------- 
#elif defined(M64BY64) // 64x64 straight connection (no matrices)
// http://marc.merlins.org/perso/arduino/post_2018-07-30_Building-a-64x64-Neopixel-Neomatrix-_4096-pixels_-running-NeoMatrix-FastLED-IR.html
const uint8_t matrix_brightness = 32;
//
// Used by LEDMatrix
const uint8_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
const uint8_t MATRIX_TILE_HEIGHT= 64; // height of each matrix
const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 1;  // number of matrices arranged vertically
#define NUM_STRIPS 16
#define NUM_LEDS_PER_STRIP 256

// Used by NeoMatrix
const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
const uint16_t NUMMATRIX = mw*mh;

// Compat for some other demos
const uint16_t NUM_LEDS = NUMMATRIX; 
const uint8_t MATRIX_HEIGHT = mh;
const uint8_t MATRIX_WIDTH = mw;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

#ifdef LEDMATRIX
// cLEDMatrix defines 
cLEDMatrix<MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, VERTICAL_ZIGZAG_MATRIX> ledmatrix;

// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
CRGB *matrixleds = ledmatrix[0];
#else
CRGB matrixleds[NUMMATRIX];
#endif

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT,  
    NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG );

#ifdef ESP32_16PINS
FASTLED_USING_NAMESPACE
// -- Task handles for use in the notifications
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t userTaskHandle = 0;

void FastLEDshowESP32()
{
    if (userTaskHandle == 0) {
	const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 200 );
	// -- Store the handle of the current task, so that the show task can
	//    notify it when it's done
	userTaskHandle = xTaskGetCurrentTaskHandle();

	// -- Trigger the show task
	xTaskNotifyGive(FastLEDshowTaskHandle);

	// -- Wait to be notified that it's done
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
	userTaskHandle = 0;
    }
}

void FastLEDshowTask(void *pvParameters)
{
    const TickType_t xMaxBlockTime = pdMS_TO_TICKS( 500 );
    // -- Run forever...
    for(;;) {
	// -- Wait for the trigger
	ulTaskNotifyTake(pdTRUE,portMAX_DELAY);

	// -- Do the show (synchronously)
	FastLED.show();

	// -- Notify the calling task
	xTaskNotifyGive(userTaskHandle);
    }
}
#endif // ESP32_16PINS
#else
#error Please write a matrix config
#endif // end Matrix resolution and display defines

//============================================================================ 

#ifdef ESP8266
// Turn off Wifi in setup()
// https://www.hackster.io/rayburne/esp8266-turn-off-wifi-reduce-current-big-time-1df8ae
//
#include "ESP8266WiFi.h"
extern "C" {
#include "user_interface.h"
}
// min/max are broken by the ESP8266 include
#define min(a,b) (a<b)?(a):(b)
#define max(a,b) (a>b)?(a):(b)
#endif // ESP8266


uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t speed = 255;

float matrix_gamma = 1; // higher number is darker, needed for Neomatrix more than SmartMatrix

// Like XY, but for a mirror image from the top (used by misconfigured code)
int XY2( int x, int y, bool wrap=false) { 
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


void matrix_setup() {
    Serial.begin(115200);
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Serial.begin");
    matrix_gamma = 2.4; // higher number is darker, needed for Neomatrix more than SmartMatrix
#if defined(SMARTMATRIX)
    matrix_gamma = 1; // SmartMatrix should be good by default.
    matrixLayer.addLayer(&backgroundLayer); 
    matrixLayer.begin();
    matrixLayer.setBrightness(matrix_brightness);
    matrixLayer.setRefreshRate(240);
    backgroundLayer.enableColorCorrection(true);
    Serial.print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix GFX output, total LEDs: ");
    Serial.println(NUMMATRIX);
    delay(1000);
    // Quick hello world test
#ifndef DISABLE_MATRIX_TEST
    backgroundLayer.fillScreen( {0x80, 0x80, 0x80} );
    backgroundLayer.swapBuffers();
    delay(1000);
#endif

    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix Init Done");
// Example of parallel output
#elif defined(M32B8X3)
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
// Serialized (slow-ish) output
#elif defined(M16BY16T4)
    FastLED.addLeds<NEOPIXEL,MATRIXPIN>(matrixleds, NUMMATRIX).setCorrection(TypicalLEDStrip);
    Serial.print("Neomatrix total LEDs: ");
    Serial.print(NUMMATRIX);
    Serial.print(" running on pin: ");
    Serial.println(MATRIXPIN);
// 64x64 straight wiring
#else
    // https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
    #ifdef ESP32_16PINS
	xTaskCreatePinnedToCore(FastLEDshowTask, "FastLEDshowTask", 2048, NULL, 2, &FastLEDshowTaskHandle, FASTLED_SHOW_CORE);
	FastLED.addLeds<WS2811_PORTA,NUM_STRIPS,((1<<2) + (1<<4) + (1<<5) + (1<<12)+ (1<<13) + (1<<14) + (1<<15) + (1<<16) + 
						(1<<18) + (1<<19) + (1<<21) + (1<<22) + (1<<23) + (1<<25) + (1<<26) + (1<<27) 
						)>(matrixleds, NUM_LEDS_PER_STRIP);
        Serial.print("Neomatrix 16 way bitbang output, total LEDs: ");
        Serial.println(NUMMATRIX);
    #else // ESP32_16PINS
        // https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples
        FastLED.addLeds<WS2812B, 2, GRB>(matrixleds, 0*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        #ifdef ESP32
        FastLED.addLeds<WS2812B, 4, GRB>(matrixleds, 1*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B, 5, GRB>(matrixleds, 2*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,12, GRB>(matrixleds, 3*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,13, GRB>(matrixleds, 4*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,14, GRB>(matrixleds, 5*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,15, GRB>(matrixleds, 6*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,16, GRB>(matrixleds, 7*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,18, GRB>(matrixleds, 8*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,19, GRB>(matrixleds, 9*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,21, GRB>(matrixleds,10*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,22, GRB>(matrixleds,11*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,23, GRB>(matrixleds,12*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,25, GRB>(matrixleds,13*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,26, GRB>(matrixleds,14*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP); 
        FastLED.addLeds<WS2812B,27, GRB>(matrixleds,15*NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
        Serial.print("Neomatrix 16 pin via RMT 8 way parallel output, total LEDs: ");
        Serial.println(NUMMATRIX);
        #endif // ESP32
    #endif // ESP32_16PINS
#endif
#if !defined(SMARTMATRIX)
    FastLED.setBrightness(matrix_brightness);
#endif
    Serial.print("Brightness: ");
    Serial.println(matrix_brightness);
    Serial.print("Gamma Correction: ");
    Serial.println(matrix_gamma);
    // Gamma is used by AnimatedGIFs, as such:
    // CRGB color = CRGB(matrix->gamma[red], matrix->gamma[green], matrix->gamma[blue]);
    matrix->precal_gamma(matrix_gamma);

// LEDMatrix alignment is tricky, make sure things are aligned correctly
#ifndef DISABLE_MATRIX_TEST
#ifdef LEDMATRIX
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

    // At least on teensy, due to some framework bug it seems, early
    // serial output gets looped back into serial input
    // Hence, flush input.
    while(Serial.available() > 0) { char t = Serial.read(); t = t; }
}

#endif
