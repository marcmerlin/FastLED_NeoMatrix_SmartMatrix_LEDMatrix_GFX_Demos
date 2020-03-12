Introduction
------------
This is a collection of demos I gathered after writing my first Adadfruit::GFX demo ( GFX/MatrixGFXDemo ) and later GFX/fontzoom.

You'll find they are in 3 directories depending on which API they use (Adafruit::GFX, FastLED, or LEDMatrix)

Those demos work on multiple hardware backends thanks to 
https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/master/neomatrix_config.h  
All those backends ultimately run on top of https://github.com/marcmerlin/Framebuffer_GFX , so you should have
a look at it to understand the base layer/API everything is built on top of (and that library itself offers
the Adafruit::GFX and FastLED APIs as explained in its README).


Hardware backends and glue drivers tha can run this demo code
-------------------------------------------------------------
I used all the low level drivers on the left, wrote all the glue drivers in the middle, and FrameBuffer::GFX
```
Low Level Drv|Glue Driver for FrameBuffer::GFX
FastLED     - FastLED_NeoMatrix  -------------\     FastLED CRGB Array 
SmartMatrix - SmartMatrix_GFX -----------------\    24bit FB storage        API Support
ILI9341 \                                       \   CRGB methods like
SSD1331  |--- FastLED_SPITFT_GFX ----------------\  scale8/fadeToBlackBy   ,FastLED API
ST7735  /                                         |        |              / (XY 2D to 1D mapping)
                                                  |        |             /
ArduinoOnPc-FastLED-GFX-LEDMatrix arduino         - FrameBuffer::GFX------ Adafruit::NeoMatrix +
emulation for linux / Raspberry Pi:               |        |             \ Adafruit::GFX APIs
----------------------------------               /    Adafruit::GFX       \ 
rpi-rgb-led-matrix - FastLED_RPIRGBPanel_GFX ---/   LEDMatrix (optional)   `LEDMatrix API
ArduinoOnPC X11/linux - FastLED_TFTWrapper_GFX /
FastLED_SDL (linux)   -  FastLED_NeoMatrix   -/                        
```

neomatrix_config.h controls which hardware backend to run all demos on
-----------------------------------------------------------------------
For the demos to run, you need to edit 
https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/master/neomatrix_config.h
and #define the correct backend for your display.

Assuming you are running FastLED::NeoMatrix, you may want to try uncommmenting '#define M24BY24'
and modifying the 2 code sections relevant to this define to put the correct data for your array.  
Obviously you can look at M32BY8X3, M16BY16T4, and M64BY64 for ways to configure more complex matrices.
If you haven't gotten your FastLED matrix to work at all, please do make those examples work first:
- https://github.com/marcmerlin/FastLED_NeoMatrix/tree/master/examples/matrixtest
- https://github.com/marcmerlin/FastLED_NeoMatrix/tree/master/examples/MatrixGFXDemo

As of this writing, you can run on top of
- https://github.com/marcmerlin/FastLED_NeoMatrix/
- https://github.com/marcmerlin/SmartMatrix_GFX/
- https://github.com/marcmerlin/FastLED_SPITFT_GFX (SSD1331, ILI9341, and ST7735 TFTs)
- https://github.com/marcmerlin/ArduinoOnPc-FastLED-GFX-LEDMatrix (which itself supports 3 more drivers)

If you are using some of the other backends, I'll assume that you can set the correct define in neomatrix_config

This demo collection started after I wrote https://github.com/marcmerlin/FastLED_NeoMatrix which 
was designed to add GFX compatiblity for FastLED supported backends.
In that process, I picked up some demos in the FastLED directory that I 
ported to NeoMatrix.

Some time after, I found that there was a different GFX compatible-ish library 
for Neopixel Matrixes, called LEDMatrix. I was able to make them
compatible with FastLED::NeoMatrix which has better support for complex
tiled matrices with random orientations (courtesy of the original Adafruit::NeoMatrix)
and you can therefore use both APIs at the same time.

Later still, I had to use some RGB Panels for higher pixel density at the cost
of lower brightness and more resource intensive driver (SmartMatrix). 
SmartMatrix however had a completely different (and better) API, but it was not compatible
with all the demo code I already had, so I wrote 
https://github.com/marcmerlin/SmartMatrix_GFX 
to add a GFX/FastLED compatibility layer for SmartMatrix and allow all the demo
code included here to run trivially on top of RGB Panels thanks to SmartMatrix.  
It also adds LEDMatrix support on top of SmartMatrix if you use my very slightly modified fork:   
https://github.com/marcmerlin/LEDMatrix  
For instance, look at https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/LEDMatrix/Table_Mark_Estes

What you end up with are demos that run with multiple APIs (GFX, FastLED, and LEDMAtrix) on top of multiple hardware backends (listed above).

Demos examples:
- Table Mark Estes + Sublime (LEDMatrix + FastLED/FastLEDonPc)
![102_demo_snaps](https://user-images.githubusercontent.com/1369412/71480161-a982c800-27ac-11ea-8f0e-fb149b6a9ae2.jpg)
![103_demo_snaps](https://user-images.githubusercontent.com/1369412/71480163-abe52200-27ac-11ea-9cb1-f4d23bdf96ac.jpg)

- Aurora Incremental Drift (GFX/SmartMatrix):  https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/blob/master/GFX/Aurora/incrementaldrift/
![134_20190409_RGBPanels_Diffusers](https://user-images.githubusercontent.com/1369412/55811896-c81a2500-5a9e-11e9-9301-0d09083f48cb.jpg)

- Aurora Cube (GFX/SmartMatrix) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/GFX/Aurora/cube
![218_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55811825-ac168380-5a9e-11e9-9fa3-78903c3c821a.jpg)

- https://github.com/marcmerlin/NeoMatrix-FastLED-IR (GFX/SmartMatrix)
![203_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816208-a15fec80-5aa6-11e9-890e-fcb6d66e8de4.jpg)

- Sublime Demos Matrix Rain (FastLED/SmartMatrix) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/FastLED/Sublime_Demos
![200_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816516-437fd480-5aa7-11e9-9a37-35bc21276812.jpg)

- TwinkleFox (FastLED/SmartMatrix) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/FastLED/TwinkleFOX
![201_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55816588-73c77300-5aa7-11e9-9503-82d8f55a52d0.jpg)

- Table Mark Estes (LEDMatrix/FastLED_SPITFT_GFX)
![104_20190526_FastLED_SPITFT_GFX_On_Top_Of_Framebuffer_GFX](https://user-images.githubusercontent.com/1369412/76477705-64d9f680-63c3-11ea-81b1-9a10471888fe.jpg)

- Table Mark Estes (LEDMatrix/SmartMatrix) https://github.com/marcmerlin/FastLED_NeoMatrix_SmartMatrix_LEDMatrix_GFX_Demos/tree/master/LEDMatrix/Table_Mark_Estes
![225_20190401_SmartMatrix_GFX_Patterns](https://user-images.githubusercontent.com/1369412/55811839-b0db3780-5a9e-11e9-9b9e-42a38b99ca20.jpg)

- Table Mark Estes (LEDMatrix/ArduinoOnPc-FastLED-GFX-LEDMatrix/FastLED_RPIRGBPanel_GFX) on a massive 384x192
![dsc05134](https://user-images.githubusercontent.com/1369412/76477536-e2e9cd80-63c2-11ea-86f9-f925fe625a4d.jpg)

Enjoy,  
Marc <marc_soft@merlins.org>
