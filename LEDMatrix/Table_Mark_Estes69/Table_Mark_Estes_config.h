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
#define BESTPATTERNS
#ifdef BESTPATTERNS

// if not huge pb[3] becomes cube

uint8_t bestpatterns[] = {31, 193, 87, 3, 22, 28, 30, 1, 4, 45, 51, 85,  196, 5, 6, 160, 9, 10, 49, 11, 194,  67, 12, 90, 15, 18, 17, 16, 186, 21, 22, 23, 26, 27, 28, 32, 29,  33, 54, 35, 37, 40, 41, 53, 48,  52,   55, 58, 59, 61, 62, 66, 69, 70, 72, 73, 74, 75, 77, 78, 79,   82, 84,
                          85, 86, 88, 89,  31, 94, 95, 98, 101, 102, 103, 104, 195, 105,  108, 109, 110,  111, 113, 114, 115, 116, 117, 118, 119, 120, 121, 124, 126, 132,  131, 133,  134, 136,  139, 140, 141, 142,  143, 144, 145,  146, 147, 148, 150, 152,
                          153, 157, 158, 160, 161, 162, 163, 164, 167,  170, 176, 177,  178, 179, 182, 87, 3, 185, 19,  187, 189, 190, 192, 45,193,195,20,30
                         };
#define numbest           sizeof(bestpatterns)

#define lastpatindex numbest
#else
#define lastpatindex mpatterns
#endif

// By default audio support is on for what's expected to be teensy.
#define TME_AUDIO
// But turn it off on ARDUINOONPC / Raspberry Pi and ESP32


#ifdef ESP32
#undef TME_AUDIO
#endif

// Don't load non existent EasyTransfer for platforms without audio
#ifdef TME_AUDIO
#include <EasyTransfer.h>// used for exchange with 2nd arduino for audio processing

#endif

#define TIMING              99
//seconds per pattern
#define LATCHA              23
#define LATCHB              14
int16_t pattern = 45;//this picks the pattern to start with...
// --------------------------- Config End ----------------------------------
