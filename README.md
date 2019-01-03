This is a collection of demos I gathered after writing my first
Adadfruit::GFX demo ( GFX/MatrixGFXDemo ) and later GFX/fontzoom .

This started after I wrote
https://github.com/marcmerlin/FastLED_NeoMatrix  
which was designed to add GFX compatiblity for FastLED supported backends.
In that process, I picked up some demos in the FastLED directory that I 
ported to NeoMatrix.

Some time after, I found that there was a different GFX compatible-ish library 
for Neopixel Matrixes, called LEDMatrix. I was able to make them
compatible with FastLED::NeoMatrix which has bettern support for complex
tiled matrices with random orientations (courtesy of the original
Adafruit::NeoMatrix)

Later still, I had to use some RGB Panels for higher pixel density at the cost
of lower brightness and more resource intensive driver (SmartMatrix). 
SmartMatirx however had a completely (and better) API, but it was not compatible
with all the demo code I already had, so I wrote  
https://github.com/marcmerlin/SmartMatrix_GFX  
to add a GFX/FastLED compatibility layer for SmartMatrix and allow all the demo
code included here to run trivially on top of RGB Panels thanks to SmartMatrix.

Enjoy,
Marc <marc_soft@merlins.org>
