// --------------------------- Config Start --------------------------------
// Randomly slowdown animation. Nice in principle, but not when debugging performance
#define RANDOMSLOWME

// Control whether pattern order is random from the start or after one pass
#define MIXIT_AFTER_FIRST_PASS

// write the pattern number in upper left (makes more sense on higher res displays)
//#define SHOW_PATTERN_NUM
//
// Display FPS computed by Framebuffer::GFX
//#define DISPLAY_FPS

// Some pattern transitions look weird without a clear in between
//#define CLEAR_BETWEEN_PATTERNS

// This allows a selection of only my favourite patterns.
// Comment this out to get all the patterns -- merlin
//#define BESTPATTERNS
#ifdef BESTPATTERNS
// 82 and 89 are similar     55 and 102 are similar
uint8_t bestpatterns[] = {
   3, 8, 14, 17, 26, 55, 58, 59, 61, 69, 72, 82, 87, 102, 108, 109, 111, 115, 124, 134, 139, 155,
   4, 10, 11, 16, 18, 25, 67, 70, 73, 77, 80, 86, 104, 105, 110,  // good in original tmed
   19, 20, 26, 81, 89, 94, 96, 98, 101, 103, 107, 112, 113, 114, 118, 119, 120, 121, 126, 128, 131, 134, 139, 141, 143, 144, 145, 147, 149, 151, 158,    // good but not picked for 128x192
};
#define numbest           sizeof(bestpatterns)
#define lastpatindex numbest
#else
#define lastpatindex mpatterns
#endif

// By default audio support is on for what's expected to be teensy.
#define TME_AUDIO
// But turn it off on ARDUINOONPC / Raspberry Pi and ESP32
#ifdef ARDUINOONPC
#undef TME_AUDIO
#endif
#ifdef ESP32
#undef TME_AUDIO
#endif

#ifdef TME_AUDIO
#include <EasyTransfer.h>// used for exchange with 2nd arduino for audio processing
#endif

#define TIMING              90//seconds per pattern
#define LATCH               23

int16_t pattern = 112;//this picks the pattern to start with...
// --------------------------- Config End ----------------------------------
