SmartMatrix GFX, Control Scan Based Matrices with SmartMatrix and Adafruit GFX API
==================================================================================

Adafruit::GFX compatible library for scan based matrices.
This library requires SmartMatrix, Adafruit_GFX, and FastLED libraries.
- https://github.com/pixelmatix/SmartMatrix
- https://github.com/adafruit/Adafruit-GFX-Library
- https://github.com/FastLED/FastLED  
(technically it can work without FastLED, but it's convenient to use the FastLED CRGB representation
and in turn, it gives extra primitives that can be used against pixels, defined here: https://github.com/FastLED/FastLED/blob/master/pixeltypes.h#L90 )

Example code: https://github.com/marcmerlin/SmartMatrix_GFX/blob/master/examples/MatrixGFXDemo/MatrixGFXDemo.ino

This code was taken from FastLED_NeoMatrix and adapted to work with the SmartMatrix library. SmartMatrix is used to drive row scan panels. They are not as good as NeoPixel based panels which you can run with FastLED::NeoMatrix instead, but you should consider SmartMatrix driven panels if one of those reasons apply to you:
* They are cheaper given that the pixels do not have logic (they also don't stay on unless you keep refreshing them)
* One big reason to use them is that you can have much higher density (2.5 to 5mm per pixel vs 10mm for the typical neopixel matrix)
* scan panels are 50 to 70% cheaper per pixel than neopixel based matrices.

That being said, I do recommend that you use Neopixel matrices whenever you can as for their much better display quality, brightness, and being easier to drive, but if you decide to use scan based matrices for the reasons above and you'd like Adafruit::GFX compatibility, then this library is for you.

It also offers FastLED compatibility if you'd like to use those primitives against your virtual display (like nblend, fade, etc...).

RGB Panels vs NeoPixels and other addressable LEDs
--------------------------------------------------
Neopixels and other pixels like APA102 have their own chip for each pixel that take care of accepting a 24bit (or better) 
color value and then refreshing the LED to get that color value for you with no work from you.  
RGB Panels have no such smarts and require you to constantly refresh every LED and even create colors by flashing each R G B
pixel between on and off at the right speed to create intensities and color mixes.  
RGB Panels are cheaper, not as bright, and have much better density (due to lack of per pixel controlling chips)  
https://www.sparkfun.com/sparkx/blog/2650 is an awesome page that explains how complex some of them, can be to drive.

Adafruit::GFX vs SmartMatrix vs FastLED APIs
--------------------------------------------
Years ago, back when we only had 8x8 displays, Adafruit wrote a nice API, https://github.com/adafruit/Adafruit-GFX-Library .
It is in no means perfect or exhaustive, but it does what most people need, including font support. Its huge strength is how
it works many different hardware backends, all the way back to 8x8 matrices. See this example of code working on 3 different
hardware backends all using the same GFX demo code: 
http://marc.merlins.org/perso/arduino/post_2017-04-24_Adafruit-GFX-on-NeoMatrix-and-RGB-Matrix-Panel-Demo.html 
https://www.youtube.com/watch?tv=9yGZLtewmfI

Now Adafruit::GFX has a drawback nowadays which is how it only supports color in 16 bits (RGB 565).  
Honestly it is good enough for most displays that aren't good enough to show 16,777,216 colors, and if you care, there is
a bypass to drawPixel that lets you draw in 24bit color.

Now, SmartMatrix comes with a much fancier API with multiple layers (used for scrolling on top of drawings),
better color resolution, and many more things. It's just a better API all around, but it is not compatible with
Adafruit::GFX code.  
This is where https://github.com/marcmerlin/SmartMatrix_GFX comes in: it adds Adafruit::GFX support to SmartMatrix.
Similarly, you can use https://github.com/mrfaptastic/ESP32-RGB64x32MatrixPanel-I2S-DMA which also offers GFX support
to a more limited set of RGB panels but with DMA support on ESP32 (read below for differences).

FastLED is not a 2D API per se, but used along with https://github.com/marcmerlin/FastLED_NeoMatrix you can get GFX API
support while adding FastLED primitives like nscale and fade.  
SmartMatrix_GFX adds support for both GFX and FastLED API support to the SmartMatrix backend.

If you will ever only use SmartMatrix, you should use its superior API.  
If you'd like to be compatible with other backends, including better FastLED supported matrices (Neopixels and better
addressable LEDs don't flicker, are brighter and easier to drive), and the GFX API is good enough for you, you should use
it, along with SmartMatrix::GFX and you'll be able to trivially port your code to many other hardware backends.

For an example of the same code on multiple GFX backends:
- https://github.com/marcmerlin/LED-Matrix/blob/master/examples/directmatrix8x8_tricolor_direct_sr/directmatrix8x8_tricolor_direct_sr.ino
- https://github.com/adafruit/Adafruit_NeoMatrix/tree/master/examples/MatrixGFXDemo
- https://github.com/adafruit/RGB-matrix-Panel/blob/master/examples/PanelGFXDemo_16x32/PanelGFXDemo_16x32.ino- 
- https://github.com/marcmerlin/FastLED_NeoMatrix/tree/master/examples/MatrixGFXDemo
- https://github.com/mrfaptastic/ESP32-RGB64x32MatrixPanel-I2S-DMA/blob/master/examples/PanelGFXDemo/PanelGFXDemo.ino
- https://github.com/marcmerlin/SmartMatrix_GFX/tree/master/examples/MatrixGFXDemo


Adafruit_RGB_matrix_Panel vs SmartMatrix vs ESP32-RGB64x32MatrixPanel-I2S-DMA vs SmartMatrix_GFX 
------------------------------------------------------------------------------------------------
The first 3 libraries all support HUB75 RGB Panels, although not in the same way. 

- https://github.com/adafruit/RGB-matrix-Panel is the original library from Adafruit. It uses bit banging, offers 4bits per pixel and is hardcoded in assembly for some older arduino chips (arduino 328p, ATmega). It is limited to single RGB Panels (16x32 and 32x32) and mostly older and slower arduino chips. This lib does not work with newer faster chips (teensy, ESP8266, ESP32), 64x64 panels with E address line, or chained panels.  
This Adafruit library of course supports the Adafruit::GFX backend, allowing you to reuse your GFX code on all backends that support it. See above.  
https://github.com/sparkfunX/RGBmatrixPanelHalfScan is an alternate library for an odd sized 32x32 1/8th scan panel.


- https://github.com/mrfaptastic/ESP32-RGB64x32MatrixPanel-I2S-DMA offers a totally different approach to offering
Adafruit::GFX on RGB panels. It uses DMA on ESP32 to do mostly CPU free updates. It is a proof of concept that only offers
64x32 as of right now, but could be extended to more. Contrary to SmartMatrix it does full frame PWM (SmartMatrix does line
level PWM which can yield different artifacts on camera).  
Color depth is only 4 bits per pixel compared to 8bpp or higher on SmartMatrix, but again for most things, it's sufficient. 
This library is ESP32 only.

- https://github.com/pixelmatix/SmartMatrix is the fanciest RGB Panel library by far. It however does not offer GFX API
compatibility. Its API however offers much more, and hardware-wise, it supports most RGB Panels out there (including 64x64
with E address line and panel chaining up to at least a total resolution of 128x128).  
SmartMatrix was written for teensy (teensy 3.5 or 3.6 greatly recommended for panels 64x64 or bigger), however its teensylc
branch actually supports ESP32. See https://community.pixelmatix.com/t/smartmatrix-library-esp32-port/272

- https://github.com/marcmerlin/SmartMatrix_GFX is not a hardware support library, it adds a FastLED and Adafruit::GFX
support to SmartMatrix. Because of SmartMatrix' heavy use of C++ templates, making it seemingly impossible to inherit the
code in a library, SmartMatrix::GFX creates its own FastLED style virtual framebuffer in which graphics are rendered as if
you were using FastLED::NeoMatrix and then each frame is then handed over to SmartMatrix pixel by pixel. It's not that
efficient since it doubles the RAM needed to store graphics, but it still works fine and doesn't matter too much on chips 
like ESP32 that have more RAM anyway.

Microcontroller support and level shifters
------------------------------------------
If you use the newer and faster microcontrollers, they are 3.3V and it is greatly recommended that you use level shifters 
(74HCT245 or equivalent).

- If you are using older 16 bits microcontroller, you can only use the Adafruit RGB-matrix-Panel driver. The chips are 5V,
so you don't need level shifters.

- If you are using teensy (3.x), you should use SmartMatrix, and can use SmartMatrix::GFX on top. You can use this excellent
shield that includes level shifters: https://docs.pixelmatix.com/SmartMatrix/shieldref.html

- If you are using ESP32, you can use SmartMatrx/SmartMatrix::GFX or ESP32-RGB64x32MatrixPanel-I2S-DMA . You should then use 
this shield to get level shifters: https://www.evilgeniuslabs.org/hexadecimal-nodemcu-32s-wi-fi-and-ble-led-controller . t
does not plug directly into the RGBpanel, but at least you can wire directly to the level shifters and not worry about the
ever changing pin order of the ESP32 chips.
