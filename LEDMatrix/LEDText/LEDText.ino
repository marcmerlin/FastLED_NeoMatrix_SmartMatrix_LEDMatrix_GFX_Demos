#define LEDMATRIX
#ifndef ARDUINOONPC
// Replace this with another backend if you wish
#define ILI9341
#endif
#include "neomatrix_config.h"
#include <LEDText.h>
//#include <Font12x16.h>
//#include <FontMatrise.h>
//#include <ComicSansP24.h>
#include <font36.h>


cLEDText ScrollingMsg;

const unsigned char TxtDemo[] = { EFFECT_FRAME_RATE "\x00"
                                  EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff"
                                  EFFECT_SCROLL_LEFT "   The "
                                  EFFECT_SCROLL_UP "Quick "
                                  EFFECT_SCROLL_LEFT "Brown "
                                  EFFECT_SCROLL_DOWN "Fox"
                                  EFFECT_SCROLL_LEFT " Jumps "
                                  EFFECT_SCROLL_UP "Over  "
                                  EFFECT_SCROLL_LEFT "The "
                                  EFFECT_SCROLL_DOWN "Lazy  "
                                  EFFECT_SCROLL_LEFT "Dog " };
uint16_t Options;

void setup()
{
    matrix_setup();

    matrix->clear();

    //ScrollingMsg.SetFont(MatriseFontData);
    //ScrollingMsg.SetFont(ComicSansP24Data);
    //ScrollingMsg.SetFont(FontArial59x56Data);
    ScrollingMsg.SetFont(FontArialP59x56Data);
    ScrollingMsg.Init(&ledmatrix, mw, ScrollingMsg.FontHeight() + 1, 0, 0);
    //ScrollingMsg.Init(&ledmatrix, mw, mh, 0, 0);
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
    //Options = INSTANT_OPTIONS_MODE;
    ScrollingMsg.SetOptionsChangeMode(Options);
}


void loop()
{
    if (ScrollingMsg.UpdateText() == -1)
    {
	ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
	//Options ^= INSTANT_OPTIONS_MODE;
	ScrollingMsg.SetOptionsChangeMode(Options);
    }
    else
    {
	matrix->show();
	delay(30);
    }
}
