// By Marc MERLIN <marc_soft@merlins.org>
// License: Apache v2.0
//

#include <Adafruit_GFX.h>
#include <SmartMatrix_GFX.h>
#include <FastLED.h>
#include "fonts.h"
#include "neomatrix_config.h"


int8_t matrix_loop = -1;
uint8_t matrix_reset_demo = 1;

// ---------------------------------------------------------------------------
// Shared functions
// ---------------------------------------------------------------------------

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
    uint32_t wheel=0;

    // Serial.print(WheelPos);
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
	wheel = (((uint32_t)(255 - WheelPos * 3)) << 16) + (WheelPos * 3);
    }
    if (!wheel && WheelPos < 170) {
	WheelPos -= 85;
	wheel = (((uint32_t)(WheelPos * 3)) << 8) + (255 - WheelPos * 3);
    }
    if (!wheel) {
	WheelPos -= 170;
	wheel = (((uint32_t)(WheelPos * 3)) << 16) + (((uint32_t)(255 - WheelPos * 3)) << 8);
    }
    // Serial.print(" -> ");
    // Serial.println(wheel, HEX);
    return (wheel);
}

// ---------------------------------------------------------------------------
// Matrix Code
// ---------------------------------------------------------------------------
// How many ms used for each matrix update
#define MX_UPD_TIME 10
#define matrix_show matrix->show

// type 0 = up, type 1 = up and down
// The code is complicated looking, but the state machine is so that
// you can call this function to do a frame update and then switch to 
// other work
// There are some magic numbers I had to hand tune for a 24x32 array.
// You'll have to adjust for your own array size
uint8_t font_zoom(uint8_t zoom_type, uint8_t speed) {
    static uint16_t direction;
    static uint16_t size;
    static uint8_t l;
    static int16_t faster = 0;
    static bool dont_exit;
    static uint16_t delayframe;
    const char letters[] = { 'T', 'F', 'S', 'F' };
    bool done = 0;
    uint8_t repeat = 4;

    if (matrix_reset_demo == 1) {
	matrix_reset_demo = 0;
	direction = 1;
	size = 3;
	l = 0;
	if (matrix_loop == -1) { dont_exit = 1; delayframe = 2; faster = 0; };
	matrix->setTextSize(1);
    }


    if (--delayframe) {
	// reset how long a frame is shown before we switch to the next one
	// Serial.println("delayed frame");
	delay(MX_UPD_TIME);
	return repeat;
    }
    delayframe = max((speed / 10) - faster , 1);
    // before exiting, we run the full delay to show the last frame long enough
    if (dont_exit == 0) { dont_exit = 1; return 0; }
    if (direction == 1) {
	int8_t offset = 0; // adjust some letters left or right as needed
	matrix->clear();
	matrix->setFont( &Century_Schoolbook_L_Bold[size] );
	if (mw >= 48 && mh >=64) {
	    matrix->setPassThruColor(0xD7E1EB);
	    matrix->setCursor(10-size*0.55+offset, 36+size*0.75);
	    matrix->print("TF");
	    matrix->setPassThruColor(0x05C1FF);
	    matrix->setCursor(24-size*0.55+offset, 68+size*0.75);
	    matrix->print("SF");
	} else {
	    if (letters[l] == 'T') offset = -2 * size/15;
	    if (letters[l] == '8') offset = 2 * size/15;

	    matrix->setPassThruColor(Wheel(map(letters[l], '0', 'Z', 255, 0)));


    #ifdef M32B8X3
	    matrix->setCursor(10-size*0.55+offset, 17+size*0.75);
    #else
	    matrix->setCursor(3*mw/6-size*1.75+offset, mh*7/12+size*1.60);
    #endif
	    matrix->print(letters[l]);
	}
	matrix->setPassThruColor();
	if (size<18) size++;
	else if (zoom_type == 0) { done = 1; delayframe = max((speed - faster*10) * 1, 3); }
	     else direction = 2;

    } else if (zoom_type == 1) {
	int8_t offset = 0; // adjust some letters left or right as needed

	matrix->clear();
	matrix->setPassThruColor(Wheel(map(letters[l], '0', 'Z', 64, 192)));
	matrix->setFont( &Century_Schoolbook_L_Bold[size] );
	if (mw >= 48 && mh >=64) {
	    matrix->setPassThruColor(0xD7E1EB);
	    matrix->setCursor(10-size*0.55+offset, 36+size*0.75);
	    matrix->print("TF");
	    matrix->setPassThruColor(0x05C1FF);
	    matrix->setCursor(24-size*0.55+offset, 68+size*0.75);
	    matrix->print("SF");
	} else {
	    if (letters[l] == 'T') offset = -2 * size/15;
	    if (letters[l] == '8') offset = 2 * size/15;

    #ifdef M32B8X3
	    matrix->setCursor(10-size*0.55+offset, 17+size*0.75);
    #else
	    matrix->setCursor(3*mw/6-size*1.75+offset, mh*7/12+size*1.60);
    #endif
	    matrix->print(letters[l]);
	}   
	matrix->setPassThruColor();
	if (size>3) size--; else { done = 1; direction = 1; delayframe = max((speed-faster*10)/2, 3); };
    }

    matrix_show();
    //Serial.println("done?");
    if (! done) return repeat;
    direction = 1;
    size = 3;
    //Serial.println("more letters?");
    if (++l < sizeof(letters)) return repeat;
    l = 0;
    //Serial.println("reverse pattern?");
    if (zoom_type == 1 && direction == 2) return repeat;

    //Serial.println("Done with font animation");
    faster++;
    matrix_reset_demo = 1;
    dont_exit =  0;
    // Serial.print("delayframe on last letter ");
    // Serial.println(delayframe);
    // After showing the last letter, pause longer
    // unless it's a zoom in zoom out.
    if (zoom_type == 0) delayframe *= 5; else delayframe *= 3;
    return repeat;
}


void loop() {
    uint8_t ret;
    static uint8_t cnt = 0;

    delay(5);
    // this code is meant to be run at some interval and keep its on
    // state while you do something else.
    
    if (cnt % 2) {
	ret = font_zoom(1, 25);
    } else {
	ret = font_zoom(0, 30);
    }
    if (matrix_loop == -1) matrix_loop = ret;
    if (ret) return;
    Serial.print("Finished run #");
    Serial.println(matrix_loop);
    if (matrix_loop-- > 0) return;
    Serial.println("Animation loop done, switching to other demo");
    cnt++;
    //delay(1000);
    matrix_reset_demo = 1;
}


void setup() {
    delay(1000);
    Serial.begin(115200);

    matrix_setup();
    matrix->setTextWrap(false);
    if (mw >= 48 && mh >=64) matrix->setTextSize(2);
}

// vim:sts=4:sw=4
