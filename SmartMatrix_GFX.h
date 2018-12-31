/*--------------------------------------------------------------------
  Arduino library based on Adafruit_Neomatrix but modified to work with SmartMatrix
  by Marc MERLIN <marc_soft@merlins.org>

  Original notice and license from Adafruit_Neomatrix:
  NeoMatrix is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  NeoMatrix is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with NeoMatrix.  If not, see
  <http://www.gnu.org/licenses/>.
  --------------------------------------------------------------------*/

#ifndef _SMARTMATRIX_GFX_H_
#define _SMARTMATRIX_GFX_H_

#if ARDUINO >= 100
 #include <Arduino.h>
#else
 #include <WProgram.h>
 #include <pins_arduino.h>
#endif
#include <Adafruit_GFX.h>

// Be compatible with struct CRGB in FastLED/pixeltypes.h which is uint8_t[3]
struct RGB888 {
  uint8_t raw[3];

  /// Array access operator to index into the crgb object
  inline uint8_t& operator[] (uint8_t x) __attribute__((always_inline))
  {
      return raw[x];
  }

  /// Array access operator to index into the crgb object
  inline const uint8_t& operator[] (uint8_t x) const __attribute__((always_inline))
  {
      return raw[x];
  }
};

// Matrix layout information is passed in the 'matrixType' parameter for
// each constructor (the parameter immediately following is the LED type
// from NeoPixel.h).

// These define the layout for a single 'unified' matrix (e.g. one made
// from NeoPixel strips, or a single NeoPixel shield), or for the pixels
// within each matrix of a tiled display (e.g. multiple NeoPixel shields).

#define NEO_MATRIX_TOP         0x00 // Pixel 0 is at top of matrix
#define NEO_MATRIX_BOTTOM      0x01 // Pixel 0 is at bottom of matrix
#define NEO_MATRIX_LEFT        0x00 // Pixel 0 is at left of matrix
#define NEO_MATRIX_RIGHT       0x02 // Pixel 0 is at right of matrix
#define NEO_MATRIX_CORNER      0x03 // Bitmask for pixel 0 matrix corner
#define NEO_MATRIX_ROWS        0x00 // Matrix is row major (horizontal)
#define NEO_MATRIX_COLUMNS     0x04 // Matrix is column major (vertical)
#define NEO_MATRIX_AXIS        0x04 // Bitmask for row/column layout
#define NEO_MATRIX_PROGRESSIVE 0x00 // Same pixel order across each line
#define NEO_MATRIX_ZIGZAG      0x08 // Pixel order reverses between lines
#define NEO_MATRIX_SEQUENCE    0x08 // Bitmask for pixel line order

// These apply only to tiled displays (multiple matrices):

#define NEO_TILE_TOP           0x00 // First tile is at top of matrix
#define NEO_TILE_BOTTOM        0x10 // First tile is at bottom of matrix
#define NEO_TILE_LEFT          0x00 // First tile is at left of matrix
#define NEO_TILE_RIGHT         0x20 // First tile is at right of matrix
#define NEO_TILE_CORNER        0x30 // Bitmask for first tile corner
#define NEO_TILE_ROWS          0x00 // Tiles ordered in rows
#define NEO_TILE_COLUMNS       0x40 // Tiles ordered in columns
#define NEO_TILE_AXIS          0x40 // Bitmask for tile H/V orientation
#define NEO_TILE_PROGRESSIVE   0x00 // Same tile order across each line
#define NEO_TILE_ZIGZAG        0x80 // Tile order reverses between lines
#define NEO_TILE_SEQUENCE      0x80 // Bitmask for tile line order

#include "FastLED.h"
class SmartMatrix_GFX : public Adafruit_GFX {

 public:
  // pre-computed gamma table
  uint8_t gamma[256];

  // I'd love to make my FastLED independent uint24_t definition that is compatible
  // with FastLED's CRGB, but I haven't succeeded, so for now I'm using FastLED.
  //SmartMatrix_GFX(RGB888 *, uint8_t w, uint8_t h);
  SmartMatrix_GFX(CRGB *, uint8_t w, uint8_t h, void (* showptr)());

  int XY(int16_t x, int16_t y); // compat with FastLED code, returns 1D offset
  void
    drawPixel(int16_t x, int16_t y, uint16_t color),
    drawPixel(int16_t x, int16_t y, uint32_t color),
    drawPixel(int16_t x, int16_t y, CRGB color),
    fillScreen(uint16_t color),
    setPassThruColor(uint32_t c),
    setPassThruColor(void),
    setRemapFunction(uint16_t (*fn)(uint16_t, uint16_t)),
    precal_gamma(float);

  static uint16_t
    Color(uint8_t r, uint8_t g, uint8_t b);

  void clear() { fillScreen(0); };
  void show() { _show(); };

  void setBrightness(int b) { 
    Serial.println("please call matrixLayer.setBrightness() instead");
  };


  void begin(); // no-op in this lib, left for compat


 private:

  // Because SmartMatrix uses templates so heavily, its object cannot be passed to us
  // However the main function can create a show function that copies our data from _leds
  // into the SmartMatrix object, and pass that function to us by pointer.
  void (* _show)();

  //RGB888 *_leds;
  CRGB *_leds;
  const uint8_t
    type;
  const uint8_t
    matrixWidth, matrixHeight, tilesX, tilesY;
  uint16_t
    numpix,
    (*remapFn)(uint16_t x, uint16_t y);

  uint32_t _malloc_size;
  uint32_t passThruColor;
  boolean  passThruFlag = false;
};

#endif // _SMARTMATRIX_GFX_H_
// vim:sts=2:sw=2
