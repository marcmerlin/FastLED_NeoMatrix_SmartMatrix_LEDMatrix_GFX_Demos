Matrix Demos here use the Adafruit::GFX API.  
They should work with minimal changes on other backends that support
the GFX API 

Aurora is one exception as it does have a few references to direct
FastLED style leds addressing using XY() but you should be able to
change them to DrawPixel only. It also uses extended DrawPixel which
accept both a uint32_t or a FastLED CRBG, but you can fairly easy
change those calls to downgrade them back to a native GFX RGB565
if this is all you have support for.

Both FastLED::NeoMatrix and SmartMatrix::GFX provide that GFX+FastLED API
as well as an XY mapping function to turn a coordinate into a 1D index
for the FastLED backed array (which for SmartMatrix is actually only 
a framebuffer which is copied back to SmartMatrix's framebuffer later).

* https://github.com/marcmerlin/FastLED_NeoMatrix
* https://github.com/marcmerlin/SmartMatrix_GFX
