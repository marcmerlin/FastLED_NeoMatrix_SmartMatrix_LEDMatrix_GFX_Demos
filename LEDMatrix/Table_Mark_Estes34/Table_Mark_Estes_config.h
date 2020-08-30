// --------------------------- Config Start --------------------------------
// Randomly slowdown animation. Nice in principle, but not when debugging performance
#define RANDOMSLOWME

// Control whether pattern order is random from the start or after one pass
#define MIXIT_AFTER_FIRST_PASS

// write the pattern number in upper left (makes more sense on higher res displays)
#define SHOW_PATTERN_NUM

// Some pattern transitions look weird without a clear in between
#define CLEAR_BETWEEN_PATTERNS

// This allows a selection of only my favourite patterns.
// Comment this out to get all the patterns -- merlin
//#define BESTPATTERNS
#ifdef BESTPATTERNS
// 82 and 89 are similar     55 and 102 are similar
uint8_t bestpatterns[] = {
187,
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
