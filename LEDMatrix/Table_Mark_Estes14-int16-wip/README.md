Table_Mark_Estes14 int16 wip
----------------------------
This is a temporary fork to test Table_Mark_Estes14 with array sizes of
- 128 across or more (goes beyond int8_t/byte as defined in the code
- 256 across or more (overflows uint8_t), blend8, random8 and so forth)
- matrix size of more than 64K (overflows FastLED functions that only work with uint16_t

This code is best tested/debugged in 
https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix
https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix/tree/master/examples/GFX_Table_Mark_Estes14-int16-wip
since it allows setting any size you'd like in software.

Edit neomatrix_config.h and under LINUX_RENDERER_SDL, set MATRIX_TILE_WIDTH/MATRIX_TILE_HEIGHT
