#define LEDMATRIX
#include "neomatrix_config.h"
#include <LEDText.h>
//#include <Font12x16.h>
#include <ComicSansP24.h>
//#include <FontMatrise.h>

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

#define LED_GREEN_HIGH 		(63 << 5)  
#define LED_RED_HIGH 		(31 << 11)
#define LED_BLUE_HIGH 		31
#define LED_ORANGE_HIGH		(LED_RED_HIGH    + LED_GREEN_HIGH)

void setup()
{
    matrix_setup();
    // Reset ILI9341 after it was mis-set by SSD1331 init
    tft_[0]->begin();

    ScrollingMsg.SetFont(ComicSansP24Data);
    ScrollingMsg.Init(&ledmatrix1, mw1, ScrollingMsg.FontHeight() + 1, 0, 0);
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
    ScrollingMsg.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
    Options = INSTANT_OPTIONS_MODE;
    ScrollingMsg.SetOptionsChangeMode(Options);
}

void LEDTextScroll() {
    FastLED_ArduinoGFX_TFT *matrix = matrix_[0];
    if (ScrollingMsg.UpdateText() == -1)
    {
	ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
	Options ^= INSTANT_OPTIONS_MODE;
	ScrollingMsg.SetOptionsChangeMode(Options);
    }
    else
    {
	matrix->show();
	//delay(30);
    }
}

void loop()
{
    matrix = matrix_[1];
    uint16_t mw = mw2;
    uint16_t mh = mh2;

    uint8_t size = max(int(mw/8), 1);
    matrix->clear();
    matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely

    matrix->setRotation(3);
    matrix->setTextSize(size);
    matrix->setTextColor(LED_BLUE_HIGH);
    for (int16_t x=8*size; x>=-6*8*size; x--) {
	matrix->clear();
	matrix->setCursor(x,mw/2-size*4);
	matrix->print("Rotate");
	matrix->show();
	// note that on a big array the refresh rate from show() will be slow enough that
	// the delay become irrelevant. This is already true on a 32x32 array.
        //delay(50/size);
	LEDTextScroll();
    }
}
