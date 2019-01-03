Matrix Demos here use FastLED + LEDMatrix API

They were designed for
https://github.com/AaronLiddiment/LEDMatrix
or its fork that supports tiled matrices:
https://github.com/Jorgen-VikingGod/LEDMatrix
Both those libs support an Adafruit::GFX like API while not being a real GFX
while being a 24bit color re-implementation of that lib (while 
https://github.com/marcmerlin/FastLED_NeoMatrix inherits from the Adafruit
lib and adds 24bit bypass calls to support 24bit color too).

Both FastLED::NeoMatrix and SmartMatrix::GFX are compatible with
LEDMatrix via the initialization in config.h (#define LEDMATRIX before
including config.h), and therefore also support these demos.

* https://github.com/marcmerlin/FastLED_NeoMatrix
* https://github.com/marcmerlin/SmartMatrix_GFX


