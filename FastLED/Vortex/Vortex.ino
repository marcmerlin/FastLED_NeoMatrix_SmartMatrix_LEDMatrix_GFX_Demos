#include "neomatrix_config.h"

#define leds matrixleds

class Vortex {
    int x = 0;
    int y = 0;
    int right = 1;
    int up = 0;
    int w = mw - 1;
    int h = mh - 1;
    int margin = 0;
    int hue;

  public:
    Vortex() {

    }

    void vortex() {
      leds[ XY(x, y)]  = CHSV(hue, 255, 255);
      // End of right
      if ((x >= (w - margin)) && (up == 0)) {
        up = 1;
        right = 0;
          //    vortexHue += 15;
      }
      // End of up
      else if ((y >= (h - margin)) && (up == 1)) {
        up = 0;
        right = -1;
        //    vortexHue += 15;
      }
      // End of left
      else if ((x == (0 + margin)) && (up == 0 && right == -1)) {
        up = -1;
        right = 0;
        //    vortexHue += 15;
      }
      // End of down
      else if ((x == (0 + margin) && y == (1 + margin)) && (up == -1 && right == 0)) {
        y += up;
        up = 0;
        right = 1;
        hue += 15;
        margin++;
        y++;
      }

      // Final LED
      if (right == 0 && up == -1 && margin == ( (mh / 2) - 1)) { // >=
        //delay(5000);
        hue = random(0, 255);
        margin = 0;
        x = -1;
        y = 0;
        right = 1;
        up = 0;
      }

     // Option toggle?
      //  fadeLightBy(leds, (mw * mh), 20); 
      x += right;
      y += up;
    }
};

#define SNAKE_GAP 30
#define NUM_SNAKES ((NUM_LEDS / SNAKE_GAP) / 2)
Vortex vortexs[NUM_SNAKES];

int vortexsStarted = 1;
//int const vortexDelay = ((mw * 2) + (mh * 2) - 1);
int const vortexDelay = SNAKE_GAP * 2;
int vortexGap = 0;

void vortex() {

  if (vortexsStarted < NUM_SNAKES) {
    if (vortexGap == vortexDelay)  {
      vortexsStarted++;
      vortexGap = 0;
    }
    else {
      vortexGap++;
    }
  }

  for (int  i = 0; i < vortexsStarted; i++) {
    vortexs[i].vortex();
  }
  fadeToBlackBy(leds, (mw * mh), 55); // TWEAK ME
  //FastLED.delay(20);
  EVERY_N_SECONDS(10) {
    Serial.println(FastLED.getFPS());
  }
}



void loop()
{
  vortex();
  matrix->show();
}


void setup() {
  matrix_setup();
}
