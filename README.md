This is a collection of demos I gathered after writing my first
Adadfruit::GFX demo ( GFX/MatrixGFXDemo ) and later GFX/fontzoom .

This started after I wrote https://github.com/marcmerlin/FastLED_NeoMatrix which 
was designed to add GFX compatiblity for FastLED supported backends.
In that process, I picked up some demos in the FastLED directory that I 
ported to NeoMatrix.

Some time after, I found that there was a different GFX compatible-ish library 
for Neopixel Matrixes, called LEDMatrix. I was able to make them
compatible with FastLED::NeoMatrix which has bettern support for complex
tiled matrices with random orientations (courtesy of the original
Adafruit::NeoMatrix)

Later still, I had to use some RGB Panels for higher pixel density at the cost
of lower brightness and more resource intensive driver (SmartMatrix). 
SmartMatrix however had a completely different (and better) API, but it was not compatible
with all the demo code I already had, so I wrote 
https://github.com/marcmerlin/SmartMatrix_GFX 
to add a GFX/FastLED compatibility layer for SmartMatrix and allow all the demo
code included here to run trivially on top of RGB Panels thanks to SmartMatrix.  
It also adds LEDMatrix support if you use my very slightly modified fork:   
https://github.com/marcmerlin/LEDMatrix
For instance, look at https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/LEDMatrix/Table_Mark_Estes

Demos examples:
- Aurora Incremental Drift (GFX):  https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/master/GFX/Aurora/incrementaldrift/
![134_20190409_RGBPanels_Diffusers](https://user-images.githubusercontent.com/1369412/55811896-c81a2500-5a9e-11e9-9301-0d09083f48cb.jpg)

- Aurora Cube (GFX) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/GFX/Aurora/cube
![218_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55811825-ac168380-5a9e-11e9-9fa3-78903c3c821a.jpg)

- https://github.com/marcmerlin/NeoMatrix-FastLED-IR (GFX)
![203_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816208-a15fec80-5aa6-11e9-890e-fcb6d66e8de4.jpg)

- Sublime Demos Matrix Rain (FastLED) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/FastLED/Sublime_Demos
![200_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816516-437fd480-5aa7-11e9-9a37-35bc21276812.jpg)

- TwinkleFox (FastLED) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/FastLED/TwinkleFOX
![201_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816588-73c77300-5aa7-11e9-9503-82d8f55a52d0.jpg)


- Table Mark Estes (LEDMatrix) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/LEDMatrix/Table_Mark_Estes
![225_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55811839-b0db3780-5a9e-11e9-9b9e-42a38b99ca20.jpg)

- Table Mark Estes (LEDMatrix) 
![245_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55811847-b5075500-5a9e-11e9-91da-5857d2fb1bcc.jpg)

Enjoy,  
Marc <marc_soft@merlins.org>

