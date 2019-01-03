Matrix Demos here use FastLED's leds[idx] direct addressing to read and write 
pixels, which is not compatible with the GFX API (which does not allow reading
pixels, only writing to them).

Both FastLED::NeoMatrix and SmartMatrix::GFX provide that FastLED API
as well as an XY mapping function to turn a coordinate into a 1D index
for the FastLED backed array (which for SmartMatrix is actually only 
a framebuffer which is copied back to SmartMatrix's framebuffer later).

* https://github.com/marcmerlin/FastLED_NeoMatrix
* https://github.com/marcmerlin/SmartMatrix_GFX
