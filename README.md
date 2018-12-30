SmartMatrix GFX, Control Scan Based Matrices with SmartMatrix and Adafruit GFX API
==================================================================================

Adafruit::GFX compatible library for scan based matrices.
This library requires SmartMatrix and Adafruit_GFX libraries.

Example code: https://github.com/marcmerlin/SmartMatrix_GFX/blob/master/examples/MatrixGFXDemo/MatrixGFXDemo.ino

This code was taken from FastLED_NeoMatrix and adapted to work with the SmartMatrix library. SmartMatrix is used to drive row scan panels. They are not as good as NeoPixel based panels which you can run with FastLED::NeoMatrix instead, but you should consider SmartMatrix driven panels if one of those reasons apply to you:
* They are cheaper given that the pixels do not have logic (they also don't stay on unless you keep refreshing them)
* One big reason to use them is that you can have much higher density (2.5 to 5mm per pixel vs 10mm for the typical neopixel matrix)
* scan panels are 50 to 70% cheaper per pixel than neopixel based matrices.

That being said, I do recommend that you use Neopixel matrices whenever you can as for their much better display quality, brightness, and being easier to drive, but if you decide to use scan based matrices for the reasons above and you'd like Adafruit::GFX compatibility, then this library is for you.

It also offers FastLED compatibility if you'd like to use those primitives against your virtual display (like nblend, fade, etc...).
