
#define neomatrix_config_h
#define SMARTMATRIX//I added this per your instructions...
//#define M64BY64// I added this per your instructions...only if one chunk



// Teensy 3.6

#define ILI9341
#define ILI_ROTATE 1




#include <Adafruit_GFX.h>
bool init_done = 0;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


//============================================================================
// Matrix defines (SMARTMATRIX vs NEOMATRIX and size)
//============================================================================


#define GPIOPINOUT 3
#pragma message "Compiling for SMARTMATRIX"
#include <SmartLEDShieldV4.h>  // if you're using SmartLED Shield V4 hardware
#include <SmartMatrix3.h>
#include <SmartMatrix_GFX.h>


#include <FastLED.h>
#include <LEDMatrix.h>


uint8_t matrix_brightness = 255;//this is the one that sets brightnessss


#pragma message "Compiling for Teensy with 64x64 32 scan panel xx"
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
//const uint8_t kPanelType = SMARTMATRIX_HUB75_64ROW_MOD32SCAN;
const uint16_t MATRIX_TILE_WIDTH = 64; // width of EACH NEOPIXEL MATRIX (not total display)
const uint16_t MATRIX_TILE_HEIGHT = 32; // height of each matrix

// Used by LEDMatrix
const uint8_t MATRIX_TILE_H     = 1;  // number of matrices arranged horizontally
const uint8_t MATRIX_TILE_V     = 2;  // number of matrices arranged vertically

// Used by NeoMatrix
const uint16_t mw = MATRIX_TILE_WIDTH *  MATRIX_TILE_H;
const uint16_t mh = MATRIX_TILE_HEIGHT * MATRIX_TILE_V;
const uint32_t NUMMATRIX = mw * mh;
const uint32_t NUM_LEDS = mw * mh;
const int MATRIX_HEIGHT = mh;
const int MATRIX_WIDTH = mw;
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
cLEDMatrix < -MATRIX_TILE_WIDTH, MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
           MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS > ledmatrix;

/*cLEDMatrix < -MATRIX_TILE_WIDTH, -MATRIX_TILE_HEIGHT, HORIZONTAL_MATRIX,
           MATRIX_TILE_H, MATRIX_TILE_V, HORIZONTAL_BLOCKS > ledmatrix;
*/
// cLEDMatrix creates a FastLED array inside its object and we need to retrieve
// a pointer to its first element to act as a regular FastLED array, necessary
// for NeoMatrix and other operations that may work directly on the array like FadeAll.
//CRGB *matrixleds = ledmatrix[0];
#else
//CRGB matrixleds[NUMMATRIX];
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
}

//----------------------------------------------------------------------------





uint16_t speed = 255;

float matrix_gamma = 1; // higher number is darker, needed for Neomatrix more than SmartMatrix

// Like XY, but for a mirror image from the top (used by misconfigured code)
int XY2( int x, int y, bool wrap = false) {
  wrap = wrap; // squelch compiler warning
  return matrix->XY(x, MATRIX_HEIGHT - 1 - y);
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
  if (x >= MATRIX_WIDTH) return (MATRIX_WIDTH - 1);
  return x;
}

void show_free_mem() {
  Framebuffer_GFX::show_free_mem();
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
  delay(100);
#endif
  //    Serial.begin(115200);
  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Serial.begin");
  matrix_gamma = 2.4; // higher number is darker, needed for Neomatrix more than SmartMatrix

  matrix_gamma = 1.5; // SmartMatrix should be good by default.
  matrixLayer.addLayer(&backgroundLayer);
  // SmartMatrix takes all the RAM it can get its hands on. Get it to leave some
  // free RAM so that other libraries can work too.

  matrixLayer.begin();

  // This sets the neomatrix and LEDMatrix pointers
  show_callback();
  matrixLayer.setRefreshRate(240);
  backgroundLayer.enableColorCorrection(true);
  Serial.print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix GFX output, total LEDs: ");
  Serial.println(NUMMATRIX);
  delay(1000);
  // Quick hello world test

  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix  Demo");
  backgroundLayer.fillScreen( {0x20, 0x20, 0x20} );
  // backgroundLayer.swapBuffers();
  show_callback();
  delay(300);

  Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> SmartMatrix Init Done");


  Serial.print("Neomatrix parallel output, total LEDs: ");
  Serial.println(NUMMATRIX);
  // Serialized (slow-ish) output


  show_free_mem();
  matrix->begin();

  Serial.print("Setting Brightnessxx: ");
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

  matrix->show();
  delay(500);
#endif
#endif

  Serial.println("neomatrix_config setup done");
  // At least on teensy, due to some framework bug it seems, early
  // serial output gets looped back into serial input
  // Hence, flush input.

}
