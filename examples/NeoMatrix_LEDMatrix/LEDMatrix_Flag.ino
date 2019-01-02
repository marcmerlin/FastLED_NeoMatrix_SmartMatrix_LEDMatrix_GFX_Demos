#define LEDMATRIX
#include "config.h"


void ledmatrix_setup()
{
    Serial.println("ledmatrix setup");
    ledmatrix.DrawLine (0, 0, ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(0, 255, 0));
    ledmatrix.DrawPixel(0, 0, CRGB(255, 0, 0));
    ledmatrix.DrawPixel(ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(0, 0, 255));
    matrix->show();
    Serial.println("ledmatrix setup done");
}


void flag()
{
    matrix->clear();
    ledmatrix.DrawFilledRectangle(0, 0, ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(0, 0, 255));
    ledmatrix.DrawRectangle(0, 0, ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(255, 255, 255));
    ledmatrix.DrawLine(0, 0, ledmatrix.Width() - 1, ledmatrix.Height() - 1, CRGB(255, 255, 255));
    ledmatrix.DrawLine(0, 1, ledmatrix.Width() - 1, ledmatrix.Height() - 2, CRGB(255, 255, 255));
    ledmatrix.DrawLine(0, ledmatrix.Height() - 1, ledmatrix.Width() - 1, 0, CRGB(255, 255, 255));
    ledmatrix.DrawLine(0, ledmatrix.Height() - 2, ledmatrix.Width() - 1, 1, CRGB(255, 255, 255));
    matrix->show();
}
