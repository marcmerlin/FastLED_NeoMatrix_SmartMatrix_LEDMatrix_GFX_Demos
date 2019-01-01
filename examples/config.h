#ifndef config_h
#define config_h

#define SMARTMATRIX
#ifndef SMARTMATRIX
#ifdef ESP32
// 64x64 matrix with optional 16 pin parallel driver
// 55fps without 16PINS, 110fps with 16PINS
#define ESP32_16PINS
#elif ESP8266
// ESP8266 shirt with neopixel strips
#define M32B8X3
#else
#error Please write a matrix config
#endif

#ifdef ESP32
    #ifdef ESP32_16PINS
    // This uses https://github.com/hpwit/fastled-esp32-16PINS.git
    // instead of https://github.com/samguyer/FastLED.git
    #define FASTLED_ALLOW_INTERRUPTS 0
    #define FASTLED_SHOW_CORE 0
    #else
    // Allow infrared
    #define FASTLED_ALLOW_INTERRUPTS 1
    #endif // ESP32_16PINS
#endif
#if defined(ESP32) && ! defined(ESP32_16PINS)
#pragma message "Please use https://github.com/samguyer/FastLED.git as stock FastLED is unstable with ESP32"
#endif
#endif // SMARTMATRIX

// The above optional defines must be before FastLED is included.
#include <Adafruit_GFX.h>
#include <SmartLEDShieldV4.h>  // comment out this line for if you're not using SmartLED Shield V4 hardware (this line needs to be before #include <SmartMatrix3.h>)
#include <SmartMatrix3.h>
#include <SmartMatrix_GFX.h>
#include <FastLED.h>


// Separate Neopixel Strip, if used. Not the NeoMatrix
uint8_t led_brightness = 64;
#if defined(SMARTMATRIX)
const uint8_t matrix_brightness = 255;
// Used by LEDMatrix
#define MATRIX_TILE_WIDTH   64 // width of EACH NEOPIXEL MATRIX (not total display)
#define MATRIX_TILE_HEIGHT  64 // height of each matrix
#define MATRIX_TILE_H       1  // number of matrices arranged horizontally
#define MATRIX_TILE_V       1  // number of matrices arranged vertically

// Used by NeoMatrix
#define mw (MATRIX_TILE_WIDTH *  MATRIX_TILE_H)
#define mh (MATRIX_TILE_HEIGHT * MATRIX_TILE_V)
#define NUMMATRIX (mw*mh)

// Compat for some other demos
#define NUM_LEDS NUMMATRIX 
#define MATRIX_HEIGHT mh
#define MATRIX_WIDTH mw
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

/// SmartMatrix Defines
#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
#define kMatrixWidth  mw       // known working: 32, 64, 96, 128
#define kMatrixHeight mh       // known working: 16, 32, 48, 64
const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 2;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
//const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrixLayer, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);

CRGB matrixleds[NUMMATRIX];

// Sadly this callback function must be copied around with this init code
void show_callback() {
    for (uint16_t y=0; y<kMatrixHeight; y++) {
	for (uint16_t x=0; x<kMatrixWidth; x++) {
	    CRGB led = matrixleds[x + kMatrixWidth*y];
	    // rgb24 defined in MatrixComnon.h
	    backgroundLayer.drawPixel(x, y, { led.r, led.g, led.b } );
	}
    }
    // This should be zero copy
    // that said, copy or no copy is about the same speed in the end.
    backgroundLayer.swapBuffers(false);
}

SmartMatrix_GFX *matrix = new SmartMatrix_GFX(matrixleds, mw, mh, show_callback);

#elif defined(M32B8X3)
const uint8_t matrix_brightness = 64;
// Used by LEDMatrix
#define MATRIX_TILE_WIDTH   8 // width of EACH NEOPIXEL MATRIX (not total display)
#define MATRIX_TILE_HEIGHT  32 // height of each matrix
#define MATRIX_TILE_H       3  // number of matrices arranged horizontally
#define MATRIX_TILE_V       1  // number of matrices arranged vertically

