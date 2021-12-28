Shows how to run 2 different TFTs with Framebuffer::GFX and neomatrix_config.h
Demo: https://youtu.be/LFIMByo7HCU

To be clear, you don't need to add FrameBuffer::GFX or https://github.com/marcmerlin/FastLED_ArduinoGFX_TFT
to run Adafruit::GFX code, but you do need it for 24bit FastLED and LEDMatrix code, which is what is running
on the bottom screen.