// Used by NeoMatrix
#define mw (MATRIX_TILE_WIDTH *  MATRIX_TILE_H)
#define mh (MATRIX_TILE_HEIGHT * MATRIX_TILE_V)
#define NUMMATRIX (mw*mh)

// Compat for some other demos
#define NUM_LEDS NUMMATRIX 
#define MATRIX_HEIGHT mh
#define MATRIX_WIDTH mw
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

CRGB matrixleds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, MATRIX_TILE_H, MATRIX_TILE_V, 
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
    NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG + 
    NEO_TILE_TOP + NEO_TILE_LEFT +  NEO_TILE_PROGRESSIVE);

#else
//---------------------------------------------------------------------------- 
const uint8_t matrix_brightness = 32;
//
// Used by LEDMatrix
#define MATRIX_TILE_WIDTH   64 // width of EACH NEOPIXEL MATRIX (not total display)
#define MATRIX_TILE_HEIGHT  64 // height of each matrix
#define MATRIX_TILE_H       1  // number of matrices arranged horizontally
#define MATRIX_TILE_V       1  // number of matrices arranged vertically
#define NUM_STRIPS 16
#define NUM_LEDS_PER_STRIP 256

// Used by NeoMatrix
#define mw (MATRIX_TILE_WIDTH *  MATRIX_TILE_H)
#define mh (MATRIX_TILE_HEIGHT * MATRIX_TILE_V)
#define NUMMATRIX (mw*mh)

// Compat for some other demos
#define NUM_LEDS NUMMATRIX 
#define MATRIX_HEIGHT mh
#define MATRIX_WIDTH mw
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

CRGB matrixleds[NUMMATRIX];

FastLED_NeoMatrix *matrix = new FastLED_NeoMatrix(matrixleds, MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT,  
    NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG );
`
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
#endif

// Like XY, but for a mirror image from the top (used by misconfigured code)
int XY2( int x, int y, bool wrap=false) { 
    return matrix->XY(x,MATRIX_HEIGHT-1-y);
}


uint16_t XY( uint8_t x, uint8_t y) {
    return matrix->XY(x,y);
}

#ifdef ESP8266
#define NEOPIXEL_PIN D1 // GPIO5


// D4 is also the system LED, causing it to blink on IR receive, which is great.
#define RECV_PIN D4     // GPIO2

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
#endif

bool matrix_reset_demo = 1;

uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint16_t speed = 255;

int wrapX(int x) { 
	if (x < 0 ) return 0;
	if (x >= MATRIX_WIDTH) return (MATRIX_WIDTH-1);
	return x;
}

void matrix_show();
void aurora_setup();


void matrix_setup() {
#if defined(SMARTMATRIX)
    matrixLayer.addLayer(&backgroundLayer); 
    matrixLayer.begin();
    matrixLayer.setBrightness(matrix_brightness);
    matrixLayer.setRefreshRate(240);
    backgroundLayer.enableColorCorrection(true);
    delay(1000);
    // Quick hello world test
    backgroundLayer.fillScreen( {0x80, 0x80, 0x80} );
    backgroundLayer.swapBuffers();
    delay(1000);
    Serial.print("SmartMatrix GFX output, total LEDs: ");
    Serial.println(NUMMATRIX);
#elif defined(M32B8X3)
    // Init Matrix
    // Serialized, 768 pixels takes 26 seconds for 1000 updates or 26ms per refresh
    // FastLED.addLeds<NEOPIXEL,MATRIXPIN>(matrixleds, NUMMATRIX).setCorrection(TypicalLEDStrip);
    // https://github.com/FastLED/FastLED/wiki/Parallel-Output
    // WS2811_PORTA - pins 12, 13, 14 and 15 or pins 6,7,5 and 8 on the NodeMCU
    // This is much faster 1000 updates in 10sec
    //FastLED.addLeds<NEOPIXEL,PIN>(matrixleds, NUMMATRIX); 
    FastLED.addLeds<WS2811_PORTA,3>(matrixleds, NUMMATRIX/3).setCorrection(TypicalLEDStrip);
    Serial.print("Neomatrix parallel output, total LEDs: ");
    Serial.println(NUMMATRIX);
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
}

#endif // config.h
