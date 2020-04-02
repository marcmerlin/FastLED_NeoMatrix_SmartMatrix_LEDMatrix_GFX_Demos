/*
   64 x 64 matrix /  LED Table code:
   By Mark Estes
   Copyright (c) 2019 Mark Estes

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// --------------------------- Config Start --------------------------------
// Randomly slowdown animation. Nice in principle, but not when debugging performance
//#define RANDOMSLOWME

// Control whether pattern order is random from the start or after one pass
//#define MIXIT_AFTER_FIRST_PASS
// mixit = true;

#define SHOW_PATTERN_NUM

// This allows a selection of only my favourite patterns.
// Comment this out to get all the patterns -- merlin
//#define BESTPATTERNS
#ifdef BESTPATTERNS
// 82 and 89 are similar     55 and 102 are similar
uint8_t bestpatterns[] = {
   3, 8, 14, 17, 26, 55, 58, 59, 61, 69, 72, 82, 102, 109, 111, 132,
   4, 10, 11, 25, 67, 70, 73, 77, 80, 86, 104, 105, 110,    // good in original tmed
   20, 89, 94, 101, 124, 128, 134, 143, 145, 155,// good but not picked for Neomatrix
};
#define numbest           sizeof(bestpatterns)
#define lastpatindex numbest
#else
#define lastpatindex mpatterns
#endif

// very nice rain going sideways
// Case: 69  drops with effects , Adjunct 3 wind: 56 fancy: 14 afancy: 9 fader: 2Flop-0:  1, Flop-1:  1, Flop-2:  0, Flop-3:  0, Flop-4:  1, Flop-5:  1, Flop-6:  0, Flop-7:  0, Flop-8:  1, Flop-9:  0,
// Case: 79  stars3,
//  Case: 142  Crazy Snow, ?
//  Case: 60  fireball with horizontal mirror
// Case: 99  , Adjunct 8
// Case: 104  circlearc
// Case: 66  hypnoduck
//  Case: 149  VORTEX but only with wide circles and faster speed
//  Case: 60  fireball,
//  Case: 114  drops with wind , Adjunct 5
//  Case: 92  DRIP2 ,
//  Case: 130 spin2 but consider removing the occasional fade
// --------------------------- Config End ----------------------------------


#define LEDMATRIX
#include "matrix.h"
//#include "neomatrix_config.h"
#define zeds ledmatrix
#include "Effects.h"
#include "Drawable.h"
#include "Boid.h"
#include "Attractor.h"
#include "Geometry.h"
#include "PatternAttract.h"
PatternAttract attract;
#include "PatternBounce.h"
PatternBounce bounce;
#include "PatternCube.h"
PatternCube cube;
#include "PatternFlock.h"
PatternFlock flock;
#include "PatternFlowField.h"
PatternFlowField flowfield;
#include "PatternIncrementalDrift.h"
PatternIncrementalDrift incrementaldrift;
#include "PatternIncrementalDrift2.h"
PatternIncrementalDrift2 incrementaldrift2;
#include "PatternPendulumWave.h"
PatternPendulumWave pendulumwave;
#include "PatternRadar.h"
PatternRadar radar;
#include "PatternSpiral.h"
PatternSpiral spiral;
#include "PatternSpiro.h"
PatternSpiro spiro;
#include "PatternSwirl.h"
PatternSwirl swirl;
#include "PatternWave.h"
PatternWave wave;

AuroraDrawable* items[] = {
  &attract,//0
  &bounce,//1
  &cube,//2
  &flock,//3
  &flowfield,//4
  &incrementaldrift,//5
  &incrementaldrift2,//6
  &pendulumwave,//7
  &radar,//8
  &spiral,//9
  &spiro,//10
  &swirl,//11
  &wave,//12
};
AuroraDrawable *patternz;
int8_t item = random(13);

#define MIDLX               (MATRIX_WIDTH/2)
#define MIDLY               (MATRIX_HEIGHT/2)
#define THREEHAVES          (MATRIX_WIDTH * 3 / 2)
#define THREEQUARTERS       (MIDLX * 3 / 2)
#define QUARTER              (MIDLX / 2)
#define mpatterns           (175)// max number of patterns

#define TIMING             120//seconds per pattern

#define  BallCount          14


//int countdownMS = Watchdog.enable(4000);
int16_t pattern = 0;//this picks the pattern to start with...
int16_t   afancy, velo = 30 , pointyfix=4, fpeed[MATRIX_WIDTH * 2], targetfps = 40;
int16_t  how, cool, sparky = 90, ccc, xxx, yyy, dot = 3, radius2, rr, adjunct = 3;

// FIXME(MarkEstes): arrays take space, it would be nice to reuse the same arrays for some demos.
// These arrays can all have values indexed on width or height, which means they can go higher than 256
// if width or height are bigger than 256.
uint16_t fcount[MATRIX_WIDTH * 2], fvelo[MATRIX_WIDTH * 2], fcolor[MATRIX_WIDTH * 2];
// this was defined as byte, -128 to 127, not related to array size.
int8_t fcool[MATRIX_WIDTH * 2], fcountr[MATRIX_WIDTH * 2], xpoffset[MATRIX_WIDTH * 2], xvort[MATRIX_WIDTH * 2], yvort[MATRIX_WIDTH * 2];
// TOOD(merlin)): share heatz array with another one from aurora to save space
//int8_t heatz[MATRIX_WIDTH][MATRIX_HEIGHT];
// re-use array from aurora to avoid duplicating memory usage requirements.
#define heatz noise
boolean rimmer[MATRIX_WIDTH * 2], xbouncer[MATRIX_WIDTH * 2], ybouncer[MATRIX_WIDTH * 2];

int16_t maxiq,  pointy,  hue, steper,  xblender, hhowmany, blender = 120, radius3,  ccoolloorr,  h = 0,  howmany, xhowmany;
int16_t dot2 = 6, sdot, phew, raad, lender = 128, xsizer, ysizer, xx,  yy, flipme = 1, shifty = 4,  poffset, wind = 2, fancy , sinewidth, mstep,  inner, bfade = 3;
int  directn = 1, quash = 5, quiet = 0, waiter = 7;

uint32_t  counter, ringdelay, bringdelay, firedelay, hitcounter;
int16_t slowest = 5, fastest = 20;
boolean  flop[10] , ringme = false, blackringme = false, nextsong = false;

boolean mixit = false, slowme = false;
uint64_t lasttest, lastmillis, dwell = 120000;
float  mscale = 1.4, fps = 30, Gravity = -9.81;
float radius, xslope[MATRIX_WIDTH * 2], yslope[MATRIX_WIDTH * 2], xfire[MATRIX_WIDTH * 2], yfire[MATRIX_WIDTH * 2], cangle, sangle;
float locusx, locusy, driftx, drifty, xcen, ycen, yangle, xangle, eeksangle, whyangle;

int StartHeighty = 1, Positiony[BallCount], Positionx[BallCount];
float Heighty[BallCount], ImpactVelocityStart = sqrt( -2 * Gravity * StartHeighty ), ImpactVelocity[BallCount], TimeSinceLastBounce[BallCount], Dampening[BallCount];
long  ClockTimeSinceLastBounce[BallCount];

// Arduino gcc may allow referencing functions before they are defined,
// but gcc in ArduinoOnPC, does not, so copy all the signatures here.
void newpattern();
void whatami();
void runpattern();
void Diamondhole();
void Inca(int16_t brit);
void Ringo();
void tuber2();
void diagonally();
void Roundhole();
void drifter();
void volcano(int16_t brit);
void pyrimid();
void solidpyrimid();
void solid2(int16_t brit);
void solid3(int16_t brit);
void solid4();
void solid(int16_t brit);
void solid5();
void solid6(int16_t klr);
void fuzzy();
void corner();
void tuber();
void fireball();
void fireworks();
void streaker();
void ringer();
void bkringer();
void sinx();
void drip();
void mirror();
void roger();
void rogerv();
void confetti();
void confetti3();
void confetti4();
void confetti2();
void bubbles();
void bubbles2();
void tinybubbles();
void koi();
void squarebubbles();
void starbubbles88();
void tinybubbles2();
void tinybubbles3();
void sticks();
void Bargraph();
void adjustme();
void spire2();
void spire3();
void spire();
void triple();
void siny();
void whitewarp();
void warp();
void spiralz();
void spiral2();
void spiral3();
void lfado(int16_t bbc);
void redfado(int16_t bbc);
void greenfado(int16_t bbc);
void bluefado(int16_t bbc);
void xspin();
void spin2();
void magictime();
void rmagictime();
void splat();
void bouncez();
void starbounce();
void triforce();
void seasick3();
void seasickness();
void seasick2();
void seasick();
void seasick4();
void seasick5();
void smile();
void smile2();
void smile4();
void smile3();
void hypnoduck();
void hypnoduck2();
void hypnoduck3();
void hypnoduck4();
void starer();
void bkstarer();
void triangler();
void boxer();
void bkboxer();
void homer();
void homer2();
void homer3();
void nringer(int16_t i);
void drawtriangle();
void triangle(int16_t xloc, byte yloc, byte bigg, byte angle, byte kolor);
void drawstar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler);
void whitestar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler);
void starz();
void starz3();
void starz2();
void spoker();
void spoker3();
void circlearc();
void wheelz();
void wheelz2();
void swirlz();
void swirl2();
void swirl3();
void swirl4a();
void swirl4();
void swirl5();
void drops();
void drips();
void twister();
void slowmo();
void dualwind();
void scales();
void eastwestwind();
void spiralwind();
void BouncingBalls(int Ballz);
void Bouncingtri(int Ballz);
void snow(int16_t ccc);
void VORTEX();
void Fire();

void setup()
{
  matrix_setup();
  Serial.println("Reset");
#ifdef BESTPATTERNS
  pattern = bestpatterns[0];
#endif
  // WARNING: make sure that none of those pins are used by SmartMatrix, or the output will be broken
#ifndef ARDUINOONPC
  randomSeed(analogRead(1) - analogRead(2) + analogRead(5));
#endif
  driftx = random8(4, MATRIX_WIDTH - 4);//set an initial location for the animation center
  drifty = random8(4, MATRIX_HEIGHT - 4);// set an initial location for the animation center
  mstep = int16_t( 256 / min((MATRIX_WIDTH - 1), 255)); //mstep is the step size to distribute 256 over an array the width of the matrix
  steper = random8(2, 8);// steper is used to modify h to generate a color step on each move
  lastmillis = millis();
  lasttest = millis();
  hue = random8();//get a starting point for the color progressions
  mscale = 2.2;
  //Watchdog.reset();
  cangle = (sin8(random(25, 220)) - 128.0) / 128.0;//angle of movement for the center of animation gives a float value between -1 and 1
  sangle = (sin8(random(25, 220)) - 128.0) / 128.0;//angle of movement for the center of animation in the y direction gives a float value between -1 and 1

  whatami();//this prints out the current status of stuff
 // Watchdog.reset();
  smile2();// make one frame of the smile 2 pattern
  matrix->show();
  delay(2000);
  effects.leds = matrixleds;
  effects.Setup();
  // delay(1000);
}

char readchar;

void loop()
{
 // Watchdog.reset();

  hue += 1;//increment the color basis
  h = hue;  //set h to the color basis
  if (counter % shifty == 0) driftx =  driftx + cangle;//move the x center every so often
  if (driftx > (MATRIX_WIDTH - QUARTER ))//change directin of drift if you get near the right 1/4 of the screen
    cangle = 0 - abs(cangle);
  if (driftx < QUARTER )//change directin of drift if you get near the right 1/4 of the screen
    cangle = abs(cangle);
  if ((counter + shifty / 2) % shifty == 0) drifty =  drifty + sangle;//move the y center every so often
  if (drifty > ( MATRIX_HEIGHT - MIDLY / 2))// if y gets too big, reverse
    sangle = 0 - abs(sangle);
  if (drifty < MIDLY / 2) {// if y gets too small reverse
    sangle = abs(sangle);
  }

  driftx = constrain(driftx, MIDLX / 4, MATRIX_WIDTH - MIDLX / 4);//constrain the center, probably never gets evoked any more but was useful at one time to keep the graphics on the screen....
  drifty = constrain(drifty, MIDLY / 4, MATRIX_HEIGHT - MIDLY / 4);
  // test for frame rate,  every 8 frames
  if (counter % 8 == 0) {
    fps = 8000.00 / (millis() - lasttest);
    lasttest = millis();

    // adjust frame rate if it is too high or low
    if (fps > targetfps)
      waiter++;

    if (fps > targetfps + 11)
      waiter += 3;

    if (fps > targetfps + 25)
      waiter += 3;

    if (fps <= targetfps && waiter > 0)
      waiter--;

    if (fps <= targetfps - 11 && waiter > 3)
      waiter -= 3;

    if (fps <= targetfps - 25 && waiter > 3)
      waiter -= 3;
  }

  // this calls the pre frame fade,based on a int16_t "bfade" which is mostly random, but sometimes assignes for a specific effect
  switch (bfade)
  {
    case 0:
      break;
    case 1:
      lfado(10);
      break;
    case 2:
      lfado(20);
      break;
    case 3:
      lfado(30);
      break;
    case 4:
      lfado(40);
      break;
    case 5:
      lfado(50);
      break;
    case 6:
      redfado(16 + (random8() >> 3));
      break;
    case 7:
      greenfado(16 + (random8() >> 3));
      break;
    case 8:
      bluefado(16 + (random8() >> 3));
      break;

    case 98:
      break;
    case 99:

      lfado(2); //almost none  2/256 or 3.1%
      break;
    case 100:

      lfado(4); //almost none  2/256 or 3.1%
      break;
    case 101:

      lfado(8); //almost none  6/256 or 4.6%
      break;

    case 102:

      lfado(12); //almost none  6/256 or 4.6%
      break;

    case 103:

      lfado(16); //almost none  6/256 or 4.6%
      break;

    case 104:

      lfado(24); //almost none  6/256 or 4.6%
      break;

    case 105:

      lfado(32); //almost none  6/256 or 4.6%
      break;

    case 106:
      bluefado(8);
      break;

    case 107:
      bluefado(16);
      break;
    case 108:
      bluefado(32);
      break;
    case 109:
      greenfado(16);
      break;
    case 110:
      greenfado(32);
      break;
    case 111:
      redfado(10);
      break;
    case 112:
      redfado(25);
      break;
    case 113:
      redfado(40);
      break;
    default:
      lfado(1 + (bfade << 4)); // 1 = 16,  4 = 64, this sets the amont of fade as a fraction over 256  range is 16/256 (6.25%) i.e. not much  to 64/256 (25%)or considerable
      break;
  }

  switch (fancy) {

    case 0:
      break;
    case 1:
      triangler();
      break;
    case 2:
      bkringer();
      break;
    case 3:
      bkstarer();
      break;
    case 4:
      boxer();
      break;
    case 5:
      bkboxer();
      break;
    case 6:
      starer();
      break;
    case 7:
      boxer();
      break;
    case 8:
      ringer();
      break;
    case 9:
      bkringer();
      ringer();
      break;
    case 10:
      bkringer();
      boxer();
      break;
    case 11:
      bkringer();
      starer();
      break;
    case 12:
      bkringer();
      triangler();
      break;
    case 13:
      bkboxer();
      ringer();
      break;
    case 14:
      bkboxer();
      boxer();
      break;
    case 15:
      bkboxer();
      starer();
      break;
    case 16:
      bkboxer();
      triangler();
      break;
    case 17:
      bkstarer();
      ringer();
      break;
    case 18:
      bkstarer();
      boxer();
      break;
    case 19:
      bkstarer();
      starer();
      break;
    case 20:
      bkstarer();
      triangler();
      break;
    case 21:
      nringer(counter % MATRIX_WIDTH);
      break;

    case 22:
      confetti2();
      break;

    case 23:
      confetti4();
      break;
    case 24:
      confetti();
      break;



    default:
      break;
  }
  switch (afancy) {
    case 1:
      adjunct = beatsin16(2, 0, 7, 0);
      break;
    case 2:
      adjunct = beatsin16(2, 7, 14, 0);
      break;
          case 3:
      adjunct = beatsin16(3, 4, 8, 0);
      break;
          case 25:
      bfade = beatsin16(2, 0, 5, 0);
      break;

    case 26:
      bfade = beatsin16(4, 98, 105, 0);
      break;
    case 27:
      bfade = beatsin16(2, 106, 113, 0);
      break;
    case 28:
      bfade = beatsin16(6, 0, 5, 0);
      break;
    case 29:
      bfade = beatsin16(5, 98, 105, 0);
      break;
    case 30:
      bfade = beatsin16(6, 106, 113, 0);
      break;
    default:
      break;
  }

  switch (wind)
  {
    case 0:
      break;
    case 1:
      zeds.ShiftUp();
      break;
    case 2:
      zeds.ShiftUp();
      zeds.ShiftRight();
      break;
    case 3:
      zeds.ShiftRight();
      break;
    case 4:
      zeds.ShiftRight();
      zeds.ShiftDown();
      break;
    case 5:
      zeds.ShiftDown();
      break;
    case 6:
      zeds.ShiftDown();
      zeds.ShiftLeft();
      break;
    case 7:
      zeds.ShiftLeft();
      break;
    case 8:
      zeds.ShiftUp();
      zeds.ShiftLeft();
      break;

    case 9:
      dualwind();
      break;

    case 10:
      eastwestwind();
      break;

    case 11:
      spiralwind();
      break;

    default:
      break;

  }
  if (slowme) slowmo();
  EVERY_N_SECONDS(9) {
    cangle = random(25, 85) / 100.0;
    sangle = random(25, 85) / 100.0;
    if (random8() > 128) cangle = -cangle;
    if (random8() > 128) sangle = -sangle;
    fcool[random(64)] = random (7, 25);
  }
  EVERY_N_SECONDS(13) {
    if (flop[4])
      blender += 4;
    // if (flop[6])
    //  velo -= 4;
    fcool[random(64)] = random (7, 27);
  }
  //EVERY_N_SECONDS(60) {
  //  noisetest();
  //}
  runpattern();//generate a updated screen
  counter++;//increment the counter which is used for many things
  matrix->show();
  delay(waiter);//frame rate control
  if (Serial.available()) readchar = Serial.read(); else readchar = 0;
  if (readchar > 31 || millis() > lastmillis + dwell || nextsong) //when to change patterns
  {
    Serial.print("  Actual FPS: ");
    Serial.println (fps, 2);
    newpattern();
  }
}

void newpattern()//generates all the randomness for each new pattern
{
  int16_t new_pattern = 0;
  // Allows keeping a pattern index for selecting bestof patterns
  static uint8_t local_pattern = 0;

#ifndef BESTPATTERNS
  local_pattern = pattern;
#endif

  if (readchar) {
    while ((readchar >= '0') && (readchar <= '9')) {
      new_pattern = 10 * new_pattern + (readchar - '0');
      readchar = 0;
      if (Serial.available()) readchar = Serial.read();
    }

    if (new_pattern) {
      Serial.print("Got new pattern via serial ");
      Serial.println(new_pattern);
    } else {
      Serial.print("Got serial char ");
      Serial.println(readchar);
    }
  }

  if (readchar == 'n') { local_pattern++; Serial.println("Serial => next"); }
  else if (readchar == 'p') { local_pattern--; Serial.println("Serial => previous"); }
  else if (!new_pattern) {
    // when set to true, plays the patterns in random order, if not, they increment, I start with increment and eventually flip this flag to make the progression random
    if (mixit) local_pattern = random(mpatterns); else local_pattern ++;
  }

#ifdef BESTPATTERNS
  // wrap around from 0 to last pattern.
  if (!new_pattern) {
    if (local_pattern >= 250) local_pattern = numbest-1;
    if (local_pattern >= numbest) local_pattern = 0;

    pattern = bestpatterns[local_pattern];
    Serial.print("Mapping best pattern idx ");
    Serial.print(local_pattern);
    Serial.print(" to ");
    Serial.println(pattern);
  }
#else
  if (local_pattern >= 250) local_pattern = lastpatindex-1;
  if (local_pattern >= lastpatindex) local_pattern = 0;

  pattern = local_pattern;
#endif
  if (new_pattern) pattern = new_pattern;
  // Skip missing patterns
  if ( pattern > 26 && pattern < 54) pattern = 54;
  if ( pattern == 64) pattern = 65;
  matrix->clear(); // without clear, some pattern transitions via blending look weird

  velo = 0; // random8()/2;
  nextsong = false;


  targetfps = random(slowest, fastest);
  bfade = random(0, 9);
  wind = random(70) ;
  fancy = random(80);
  afancy = random8();
  dot = random(2, 6);// controls the size of a circle in many animations
  dot2 = random(2, 6);
  adjunct = random(38);//controls which screen wide effect is used if any

  dwell = 1000 * (random(TIMING * 0.85, TIMING * 1.35)); //set how long the pattern will play
  ringdelay = random(30, 90);//sets how often one of the effects will happen
  bringdelay = random(70, 115);//sets how often one of the effects will happen
  counter = 0;// reset the counter with each new pattern
  steper = random(2, 8);//color tempo
  shifty = random(1, 5); //how often the drifter moves
  ccoolloorr = random8();
  blender = random8();
  for (int16_t g = 0; g < 10; g++) {
    flop[g] = false;
    if (random8() < 128)
      flop[g] = true;
  }
  cool = random (10, 18);
  for (int16_t i = 0; i < MATRIX_HEIGHT; i++)
    fcool[i] = random (9, 22);
  slowme = false;
#ifdef RANDOMSLOWME
  if (random8() > 74)
    slowme = true;
#endif
  hue += random(69);//picks the next color basis
  h = hue;
  // new drift factors for x and y drift
  cangle = random(20, 80) / 100.0;
  sangle = random(20, 80) / 100.0;
  if (random8() > 128) cangle = -cangle;
  if (random8() > 128) sangle = -sangle;

  whatami();//write to screen the lebels (if present) and set some parameters specific to the given pattern
}


void whatami()// set some parameters specific to the pattern and send some data to the serial port for trouble shooting/ tweaking
{
  lastmillis = millis();
  Serial.print(" Case: ");
  Serial.print(pattern);
  Serial.print("  ");
  switch (pattern)
  {
    case 0:
      Serial.print("Dhole "); //label
      //specify the screen effect as 2 which in this case means
      // HorizontalMirror() followed by VerticalMirror() if not specified,
      // it will be what ever was assigned randomly for this pattern
      adjunct = random(2, 5);
      break;

    case 1:
      Serial.print("Inca ");
      adjunct = random(2, 5);
      if (!flop[3] && !flop[4]) fancy = 0;
      break;

    case 2:
      Serial.print("Ringo ");
      fancy = random(10);
      break;

    case 3:
      Serial.print("Diag ");
      targetfps = 40;
      break;

    case 4:
      Serial.print("Rhole ");
      targetfps = 40;
      break;

    case 5:
      Serial.print("Drft ");
      targetfps = 40;
      break;

    case 6:
      adjunct = 0;
      bfade = 99;
      Serial.print("DRIP ");
      wind = 0;
      fancy = 0;
      break;

    case 7:
      Serial.print("Volc ");
      targetfps = 40;
      break;

    case 8:
      Serial.print("Pym ");
      targetfps = 80;
      wind = 0;
      shifty = 1;
      slowme = false;
      adjunct = random (2, 6);
      break;

    case 9:
      Serial.print("Pyms ");
      if (flop[1]) steper = steper * 2;
      wind = 0;
      slowme = false;
      shifty = 1;
      adjunct = random (2, 5);
      if (flop[4] || flop[5]) adjunct = 4;
      break;

    case 10:
      //  driftx = MIDLX;//pin the animation to the center
      //  drifty = MIDLY;
      Serial.print("Corn ");
      slowme = false;
      shifty = 1;
      adjunct = random (1, 8);
      break;

    case 11:
      adjunct = 0;
      targetfps = random(10, 40);
      Serial.print("Wt warp ");
      break;

    case 12:
      Serial.print("Fzy ");
      bfade = 0;
      targetfps = random (5, 15);
      fancy = 0;
      slowme = false;
      break;

    case 13:
      bfade = 1;
      //adjunct = 0;
      // fancy = 0;
      Serial.print("Conf ");
      wind = random(11);
      targetfps = random (5, 15);
      break;

    case 14:
      adjunct = 0;
      fancy = 0;
      targetfps = random (25, 55);
      Serial.print("spire2 ");
      break;

    case 15:
      Serial.print("streaker ");
      adjunct = 0;
      break;

    case 16:
      Serial.print("fireball ringer ");
      adjunct = 0;
      bfade = constrain(bfade, 1, 3);
      targetfps = 15;
      break;

    case 17:
      Serial.print("Warp ");
      adjunct = 0;
      targetfps = 15;
      break;

    case 18:
      adjunct = 0;
      Serial.print("Siny ");
      break;

    case 19:
      //adjunct = 0;
      Serial.print("Sinx ");
      targetfps = 20;
      break;

    case 20:
      adjunct = 0;
      Serial.print("triple ");
      targetfps = random(15, 30);
      bfade = random(3, 6);
      //  dot = 1;
      break;

    case 21:
      bfade = 2;
      if (flop[4]) bfade = 100;
      fancy = 0;
      Serial.print("spire3 ");
      targetfps = 20;
      break;

    case 22:
      adjunct = 5;
      steper = mstep;
      Serial.print("BarG mirror");
      break;

    case 23:
      if (flop[5])
        afancy = 25;
      Serial.print("roger ");
      targetfps = 5;
      bfade = 1;
      break;

    case 24:
      if  (flop[0])
      {
        adjunct = 11;//6 is quad, 11 is cool
        wind = 8;
      }
      else
      {
        adjunct = 6;
        wind = 4;
      }
      bfade = 4;
      fancy = 0;
      Serial.print("barg V mirror ");
      steper = mstep;
      break;

      break;

    case 25:
      Serial.print("spire ");
      adjunct = 0;
      targetfps = 40;
      break;

    case 26:
      //adjunct = 0;
      //fancy = 0;
      Serial.print("Sinx ");
      steper = mstep;
      targetfps = 20;
      if (flop[6]) // cool shit
      {
        bfade = 3;
        adjunct = 3;
        wind = 2;
        fancy = 0;
      }
      break;


    //======================================

    case 54:
      Serial.print("splat ");
      dwell = dwell >> 2;
      targetfps = random (15, 20);
      bfade = random(3);
      break;

    case 55:
      Serial.print("seasick 2");
      bfade = 1;
      targetfps = 50;
      fancy = 0;
      wind = 0;
      break;

    case 56:
      Serial.print("bounce ");
      fancy = random(1, 28);//more likely
      if (flop[4])afancy = 25;
      break;

    case 57:
      Serial.print("bounce adj ");
      adjunct = random(3, 12);
      fancy = random(1, 28);//more likely than not
      break;

    case 58:
      Serial.print("whitewarp ");
      //  adjunct = 0;
      fancy = random(1, 17);
      targetfps = random (15, 40) ;
      break;

    case 59:
      Serial.print("fireball ");
      adjunct = 0;
      fancy = random(1, 17);
      break;

    case 60:
      targetfps = random (25, 38);
      adjunct = random(3, 11);
      Serial.print("fireball");
      if ( flop[0]) {
        dot = 2;
        adjunct = 3;
        wind = 7;
        fancy = random(1, 27);
        bfade = random(3, 8);
      }
      break;

    case 61:
      targetfps = random (16, 25);
      Serial.print("warp, effects and wind");
      fancy = random(1, 23);
      wind = random(1, 11);
      break;

    case 62:
      targetfps = random(15, 25);
      fancy = random(1, 17);
      break;

    case 63:
      bfade = 100;
      wind = random(1, 11);
      targetfps = random(10, 20);
      fancy = random(1, 23);
      Serial.print("confetti 4");
      break;

    case 65:
      Serial.print("Smile");
      targetfps = random (20, 35);
      wind = 0;
      break;

    case 66:
      targetfps = random (15, 25);
      if (wind % 2 != 0)
        wind--;
      Serial.print("hypnoduck");
      break;

    case 67:
      targetfps = random (15, 25);
      adjunct = 0;
      //  fancy = 0;
      Serial.print("hypnoduck 2");
      break;

    case 68:
      targetfps = random (15, 35);
      // adjunct = 0;
      //  fancy = 0;
      Serial.print("Roger");
      break;

    case 69:
      targetfps = random (13, 25);
      Serial.print("drops with effects ");
      fancy = random(1, 17);
      break;

    case 70:
      Serial.print("spin2 ");
      //targetfps = random (5, 15);
    break;
 case 71:
      Serial.print("xspin ");
      //targetfps = random (5, 15);
      break;

    case 72:
      Serial.print("homer ");
      targetfps = random (15, 25);
      break;

    case 73:
      Serial.print("homer egg ");
      targetfps = random (15, 25);
      wind = 0;
      break;

    case 74:
      Serial.print("fireball w/ eff ");
      // targetfps = random (5, 15);
      break;

    case 75:
      Serial.print("seasick");
      bfade = random(3);
      targetfps = 60;
      break;

    case 76:
      targetfps = random(5, 12);
      bfade = random(6, 9);
      break;

    case 77:
      Serial.print("whtwarp ");
      targetfps = random(8, 25);
      wind = 0;
      break;

    case 78:
      Serial.print("tri warp ");
      targetfps = random(15, 35);
      wind = 0;
      fancy = 0;
      break;

    case 79:
      Serial.print("stars3");
      targetfps = random(30, 30);
      wind = 0;
      break;

    case 80:
      Serial.print("starz ");
      targetfps = random(15, 30);
      break;

    case 81:
      Serial.print("starz2 ");
      targetfps = random(15, 30);
      wind = 2 * wind + 1;// less likely
      break;

    case 82:
      Serial.print("swirl 2 ");
      targetfps = random(15, 25);
      wind = 0;
      fancy = 0;
      bfade = random (6, 9); //color fade
      break;

    case 83:
      if (flop[4] || flop[5]) adjunct = 9;
      Serial.print("circlearc ");
      fancy = fancy / 2;
      targetfps = random(15, 35);
      break;

    case 84:
      Serial.print("fireball ");
      targetfps = random(10, 20);
      if (flop[6]) afancy = random(20, 30);
      break;

    case 85:
      Serial.print("wheelz ");
      targetfps = random(15, 25);
      break;

    case 86:
      Serial.print("starbounce ");
      bfade = random(2, 6);
      if (flop[4]) afancy = random (25, 28);
      break;

    case 87:
      Serial.print("wheels2 ");
      bfade = random(1, 4);
      break;

    case 88:
      Serial.print("triforce ");
      break;

    case 89:
      targetfps = random(6, 20);
      Serial.print("swirl");
      wind = 0;
      break;

    case 90:
      targetfps = random(9, 20);
      bfade = random(2, 6);
      Serial.print("swirl4a ");
      if (flop[4] || flop[5] || flop[6]) wind = 0;
      fancy = 0;
      if (flop[7] || flop[8]) slowme = false;
      break;

    case 91:
      Serial.print("just fancy");
      fancy = random(1, 17);
      targetfps = random(15, 25);
      break;

    case 92:
      targetfps = 10;
      wind = 0;
      bfade = 0;
      adjunct = 0;
      Serial.print("DRIP2 ");
      fancy = 0;
      break;

    case 93:
      bfade = random (1, 6);
      adjunct = 0;
      Serial.print("spoke");
      fancy = 0;
      wind = 0;
      targetfps = random (5, 15);
      break;

    case 94:
      Serial.print("swirl3");
      bfade = random (2, 6);
      wind = 0;
      fancy = 0;
      targetfps = random (10, 20);
      break;

    case 95:
      Serial.print("dual drip");
      wind = 0;
      fancy = 0;
      bfade = 99;
      targetfps = 10;
      break;

    case 96:
      fancy = random(2, 12);// avoid triangler
      targetfps = random(15, 25);
      Serial.print("trianguler");
      break;

    case 97:
      wind = 0;
      if (flop[7]) bfade = 1;
      targetfps = random(15, 25);
      Serial.print("xspin");
      break;

    case 98:
      dwell = dwell * 2;
      targetfps = random (10, 20);
      Serial.print("swirl5");
      bfade = random (2, 6);
      wind = wind * 2 + 1;//less likely
      fancy = 0;
      break;

    case 99:
      targetfps = random (15, 25);
      break;

    case 100:
      fancy = random(1, 17);
      targetfps = random(15, 25);
      Serial.print("just fancy");
      slowme = false;
      break;

    case 101:
      Serial.print("conf4 warp");
      targetfps = random(10, 25);
      break;

    case 102:
      Serial.print("seasick4");
      break;

    case 103:
      Serial.print("hypnoduck3");
      break;

    case 104:
      Serial.print("circlearc");
      break;

    case 105:
      wind = 0;
      Serial.print("hypnoduck4");
      targetfps = random(20, 42);
      break;

    case 106:
      Serial.print("circlearc");
      targetfps = random (20, 40);
      adjunct = 3;
      fancy = 0;
      wind = 3;
      break;

    case 107:
      Serial.print("floaty star, Rmag, bkstar");
      fancy = random(6, 9);//avoid bk-starer
      targetfps = random(15, 20);
      break;

    case 108:
      Serial.print("wtwarp rmagic adjust");
      targetfps = random(8, 20);
      adjunct = random(2, 10);
      break;

    case 109:
      Serial.print("xspin, warp");
      //targetfps = random(15, 30);
      break;

    case 110:
      Serial.print("bubbles ");
      targetfps = random(15, 35);
      bfade = 10;//lots
      fancy = 0;
      break;

    case 111:
      Serial.print("bubbles2 ");
      targetfps = random(15, 44);
      bfade = 10;//lots
      fancy = 0;
      break;

    case 112:
      Serial.print("seasick5 ");
      targetfps = random(14, 30);
      bfade = random(3);
      fancy = 0;
      if (wind < 9) wind = 3;
      break;

    case 113:
      Serial.print("homer3 ");
      targetfps = random(25, 40);
      bfade = random(2, 4);
      break;

    case 114:
      Serial.print("drops with wind ");
      targetfps = random(20, 30);
      bfade = random(2, 4);
      wind = random(6, 11);
      fancy = 0;
      break;

    case 115:
      Serial.print("streaker - dual hypno ");
      targetfps = random(30, 50);
      // bfade = random(2, 4);
      fancy = 0;
      wind = 0;
      break;

    case 116:
      Serial.print("fireball - tri ");
      targetfps = random(40, 60);
      bfade = 4;
      break;

    case 117:
      Serial.print("streaker triangle  ");
      wind = 0;
      targetfps = random(10, 50);
      //bfade = 4;
      break;

    case 118:
      Serial.print("drops ");
      targetfps = random(9, 30);
      bfade = random (1, 3);
      if (flop[0] || flop[1]) wind = 0;
      fancy = 0;
      break;

    case 119:
      Serial.print("spin2 ");
      targetfps = random(9, 30);
      bfade = random (1, 3);
      if ( flop[0]) wind = 8; else wind = 9;
      break;

    case 120:
      Serial.print("windy drops ");
      targetfps = random(25, 38);
      bfade = random (0, 4);
      wind = random(2, 5);
      adjunct = 11 ;
      fancy = 0;
      break;

    case 121:
      Serial.print("round dr0ps wind ");
      targetfps = random(25, 38);
      bfade = random (3, 6);
      wind = random(2, 5);
      adjunct = 11 ;
      fancy = 0;
      break;

    case 122:
      Serial.print("round dr0ps ");
      targetfps = random(25, 38);
      bfade = random (2, 5);
      if (flop[0] && flop[1]) wind = 6; else if (flop[2]) wind = 3; else wind = 0;
      adjunct = 0;
      fancy = 0;
      break;

    case 123:
      bfade = 99;
      fancy = 0;
      wind = 0;
      targetfps = random(15, 45);
      Serial.print("volcano bubbles");
      break;

    case 124:
      //fancy = 0;
      //wind = 0;
      Serial.print("tiny bubbles");
      break;

    case 125:
      // fancy = 0;
      // wind = 0;
      Serial.print("volc inca bubbles");
      break;

    case 126:
      fancy = 0;
      wind = 0;
      Serial.print("whitewarp fireworks");
      break;

    case 127:
      Serial.print("seasick 3");
      targetfps = 60;
      bfade = 1;
      break;

    case 128:
      Serial.print("magictime");
      targetfps = 15;
      bfade = 2;
      fancy = random(1, 17);
      break;

    case 129:
      Serial.print("a pat: cube");
      item = 2;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      afancy = 28;
      wind = 0;
      adjunct = 0;
      break;

    case 130:
      Serial.print("spin2 ");
      Serial.print("triforce ");
      targetfps = random(9, 30);
      afancy = 28;
      if ( flop[0]) wind = 8; else wind = 9;
      break;

    case 131:
      Serial.print("seasickness");
      targetfps = random(20, 60);
      bfade = 101;
      break;

    case 132:
      Serial.print("spiral moving");
      targetfps = random(20, 60);
      adjunct = random8();
      wind = 0;
      fancy = random8()/2;
      break;

    case 133:
      Serial.print("spiral2 fixed");
      targetfps = random(10 - 24);
      if (flop[3]) adjunct = random8() / 2;
      wind = wind * 2 + 1;
      fancy = random8()/2;
      break;

    case 134:
      Serial.print("spiral fixed");
      targetfps = random(10 - 34);
      if (flop[3]) adjunct = random8() / 2;
      wind = wind * 2 + 1;
      if (flop[6]) fancy = 0;
      bfade = 2;
      break;

    case 135:
      Serial.print("spiral2 moving");
      targetfps = random(10 - 34);
      wind = wind * 2 + 1;
      fancy = random8()/2;
      break;

    case 136:
      Serial.print("spirre3, conf2 ");
      targetfps = random(10 - 24);
      fancy = 0;
      bfade = 1;
      adjunct = 3;
      flop[0] = true;
      flop[1] = false;
      flop[2] = true;
      break;

    case 139:
      Serial.print("spiral3 fixed");
      targetfps = random(8 - 24);
      adjunct = random8();
      wind = wind * 2 + 1;
      fancy = random8()/2;
      afancy = random8();
      break;

    case 140:
      Serial.print("spirre3, conf2 wild ");
      //targetfps = 30;
      // fancy = 0;
      // bfade = 1;
      adjunct = 3;
      flop[0] = true;
      flop[1] = false;
      flop[2] = true;
      break;

    case 141:
      Serial.print("snow 128");
      dwell = 1 * dwell;
      bfade = 0;
      adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = random(fastest, 3 * fastest);
      slowme = false;//no slowmo.
      break;

    case 142:
      Serial.print("Crazy Snow");
      dwell = 1 * dwell;
      bfade = 0;
      // adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = random(fastest, 3 * fastest);
      slowme = false;//no slowmo.
      break;

    case 143:
      Serial.print("bouncer");
      // dwell = 1.5 * dwell;
      bfade = random(2, 5);
      //adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = 60;
      slowme = false;//no slowmo.
      directn = 0;
      break;

    case 144:
      Serial.print("bouncer delux");
      dwell = 1.5 * dwell;
      bfade = 2;
      if (flop[2]) directn = 0; else directn = 1;
      adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = 60;
      slowme = false;//no slowmo.
      break;

    case 145:
      Serial.print("bouncer tri");
      // dwell = 1.5 * dwell;
      bfade = 5;
      adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = 60;
      slowme = false;//no slowmo.
      if ( flop[0]) directn = 0; else directn = 1;
      break;

    case 146:
      Serial.print("scales");
      // dwell = 1.5 * dwell;
      bfade = 100;
      adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = 2;
      waiter = 100;
      slowme = false;//slowmo.
      break;

    case 147:
      adjunct = 12;
      targetfps = random(8, 30);
      Serial.print("Wt warp ");
      break;

    case 148:
      targetfps = random(6, 20);
      bfade = random(2, 6);
      Serial.print("swirl4 ");
      if (flop[4] || flop[5] || flop[6]) wind = 0;
      fancy = 0;
      slowme = false;
      break;

    case 149:
      targetfps = random(6, 30);
      bfade = 100;
      if (flop[7] && flop[8]) bfade = 101;
      Serial.print("VORTEX ");
      if (flop[7] || !flop[6]) wind = 0;
      if (flop[1] || !flop[8]) adjunct = 0;
      fancy = 0;
      slowme = false;
      if (flop[2] && flop[3] && flop[4]) slowme = true;
      break;

    case 150:
      targetfps = random(20, 60);
      /*bfade = 0;
        if (flop[7] && flop[8]) bfade = 101;*/
      Serial.print("Fire  ");
      if (!flop[7] || flop[6]) wind = 0;
      if (flop[1] || !flop[8]) adjunct = 0;
      fancy = 0;
      slowme = false;
      if (flop[2] && flop[3] && flop[4]) slowme = true;
      break;

    case 151:
      Serial.print("tinybubbles3");
      //slowme = false;
      break;

    case 152:
      Serial.print("floating spirre3, conf2 ");
      targetfps = random(6, 30);
      fancy = 0;
      bfade = 100;
      adjunct = 3;
      flop[0] = true;
      flop[1] = false;
      flop[2] = true;
      break;

    case 155:
      bfade = 99;
      fancy = 0;
      wind = 0;
      targetfps = random(10, 40);
      Serial.print("star bubbles");
      break;

    case 156:
      bfade = 99;
      fancy = 0;
      wind = 0;
      targetfps = random(8, 15);
      Serial.print("squarebubbles");
      break;

    case 158:
      targetfps = random(6, 20);
      shifty = 1;
      slowme = false;//no slowmo.
      Serial.print("tuber ");
      fancy = random(15);
      if (random8() > 128) adjunct = 5;
      bfade = random(108, 111);
      break;

    case 159:
      targetfps = random(6, 30);
      bfade = 100;
      if (flop[7] && flop[8]) bfade = 101;
      Serial.print("VORTEX ");
      if (flop[7] || !flop[6]) wind = 0;
      afancy = 1;
      if (flop[1] || !flop[8]) afancy = 2;
      fancy = 0;
      slowme = false;
      if (flop[2] && flop[3] && flop[4]) slowme = true;
      break;

    case 160:
      Serial.print("a pat: ");
      item = 1;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 0;
        fancy = 0;
      }
      afancy = 25;
      break;

    case 161:
      Serial.print("a pat: cube");
      item = 2;
      bfade = 1;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      afancy = 26;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 0;
        fancy = 0;
      }
      break;

    case 162:
      Serial.print("a pat: ");
      item = 4;
      bfade = 0;
      adjunct = 0;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      afancy = 26;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;

    case 163:
      Serial.print("a pat: ");
      item = 5;
      bfade = 1;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      afancy = 26;
      if ( flop[3] || flop[4] || flop[5]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;

    case 164:
      Serial.print("a pat: ");
      item = 12;
      bfade = 0;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        afancy = 26;
      }
      break;

    case 165:
      Serial.print("a pat: ");
      item = 3;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;

    case 166:
      Serial.print("a pat: ");
      item = 6;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      afancy = 27;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;

    case 167:
      Serial.print("a pat: ");
      item = 7;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        afancy = 27;
      }
      break;

    case 168:
      Serial.print("a pat: ");
      item = 8;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        afancy = 27;
      }
      break;

    case 169:
      Serial.print("a pat: ");
      item = 9;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 3;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 2;
        afancy = 26;
      }
      break;

    case 170:
      Serial.print("a pat: ");
      item = 10;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        afancy = 26;
      }
      break;

    case 171:
      Serial.print("a pat: cube");
      item = 2;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      };
      break;

    case 172:
      Serial.print("a pat: ");
      item = 0;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      };
      break;

    /*case 173:
      Serial.print("Koi");
      fancy = 0;
      bfade = 101;
      slowme = false;
      targetfps = 2;
      break;
*/
    case 174:
      Serial.print("174");
      if (flop[9] || flop[2]) {
        adjunct = 0;
        fancy = 0;
        bfade = 3;
        slowme = true;//no slowmo.
      }
      break;

    default:
      Serial.print("D-fault");
      nextsong = true;
#ifdef MIXIT_AFTER_FIRST_PASS
      mixit = true;//after  you get here the first time, it all gets random.
#endif
      break;
  }

  /*Serial.print(", Time (s) ");
    Serial.print((dwell) / 1000, 1);
    Serial.print(", Step: ");
    Serial.print(steper);
    Serial.print(", dot: ");
    Serial.print(dot);*/
  Serial.print(", Adjunct ");
  Serial.print(adjunct);
  Serial.print(" wind: ");
  Serial.print(wind);
  Serial.print(" fancy: ");
  Serial.print(fancy);
    Serial.print(" afancy: ");
  Serial.print(afancy);
  Serial.print(" fader: " );
  Serial.print(bfade);
  /*Serial.print(" target FPS: " );
    Serial.print(targetfps);

    Serial.print(" velo: " );
    Serial.print(velo);*/
  if (slowme)
    Serial.print("  Slowmo!, ");

   //Serial.println("  ");
    for (int16_t g = 0; g < 10; g++) {

     Serial.print ("Flop-");
     Serial.print(g);
     Serial.print(":  ");
     Serial.print(flop[g]);
     Serial.print(", ");
    }
#ifdef ARDUINOONPC
  Serial.println(""); // ArduinoOnPC doesn't output a line before newline, so output it early.
#endif
}

void runpattern() {//here the actuall effect is called based on the pattern number,  sometimes more than one is called, sometimes the logical switches, dictate what is called
  switch (pattern) {
    case 0:
      Diamondhole();
      adjustme();// apply the screenwide effect
      break;

    case 1:
      Inca(blender);
      zeds.QuadrantBottomTriangleMirror();
      break;

    case 2:
      Ringo();
      if (flop[0]) zeds.QuadrantBottomTriangleMirror();
      break;

    case 3:
      diagonally();
      adjustme();
      break;

    case 4:
      Roundhole();
      adjustme();
      break;

    case 5:
      drifter();
      adjustme();
      break;

    case 6:
      drip();
      break;

    case 7:
      if (flop[2] || flop[1]) solid5();
      volcano(255);
      adjustme();
      break;

    case 8:
      if (flop[2] || flop[1]) solid5(); else solid5();
      pyrimid();
      adjustme();
      break;

    case 9:
      solidpyrimid();
      adjustme();
      break;

    case 10:
      corner();
      // driftx = MIDLX;
      //  drifty = MIDLY;
      adjustme();
      break;

    case 11:
      whitewarp();
      break;

    case 12:
      fuzzy();
      break;

    case 13:
      confetti();
      break;

    case 14:
      spire2();
      if (flop[0] && flop[1]) adjustme();
      break;

    case 15:
      streaker();
      break;

    case 16:
      fireball();
      ringer();
      break;

    case 17:
      warp();
      break;

    case 18:
      siny();
      if (flop[0] && flop[2]) adjustme();
      break;

    case 19:
      sinx();
      if (flop[0] && !flop[2]) adjustme();
      break;

    case 20:
      triple();
      if ((flop[3] && flop[1]) || (flop[4] && flop[8]) ) adjustme();
      break;

    case 21:
      spire3();
      twister();
      break;

    case 22:
      solid5();
      Bargraph();
      adjustme();
      break;

    case 23:
      roger();
      if (flop[6] && (flop[1] || !flop[2])) adjustme();
      break;

    case 24:
      if (flop[4]) solid5();
      Bargraph();
      break;

    case 25:
      spire();
      if (flop[2]) adjustme();
      break;

    case 26:
      sinx();
      if (flop[7] || flop[5] || !flop[2]) adjustme();
      break;

    case 54:
      splat();
      break;

    case 55:
      seasick2();
      break;

    case 56:
      bouncez();
      if (flop[6 || flop[5]]) adjustme();
      break;

    case 57:
      bouncez();
      adjustme();
      break;

    case 58:
      whitewarp();
      adjustme();
      if (flop[1] && wind < 9) twister();
      break;

    case 59:
      fireball();
      break;

    case 60:
      if (flop[0] || flop[1] ) confetti4();
      fireball();
      adjustme();
      break;

    case 61:
      EVERY_N_SECONDS(3 + 3 * dot) {
        fancy = random(1, 23);
        adjunct = random (12);
      }
      warp();
      adjustme();
      break;

    case 62:
      warp();
      if (flop[2]) confetti4();
      adjustme();
      break;

    case 63:
      confetti();
      confetti4();
      if (wind < 9) twister();
      if (flop[3]) adjustme();
      break;

    case 64:
      triple();
      if (flop[4]) adjustme();
      break;

    case 65:
      if (flop[3] && flop[4] && flop[2]) smile();
      else if (flop[6] && flop[7] && flop[5]) smile4();
      else if (flop[1] && flop[8] && flop[3]) smile3();
      else smile2();
      break;

    case 66:
      hypnoduck();
      if (flop[8]) adjustme();
      break;

    case 67:
      hypnoduck2();
      if (flop[9] && flop[3]) adjustme();
      break;

    case 68:
      roger();
      adjustme();
      break;

    case 69:
      drops();
      adjustme();
      break;

    case 70:
      spin2();
      if (!flop[0] && flop[1] && !flop[2]) adjustme();
      break;

    case 71:
      xspin();
      break;

    case 72:
      homer();
      break;

    case 73:
      homer2();
      if (flop[1] && flop[2] && wind < 9) twister();
      break;

    case 74:
      fireball();
      adjustme();
      break;

    case 75:
      seasick();
      break;

    case 76:
      confetti3();
      break;

    case 77:
      //      solid3(96);
      whitewarp();
      break;

    case 78:
      driftx = MIDLX;
      drifty = MIDLY;
      warp();
      drawtriangle();
      break;

    case 79:
      starz3();
      adjustme();
      break;

    case 80:
      starz();
      adjustme();
      break;

    case 81:
      starz2();
      adjustme();
      break;

    case 82:
      swirl2();
      break;

    case 83:
      if (flop[1] && flop[2] && wind < 9) twister();
      circlearc();
      adjustme();
      break;

    case 84:
      if (flop[1] && flop[2] && wind < 9) twister();
      fireball();
      break;

    case 85:
      wheelz();
      adjustme();
      break;

    case 86:
      starbounce();
      adjustme();
      break;

    case 87:
      wheelz2();
      break;

    case 88:
      if (!flop[2]) warp();
      triforce();
      if (flop[2]) adjustme();
      break;

    case 89:
      swirlz();
      break;

    case 90:
      swirl4a();
      break;

    case 91:
      confetti2();
      EVERY_N_SECONDS(10 + 3 * dot) {
        fancy = random(1, 22);
      }
      if (flop[2] || flop[5]) adjustme();
      break;

    case 92:
      drip();
      mirror();
      break;

    case 93:
      spoker();
      break;

    case 94:
      swirl3();
      break;

    case 95:
      drip();
      mirror();
      break;

    case 96:
      triangler();
      break;

    case 97:
      xspin();
      break;

    case 98:
      swirl5();
      break;

    case 99:
      spoker3();
      break;

    case 100:
      EVERY_N_SECONDS(15 + 3 * dot)
      fancy = random(1, 22);
      adjustme();
      confetti2();
      break;

    case 101:
      confetti4();
      if (flop[0] || flop[1] || flop[2]) warp();
      break;

    case 102:
      seasick4();
      break;

    case 103:
      hypnoduck3();
      break;

    case 104:
      circlearc();
      break;

    case 105:
      hypnoduck4();
      break;

    case 106:
      circlearc();
      adjustme();
      break;

    case 107:
      for (int16_t j = 1; j < MATRIX_WIDTH - 8; j++)//0
        drawstar(driftx, drifty, j, j / 2, 7, 2 * h, h + j * 4);
      if (flop[0]) rmagictime();
      bkstarer();
      adjustme();// hey long time no see....
      break;


    case 108:
      whitewarp();
      rmagictime();
      if (flop[1] && flop[2] && wind < 9) twister();
      break;

    case 109:
      warp();
      xspin();
      if (flop[0] && !flop[5]) adjustme();
      break;

    case 110:
      bubbles();
      break;

    case 111:
      bubbles2();
      break;

    case 112:
      seasick5();
      break;

    case 113:
      homer3();
      break;

    case 114:
      drops();
      break;

    case 115:
      driftx = xxx;
      drifty = yyy;
      streaker();
      hypnoduck();
      break;

    case 116:
      fireball();
      triangler();
      if (flop[5]) adjustme();
      break;

    case 117:
      if (flop[8] || flop[6]) {
        driftx = MIDLX;
        drifty = MIDLY;
      }
      if (flop[5]) solid5();
      streaker();
      drawtriangle();
      break;

    case 118:
      drops();
      // adjustme();
      break;

    case 119:
      spin2();
      break;

    case 120:
      drops();
      twister();
      if (flop[5]) adjustme();
      break;

    case 121:
      drips();
      twister();
      adjustme();
      break;

    case 122:
      drips();
      twister();
      adjustme();
      break;

    case 123:
      if (flop[5]) {
        driftx = MIDLX;
        drifty = MIDLY;
      }
      if (flop [3]) {
        if (flop[4]) volcano(55); else Inca(55);
      }
      tinybubbles2();
      break;

    case 124:
      tinybubbles();
      break;

    case 125:
      tinybubbles2();
      adjustme();
      break;

    case 126:
      whitewarp();
      fireworks();
      if (flop[6] && flop[7]) adjustme();
      break;

    case 127:
      seasick3();
      break;

    case 128:
      magictime();
      adjustme();
      if (flop[2]) confetti2(); else warp();
      break;

    case 129:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 130:
      whitewarp();
      spin2();
      triforce();
      if (flop[2]) adjustme();
      break;

    case 131:
      seasickness();
      break;

    case 132:
      spiralz();
      adjustme();
      break;

    case 133:
      drifty = MIDLY;
      driftx = MIDLX;
      spiral2();// add a spiral
      adjustme();
      break;

    case 134:
      drifty = MIDLY;
      driftx = MIDLX;
      spiralz();// add a spiral
      adjustme();
      break;
    case 135:

      spiral2();// add a spiral
      if (flop[7]) adjustme();
      break;

    case 136://i love this
      drifty = MIDLY;
      driftx = MIDLX;
      if (flop[6]) solid5();
      spire3();
      confetti2();
      twister();
      adjustme();
      break;

    case 139:
      spiral3();
      if (flop[7]) adjustme();
      break;

    case 140:
      //i love this
      drifty = MIDLY;
      driftx = MIDLX;
      spire3();
      confetti2();
      twister();
      adjustme();
      break;

    case 141:
      if (flop[2]) snow(138); else snow(random8());
      break;

    case 142:
      if (flop[2]) snow(blender); else snow(random8());
      adjustme();
      break;

    case 143:
      BouncingBalls(dot);
      if (flop[6]) adjustme();
      break;

    case 144:
      solid5();
      BouncingBalls(12);
      break;

    case 145:
      if (flop[5] && flop[7]) solid5(); else Inca(64);
      Bouncingtri(dot);
      break;

    case 146:
      scales();
      zeds.VerticalMirror();
      break;

    case 147:
      whitewarp();
      adjustme();
      EVERY_N_SECONDS(4 * dot) {
        adjunct = random(16);
        flop[6] = !flop[6];
      }
      break;

    case 148:
      swirl4();
      break;

    case 149:
      VORTEX();
      break;

    case 150:
      Fire();
      break;

    case 151:
      tinybubbles3();
      break;

    case 152://i love this 136
      spire3();
      confetti2();
      twister();
      adjustme();
      break;

    case 155://123
      if (flop[5] && flop[7]) {
        solid5();
        driftx = MIDLX;
        drifty = MIDLY;
      }
      else solid4();//black
      starbubbles88();
      break;

    case 156://123
      driftx = MIDLX;
      drifty = MIDLY;
      if (flop[5] || flop[3]) solid5(); else solid4();//black
      squarebubbles();
      break;

    case 158:
      if (flop[5]) solid5();
      tuber();
      adjustme();
      break;

    case 159:
      tuber();
      //VORTEX();
      adjustme();
      break;

    case 160:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 161:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 162:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 163:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 164:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 165:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 166:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 167:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 168:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 169:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 170:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 171:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    case 172:
      patternz->drawFrame();
      if (flop[5] && flop[9]) adjustme();
      break;

    /*case 173:
      koi();
      break;*/

    case 174:
      if (flop[0] && flop[1] ) {
        confetti2();
        streaker();
      }
      else {
        spiral2();
      }
      if (flop[3] && flop[7]) adjustme();
      break;

    default:
      nextsong = true;
      matrix->clear();
      break;
  }
#ifdef SHOW_PATTERN_NUM
  uint8_t print_width = 1;
  if (pattern > 9)  print_width = 2;
  if (pattern > 99) print_width = 3;
  zeds.DrawFilledRectangle(0, 0, 5 * print_width - 1, 6, 0);
  matrix->setCursor(0, 0);
  matrix->print(pattern);
#endif
}


void Diamondhole()//eff 0
{
  // ** Fill LED's with diagonal stripes
  if (flop[7] || flop[5] || flop[3]) {
    dot = beatsin16(dot2, 2, 9, 0);
    cool = beatsin16(dot2, 4, 9, blender);
  }
  else
    dot = 1;

  for (int16_t x = 0; x < (MATRIX_WIDTH  + MATRIX_HEIGHT); x += dot)
  {
    zeds.DrawLine(x - MATRIX_HEIGHT - 1, MATRIX_HEIGHT - 1, x, 0, CHSV(h * 2 + x * cool, 255 - velo / 4, MATRIX_HEIGHT * 2 + 2 * x - 8));

  }

}

void Inca(int16_t brit)//eff 1
{
  // ** Fill LED's with horizontal stripes


  if (flop[4])
    dot = beatsin16(1, 2, 10, 0);
  else
    dot = beatsin16(4, 2, 8, 0);

  cool = beatsin16(dot2 + 3, 4, 8 , blender);

  for (int16_t y = 0; y < MATRIX_HEIGHT - 1; y += dot )
  {
    if (flop[1])
      zeds.DrawLine(0, y, MATRIX_WIDTH  - 1, y, CHSV(h  + y * cool , 255 - velo / 4, brit));
    else
      zeds.DrawLine(0, y, MATRIX_WIDTH  - 1, y, CHSV(y * dot + h,  222 + cool * 4 , brit));

  }

}

void Ringo()// eff 2
{
  if (flop[7] || flop[5] || flop[3])
    dot = beatsin16(dot2, 1, 9, 0);

  for (int16_t x = 0; x < (MATRIX_WIDTH * 2); x ++)
    if (flop[2] || flop[7] || flop[8])
      zeds.DrawLine(x - MATRIX_HEIGHT, MATRIX_HEIGHT - 1, x, 0, CHSV( dot * x - h , 255 , 255));
    else
      zeds.DrawLine(x - MATRIX_HEIGHT, MATRIX_HEIGHT - 1, x, 0, CHSV(blender + dot * x,  255 , 255));
}


void tuber2()//
{
  if (flop[7] || flop[5] || flop[3])
    dot = beatsin16(dot2, 1, 9, 0);

  for (int16_t x = 0; x < (MATRIX_WIDTH * 1.5 ); x += dot2 + 3)
    if (!flop[2])
      zeds.DrawCircle(driftx, drifty, (counter % (dot2 + 3)) + x, CHSV(h - x * dot , 255 -  velo / 4, 255));
    else
      zeds.DrawCircle(driftx, drifty, (counter % (dot2 + 3)) + x, CRGB::White);
}

void diagonally()// eff 3
{
  if (flop[7] || flop[5] || flop[3])
    dot = beatsin16(dot2 + 4, 3, 9, 0);
  for (int16_t y = 0; y <= MATRIX_HEIGHT * 3 / 4  ; y += dot)
    if ( !flop[8] )
      zeds.DrawCircle(driftx, drifty , MATRIX_HEIGHT * 3 / 4 + 3 - y, CHSV(h  + y * steper, 255 - velo / 4, 255 - 2 * y));
    else
      zeds.DrawCircle(driftx, drifty , MATRIX_HEIGHT * 3 / 4 + 3 - y, CHSV(h  + y * steper, 255 -  y, 255));

}


void Roundhole()// eff4
{
  if (flop[2])
    solid3(96);
  else {
    if (flop[6])
      solid5();
  }
  if (flop[7] || flop[5] || flop[3])
    dot = beatsin16(dot2 + 6, 2, 9, 0);
  for (int16_t y = 0; y < MATRIX_HEIGHT - 1 ; y += dot)
    zeds.DrawCircle(driftx, drifty, MATRIX_HEIGHT - y, CHSV(y * dot2 - h  , 255 -  velo / 4, 255));
}

void drifter()//pattern=5
{
  if (flop[1])//likely
    solid3(128);
  else if ( flop[0])
    solid2(128);//possibly

  if (flop[7] || flop[5] )
    dot = beatsin16(dot2, 2, 9, 0);

  cool = beatsin16(dot2, 4, 12, blender);


  for (int16_t y = 0; y <= MATRIX_HEIGHT  + 1 ; y += dot )
    zeds.DrawFilledCircle(driftx, drifty , MATRIX_HEIGHT  + 5 - y, CHSV(h + y * cool, 255 - velo / 5, 255));
}




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void volcano(int16_t brit)//pattern=7
{

  for (int16_t y = 0; y <  MATRIX_WIDTH + 8 ; y += (dot + 1))
    zeds.DrawCircle(driftx , drifty  ,  MATRIX_WIDTH + 4  - y, CHSV( h - y * 16, 255 - velo / 4, brit));
}

void pyrimid()//pattern=8
{


  dot = beatsin16(dot2 + 3, 2, 9, 0);

  for (int16_t y = 0; y < MATRIX_WIDTH; y += dot )
    zeds.DrawCircle(driftx, drifty,  y, CHSV(h  - y * 8, 255 - velo / 4, 255));

}

void solidpyrimid()//pattern=9
{

  for (int16_t y = dot; y < MATRIX_WIDTH; y += dot + 1)
    zeds.DrawRectangle(driftx - y,  drifty - y  , driftx  + y  , drifty + y , CHSV(-h + y * 5 , 255 - velo / 4, 255 ));
}

void solid2(int16_t brit)//solid colors rotate
{
  zeds.DrawFilledRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(h, 255 - velo / 4, brit));
}


void solid3(int16_t brit)//solid random color
{
  if (counter == 0)
    rr = random8();
  zeds.DrawFilledRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(rr + h, beatsin16(15, 192, 255, 0), brit));
}


void solid4()//solid black
{

  zeds.DrawFilledRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CRGB::Black);
}

void solid(int16_t brit)//colors rotate forward
{
  if (counter == 0)
    rr = random8();
  zeds.DrawFilledRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(rr + beatsin16(15, 0, 96, 0), 255 - velo / 4, brit));
}

void solid5()//colors rotate forward
{
  for (int16_t i = 0; i < MATRIX_WIDTH; i++)
    for (int16_t j = 0; j < MATRIX_HEIGHT; j++)
      zeds(i, j) = CHSV(i * dot2 + dot / 2 * j +  h, 255, 64);
}

void solid6(int16_t klr)//solid color
{
  for (int16_t i = 0; i < MATRIX_WIDTH; i++)
    for (int16_t j = 0; j < MATRIX_HEIGHT; j++)
      zeds(i, j) = CHSV(klr, 188, 168);
}

void fuzzy() {  ///pattern 12
  if (flop[6])
    h = blender;
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV(h, 255 - velo / 8, 255);
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV(h + (random8() >> 2), 255, 255);
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV( h + (random8() >> 2), 180 + random(75), 220 + random(35));
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV( h + (random8() >> 2), 180 + random(75), 200 + random(55));
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV( h + (random8() >> 2), 180 + random(75), 180 + random(75));
  zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CHSV( h + (random8() >> 2) + 128, 180 + random(75), 180 + random(75));
}

void corner()//pattern=10
{
  solid5();
  fireball();
}




void tuber()//
{
  if (counter == 0)
  {
    for (int16_t u = 0; u < MATRIX_WIDTH; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = u * dot2 + 3;
      fcolor[u] = u * 2;
    }
  }

  dot = beatsin16(1, 4, 7, 2);
  solid4();//black
  for (int16_t u = 0; u < (MATRIX_WIDTH ); u ++) {
    fpeed[u]++;
    if (fpeed[u] > MATRIX_WIDTH) {
      fpeed[u] = dot2 + 3;
      xfire[u] = driftx;
      yfire[u] = drifty;
    }

    if (!flop[3])
      zeds.DrawCircle(xfire[u], yfire[u], fpeed[u],  CHSV(fcolor[u] + h  , 255 -  velo / 4, 255));
    else
      drawstar(xfire[u], yfire[u], fpeed[u], fpeed[u] / 3, dot, h, fcolor[u] + h);

  }
}

void fireball() {// with colored dots in pairs sometimes
  if (counter == 0)
  {
    ccoolloorr = random8();
    howmany = random(MATRIX_WIDTH + 4 , 2 + MATRIX_WIDTH * 2);
    how = howmany;
    for (int16_t u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = random(1, 5);
      blender = random8();
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;
      fvelo[u] = random8();
      if ( flop[0])
        fcolor[u] = ccoolloorr + random(64);
      else
        fcolor[u] = random8();
    }
  }
  if (flop[4] || flop[5])
    howmany = beatsin16(4, 0, how, 0);
  for (int16_t u = 0; u < howmany; u++) {
    zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
    xfire[u] = xfire[u] + xslope[u];
    yfire[u] = yfire[u] + yslope[u];
    fcount[u] = 0;
    if (yfire[u] < 0 || yfire[u] > MATRIX_WIDTH - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      if ( flop[0])
        fcolor[u] = ccoolloorr + random(64);
      else
        fcolor[u] = random8();

      blender = random8();
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;

    }

  }
  zeds(driftx, drifty) = CHSV(ccoolloorr - 96, 255 - velo / 4, 225);
}


void fireworks() {// with colored dots in pairs sometimes
  if (counter == 0)
  {
    flop[3] = true;
    firedelay = random8() + 20;
    ccoolloorr = random8();
    howmany = random(MATRIX_WIDTH , MATRIX_WIDTH * 2);

    for (int16_t u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] =   drifty;
      fpeed[u] = random(1, 5);
      blender = random8();
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;
      fvelo[u] = random8();
      if ( flop[0])
        fcolor[u] = ccoolloorr + random(32);
      else
        fcolor[u] = random8();
    }
  }
  if (flop[3]) {
    for (int16_t u = 0; u < howmany; u++) {
      zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
      zeds(xfire[u] + 1, yfire[u] - 1) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
      xfire[u] = xfire[u] + xslope[u];
      yfire[u] = yfire[u] + yslope[u];
      fcount[u] = 0;
      if (yfire[u] < 0 || yfire[u] > MATRIX_WIDTH - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1) {
        xfire[u] = driftx;
        yfire[u] = drifty;
        if ( flop[0])
          fcolor[u] = ccoolloorr + random(32);
        else
          fcolor[u] = random8();

        blender = random8();
        yslope[u] = (cos8(blender) - 128.0) / 128.0;
        xslope[u] = (sin8(blender) - 128.0) / 128.0;

      }

    }
    zeds(driftx, drifty) = CHSV(ccoolloorr - 96, 255 - velo / 4, 255);
  }
  if (counter >= firedelay) {
    firedelay = counter + random8() + 20;
    flop[3] = ! flop[3];
  }
}



void streaker() {
  if (counter == 0)
  {
    //  beatsolid(85);
    ccoolloorr = random8();
    howmany = random(MATRIX_WIDTH * 2 / 3, THREEHAVES);
    how = howmany;
    for (int16_t u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = random(1, 5);
      blender = random8();
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;
      fvelo[u] = random8();
      if ( flop[0])fcolor[u] = ccoolloorr + random(42);
      else
        fcolor[u] = random8();

    }
  }
  if (flop[4]) howmany = beatsin16(3, 1, how, 0);
  for (int16_t u = 0; u < howmany; u++)
  {
    zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
    xfire[u] = xfire[u] + xslope[u] * fpeed[u];
    yfire[u] = yfire[u] + yslope[u] * fpeed[u];
    fcount[u] = 0;

    if (yfire[u] < 0 || yfire[u] >  MATRIX_WIDTH - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1)
    {
      xfire[u] = driftx;
      yfire[u] = drifty;
      if ( flop[0])
        fcolor[u] = ccoolloorr + random(64);
      else
        fcolor[u] = random8();
      blender = random8();
      fpeed[u] = random(1, 5);
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;
    }
  }

}

void ringer() {
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= MATRIX_WIDTH)
    {
      if (flop[0] || flop[1])
        zeds.DrawCircle(driftx, drifty , counter - ringdelay, CHSV( h + 85, 255 - velo / 4, 255));
      else
        zeds.DrawCircle(driftx, drifty , counter - ringdelay, CRGB::White);
    }
    else
      ringdelay = counter + random(targetfps * 5, targetfps * 10);
  }
}

void bkringer() {
  if (counter >= bringdelay)
  {
    if (counter - bringdelay <= MATRIX_WIDTH + 13)
    {
      zeds.DrawCircle(driftx, drifty , (MATRIX_WIDTH + 12 - counter + bringdelay), CHSV(h + 60, 255 - velo / 4, 255));
      zeds.DrawCircle(driftx, drifty, (MATRIX_WIDTH + 8 - counter + bringdelay), CHSV(h + 70 , 255 - velo / 4, 255));
      zeds.DrawCircle(driftx, drifty , (MATRIX_WIDTH + 4 - counter + bringdelay), CHSV(h + 80 , 255 - velo / 4, 255));
      zeds.DrawCircle(driftx, drifty , (MATRIX_WIDTH  - counter + bringdelay), CHSV(h + 90 , 255 - velo / 4, 255));
    }
    else {
      bringdelay = counter + random(targetfps * 4, targetfps * 15);

    }
  }
}

void sinx() {
  if (counter == 0) {
    radius2 = random((MATRIX_WIDTH >> 2) + 4, (MATRIX_WIDTH >> 1) + 8) + 4;
    radius3 = random (MATRIX_WIDTH >> 3, MATRIX_WIDTH >> 2) + 4;
  }
  if (flop[7] || flop[5] )
    dot = beatsin16(2, 3, 12, 128);
  else
    dot = 5;

  for (int16_t j = radius2 >> 1; j < radius2 + 4; j += dot) {
    if ( flop[0])
    {
      zeds.DrawCircle(driftx + ((radius3 * (cos8(h  ) - 128)) >> 7), drifty + ((radius3 * (sin8(h ) - 128)) >> 7), j, CHSV(h + dot * j , velo / 8 + 223, 255));
      zeds.DrawCircle(driftx + (radius3 * ((cos8(h  + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h  + 128) - 128)) >> 7), j, CHSV(h + dot * j + 128 , velo / 8 + 223, 255));
      if (flop[2]) {
        zeds.DrawCircle(driftx + ((radius3 * (cos8(h * 2) - 128)) >> 7), drifty + ((radius3 * (sin8(h * 2) - 128)) >> 7), j * 3 / 2, CHSV(h + dot * j + 128 , velo / 8 + 223, 255));
        zeds.DrawCircle(driftx + (radius3 * ((cos8(h * 2 + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h * 2 + 128) - 128)) >> 7), j * 3 / 2, CHSV(h + dot * j , velo / 8 + 223, 255));
      }
      if (!flop[1]) {
        zeds.DrawCircle(driftx + ((3 * radius3 * (cos8(-h * 2) - 128)) >> 7), drifty + ((3 * radius3 * (sin8(-h * 2) - 128)) >> 7), j * 2  , CHSV(h + dot * j + 128 , velo / 8 + 223, 255));
        zeds.DrawCircle(driftx + ((3 * radius3 * (cos8(-h * 2 + 128) - 128)) >> 7), drifty + ((3 * radius3 * (sin8(-h * 2 + 128) - 128)) >> 7), j * 2  , CHSV(h  + dot * j, velo / 8 + 222, 255));
      }
    }
    else
    {
      zeds.DrawCircle(driftx + ((radius3 * (cos8(-h * 4) - 128)) >> 7), drifty + ((radius3 * (sin8(-h * 4) - 128)) >> 7), j, CHSV(h , 255 - velo / 4, 255));
      zeds.DrawCircle(driftx + (radius3 * ((cos8(-h *  + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h * 4 + 128) - 128)) >> 7), j, CHSV(h  , 255 - velo / 4, 255));
      if (flop[2]) {
        zeds.DrawCircle(driftx + ((radius3 * (cos8(-h * 3) - 128)) >> 7), drifty + ((radius3 * (sin8(-h * 3) - 128)) >> 7), j * 1.5 , CHSV(h + 85 , 255 - velo / 4, 255));
        zeds.DrawCircle(driftx + (radius3 * ((cos8(-h * 3 + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h * 3 + 128) - 128)) >> 7), j * 1.5  , CHSV(h + 85 , 255 - velo / 4, 255));
      }
      if (!flop[1]) {
        zeds.DrawCircle(driftx + ((4 * radius3 * (cos8(h * 2) - 128)) >> 7), drifty + ((4 * radius3 * (sin8(h * 2) - 128)) >> 7), j * 2, CHSV(h - 85 , 255 - velo / 4, 255));
        zeds.DrawCircle(driftx + ((4 * radius3 * (cos8(h * 2 + 128) - 128)) >> 7), drifty + ((4 * radius3 * (sin8(h * 2 + 128) - 128)) >> 7), j * 2, CHSV(h - 85 , 255 - velo / 4, 255));
      }
    }
  }
}

void drip() {
  if (counter == 0)
  {
    if (flop[4]) Ringo();
    ccoolloorr = random8();
    if (flop[1])
      ccoolloorr = 42;
    for (howmany = 0; howmany < MATRIX_WIDTH; howmany++)
    {
      xslope[howmany] = ccoolloorr + random(45);//color

    }
    if (flop[2])
      for (howmany = 0; howmany < MATRIX_WIDTH; howmany++)
      {
        xslope[howmany] = ccoolloorr + random(86);//color

      }
  }
  for (xx = 0; xx < MATRIX_WIDTH ; xx++)
  {
    if (random8() < 40)
      for (yy = 0; yy < MATRIX_HEIGHT - 1; yy++)
      {
        zeds(xx, yy) = zeds (xx, yy + 1);
      }
    if (flop[2])
    {
      if (random8() > 168) {
        xslope[xx] = xslope[xx] + 1;
        zeds(xx, MATRIX_HEIGHT - 1) =  CHSV(xslope[xx], 255 - velo / 4, 255);
      } else
        zeds(xx, MATRIX_HEIGHT - 1) = CRGB::Black;
    }
    else
    {
      if (random8() > 128)

        zeds(xx, MATRIX_HEIGHT - 1) =  CHSV(random8(), 255 - velo / 4, 255);
      else
        zeds(xx, MATRIX_HEIGHT - 1) = CRGB::Black;
    }
  }
}

void mirror() {
  for (xx = 0; xx < MATRIX_WIDTH; xx++)
    for (yy = 0; yy < MIDLY; yy++)
      zeds(xx, yy) = zeds(xx, MATRIX_HEIGHT - yy - 1);

}

void roger()
{
  if (counter == 0)
    ccoolloorr = random8();
  if (flop[4] && flop[5]) {
    zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h  + 128, 255 - velo / 4, 100));
    zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) , CHSV(h , 255 - velo / 4, 255));

    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 0, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 1, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 4, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 5, 2, CRGB::Black);
    zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(h , 235, 135));
    zeds.HorizontalMirror();
  }
  if (flop[4] && !flop[5]) {
    zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h  + 128, 255 - velo / 4, 190));
    zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) , CHSV(h , 255 - velo / 4, 255));

    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 0, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 1, 2, CRGB::Black);

    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CRGB::Black);
    if ((counter / 16) % 2 == 0) {
      zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(h , 255 - velo / 4, counter % 32 * 8));
      zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h + 30 , 255 - velo / 4, counter % 32 * 8));
    }
    else {
      zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(h , 255 - velo / 4, 2565 - (counter % 32) * 8));
      zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h + 30 , 255 - velo / 4, 255 - (counter % 32) * 8));
    }
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 4, 2, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 5, 2, CRGB::Black);
    zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CRGB::Black);
    zeds.HorizontalMirror();
  }
  if (!flop[4] && flop[5]) {
    if (flop[8])
      zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h + 84 , 255 - velo / 4, 190));
    else {
      fuzzy();
      fuzzy();
      fuzzy();
    }

    zeds.DrawCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(h  - 45, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 0, 5, CHSV(h  + 30, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 1, 4, CHSV(h  + 15, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 3, CHSV(h  , 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h  - 15, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 4, 1, CHSV(h  - 30, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 5, 0, CHSV(h  - 45, 255 - velo / 4, 255));
    zeds.DrawCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CRGB::Black);
    zeds.HorizontalMirror();
  }
  if (!flop[4] && !flop[5])
  {
    // zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 0, 0, CHSV(ccoolloorr  + 45, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 1, 1, CHSV(ccoolloorr  + 22, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(ccoolloorr  , 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 3, CHSV(ccoolloorr  - 15, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 4, 4, CHSV(ccoolloorr  - 30, 255 - velo / 4, 255));
    zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 5, 5, CHSV(ccoolloorr  - 45, 255 - velo / 4, 255));
    if ((counter / 200) % 2 == 0) {
      zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(ccoolloorr - 45, 255 - velo / 4, 55 + counter % 200));
      zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(ccoolloorr + 45 , 255 - velo / 4, 255 - counter % 200));
    }
    else {
      zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(ccoolloorr - 45, 255 - velo / 4, 255 - counter % 200));
      zeds.DrawFilledCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(ccoolloorr + 45, 255 - velo / 4, 55 + counter % 200));
    }
    zeds.HorizontalMirror();
  }
}

void rogerv() {
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 0, 0, CHSV(h  + 20, 255 - velo / 4, 255));
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 1, 0, CHSV(h  + 10, 255 - velo / 4, 255));
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 2, 0, CHSV(h  , 255 - velo / 4, 255));
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 3, 0, CHSV(h  - 10, 255 - velo / 4, 255));
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 4, 0, CHSV(h  - 20, 255 - velo / 4, 255));
  zeds.DrawLine(MIDLX, MATRIX_HEIGHT - 2, 5, 0, CHSV(h  - 30, 255 - velo / 4, 255));
  zeds.DrawCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CRGB::White);
  // zeds.DrawCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CRGB::White);
  zeds.HorizontalMirror();

}

void confetti() {
  if (random8() < 224)
    zeds.DrawCircle(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), random(1, 7), CHSV(random8(), 255 - velo / 4, 255));
  else
    zeds.DrawCircle(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), random(1, 7), CHSV(h + 128 , 255 - velo / 4, 255));
}

void confetti3() {
  if (counter == 0)
    if (flop[1] || flop[2]) blender = 164;
  if (random8() < blender) {
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(random8(), 255 - velo / 4, 255);
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(random8(), 255 - velo / 4, 255);
  }

  else
  {
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CRGB::White;
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CRGB::White;
  }
}

void confetti4() {
  if (!flop[2]) {
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(blender + (random8() >> 2), 255 - velo / 4, 190 + (random8() >> 2));
    if (counter % 27 == 0)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
  }
  else
  {
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
    if (counter % 27 == 0)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(blender + (random8() >> 2), 255 - velo / 4, 190 + (random8() >> 2));
  }

}

void confetti2() {
  if (random8() > blender)
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(h + random(32), 255 - velo / 4, 255);
  else {
    zeds.DrawCircle(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), random(2, 9), CHSV(h + random(64)  , 255 - random(128), 255));
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(h + random(32), 255 - velo / 4, 255);
  }
}



void bubbles() {
  if (counter == 0)
  {


    howmany = random ((MIDLX >> 1) + 4, MIDLX + 8 );
    for (int16_t u = 0; u < howmany; u++) {
      xfire[u] = random(MATRIX_WIDTH);
      yfire[u]  = random(MATRIX_HEIGHT);
      fvelo[u] = random8();
      if (flop[2])
        fcolor[u] = random8(); //color
      else
        fcolor[u] = 160 + random(50);
      fpeed[u] = random(1, 8); //speed

      fcount[u] = random(3, (MIDLX >> 1) - 4); //radius
      if (random8() > 128)
        rimmer[u] = true;
      else
        rimmer[u] = false;
    }
  }

  for (int16_t u = 0; u < howmany; u++)
  {
    zeds.DrawFilledCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CHSV(fcolor[u], fvelo[u] / 4 + 192, 255));
    if (u % 23 ==  0)
      zeds.DrawFilledCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CRGB::Black);
    if (rimmer[u])
      zeds.DrawCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CHSV(fcolor[u] + 85 , fvelo[u] / 4 + 192, 255));
    else
      zeds.DrawCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CRGB::White);

    if (counter % fpeed[u] == 0)
    {
      if (u % 2 == 0)
      {
        if (u % 4 == 0)
          yfire[u]++;
        else
          yfire[u]--;
      }
      else if (u % 3 == 0)
        xfire[u]++;
      else
        xfire[u]--;

    }
    if (yfire[u] > MATRIX_HEIGHT + fcount[u] + 3  || xfire[u] > MATRIX_WIDTH + fcount[u] + 3 || xfire[u] < -fcount[u] - 4 || yfire[u] < -fcount[u] - 4)
    {

      fcolor[u] = random8(); //color
      fpeed[u] = random(1, 7); //speed
      fcount[u] = random(3, (MIDLX >> 1) - 4); //radius

      if (random8() > 128)
        rimmer[u] = true;
      else
        rimmer[u] = false;
      if (u % 2 == 0)
      {
        xfire[u] = random(3, MATRIX_WIDTH - 3);
        if (u % 4 == 0)
          yfire[u] =   -fcount[u] - 3;
        else
          yfire[u] = MATRIX_HEIGHT + fcount[u] + 3;

      }
      else
      {
        yfire[u] = random(3, MATRIX_HEIGHT - 3);
        if (u % 3 == 0)
          xfire[u] =  -fcount[u] - 3;
        else
          xfire[u] = MATRIX_WIDTH + fcount[u] + 3;
      }

    }
  }
}

void bubbles2() {
  if (counter == 0)
  {
    howmany = random ((MIDLX >> 1) - 4, MIDLX - 8);

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(4,  (MIDLX >> 1) - 4 ); //radius
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
  }

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];

    zeds.DrawFilledCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    if (rimmer[u])
      zeds.DrawCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      zeds.DrawCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void tinybubbles() {
  if (counter == 0)
  {
    howmany = MATRIX_WIDTH * 1.5;

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(3,  9 ); //radius
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
  }

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];

    zeds.DrawFilledCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    if (flop[7] || flop[8])
      if (u % 7 == 0)
        drawstar(xfire[u], yfire[u], fcount[u], fcount[u] / 3, 7, h, fcolor[u] + 128);
    if (rimmer[u])
      zeds.DrawCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      zeds.DrawCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }

}

void koi() {//fish in the pond
  solid6(160 + beatsin16(2, 0, 45, 0));
  if (counter == 0)
  {

    howmany = MIDLX - random(18);
    fcolor[0] = random(MATRIX_WIDTH / 5, MATRIX_WIDTH * 4 / 5); //locatin of lilly pad
    fvelo[0] = random(MATRIX_HEIGHT / 5, MATRIX_HEIGHT * 4 / 5);
    for (int16_t u = 0; u < howmany + 5; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u + 1] = fcolor[u] + random(12) + 12; //locatin of lilly pad
      if (fcolor[u + 1] > MATRIX_WIDTH) fcolor[u + 1] -= MATRIX_WIDTH;
      fvelo[u + 1] = fvelo[u] + random(32) + 16; //locationof lilly pad
      if (fvelo[u + 1] > MATRIX_WIDTH) fvelo[u + 1] -= MATRIX_WIDTH;
      fcount[u] = random(4, 9); //radius
      fpeed[u] = random(1, 8); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }

  }
  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + 0.20 * fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - 0.20 * fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + 0.20 * fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - 0.20 * fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u] || random8() < 16  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u] || random8() < 16 )
      ybouncer[u] = !ybouncer[u];


    for (int16_t j = 0; j < fcount[u]; j++) {
      zeds(xfire[j] + random(4) - 2, yfire[j] + random(4) - 2) = CHSV(random(20) + 16, 255, 255);
      if (random8() > 237)
        zeds(xfire[j] + random(4) - 2, yfire[j] + random(4) - 2) = CRGB::White;
    }

  }


  for (int16_t j = 0; j < 4; j++) {
    zeds.DrawFilledCircle(fcolor[j], fvelo[j], 8 + 2 * j, CHSV(j * 16 + 70, 245, 252));
  }
}


void squarebubbles() {//square

  if (counter == 0)
  {
    howmany = MIDLX - 16;

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(4,  (MIDLX >> 1) - 2 ); //radius
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
  }

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];


    for (int16_t j = 0; j < fcount[u]; j++) {

      drawstar(xfire[u], yfire[u], j * 1.41, j, 4 , h * 2 + fvelo[u], fcolor[u] - h);
    }

  }
}

void starbubbles88() {

  if (counter == 0)
  {
    howmany = MIDLX - 16;

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(6,  (MIDLX >> 1)); //radius size
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
  }

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];

    // zeds.DrawFilledCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    for (int16_t j = 0; j < fcount[u]; j++)
      drawstar(xfire[u], yfire[u], j, j / 3, 3 + (u % 5), h * 2 + fvelo[u], fcolor[u] + h);
    if (flop[7] && u % 11 == 0)
      zeds.DrawCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void tinybubbles2() {
  if (counter == 0)
  {
    howmany = MATRIX_WIDTH * 2 / 3;

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(3,  (MIDLX >> 1) - 2 ); //radius
      fpeed[u] = random(1, 5); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
  }

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];
    if ( flop[3] && u % 7 == 0)
      for (int16_t j = 0; j < fcount[u]; j++)
        drawstar(xfire[u], yfire[u], j, j / 3, 4 + (u % 4), h, fcolor[u]);
    else
      zeds.DrawFilledCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));


    if (rimmer[u])
      zeds.DrawCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      zeds.DrawCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}


void tinybubbles3() {
  if (counter == 0)
  {
    howmany = MATRIX_WIDTH * 2 / 3;

    for (int16_t u = 0; u < howmany; u ++) {
      xfire[u] = random(QUARTER , THREEQUARTERS );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(3,  (MIDLX >> 1) - 6 ); //radius
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 168) {
        rimmer[u] = true;
        xbouncer[u] = false;
        ybouncer[u] = false;

      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
        ybouncer[u] = true;
      }
    }
    howmany = 1;
  }
  /*EVERY_N_SECONDS(2)
    if (howmany < MATRIX_WIDTH * 2 / 3)
    howmany++;
    else
    howmany = 1;
  */
  howmany = beatsin16(2, 1, -1 + MATRIX_WIDTH * 2 / 3, 0);

  for (int16_t u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH - fcount[u]   || xfire[u] < fcount[u]  )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT - fcount[u] || yfire[u] < fcount[u]  )
      ybouncer[u] = !ybouncer[u];

    zeds.DrawFilledCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    if (rimmer[u])
      zeds.DrawCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      zeds.DrawCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void sticks() {

  ccoolloorr = random8();
  if (random8() > 22)
  { zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 4, 255));
    zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 4, 255));
    zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 4, 255));
  }
  else
  { zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
    zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
    zeds.DrawLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
  }
}

void  Bargraph() {
  if (counter == 0)
    for (int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++) {
      fcolor[hhh] = random(MIDLY / 2, MATRIX_HEIGHT - MIDLY / 2 - 1);
      if (pattern == 22 || pattern == 27)
        fcolor[hhh] = random(MIDLY >> 2, MIDLY - 1);
      fpeed[hhh] = random(4, 9);
      fcount[hhh] = 0;
      poffset = random8();
    }


  for (int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
  {
    if (fcount[hhh] > fpeed[hhh])
    {
      if    (pattern == 22 || pattern == 27) {
        if (fcolor[hhh] > MIDLY / 2)
          fcolor[hhh] = fcolor[hhh] - 5 + random(9);
        else
          fcolor[hhh] = fcolor[hhh] - 3 + random(9);

        fcolor[hhh] = constrain(fcolor[hhh], 1, MIDLY - 1);
      }

      else {
        if (fcolor[hhh] > MIDLY)
          fcolor[hhh] = fcolor[hhh] - 5 + random(9);
        else
          fcolor[hhh] = fcolor[hhh] - 3 + random(9);

        fcolor[hhh] = constrain(fcolor[hhh], 1, MATRIX_HEIGHT - 1);

      }

      fcount[hhh] = 0;
      fpeed[hhh] = random(4, 9);
    }
    else
      fcount[hhh]++;

    zeds.DrawLine(hhh, 0, hhh, fcolor[hhh], CHSV(h + poffset + hhh * steper, 255 - velo / 4, 255));

  }
}

void adjustme() {  // applies the screen wide effect
  switch (adjunct) {
    case 0://no effect
      break;
    case 1://no effect
      break;
    case 2:
      zeds.HorizontalMirror();
      zeds.VerticalMirror();
      break;
    case 3:
      zeds.QuadrantBottomTriangleMirror();
      break;
    case 4:
      zeds.HorizontalMirror(1);
      break;
    case 5:
      zeds.VerticalMirror();
      break;
    case 6:
      zeds.QuadrantRotateMirror();
      break;
    case 7:
      zeds.TriangleTopMirror(1);
      break;
    case 8:
      zeds.QuadrantMirror();
      break;
    case 9:
      zeds.HorizontalMirror(1);
      break;
    case 10:
      zeds.TriangleBottomMirror(1);
      break;
    case 11:
      zeds.TriangleBottomMirror(1);
      break;
    case 12:
      zeds.TriangleTopMirror(1);
      zeds.VerticalMirror();
      break;

    default:// no effect
      break;
  }
}

void spire2() {

  if (counter == 0)
  {
    radius =  MATRIX_WIDTH / 2 ;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot + 4 + random(5);
  }

  if (h % 24 == 0)
  {
    if (radius < 4)
      flop[0] = 1 - flop[0];
    if (radius > MATRIX_WIDTH * 2 / 3)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;

    if (radius2 < 4)
      flop[1] = 1 - flop[1];
    if (radius2 > MATRIX_WIDTH * 2 / 3)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }

  float xer = driftx + radius * (cos8(h * 2) - 128.0) / 128.0;
  float yer = drifty + radius * (sin8(h * 2) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h , 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 128, 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx + radius * (cos8(h * 2 + 85) - 128.0) / 128.0;
  yer = drifty + radius * (sin8( h * 2 + 85) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 85, 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2 + 85) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2 + 85) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 128 + 85, 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);

  xer = driftx + radius * (cos8(h * 2 + 174) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(h * 2 + 174) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 174, 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2 + 174) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2 + 174) - 128.0) / 128.0;
  zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 128 + 174, 255 - velo / 4, 255));
  if (flop[2])  zeds.DrawCircle(xer, yer, dot + 1, CRGB::White);
}

void spire3() {

  if (counter == 0)
  {
    radius =  MIDLX + 7;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot  + random(1, 5);
    howmany = random (4, 8);
  }


  if (h % 16 == 0)
  {

    if (radius < 4)
      flop[0] = 1 - flop[0];
    if (radius > 8 + MATRIX_WIDTH / 2)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;


    if (radius2 < 4)
      flop[1] = 1 - flop[1];
    if (radius2 > 8 + MATRIX_WIDTH / 2)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }
  for (int16_t i = 0; i < howmany; i++) {
    float xer = driftx + radius * (cos8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    float yer = drifty + radius * (sin8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      zeds.DrawCircle(xer, yer, dot + 1, CHSV(h + i * 256 / howmany, 255 - velo / 4, 255));
    else {
      zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + i * 256 / howmany, 255 - velo / 4, 255));
      zeds.DrawCircle(xer, yer, dot, CHSV(85 + h + i * 256 / howmany, 255 - velo / 4, 255));
    }
    xer = driftx - radius2 * (cos8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    yer = drifty - radius2 * (sin8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      zeds.DrawCircle(xer, yer, dot + 1, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 4, 255));
    else {
      zeds.DrawFilledCircle(xer, yer, dot, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 4, 255));

      zeds.DrawCircle(xer, yer, dot, CHSV(85 + h + 32 + i * 256 / howmany, 255 - velo / 4, 255));
    }
  }
}

void spire() {

  if (counter == 0)
  {
    radius =  MATRIX_WIDTH / 2 ;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot + 3 + random(5);
  }

  if (h % 16 == 0)
  {
    if (radius < 2)
      flop[0] = 1 - flop[0];
    if (radius > MATRIX_WIDTH * 2 / 3)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;

    if (radius2 < 2)
      flop[1] = 1 - flop[1];
    if (radius2 > MATRIX_WIDTH * 2 / 3)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }

  float xer = driftx + radius * (cos8(2 * h) - 128.0) / 128.0;
  float yer = drifty + radius * (sin8(2 * h) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h, 255 - velo / 4, 255));
  xer = driftx - radius * (cos8(2 * h) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h + 128, 255 - velo / 4, 255));

  xer = driftx + radius * (cos8(2 * h + 84) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(2 * h + 84) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h + 84, 255 - velo / 4, 255));
  xer = driftx - radius * (cos8(2 * h + 84) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h + 84) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h - 84, 255 - velo / 4, 255));

  xer = driftx + radius * (cos8(2 * h + 42) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(2 * h + 42) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h + 42, 255 - velo / 4, 255));
  xer = driftx - radius * (cos8(2 * h + 42) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h + 42) - 128.0) / 128.0;
  zeds.DrawCircle(xer, yer, dot, CHSV(h - 42, 255 - velo / 4, 255));
}

void triple() {
  if (counter == 0) {
    radius2 = random(MATRIX_WIDTH / 4 , MATRIX_WIDTH / 2) - 5;
  }
  dot2 = beatsin16(7, 3, 9, 0);
  radius3 = beatsin16(3, radius2 / 2 - 4, radius2 * 3 / 2, 0);
  for (int16_t i = radius2 ; i > 1 ; i--) {
    zeds.DrawFilledCircle(driftx + ((radius3 * (cos8(h * dot) - 128)) >> 7), drifty + ((radius3 * (sin8(h * dot) - 128)) >> 7), i, CHSV( h + dot2 * i, 255 - velo / 4, 255));
    zeds.DrawFilledCircle(driftx + ((radius3 * (cos8(h * dot + 85) - 128) ) >> 7), drifty + ((radius3 * (sin8(h * dot + 85 ) - 128) ) >> 7), i, CHSV(h + dot2 * i + 85 , 255 - velo / 4, 255));
    zeds.DrawFilledCircle(driftx + (( radius3 * (cos8(h * dot - 85) - 128)) >> 7), drifty + ((radius3 * (sin8(h * dot - 85 ) - 128) ) >> 7), i, CHSV(h + dot2 * i - 85  , 255 - velo / 4, 255));
    if (!flop[2]) {
      zeds.DrawFilledCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot + 42) - 128)) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot + 42) - 128)) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 , 255 - velo / 4, 255));
      zeds.DrawFilledCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot + 85 + 42) - 128) ) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot + 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 + 85  , 255 - velo / 4, 255));
      zeds.DrawFilledCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot - 85 + 42) - 128)) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot - 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 - 85   , 255 - velo / 4, 255));
    }
    else
    {
      zeds.DrawFilledCircle(driftx + ((dot  * radius3 * (cos8(h * dot + 42) - 128)) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot + 42) - 128)) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 , 255 - velo / 4, 255));
      zeds.DrawFilledCircle(driftx + ((dot  * radius3 * (cos8(h * dot + 85 + 42) - 128) ) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot + 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 + 85  , 255 - velo / 4, 255));
      zeds.DrawFilledCircle(driftx + ((dot  * radius3 * (cos8(h * dot - 85 + 42) - 128)) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot - 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 - 85   , 255 - velo / 4, 255));
    }
  }
}

void siny() {

  if (counter == 0) {
    radius2 = random(MATRIX_WIDTH >> 2, (MATRIX_WIDTH >> 1) - 4);
    radius3 = random (4, MIDLX - 4 );
    ringdelay = ringdelay * random(2, 5);
  }
  if (flop[1]) {
    zeds.DrawCircle(MIDLX + ((radius3 * (cos8(-h * 3) - 128)) >> 7), MIDLY + ((radius3 * (sin8(-h * 3) - 128)) >> 7), radius2 + 1, CHSV(h * 2 , 255 - velo / 4, 255));
    zeds.DrawCircle(MIDLX + ((radius3 * (cos8(-h * 3 + 128) - 128)) >> 7), MIDLY + ((radius3 * (sin8(-h * 3 + 128) - 128)) >> 7), radius2 - 1, CHSV(h * 2 + 128 , 255 - velo / 4, 255));
  }
  else {
    zeds.DrawCircle(MIDLX + ((radius3 * (cos8(h * 3) - 128)) >> 7), MIDLY + ((radius3 * (sin8(h * 3) - 128)) >> 7), radius2 + 1, CHSV(h * 2 , 255 - velo / 4, 255));
    zeds.DrawCircle(MIDLX + ((radius3 * (cos8(h * 3 + 128) - 128)) >> 7), MIDLY + ((radius3 * (sin8(h * 3 + 128) - 128)) >> 7), radius2 - 1, CHSV(h * 2 + 128 , 255 - velo / 4, 255));
  }
}
void whitewarp() {
  if (counter == 0 )
  {
    howmany = random (MIDLX , MATRIX_WIDTH + 4 );

    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = random8();
      fvelo[i] = random8();
      fpeed[i] = random(2, 12);
      xfire[i] = driftx;
      yfire[i] = drifty;

    }
  }

  for (int i = 0; i < howmany; i++)
  {
    xfire[i] = xfire[i] + fpeed[i] / 4.0 * (sin8(fcount[i] + h ) - 128.0) / 128.0;
    yfire[i] = yfire[i] + fpeed[i] / 4.0 * (cos8(fcount[i] + h ) - 128.0) / 128.0;

    if (flop[6])
      zeds(xfire[i], yfire[i]) = CRGB::White;
    else
      zeds(xfire[i], yfire[i]) = CHSV(fcolor[i] , fvelo[i] / 4 + 192, 255); //one shade of color

    if (xfire[i] < 0 || yfire[i] < 0 || xfire[i] > MATRIX_WIDTH || yfire[i] > MATRIX_HEIGHT) {
      xfire[i] = driftx;
      yfire[i] = drifty;
      fcount[i] = random8(); //angle
      fcolor[i] = random8();
      fvelo[i] = random8();
      fpeed[i] = random8(2, 12);
    }
  }
  if (flop[6]) {
    zeds(xfire[howmany - 1], yfire[howmany - 1]) = CHSV(fcolor[howmany - 1] , fvelo[howmany - 1] / 4 + 192, 255); //many color
    zeds(xfire[howmany - 2], yfire[howmany - 2]) = CHSV(fcolor[howmany - 2] , fvelo[howmany - 2] / 4 + 192, 255); //many color
  }
  else {
    zeds(xfire[howmany - 1], yfire[howmany - 1]) = CRGB::White;
    zeds(xfire[howmany - 2], yfire[howmany - 2]) = CRGB::White;
  }
}

void warp() {
  if (counter == 0 )
  {
    howmany = random (MIDLX , MATRIX_WIDTH * 7 / 5);

    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random(45);//color
      fvelo[i] = random8();
      fpeed[i] = random(2, 12);
      xfire[i] = driftx;
      yfire[i] = drifty;

    }
  }

  for (int i = 0; i < howmany; i++)
  {
    xfire[i] = xfire[i] + (fpeed[i] / 4.0) * (sin8(fcount[i] + h ) - 128.0) / 128.0;
    yfire[i] = yfire[i] + ( fpeed[i] / 4.0) * (cos8(fcount[i] + h ) - 128.0) / 128.0;
    if (!flop[0])
      zeds(xfire[i], yfire[i]) += CHSV(fcolor[i], fvelo[i] / 2 + 128, 255); //random colors
    else if (!flop[1])
      zeds(xfire[i], yfire[i]) += CRGB::White;
    else
      zeds(xfire[i], yfire[i]) += CHSV(blender * 64 / howmany, fvelo[i] / 2 + 128, 255); //one shade of color

    if (xfire[i] < 0 || yfire[i] < 0 || xfire[i] > MATRIX_WIDTH || yfire[i] > MATRIX_HEIGHT) {
      xfire[i] = driftx;
      yfire[i] = drifty;
      fcount[i] = random8(); //angle
      fcolor[i] = random8();;
      fpeed[i] = random8(2, 8);
    }
  }
  if (!flop[1]) {
    zeds(xfire[howmany - 1], yfire[howmany - 1]) = CHSV(blender + 64 / howmany , fvelo[howmany - 1] / 2 + 128, 255);
    zeds(driftx, drifty) = CHSV(blender - 64 / howmany , 255 - velo / 4, 255);
  }
  else {
    zeds(xfire[howmany - 1], yfire[howmany - 1]) = CRGB::White;
    zeds(driftx, drifty) = CRGB::White;
  }
}


void spiralz() {
  if (counter == 0 )
  {
    howmany = random(MIDLX / 3, QUARTER );
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int16_t jj = 0; jj < MATRIX_WIDTH ; jj++) {

      if (flop[1]) {//crazy helix
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] - h - (dot - 2) * jj ) - 128.0) / 128.0;
      }
      else {//clasic spiral
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
      }
      if (!flop[2])
        zeds(xx, yy) += CHSV(blender + fcount[i] + h , 245, 235); //
      else
        zeds(xx, yy) += CHSV(blender + jj * 2 + h , 245, 235); //

    }
  }
  zeds.DrawRectangle(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB::Black);
}

void spiral2() {
  if (counter == 0 )
  {
    howmany = random(MIDLX / 3,  QUARTER ) + 2;
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int16_t jj = 0; jj < 8 + triwave8(counter % 255) / 4  ; jj++)
    {

      if (flop[1]) {//crazy helix
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] - h - (dot - 2) * jj ) - 128.0) / 128.0;
      }
      else {//clasic spiral
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
      }
      if (!flop[2])
        zeds(xx, yy) += CHSV(blender + fcount[i] + h , 255, 255); //
      else
        zeds(xx, yy) += CHSV(blender + jj * 2 + h , 255, 255); //

    }
  }

  for (int i = 0; i < howmany / 2; i++)
  {
    for (int16_t jj = 0; jj < 8 + triwave8(counter % 255) / 4 ; jj++) {



      xx =  driftx + jj  * (sin8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;
      yy = drifty + jj  * (cos8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;

      if (!flop[2])
        zeds(xx, yy) += CHSV(128 + blender + fcount[i] + h , 255, 255); //
      else
        zeds(xx, yy) += CHSV(128 + blender + jj * 2 + h , 255, 255); //

    }
  }

  //  zeds.DrawRectangle(0, 0, MATRIX_WIDTH-1, MATRIX_HEIGHT-1, CRGB::Black);
}


void spiral3() {
  if (counter == 0 )
  {
    howmany = random(MIDLX / 3,  QUARTER ) + 2;
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int16_t jj = 0; jj < 32 + triwave8(counter % 255) / 8  ; jj++)
    {
      if (flop[1] || flop[6] || flop[8] || flop[3]) { //crazy helix
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] - h - (dot - 2) * jj ) - 128.0) / 128.0;
      }
      else {//clasic spiral
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
      }
      if (!flop[2])
        zeds(xx, yy) += CHSV(blender + fcount[i] + h , 255 - velo / 4, 255); //
      else
        zeds(xx, yy) += CHSV(blender + jj * 2 + h , 255 - velo / 4, 255); //

    }
  }

  for (int i = 0; i <  (howmany / 2); i++)
  {
    for (int16_t jj = 0; jj < 16 + triwave8((counter + blender) % 255) / 6  ; jj++)
    {
      xx =  driftx + jj  * (sin8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;
      yy = drifty + jj  * (cos8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;

      if (!flop[2])
        zeds(xx, yy) += CHSV(128 + blender + fcount[i] + h , 255 - velo / 4, 255); //
      else
        zeds(xx, yy) += CHSV(128 + blender + jj * 2 + h , 255 - velo / 4, 255); //

    }
  }

  zeds.DrawRectangle(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB::Black);
}

void lfado(int16_t bbc)
{
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH; hhh++)
    for (int16_t jjj = 0; jjj < MATRIX_HEIGHT; jjj++)
      //  zeds(hhh, jjj).fadeToBlackBy(bbc);//% = bbc/255
      zeds(hhh, jjj) -= CRGB(bbc, bbc, bbc); //
}


void redfado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int16_t jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (flop[1])
        zeds(hhh, jjj) -= CRGB(random(bbc / 2), random(bbc), random(bbc));//leave more red
      else
        zeds(hhh, jjj) -= CRGB(random(bbc / 2), random(bbc / 2), random(bbc));// leave more yellow
}

void greenfado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int16_t jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (!flop[2])
        zeds(hhh, jjj) -= CRGB(random(bbc ), random(bbc / 2), random(bbc));
      else
        zeds(hhh, jjj) -= CRGB(random(bbc ), random(bbc / 2), random(bbc / 2));// leave more teal
}

void bluefado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int16_t jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (flop[1])
        zeds(hhh, jjj) -= CRGB(random(bbc), random(bbc), random(bbc / 2));
      else
        zeds(hhh, jjj) -= CRGB(random(bbc / 2 ), random(bbc), random(bbc / 2)); //leave more purple

}




void xspin()  // many fingers moving in arc to middle
{
  if (counter == 0) {
    ccoolloorr = random8();
    dot = random(3, 6);

    hhowmany = random(3, 11);
    raad = 256.0 / hhowmany;
    radius = 3;
    flop[3] = true;
  }

  if ((counter % (3 * MATRIX_WIDTH))  == 0) { //-5
    dot = random(3, 6);
    ccoolloorr =  random8();
    hhowmany = random(3, 8);
    raad = 256 / hhowmany;
    radius2 = random(2, 6);//spin speed
    if (random8() > 128) flop[3] = !flop[3];
    // Serial.println(flop[3]);
  }

  for (int16_t q = 0; q < hhowmany; q++) {
    if (flop[3] == true) {
      eeksangle =  (sin8((radius2 * h + raad * q)) - 128.0) / 128.0;
      whyangle =  (cos8((radius2 * h +  raad * q)) - 128.0) / 128.0;
      zeds.DrawFilledCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CHSV(ccoolloorr +  h, 255 - velo / 4, 255));
      if (ccoolloorr % 16 == 0)
        zeds.DrawFilledCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CRGB::White);
    }
    if (flop[3] == false)
    {
      eeksangle =  (sin8((  raad * q - radius2 * h)) - 128.0) / 128.0;
      whyangle =  (cos8((  raad * q - radius2 * h)) - 128.0) / 128.0;
      zeds.DrawFilledCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CHSV(ccoolloorr + 2 * h, 255 - velo / 4, 255));
      if (ccoolloorr % 16 == 0)
        zeds.DrawFilledCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CRGB::White);
    }

  }
  if ( flop[0]) {
    if (counter % (2 * MATRIX_WIDTH) - 2 == 0)
      zeds.DrawFilledCircle(driftx  , drifty  , dot , CHSV(ccoolloorr + 21, 255 - velo / 4, 255));
    if (counter % (2 * MATRIX_WIDTH) - 3 == 0)
      zeds.DrawFilledCircle(driftx  , drifty  , dot - 1, CHSV(ccoolloorr + 42, 255 - velo / 4, 255));
    if (counter % (2 * MATRIX_WIDTH) - 4 == 0) {
      zeds.DrawFilledCircle(driftx  , drifty  , dot - 2, CHSV(ccoolloorr + 63, 255 - velo / 4, 255));

    }
  }
}

void spin2()  // 4 meteriorw moving in ovals
{
  if (counter == 0)
  {
    dot += 5;
    if (flop[6] || flop[7])
      ccoolloorr = 64;
    else
      ccoolloorr = 0;
  }


  if (!flop[8]) {
    xangle =  (sin8(2 * (h )) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h )) - 128.0) / 128.0;
  }
  else
  {
    xangle =  (sin8(-2 * (h )) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h )) - 128.0) / 128.0;
  }
  zeds.DrawFilledCircle(MIDLX + xangle * (QUARTER ), MIDLY + yangle * (MIDLY ) , dot, CHSV(h + 2 * ccoolloorr, 200, 199));
  zeds.DrawCircle(MIDLX + xangle * (QUARTER ), MIDLY + yangle * (MIDLY ) , dot, CHSV(h + 2 * ccoolloorr - 16, 255, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) + 64) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) + 64) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) + 64) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) + 64) - 128.0) / 128.0;
  }
  zeds.DrawFilledCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot, CHSV(h , 200, 199));
  zeds.DrawCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot, CHSV(h - 16, 255, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) + 128) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) + 128) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) + 128) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) + 128) - 128.0) / 128.0;
  }
  zeds.DrawFilledCircle(MIDLX + xangle * (QUARTER ), MIDLY + yangle * (MIDLY ) , dot, CHSV(h + ccoolloorr, 200, 199));
  zeds.DrawCircle(MIDLX + xangle * (QUARTER ), MIDLY + yangle * (MIDLY ) , dot, CHSV(h + ccoolloorr - 16, 255, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) - 64) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) - 64) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) - 64) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) - 64) - 128.0) / 128.0;
  }

  zeds.DrawFilledCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot, CHSV(h - ccoolloorr, 200, 199));
  zeds.DrawCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot, CHSV(h - ccoolloorr - 16, 255, 255));
}

void magictime()
{
  if (counter == 0)
  {
    locusx = driftx;
    locusy = drifty;
    raad = random(MATRIX_WIDTH / 2, MATRIX_WIDTH * 2 / 3);
    ringdelay = 50;
  }

  if (raad > 1)
  {
    zeds.DrawFilledCircle(locusx, locusy , raad, CHSV(h * 3 , 255 - (counter % 128), 255));
    raad = raad - 1;
  }

  if (raad == 2)
  {
    ringdelay = random(20, 70);
    // zeds.DrawFilledCircle(locusx, locusy , raad, CHSV(ccoolloorr ,velo+196, 255));
    //  zeds( locusx, locusy)  = CRGB::White;
    raad = raad - 1;
  }
  if (raad == 1) {
    ringdelay--;
  }

  if (ringdelay == 0)
  {
    raad = random(MATRIX_WIDTH / 2, MATRIX_WIDTH * 2 / 3);
    locusx = driftx;
    locusy = drifty;
    ringdelay = random(40, 90);
  }
}

void rmagictime()
{

  if (counter == 0)
  {

    raad = 1;
    ringdelay = random(40, 70);
    ccoolloorr = random8();
  }

  if (raad < MATRIX_WIDTH - dot)
  {
    zeds.DrawCircle(driftx, drifty , raad, CHSV(ccoolloorr + h , 255 - velo / 4, 255));
    zeds.DrawCircle(driftx, drifty , raad + 1, CHSV(ccoolloorr + h , 255 - velo / 4, 255));
    zeds.DrawCircle(driftx, drifty , raad - 1, CHSV(ccoolloorr + h , 255 - velo / 4, 255));
    raad++;
  }

  if (raad == MATRIX_WIDTH - dot) {
    ringdelay--;
    //ringdelay = constrain(ringdelay, 0, 20);
  }

  if (ringdelay == 0)
  {
    raad = 1;

    ringdelay = random(40, 70);
    //  ccoolloorr = random(8);
  }
}


void splat()
{
  xsizer = random(MATRIX_WIDTH / 5, MATRIX_WIDTH / 3);
  ysizer = random(MATRIX_WIDTH / 5, MATRIX_WIDTH / 3);
  raad =  random(MATRIX_WIDTH / 5, MATRIX_WIDTH / 3);
  locusx = random(2, MATRIX_WIDTH - 2);
  locusy = random(2, MATRIX_WIDTH - 2);

  ccoolloorr = random8();
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, random(180, 255), random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, 255 - velo / 4, random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, random(180, 255), random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, 255 - velo / 4, random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, random(180, 255), random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, 255 - velo / 4, random(180, 255));
  zeds(random8() / mstep, random8() / mstep) = CHSV(h, random(180, 255), random(180, 255));

  switch (random(10))
  {
    case 0:
      zeds.DrawRectangle(locusx, locusy , locusx + xsizer , locusy + ysizer, CHSV(ccoolloorr , 255 - (counter % 34), 255));
      break;
    case 1:
      zeds.DrawCircle(locusx, locusy , raad, CHSV(ccoolloorr , 255 - velo / 4, 255));
      break;
    case 2:
      zeds.DrawFilledRectangle(locusx, locusy , locusx + xsizer , locusy + ysizer, CHSV(ccoolloorr , 255 - (counter % 34), 255));
      break;

    case 3:
      zeds.DrawFilledCircle(locusx, locusy , raad, CHSV(ccoolloorr , 255 - velo / 4, 255));
      break;
    case 4:
      zeds.DrawFilledRectangle(locusx, locusy , locusx + xsizer , locusy + ysizer, CHSV(ccoolloorr , 255 - (counter % 58), 255));
      break;

    case 5:
      for (int16_t i = 7; i > 0 ; i--)
        zeds.DrawFilledRectangle(locusx - i, locusy - i , locusx + 2 * i , locusy + 2 * i, CHSV(ccoolloorr + i * steper, 255 - (counter % 46), 255));
      break;

    case 6:
      for (int16_t i = raad; i > 0; i--)
        zeds.DrawFilledCircle(locusx, locusy , i, CHSV(ccoolloorr + i * steper , 255 - (counter % 58), 255));
      break;

    case 7:
      triangle(locusx, locusy, raad, h, ccoolloorr);
      break;

    case 8:

      sticks();
      sticks();
      break;

    case 9:
      zeds(locusx, locusy) = CHSV(ccoolloorr, 255 - velo / 4, 255);
      zeds(random8() / mstep, random8() / mstep) = CHSV(random8(), 255 - velo / 4, random(180, 255));
      zeds(random8() / mstep, random8() / mstep) = CHSV(random8(), 255 - velo / 4, random(180, 255));
      zeds(random8() / mstep, random8() / mstep) = CHSV(random8(), 255 - velo / 4, random(180, 255));
      zeds(random8() / mstep, random8() / mstep) = CHSV(h, 255 - velo / 4, random(180, 255));
      zeds(random8() / mstep, random8() / mstep) = CHSV(h, random(180, 255), random(180, 255));
      break;

  }

}

void bouncez()
{

  if (counter == 0)
  {
    locusx = MIDLX;
    locusy = MIDLY;
    raad =  random(MATRIX_WIDTH / 4,  MATRIX_WIDTH / 3);

    yangle = random(13, 52);
    xangle = (sin8(yangle) - 128.0) / 128.0;
    yangle = (cos8(yangle) - 128.0) / 128.0;
    xsizer = random(MATRIX_WIDTH / 4, MATRIX_WIDTH / 3);
    ysizer = xsizer;
    ccoolloorr = random8();
  }

  locusx =  locusx + xangle;
  locusy =  locusy + yangle;
  driftx = locusx;
  drifty = locusy;

  if (flop[2])
    ccoolloorr = ccoolloorr - 6;
  else
    ccoolloorr = ccoolloorr + 6;

  if (blender <= 127) {

    if (locusx > MATRIX_WIDTH - raad  || locusx < raad ) {
      if (!flop[2]) ccoolloorr = random8();
      xangle = 0 - xangle;
    }
    if (locusy > MATRIX_HEIGHT - raad  || locusy < raad  ) {
      yangle = 0 - yangle;
      if (!flop[2]) ccoolloorr = random8();
    }
    zeds.DrawCircle(locusx, locusy , raad, CHSV(ccoolloorr, 255 - velo / 4, 255));
    if (flop[1])
      zeds.DrawCircle(locusx, locusy , raad / 2, CHSV(ccoolloorr + 128, 255 - velo / 4, 235));
    if ( flop[0])
      zeds.DrawCircle(locusx, locusy , raad / 4, CHSV(ccoolloorr, 255 - velo / 4, 215));
  }
  if (blender > 127 ) {

    if (locusx > MATRIX_WIDTH - xsizer || locusx < 1)
      xangle = 0 - xangle;
    if (locusy > MATRIX_HEIGHT - ysizer || locusy < 1 )
      yangle = 0 - yangle;
    zeds.DrawRectangle(locusx, locusy , locusx + xsizer , locusy + ysizer, CHSV(ccoolloorr , 255 - velo / 4, 255));
    if (!flop[1] || flop[4] || flop[7])
      zeds.DrawCircle(locusx + xsizer / 2, locusy + xsizer / 2 , xsizer / 2 - 1, CHSV(ccoolloorr + 85 , 255 - velo / 4, 255));
  }
}

//void triangle(int16_t xloc, byte yloc, byte bigg, byte angle, byte kolor)
void starbounce()
{

  if (counter == 0)
  {
    locusx = driftx;
    locusy = drifty;
    raad =  random(MATRIX_WIDTH ,  THREEHAVES); //size
    howmany = random (3, 8);
    radius2 = random(16, 48);
    xangle = (sin8(radius2) - 128.0) / 128.0;
    yangle = (cos8(radius2) - 128.0) / 128.0;
    ccoolloorr = random8();
  }

  /* locusx =  locusx +  xangle;
    locusy =  locusy +  yangle;*/
  locusx = driftx;
  locusy = drifty;

  if (locusx > MATRIX_WIDTH - raad  || locusx < raad ) {

    xangle = 0 - xangle;
  }
  if (locusy > MATRIX_HEIGHT - raad  || locusy < raad  ) {
    yangle = 0 - yangle;

  }

  // triangle(locusx, locusy, raad, h * 2, ccoolloorr - 2 * h);
  drawstar(locusx, locusy, raad, raad / 2, howmany, h * 3, ccoolloorr + 2 * h); // random multipoint star
  if (flop[1]) {
    drawstar(locusx, locusy, raad / 2, raad / 4, howmany, -h * 3, ccoolloorr + 2 * h + 85);
    drawstar(locusx, locusy, raad / 4, raad / 8 - 1, howmany, h * 3, ccoolloorr + 2 * h - 85);
  }
  else
  { drawstar(locusx, locusy, raad / 2, raad / 4, howmany, -h * 3, ccoolloorr + 2 * h + 128);
    drawstar(locusx, locusy, raad / 4, raad / 8 - 1, howmany, h * 3, ccoolloorr + 2 * h);
  }// random multipoint star
  //void triangle(int16_t xloc, byte yloc, byte bigg, byte angle, byte kolor)
}

void triforce() {
  if (flop[0] &&  flop[2])
    solid2(96);
  else if (flop[0] && !flop[1])
    solid(85);

  for (int16_t i = 0; i < MIDLX; i += dot + 3) {
    triangle(MIDLX, MIDLY, MIDLX + 2 - i, h,  h - 85);
    if (i % 2 == 0)
      triangle(MIDLX, MIDLY, MIDLX + 2 - i, h,  h + 85);
  }
}
void seasick3()
// horizontal waves
{
  if (counter == 0) sinewidth = random(8, 12);
  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    zeds.DrawLine(jj, 0, jj, MATRIX_HEIGHT  - 1, CHSV(h + jj  + 85, 255 - velo / 4, 255));
    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8(4 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.55 + 1, jj, MATRIX_HEIGHT  - 1, CHSV(h + jj + 170, 255 - velo / 4, 255));
    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8(-4 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.45 + 2 , jj, MATRIX_HEIGHT  - 1, CHSV(h + jj , 255 - velo / 4, 255));
  }
}

void seasickness()
// full size waves overlapping with minimal fade...
{
  if (counter == 0) sinewidth = random(5, 8);
  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    for ( int u = 0; u < 4; u++) {
      zeds(jj, (MIDLY - 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY  + u - 2) += CHSV(h  + 128, 255 - velo / 4, 255);
      zeds(jj, (MIDLY - 1 ) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY  + u - 2) += CHSV(h  , 255 - velo / 4, 255);

      /* zeds(jj, (MIDLY >> 1) * (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.70 + u - 2) += CHSV(h  + 85,velo+196, 255);
        zeds(jj, (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.3 + u - 2) += CHSV(h   ,velo+196, 255);
        zeds(jj , (MIDLY >> 1) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLY  + u - 2) += CHSV(h  - 85,velo+196, 255);*/
    }
    if (flop[5])
    {
      if (flop[1])
        zeds(jj , (MIDLY >> 1) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLY ) = CHSV(blender, 255 - velo / 4, 255);
      else {
        if (flop[2])
          zeds(jj , (MIDLY >> 1) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLY ) = CRGB::Black;
        else if ( flop[0])
          zeds(jj , (MIDLY >> 1) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLY ) = CRGB::White;
      }
    }
  }

}

void seasick2()
// horizontal  and vertical waves
{

  if (counter == 0)
    sinewidth = random(2, 5);

  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    for ( int kk = -MIDLY / 4; kk < MIDLY / 4; kk++) {
      zeds(jj, (MIDLY ) * (sin8(2 * h + jj * 2 * sinewidth) - 128) / 128.0 + MIDLY  + kk) += CHSV(h  , 255 - velo / 4, 255);
      zeds((MIDLX ) * (sin8(2 * -h + jj * sinewidth) - 128) / 128.0 + MIDLX  + kk, jj) += CHSV(h + 128 , 255 - velo / 4, 255);
    }
  }
}
void seasick()
// horizontal waves
{
  if (counter == 0)
    sinewidth = random(4, 12);
  if (flop[1]) {


    solid5();
  }
  else
    solid3(48);


  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {

    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8(-4 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.60 + 1, jj, 0, CHSV(h + jj + 170, 255 - velo / 4, 255));
    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.4 + 2 , jj, MATRIX_HEIGHT  - 1, CHSV(h + jj , 255 - velo / 4, 255));
  }
}

void seasick4()
// horizontal waves
{
  if (!flop[0]) {

    solid4();
  }
  else if (flop[1])
    solid3(85);

  if (counter == 0) sinewidth = random(5, 10);
  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    for ( int u = 0; u < 6; u++) {
      zeds(jj, (MIDLY >> 1) * (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.70 + u - 3) += CHSV(h + jj + 128, 255, 255);
      zeds(jj, (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.3 + u - 3) += CHSV(h + jj + 64 , 255, 255);
      zeds(jj , (MIDLY - 3) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLY  + u - 3) += CHSV(h + jj  - 64, 255, 255);
      if (!flop[2])
        zeds((MIDLX >> 1) * (sin8(h + jj * sinewidth) - 128) / 128.0 + MIDLX  + u - 3, jj) += CHSV(h + jj, beatsin16(5, 222, 255, 0), 255);
      if (flop[5])
        zeds((MIDLX - 3) * (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 + MIDLX  + u - 3, jj) += CHSV(jj - h, beatsin16(3, 222, 255, 0), 255);
    }
  }
}


void seasick5()
// horizontal waves
{

  if (counter == 0)
    sinewidth = random(4, 12);
  if (!flop[1])
    solid2(96);
  else
    bfade = 9;

  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {

    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8(-h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.50 + 1, jj, 0, CHSV(h + jj + 128, 255 - velo / 4, 255));
    zeds.DrawLine(jj, (MIDLY >> 1) * (sin8( h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.5 + 2 , jj, MATRIX_HEIGHT  - 1, CHSV(h + jj , 255 - velo / 4, 255));
  }

  if (counter == 0) sinewidth = random(5, 10);
  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    zeds(jj, (MIDLY >> 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.80 + 2) += CHSV(h + jj - 64, 255 - velo / 4, 255);
    zeds(jj, (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.2 + 2) += CHSV(h + jj + 64 , 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.80 + 1) += CHSV(h + jj - 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.2 + 1) += CHSV(h + jj + 64 , 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.80) += CHSV(h + jj - 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.2) += CHSV(h + jj + 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.80 - 1) += CHSV(h + jj - 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.2 - 1) += CHSV(h + jj + 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 0.80 - 2) += CHSV(h + jj - 64, 255 - velo / 4, 255);
    zeds(jj , (MIDLY >> 1) * (sin8(2 * h + jj * sinewidth) - 128) / 128.0 + MIDLY * 1.2 - 2) += CHSV(h + jj + 64, 255 - velo / 4, 255);
  }
}

void smile()
{
  zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h , 255 - velo / 4, 255));
  zeds.DrawFilledCircle(MIDLX, MIDLY, MIDLX , CHSV(h + 100, 255 - velo / 4, 255)); //face
  zeds.DrawFilledCircle(MIDLX, MIDLY + 1, MIDLX - 5 , CRGB::Black);
  zeds.DrawFilledCircle(MIDLX, MIDLY - 1, MIDLX - 5 , CHSV(h + 100 , 255 - velo / 4, 255));
  zeds.DrawFilledCircle((QUARTER ) + 1, (MIDLY / 2) + 1 , 3, CRGB::Black); //eye
  zeds.HorizontalMirror();
}

void smile2()
{
  //  zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(180 ,velo+196, 255));
  Ringo();
  zeds.DrawFilledCircle(MIDLX, MIDLY, MIDLX ,  CHSV(58 , 255 - velo / 4, 255)); //face = yellow;
  zeds.DrawFilledCircle(MIDLX, MIDLY + 1, MIDLX - 5 , CRGB::Black);
  zeds.DrawFilledCircle(MIDLX, MIDLY - 1, MIDLX - 5 , CHSV(58 , 255 - velo / 4, 255));
  zeds.DrawFilledCircle((QUARTER ) + 1, (MIDLY / 2) + 1 , 3, CRGB::Black); //eye
  zeds.HorizontalMirror();
}

void smile4()//one eye cylon
{
  zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h * 2 , 255 - velo / 4, 200));
  zeds.DrawFilledCircle(MIDLX, MIDLY, MIDLX , CHSV(58 , 255 - velo / 4, 255)); //face = yellow
  zeds.DrawFilledCircle(MIDLX, MIDLY + 1, MIDLX - 5 , CRGB::Black);//mouth
  zeds.DrawFilledCircle(MIDLX, MIDLY - 1, MIDLX - 5 , CHSV(58 , 255 - velo / 4, 255)); //antimouth also yellow
  zeds.DrawFilledCircle(MIDLX + MIDLY / 2 * (cos8(h) - 128.0) / 128.0 , (MIDLY / 2) + 2 , 3, CRGB::Black); //eye
}
void smile3()
{
  // zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h * 2 + 170 , 255 - velo / 4, 255));
  Ringo();
  zeds.DrawFilledCircle(MIDLX, MIDLY, MIDLX , CHSV(h * 2 + 85 , 255 - velo / 4, 255)); //face
  zeds.DrawFilledCircle(MIDLX, MIDLY + 1, MIDLX - 5 , CHSV(h * 2 , 255 - velo / 4, 255));
  zeds.DrawFilledCircle(MIDLX, MIDLY - 1, MIDLX - 5 , CHSV(h * 2 + 85 , 255 - velo / 4, 255));
  zeds.DrawFilledCircle((QUARTER ) + 1, (MIDLY / 2) + 1 , 3, CHSV(h * 2, 255 - velo / 4, 255)); //eye
  zeds.HorizontalMirror();
}

void hypnoduck() {
  // pair of  spiral discs - hyponic light
  if (counter == 0) {
    dot = random(2, 4);
    quash = -20;//spin speed and direction
  }
  xxx = MIDLX + QUARTER  * (sin8(h) - 128.0) / 128.0;
  yyy = MIDLY + MIDLY / 2 * (cos8(h) - 128) / 128.0;

  //zeds.DrawFilledCircle(xxx, yyy, 9 + (MIDLX >> 1), CHSV( h + 85 ,velo+196, 255));//background circle

  for (int jj = 0; jj < 390; jj += 5)
  {
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    zeds.DrawFilledCircle(xxx - xangle * (jj /  17) , yyy - yangle * (jj / 17), dot, CHSV( h, 255 - velo / 4, 255));

    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    zeds.DrawFilledCircle(xxx - xangle * (jj /  17) , yyy - yangle * (jj / 17), dot, CHSV(h - 85, 255 - velo / 4, 255));
  }
  zeds.DrawFilledCircle(xxx, yyy,  dot, CHSV(h , 255 - velo / 4, 255));
  // 2nd spiral
  xxx = MIDLX + QUARTER  * (sin8(h + 128) - 128.0) / 128.0;
  yyy = MIDLY + MIDLY / 2 * (cos8(h + 128) - 128) / 128.0;
  //  zeds.DrawFilledCircle(xxx, yyy, 9 + (MIDLX >> 1), CHSV( h ,velo+196, 255));

  for (int jj = 0; jj < 330; jj += 5)
  {
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    zeds.DrawFilledCircle(xxx - xangle * (jj /  17) , yyy - yangle * (jj / 17), dot2, CHSV(h + 42 , 255 - velo / 4, 255));
    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    zeds.DrawFilledCircle(xxx - xangle * (jj /  17) , yyy - yangle * (jj / 17), dot2, CHSV( h - 42, 255 - velo / 4, 255));
  }
  zeds.DrawFilledCircle(xxx , yyy , dot, CHSV( h + 42 , 255 - velo / 4, 255));
}

void hypnoduck2()  // growing spirals
{
  if (counter == 0) {
    dot = random(2, 5);
    dot2 = random(2, 5);
    if (flop[8] ) dot2 = dot;
  }
  if (!flop[1])
    quash = 12 + dot;
  else
    quash = -12 - dot;

  if (flop[2] && flop[1])
    zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h + 85, 255 - velo / 4, 100));
  else {
    if ( flop[0])
      zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);
    else
      whitewarp();
  }

  for (uint32_t jj = 20; jj < 30 + (counter % 630); jj += 5)
  {
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    zeds.DrawFilledCircle( driftx - xangle * (jj /  (19 - dot)) , drifty - yangle * (jj / (19 - dot)), dot, CHSV(h - 85, 255 - velo / 4, 255));
    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    zeds.DrawFilledCircle( driftx - xangle * (jj /  (19 - dot)) ,  drifty - yangle * (jj / (19 - dot)), dot, CHSV(h , 255 - velo / 4, 255));
  }
}


void hypnoduck3()
// spirals with speckles of hyponic light random direction based on flop[1]
{

  dot = beatsin16(1, 1, 5, blender);


  if (!flop[1])
    quash = 3 + dot;
  else
    quash = -3 - dot;

  if (flop[2] || flop[5])
    solid5();
  else
    zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);

  for (int jj = 0; jj < beatsin16(4, 200, 780, 0) ; jj += 5)
  {
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    zeds.DrawFilledCircle( driftx - xangle * jj / 15 , drifty - yangle * jj / 15, dot, CHSV(-h + ccoolloorr - 85, 255 - velo / 4, 255));

    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    zeds.DrawFilledCircle( driftx - xangle * jj / 15 ,  drifty - yangle * jj / 15, dot, CHSV(-h + ccoolloorr + 85, 255 - velo / 4, 255));
  }
  zeds.DrawFilledCircle(driftx, drifty, dot, CHSV(-h + ccoolloorr - 85 , 255 - velo / 4, 255));
}


void hypnoduck4()
// spiral inward with the hyponic light
{

  if (flop[1]) quash = 8; else quash = -8;

  if (flop[2])

    zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);
  else
  { if (flop[0])
      solid5();
    else {

      solid4();
    }
  }
  for (int jj = beatsin16(4, 21, 976, 0) ; jj > 0; jj -= 5)// is -h an issue??
  {
    xangle =  (sin8(jj + quash * -h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * -h) - 128.0) / 128.0;
    zeds.DrawFilledCircle(driftx + xangle * (jj /  17) , drifty + yangle * (jj / 17), 2, CHSV(h, 255 - velo / 4, 255));

    xangle =  (sin8(jj + quash * -h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * -h + 128) - 128.0) / 128.0;
    zeds.DrawFilledCircle(driftx + xangle * (jj /  17) , drifty + yangle * (jj / 17), 2, CHSV(h - 87, 255 - velo / 4, 255));
  }

}

//format drawstar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler)// random multipoint star

void starer() {
  if (counter == 0)
    pointy = random(4, 9);
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= MATRIX_WIDTH + 5)
      drawstar(driftx  , drifty, 2 * (counter - ringdelay), (counter - ringdelay), pointy, blender + h, h * 2 + 85);
    else {
      ringdelay = counter + random(targetfps * 5, targetfps * 10);
      pointy = random(3, 9);
    }
  }
}

void bkstarer() {
  if (counter == 0)
    pointyfix = random(4, 9);
  if (counter >= bringdelay)
  {
    if (counter - bringdelay <= MATRIX_WIDTH + 20)
    {
      //format drawstar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler)// random multipoint star
      drawstar(driftx, drifty, 2 * (MATRIX_WIDTH - (counter - bringdelay) + 15), 15 + MATRIX_WIDTH - (counter - bringdelay), pointyfix, blender - h, h  - 60);
      drawstar(driftx, drifty, 2 * (MATRIX_WIDTH - (counter - bringdelay) + 10), 10 + MATRIX_WIDTH - (counter - bringdelay), pointyfix, blender - h, h  - 50);
      drawstar(driftx, drifty, 2 * (MATRIX_WIDTH - (counter - bringdelay) + 5), 5 + MATRIX_WIDTH - (counter - bringdelay), pointyfix, blender - h, h  - 40);
      drawstar(driftx, drifty, 2 * (MATRIX_WIDTH - (counter - bringdelay)), MATRIX_WIDTH - (counter - bringdelay), pointyfix, blender - h, h - 30  );
    }
    else
    {
      bringdelay = counter + random(targetfps * 5, targetfps * 17);
      pointy = random(4, 9);
    }
  }
}

void triangler() {
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= MATRIX_WIDTH + 10)
    {
      triangle(driftx  , drifty ,  (counter - ringdelay), 2 * h, h * dot - 90);
      triangle(driftx  , drifty ,  (counter - ringdelay + 5),  2 * h, h * dot - 70);
      triangle(driftx  , drifty ,  (counter - ringdelay + 10),  2 * h, h * dot - 50);
    }
    else
      ringdelay = counter + random(targetfps * 5, targetfps * 20);
  }
}

void boxer() {
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= MATRIX_WIDTH)
    {
      zeds.DrawRectangle(driftx - (counter - ringdelay) , drifty - (counter - ringdelay) , driftx + (counter - ringdelay), drifty + (counter - ringdelay), CHSV(h * 2 + 128, 255 - (counter % 64), 255));
    }
    else
      ringdelay = counter + random(targetfps * 3, targetfps * 15);
  }
}

void bkboxer() {
  if (counter >= bringdelay)
  {
    if (counter - bringdelay <= MATRIX_WIDTH + 13)
    {
      zeds.DrawRectangle(driftx - 12 - (counter - bringdelay) , drifty - 12 - (counter - bringdelay) , driftx + 12 + (counter - bringdelay), drifty + 12 + (counter - bringdelay), CHSV(h, 255 - (counter % 64), 255));
      zeds.DrawRectangle(driftx - 8 - (counter - bringdelay) , drifty - 8 - (counter - bringdelay) , driftx + 8 + (counter - bringdelay), drifty + 8 + (counter - bringdelay), CHSV(h +   steper * 4, 255 - (counter % 64), 255));
      zeds.DrawRectangle(driftx - 4 - (counter - bringdelay) , drifty - 4 - (counter - bringdelay) , driftx + 4 + (counter - bringdelay), drifty + 4 + (counter - bringdelay), CHSV(h +  steper * 8, 255 - (counter % 64), 255));
      zeds.DrawRectangle(driftx - (counter - bringdelay) , drifty - (counter - bringdelay) , driftx + (counter - bringdelay), drifty + (counter - bringdelay), CHSV(h + steper * 12, 255 - (counter % 64), 255));
    }
    else {
      bringdelay = counter + random(targetfps * 4, targetfps * 12);

    }
  }
}


void homer() {
  if (counter == 0 )
  {
    howmany = random (MATRIX_WIDTH * 2 - 12, MATRIX_WIDTH * 2 - 1 );
    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = random8();//color
      fpeed[i] = random(1, 7);// bigger = slower

      ccoolloorr = random8();
      xpoffset[i] = random8();
    }
  }

  for (int i = 0; i < howmany; i++)
  {
    if ( flop[0])
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0 , drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) =  CHSV(fcolor[i], 255 - velo / 4, 255);

    else
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0, drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) = CHSV(ccoolloorr, 255 - velo / 4, 255);


  }
  zeds(driftx , drifty ) = CRGB::White;
}

void homer2() {// growing egg
  if (counter == 0 )
  {
    howmany = random (MIDLX + 8, 2 * MATRIX_WIDTH - 12);
    dot = random(1, 4);
    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = random8();//color
      fpeed[i] = random(1, 4);// bigger = slower
      xpoffset[i] = random8();
      ccoolloorr = random8();
    }
  }
  int16_t tempo = dot * 2 + 50;
  if (counter % tempo == 0) {
    dot++;
    counter = counter + tempo;
  }

  if (dot >= MIDLX) {
    dot = random(1, 4);
    ccoolloorr =  random8();
  }
  zeds.DrawCircle( MIDLX  , MIDLY, dot + 1, CRGB::White);
  for (int i = 0; i < howmany; i++)
  {
    if ( flop[0])
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0 , MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) =  CHSV(fcolor[i], 255 - velo / 4, 255);
    else if (!flop[1])
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0 , MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) =  CRGB::Orange;
    else
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0, MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) = CHSV(h, 255 - velo / 4, 255);
  }
  zeds.DrawFilledCircle( MIDLX  , MIDLY, dot - 1 , CHSV(h, 255 - velo / 4, 55 + 100 * dot / MIDLX));
}

void homer3() {
  if (counter == 0 )
  {
    howmany = random (MIDLX , THREEQUARTERS);
    //dot = 2;
    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random(64);//color
      fvelo[i] = random8();
      yfire[i] = random(7);// angle of attack
      xfire[i] = random(2, 6); //dot size
      xpoffset[i] = random8();
      fpeed[i] = random(1, 8); //speed?
    }
  }
  // zeds.DrawFilledCircle(driftx , drifty, 5, CRGB::Black);
  zeds.DrawCircle(driftx , drifty, 3, CHSV(blender , 255 - velo / 4, 180 ));
  zeds.DrawCircle(driftx , drifty, 2, CHSV(blender + 128 , 255 - velo / 4, 180 ));
  for (int i = 0; i < howmany; i++)
  {
    zeds.DrawCircle(driftx +  (xfire[i] / 2 + MATRIX_WIDTH - ((counter + xpoffset[i]) % (MATRIX_WIDTH)) ) * (sin8(fcount[i] + (yfire[i] - 3) * h ) - 128.0) / 128.0 , drifty +  (xfire[i] / 2 + MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) ) * (cos8(fcount[i] + (yfire[i] - 3) * h ) - 128.0) / 128.0 , xfire[i],  CHSV(fcolor[i], fvelo[i] / 2 + 128, 255));
  }
  zeds.DrawCircle(driftx +  (xfire[7] / 2 + MATRIX_WIDTH - ((counter + xpoffset[7]) % (MATRIX_WIDTH)) ) * (sin8(fcount[7] + (yfire[7] - 3) * h ) - 128.0) / 128.0 , drifty +  (xfire[7] / 2 + MATRIX_HEIGHT - ((counter + xpoffset[7]) % (MATRIX_HEIGHT)) ) * (cos8(fcount[7] + (yfire[7] - 3) * h ) - 128.0) / 128.0 , xfire[7],  CRGB::White);
  // zeds.DrawCircle(driftx , drifty, 5, CRGB::Black);
}

void nringer(int16_t i) {

  if (flop[0] && flop[1] && !flop[2])
  {
    zeds.DrawFilledCircle(driftx, drifty , i, CRGB::White);
    zeds.DrawFilledCircle(driftx, drifty , i - 1, CRGB::Black);
  }
  else
  {
    zeds.DrawFilledCircle(driftx, drifty , i, CHSV(h * dot, 255 - velo / 4, 255));
    zeds.DrawFilledCircle(driftx, drifty , i - 1, CRGB::Black);
  }
}

void drawtriangle()//solid triangle
{
  for (int16_t i = 0; i < MIDLX; i ++)
  {
    zeds.DrawLine(i, i, MATRIX_WIDTH - i, i, CHSV(h + i * 4, 255 - velo / 4, 255));
    zeds.DrawLine(i, i, MIDLX, MATRIX_HEIGHT - i, CHSV(h + i * 4, 255 - velo / 4, 255));
    zeds.DrawLine(MATRIX_WIDTH - i, i, MIDLX, MATRIX_HEIGHT - i, CHSV(h + i * 4, 255 - velo / 4, 255));
  }
}

void triangle(int16_t xloc, byte yloc, byte bigg, byte angle, byte kolor)
{
  int16_t ax = xloc + bigg * (sin8(angle) - 128.0) / 128;
  int16_t ay = yloc + bigg * (cos8(angle) - 128.0) / 128;
  int16_t bx = xloc + bigg * (sin8(angle + 85) - 128.0) / 128;
  int16_t by = yloc + bigg * (cos8(angle + 85) - 128.0) / 128;
  int16_t cx = xloc + bigg * (sin8(angle - 85) - 128.0) / 128;
  int16_t cy = yloc + bigg * (cos8(angle - 85) - 128.0) / 128;
  zeds.DrawLine(ax, ay, bx, by, CHSV(kolor, 255 - (counter % 64), 255));
  zeds.DrawLine(cx, cy, bx, by, CHSV(kolor, 255 - (counter % 64), 255));
  zeds.DrawLine(ax, ay, cx, cy, CHSV(kolor, 255 - (counter % 64), 255));
}

void drawstar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler)// random multipoint star
{
  if (counter == 0) {
    //shifty = 3;//move quick
  }
  radius2 = 255 / points;
  for (int i = 0; i < points; i++)
  {
    zeds.DrawLine(xlocl + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
    zeds.DrawLine(xlocl + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
  }
}

void whitestar(int16_t xlocl, byte ylocl, byte biggy, byte little, byte points, byte dangle, byte koler)// random multipoint star
{
  if (counter == 0) {
    //shifty = 3;//move quick
  }
  radius2 = 255 / points;
  for (int i = 0; i < points; i++)
  {
    zeds.DrawLine(xlocl + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CRGB::White);
    zeds.DrawLine(xlocl + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CRGB::White);
  }
}

void starz()// 3 stars spin in a circle
{
  if (counter == 0) {
    howmany = random (3, 9);
    inner = random(MIDLY / 5, MIDLY / 2);
    radius2 = 255 / howmany;
  }

  xcen = MIDLX * (sin8(-2 * h - 85) - 128.0) / 128;
  ycen = MIDLY  * (cos8(-2 * h - 85 ) - 128.0) / 128;

  if (h % 16 == 0) {
    inner = inner + flipme;
    if (inner > MIDLY / 2 || inner < MIDLY / 5)
      flipme = -flipme;
  }

  for (int16_t i = 0; i < howmany; i++)
    for (int16_t j = 2; j < inner; j += 1)
    {
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h + 85 + dot * j, 255 - velo / 4, 255));
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h + 85 + dot * j, 255 - velo / 4, 255));
    }

  xcen = MIDLX  * (sin8(-2 * h + 85) - 128.0) / 128;
  ycen = MIDLY  * (cos8(-2 * h + 85) - 128.0) / 128;
  for (int16_t i = 0; i < howmany; i++)
    for (int16_t j = 2; j < inner; j += 2)
    {
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h + dot2 / 2 * j , 255 - velo / 6 , 255));
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h + dot2 / 2 * j , 255 - velo / 6 , 255));
    }
  xcen = MIDLX  * (sin8(-2 * h) - 128) / 128;
  ycen = MIDLY  * (cos8(-2 * h) - 128) / 128;
  for (int16_t i = 0; i < howmany; i++)
    for (int16_t j = 2; j < inner; j += 3)
    {
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot / 2 * j , 255 - velo / 4 , 255));
      zeds.DrawLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot / 2 * j , 255 - velo / 4 , 255));
    }
}

void starz3()// random multipoint star
{
  if (counter == 0) {
    dot = random(5, 9);
    howmany = random (3, 11);
    inner = random(MIDLY , MATRIX_WIDTH );
  }
  for (int i = 0; i < howmany; i++)
    for (int16_t j = 0; j < inner; j++)
    {
      drawstar(driftx, drifty,  j, j / 2, howmany, h, h + j * dot);
    }

}

void starz2()// pulsing  point star
{
  if (counter == 0) {
    inner = random(MIDLY - 8, MIDLY + 8 );
    shifty = 1;
    dot = random(3, 8);
    dot2 = random(5, 9);
  }


  for (int16_t j = 0; j < inner; j++)
  {
    drawstar(driftx, drifty,  j, j / 3, dot2, h, h + j * dot );
  }


}


void spoker()//
{
  if (counter == 0) {
    howmany = random (3, 8);
    radius2 = 64 / howmany;

    poffset = random(60, 98);
  }
  for (int i = 0; i < howmany * 4; i++)
  {
    zeds.DrawLine(-QUARTER ,  -MIDLY / 2, (( beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64)) - 128.0)) / 128),  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64)) - 128.0)) / 128), CHSV(h  , 255 - velo / 4, 255));
    zeds.DrawLine(MATRIX_WIDTH + QUARTER  , MATRIX_HEIGHT + MIDLY / 2,  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, dot2) * (sin8(i * radius2  +  (h % 64) + 128) - 128.0)) / 128),  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, dot2) * (cos8(i * radius2  + (h % 64) + 128) - 128.0)) / 128), CHSV(h  + poffset , 255 - velo / 4, 255));
  }
}

void spoker3()//
{
  if (counter == 0) {
    howmany = random (3, 7);
    radius2 = 64 / howmany;
    poffset = random(60, 98);
  }
  for (int i = 0; i < howmany * 4; i++)
  {
    zeds.DrawLine(-QUARTER ,  -MIDLY / 2, (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64)) - 128.0)) / 128,  (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64)) - 128.0)) / 128, CHSV(h  , 255 - velo / 4, 255));
    zeds.DrawLine(MATRIX_WIDTH + QUARTER  , MATRIX_HEIGHT + MIDLY / 2,  MATRIX_WIDTH - (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2  +  (h % 64) + 128) - 128.0)) / 128,  MATRIX_HEIGHT - (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2  + (h % 64) + 128) - 128.0)) / 128, CHSV(h  + poffset / 2 , 255 - velo / 4, 255));

    zeds.DrawLine(-QUARTER ,  MATRIX_HEIGHT + MIDLY / 2, (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64) + 64) - 128.0)) / 128,  MATRIX_HEIGHT - (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64) + 64) - 128.0)) / 128, CHSV(h + poffset  , 255 - velo / 4, 255));
    zeds.DrawLine(MATRIX_WIDTH + QUARTER  , -MIDLY / 2,  MATRIX_WIDTH - (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2  +  (h % 64) - 64) - 128.0)) / 128,  (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2  + (h % 64) - 64) - 128.0)) / 128, CHSV(h  - poffset / 2 , 255 - velo / 4, 255));
  }
}

void circlearc()// arc of circles
{
  if (counter == 0)
  {

    bfade = random (3, 6);
    howmany = random (3, 7);
    radius2 = 64 / howmany;//index angle
    radius3 = random (MATRIX_WIDTH - (MATRIX_WIDTH >> 2), MATRIX_WIDTH + (MATRIX_WIDTH >> 2));
    poffset = random(0, 6);//which version to play
    inner = random(6,  QUARTER );
    directn = 1;

  }
  if ( counter % 12 == 0) {
    radius3 = radius3 + directn;

    if (radius3 <  2 + MATRIX_WIDTH - (MATRIX_WIDTH >> 2) ||  radius3 > MATRIX_WIDTH - 2 + (MATRIX_WIDTH >> 2))
      directn = 0 - directn;
  }
  switch (poffset)
  {

    case 0:  // four -all headed in different direcitons solid
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 -  h) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  (h )) - 128.0) / 128, inner, CHSV(h, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 - h - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h  ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 4, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h  ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h  ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 4, 255));
      }
      break;

    case 1:  // four -all headed in different direcitons hollow
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawCircle( radius3 * (sin8(i * radius2 -  h ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner, CHSV(h, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 4, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 4, 255));
      }
      break;

    case 2:// white rim 2 or 4
      for (int i = 0; i < howmany * 4; i++)
      {
        if (flop[1]) {
          zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 -  h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner, CHSV(h, 255 - velo / 4, 255));
          zeds.DrawCircle( radius3 * (sin8(i * radius2 - h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner, CRGB::White);
        }
        zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 4, 255));
        zeds.DrawCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CRGB::White);

      }
      for (int i = 0; i < howmany * 4; i++)
      {
        if (flop[1]) {
          zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 4, 255));
          zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner, CRGB::White);
        }
        zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 4, 255));
        zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner, CRGB::White);
      }

      break;
    case 3:// solids small sometimes with rings
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 -  h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner / 2, CHSV(h, 255 - velo / 4, 255));

        if (flop[1])
          zeds.DrawCircle( radius3 * (sin8(i * radius2 -  h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner , CHSV(h - 32, 255 - velo / 4, 255));

        if (flop[2]) {
          zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner / 2, CHSV(h + 85, 255 - velo / 4, 255));

          if (flop[1])
            zeds.DrawCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CHSV(h + 85 - 32, 255 - velo / 4, 255));
        }
      }
      for (int i = 0; i < howmany * 4; i++)
      {

        zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner / 2, CHSV(h  - 85, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner , CHSV(h  - 85 - 32, 255 - velo / 4, 255));

        if (flop[2]) {
          zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner / 2, CHSV(h  - 85 + 32, 255 - velo / 4, 255));
          if (flop[1])
            zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner, CHSV(h  + -85 - 32, 255 - velo / 4, 255));
        }
      }

      break;
    case 4:// 8  opposite directions  littles
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 -  h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner / 2, CHSV(h, 255 - velo / 4, 255));
        if ( flop[0])
          zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner / 2, CHSV(h + 64, 255 - velo / 4, 255));
        else
          zeds.DrawFilledCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 4, 255));

      }
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h   ) + 128) - 128.0) / 128, inner / 2, CHSV(h  + 128, 255 - velo / 4, 255));
        if (flop[0])
          zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner / 2, CHSV(h  - 64, 255 - velo / 4, 255));
        else
          zeds.DrawFilledCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h   ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 4, 255));
      }
      break;
    default:// four headed together
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  + (h   ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  + (h   ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  + (h   ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  + (h   ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 4, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        zeds.DrawCircle( radius3 * (sin8(i * radius2 -  h  ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h  ) - 128.0) / 128, inner, CHSV(h, 255 - velo / 4, 255));
        if (flop[1])
          zeds.DrawCircle( radius3 * (sin8(i * radius2 - (h   ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h   ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 4, 255));
      }

      break;
  }
}

void wheelz()// circles and stars filled circles in a circle
{
  if (counter == 0) {
    howmany = random (4, 12);
    inner = random(MIDLY / 5, MIDLY / 2);
    radius2 = 255 / howmany;
    dot2 = random(5, 9);
  }
  inner = beatsin16(6, MIDLY / 3, MIDLY / 2, 0);

  for (int i = 0; i < howmany; i++) {
    zeds.DrawCircle(driftx + ((inner * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ((inner * (cos8(i * radius2 +   h) - 128.0)) / 128), inner , CHSV(h  - 12 * i , 255 - velo / 8, 255));
    if (i % 2 == 0) {
      zeds.DrawFilledCircle(driftx + (((inner) * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + (((inner) * (cos8(i * radius2 +   h) - 128.0)) / 128), inner , CHSV(h  + 12 * i , 255 - velo / 3, 255));
    }
    else
      drawstar(driftx + (((inner) * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + (((inner) * (cos8(i * radius2 +   h) - 128.0)) / 128), inner, inner / 2, dot2,  h, h  + 12 * i); // random multipoint star
  }
}

void wheelz2()// circles in a circle
{
  if (counter == 0) {
    howmany = random (4, 11);
    how = howmany;
    inner = random(MIDLY / 2 - 2, MIDLY );
    radius2 = 255 / howmany;
    dot2 = random( 3, 9);
  }
  if ( flop[3] || flop[4]) {
    howmany = beatsin16(dot , 4, 12, 0);
    radius2 = 255 / howmany;
    inner = beatsin16(dot / 3, MIDLY / 2 - 2, MIDLY, 0);
  }
  for (int i = 0; i < howmany; i++)
  { if (i % 2 == 0)
      zeds.DrawCircle(driftx + ((inner * (sin8(i * radius2 -  h) - 128.0)) / 128), drifty + ((inner * (cos8(i * radius2 -   h) - 128.0)) / 128), inner, CHSV(h  + 8 * i , 255 - velo / 4, 255));
    else
      drawstar(driftx + (((inner ) * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + (((inner ) * (cos8(i * radius2 +   h) - 128.0)) / 128), inner, inner / 2, dot2, 2 * h, h  + 12 * i); // random multipoint star
  }
}

void swirlz() {//not round orbits
  if (counter == 0)
  {
    howmany = random(MATRIX_HEIGHT * 2 / 3, THREEHAVES );
    blender = random(192);
    for ( int16_t i = 0; i < howmany; i++)
    {
      xfire[i] = random(4, MIDLX + 9); //xradius
      yfire[i] =  random(xfire[i] - 2, xfire[i] + 2); //yradius

      //if (i % 5 == 0)// make some round
      //yfire[i] = xfire[i];
      fpeed[i] = random(1, 8); //speed
      fcolor[i] = blender + random(64); //color
      fvelo[i] = random8();
      fcount[i] = random8(); //poffset
    }
  }
  for ( int16_t i = 0; i < howmany; i++) {
    zeds(driftx + xfire[i] * (sin8(h * fpeed[i] + fcount[i]) - 128.0) / 128 , drifty + yfire[i] * (cos8(h * fpeed[i] + fcount[i]) - 128.0) / 128) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255);
    if (i % 9 == 0)
      zeds(driftx + xfire[i] * (sin8(-h * fpeed[i] + fcount[i]) - 128.0) / 128 , drifty + yfire[i] * (cos8(-h * fpeed[i] + fcount[i]) - 128.0) / 128) = CRGB::White;

  }
  //make 4 of them fattys
  zeds(driftx + 1 + xfire[howmany - 1] * (sin8(h * fpeed[howmany - 1] + fcount[howmany - 1]) - 128.0) / 128 , drifty + yfire[howmany - 1] * (cos8(h * fpeed[howmany - 1] + fcount[howmany - 1]) - 128.0) / 128) = CHSV(fcolor[howmany - 1], fvelo[howmany - 1] / 4 + 192, 255);
  zeds(driftx - 1 + xfire[howmany - 2] * (sin8(h * fpeed[howmany - 2] + fcount[howmany - 2]) - 128.0) / 128 , drifty + yfire[howmany - 2] * (cos8(h * fpeed[howmany - 2] + fcount[howmany - 2]) - 128.0) / 128) = CHSV(fcolor[howmany - 2], fvelo[howmany - 1] / 4 + 192, 255);
  zeds(driftx  + xfire[howmany - 3] * (sin8(h * fpeed[howmany - 3] + fcount[howmany - 3]) - 128.0) / 128 , drifty - 1 + yfire[howmany - 3] * (cos8(h * fpeed[howmany - 3] + fcount[howmany - 3]) - 128.0) / 128) = CHSV(fcolor[howmany - 3], fvelo[howmany - 1] / 4 + 192, 255);
  zeds(driftx  + xfire[howmany - 4] * (sin8(h * fpeed[howmany - 4] + fcount[howmany - 4]) - 128.0) / 128 , drifty + 1 + yfire[howmany - 4] * (cos8(h * fpeed[howmany - 4] + fcount[howmany - 4]) - 128.0) / 128) = CHSV(fcolor[howmany - 4], fvelo[howmany - 1] / 4 + 192, 255);
}

void swirl2() {//round orbit backwards
  if (counter == 0)
  {
    xhowmany = random(MATRIX_HEIGHT , THREEHAVES);
    xblender = random8();
    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(3, MIDLX + 19); //radius
      fpeed[i] = random(1, 6); //speed
      xpoffset[i] = xblender + random(54); //color
      fvelo[i] = random8();
      fcountr[i] = random8(); //poffset
    }
  }
  for ( int16_t i = 0; i < xhowmany; i++) {
    zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], 255 - fvelo[i] / 4 , 255);
    if (i % 13 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
    if (i % 17 == 0) {
      zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(128 + xpoffset[i], 255 - fvelo[i] / 4 , 255);
      zeds(driftx + 1 + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty - 1 + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(128 + xpoffset[i], 255 - fvelo[i] / 4 , 255);
    }
  }
}

void swirl3() {
  if (counter == 0)
  {
    xhowmany = random(MATRIX_HEIGHT + 8, THREEHAVES);
    how = xhowmany;
    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(4, THREEQUARTERS); //radius
      fpeed[i] = random(1, 6); //speed
      xpoffset[i] = blender + random(64); //color
      fvelo[i] = random8();
      fcountr[i] = random8(); //offset
    }
  }
  if (flop[7])
    xhowmany = beatsin16(2, MIDLY + 2, how, 0);
  for ( int16_t i = 0; i < xhowmany; i++) {
    if (counter % int(6 * (fpeed[i] + xslope[i])) == 0)
      xslope[i]--;
    if (xslope[i] == 1)
      xslope[i] = THREEQUARTERS;
    if (i % 11 != 0 || i % 17 != 0)
      zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], fvelo[i] / 4 + 192, 255);
    if (i % 11 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
    if (i % 17 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i] - 85, fvelo[i] / 2 + 128, 255);
  }
}

void swirl4a() {// outer
  if (counter == 0)
  {
    flop[9] = true;
    xhowmany = random(MATRIX_HEIGHT * 1.5 , MATRIX_WIDTH * 2.5 );

    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(6, 18); //radius
      fpeed[i] = random(2, 16); //speed
      xpoffset[i] = blender + random(84); //color
      fvelo[i] = random8();
      fcountr[i] = random8(); //poffset
    }
  }
  EVERY_N_SECONDS(19) {
    flop[9] = !flop[9];
    /* if (flop[9])
       zeds.DrawFilledCircle(driftx, drifty,MIDLX / 7, CHSV(blender - 30, 155, 255));
      else
       zeds.DrawFilledCircle(driftx, drifty, 16 + MATRIX_WIDTH / 2, CHSV(blender - 30, 155, 255));*/
  }

  for ( int16_t i = 0; i < xhowmany; i++) {
    if (flop[9]) {
      if (counter % int( fpeed[i]  ) == 0  && xslope[i] < MIDLY - 2 )
        xslope[i]++;
    }
    else if (counter % int( fpeed[i] ) == 0  && xslope[i] > 6)
      xslope[i]--;



    if (i % 27 != 0 || i % 24 != 0) {
      zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], fvelo[i] / 4 + 192, 255);
      zeds(driftx + 1 + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], 255 - fvelo[i] / 4, 255);
    }
    if (i % 27 == 0) {
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
      zeds(driftx - 1 + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
    }
    if (i % (24 - dot) == 0) {
      zeds(driftx + 1 + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], fvelo[i] / 4 + 192, 255);
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + 1 + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i] - 32, fvelo[i] / 4 + 192, 255);
    }
  }
}

void swirl4() {// outer
  if (counter == 0)
  {
    flop[9] = true;
    xhowmany = random(MATRIX_HEIGHT * 1.5 , MATRIX_WIDTH * 2.5 );

    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(6, 24); //radius
      fpeed[i] = random(5, 20); //speed
      if (flop[5])
        xpoffset[i] = blender + (fpeed[i] - 2) * 10; //color
      else
        xpoffset[i] = blender + random(99); //color
      fcountr[i] = random8(); //poffset
      fvelo[i] = random8();
    }
  }
  EVERY_N_SECONDS(24) {
    flop[9] = !flop[9];
    /* if (flop[9])
       zeds.DrawFilledCircle(driftx, drifty,MIDLX / 7, CHSV(blender - 30, 155, 255));
      else
       zeds.DrawFilledCircle(driftx, drifty, 16 + MATRIX_WIDTH / 2, CHSV(blender - 30, 155, 255));*/
  }

  for ( int16_t i = 0; i < xhowmany; i++) {
    if (flop[9]) {
      if (counter % int( fpeed[i]  ) == 0  && xslope[i] < MIDLX)
        xslope[i]++;
    }
    else if (counter % int( fpeed[i]) == 0  && xslope[i] > 6)
      xslope[i]--;




    zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], 255 - fvelo[i] / 3, 255);
    if (i % 27 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
    /*  if (i % 24 == 0) {
        zeds(driftx + 1 + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(blender - 70,velo+196, 255);
        zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + 1 + xslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(blender - 72,velo+196, 255);
      }*/
  }
}

void swirl5() {// both directions not round
  if (counter == 0)
  {
    xhowmany = random(MATRIX_HEIGHT, MATRIX_WIDTH * 2);
    xblender = random8();
    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(4, MIDLX + 8 ); //radius
      fcolor[i] = blender + random(99);
      fvelo[i] = random8();
      yslope[i] =  random(xslope[i] - 3, xslope[i] + 3); //slightly oblong
      fpeed[i] = random(1, 8); //speed
      fcountr[i] = random8(); //poffset
    }
  }
  for ( int16_t i = 0; i < xhowmany; i++) {

    zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + yslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV( fcolor[i], fvelo[i] / 4 + 192, 255);
    if (i % 29 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + yslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255);
    if (i % 33 == 0)
      zeds(driftx + xslope[i] * (sin8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + yslope[i] * (cos8(-h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;
    if (i % 27 == 0)
      zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + yslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CRGB::White;

  }
}

void drops() {
  if (counter == 0) {// counter increments with each pass through the loop, so this runs the first time you call drops()
    howmany = random(8 + MATRIX_WIDTH * 1.25, MATRIX_WIDTH * 2 ); //how many dots,
    if (!flop[2]) blender = 80;//flop[2] is set prior to deciding to run drops() , if false, makes for a bias towards green, otherwise blender is random8()
    else   blender = random8();


    for (int16_t i = 0; i < howmany; i++) { //set up all the drops with initial values
      xslope[i] = random (MATRIX_WIDTH);//starting x location
      yslope[i] = MIDLY - random(MATRIX_HEIGHT); //starting y location, builds in some delay by putting them well off screen
      fpeed[i] = random(1, 7);// here higher ##s are slower
      fcountr[i] = random(2, 5);//  now long is the tail....
      fcolor[i] = blender + random(64); // picks colors close to blender
      fvelo[i] = random8();
    }
    if (!flop[1])fcolor[MIDLY] = blender - 152;
  }
  for (int16_t i = 0 ; i < howmany; i++) {//draw all the drops
    if (counter % fpeed[i] == 0)//only move if it is your turn
      yslope[i] ++;                           //y position = current value of y + the random speed variable
    if (yslope[i] > MATRIX_HEIGHT + fcountr[i]) {              //If the y value plus the tail exceeds the height of the matrix, then give y a new value
      fcountr[i] = random(2, 5);//tail
      yslope[i] = 0 - random(0, MATRIX_HEIGHT / 2);// new location well off the edge
      xslope[i] = random (MATRIX_WIDTH);
      fpeed[i] = random(1, 7);//higher = slower
      //fcolor[i] = blender + random(40); // color
    }
    zeds.DrawLine(xslope[i] , yslope[i] , xslope[i] , yslope[i] - fcountr[i], CHSV(fcolor[i], fvelo[i] / 4 + 192, 255)); //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
    if (i % 23 == 0)
      zeds.DrawLine(xslope[i] , yslope[i] , xslope[i] , yslope[i] - fcountr[i], CRGB::White);//toss in a white one every so often
  }
}

void drips() {
  if (counter == 0) {// counter increments with each pass through the loop, so this runs the first time you call drops()
    howmany = random(MATRIX_WIDTH * 1, MATRIX_WIDTH * 2 ); //how many dots
    how = howmany;
    if (!flop[2]) blender = 70;//flop[2] is set prior to deciding to run drops() , if false, makes for a bias towards green, otherwise blender is random8()


    for (int16_t i = 0; i < howmany; i++) { //set up all the drops with initial values
      xslope[i] = random (MATRIX_WIDTH + 2 * dot) - dot; //starting x location
      yslope[i] = MIDLY - random(MATRIX_HEIGHT); //starting y location, builds in some delay by putting them well off screen
      fpeed[i] = random(1, 7);// here higher ##s are slower
      //  fcountr[i] = random(2, 5);//  now long is the tail....
      fcolor[i] = blender + random(80); // picks colors close to blender
      fvelo[i] = random8();
    }
    if (!flop[1]) fcolor[MIDLY] = blender - 158;
  }
  if (flop[5])
    howmany = beatsin16(dot / 2, MATRIX_WIDTH, how, 0);
  for (int16_t i = 0 ; i < howmany; i++) {//draw all the drops
    if (counter % fpeed[i] == 0)//only move if it is your turn
      yslope[i] ++;                           //y position = current value of y + the random speed variable
    if (yslope[i] > MATRIX_HEIGHT + 5) {              //If the y value plus the tail exceeds the height of the matrix, then give y a new value
      //fcountr[i] = random(2, 5);//tail
      yslope[i] = 0 - random(0, MATRIX_HEIGHT / 2);// new location well off the edge
      xslope[i] = random (MATRIX_WIDTH + 2 * dot) - dot;
      fpeed[i] = random(1, 7);//higher = slower
      fcolor[i] = blender + random(60); // color
    }
    zeds.DrawCircle(xslope[i] , yslope[i] , dot, CHSV(fcolor[i], fvelo[i] / 4 + 192, 255)); //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
    if (i % MIDLX == 0)
      zeds.DrawCircle(xslope[i] , yslope[i] , dot, CRGB::White); //toss in a white one every so often
  }
}

void twister() {
  EVERY_N_SECONDS(19) {
    wind = random(0, 11);
  }
}

void slowmo() {//zzxzz
  EVERY_N_SECONDS(12)  {
    if (targetfps < fastest)
      targetfps = random(fastest, fastest * 2);
    else
      targetfps = random(slowest, fastest);

  }
}

void dualwind() {//northsouth
  for (int16_t zx = 0; zx < MATRIX_WIDTH; zx++) {
    for (int16_t zy = 0; zy < MATRIX_HEIGHT / 2; zy++) {
      zeds(zx, zy) = zeds(zx, zy + 1);
    }
    for (int16_t zy = MATRIX_HEIGHT - 1; zy >= MIDLY; zy--) {
      zeds(zx, zy) = zeds(zx, zy - 1);
    }
  }

}

void scales() {
  if (counter == 0) {
    sdot = random(2, 6) * 2;
    poffset = 1;
  }
  if (counter % (sdot - 2) == 0)

  {
    poffset = 1 - poffset;
    for ( int16_t i = 0; i < MATRIX_WIDTH; i++) {
      if ((i + sdot / 2 * poffset) % sdot == 0) {
        zeds.DrawCircle(i, 0, sdot, CHSV(blender + h, 255 - velo / 4, 255));
        // zeds.DrawFilledRectangle(0, 0, MATRIX_WIDTH, 1, CRGB::Black);
      }
    }
  }
  zeds.ShiftUp();



}


void eastwestwind() {
  for (int16_t zy = 0; zy < MATRIX_HEIGHT; zy++) {
    for (int16_t zx = 0; zx < MIDLX; zx++)
      zeds(zx, zy) = zeds(zx + 1, zy );

    for (int16_t zx = MATRIX_WIDTH - 1; zx >= MIDLX; zx--)
      zeds(zx, zy) = zeds(zx - 1, zy );
  }
}

void spiralwind() {
  if (counter % 2 == 0)
    for (int16_t zx = 0; zx < MATRIX_WIDTH; zx++) {
      for (int16_t zy = 0; zy < MATRIX_HEIGHT / 2; zy++) {
        zeds(zx, zy) = zeds(zx, zy + 1);
      }
      for (int16_t zy = MATRIX_HEIGHT - 1; zy >= MIDLY; zy--) {
        zeds(zx, zy) = zeds(zx, zy - 1);
      }
    }
  else
    for (int16_t zy = 0; zy < MATRIX_HEIGHT; zy++) {
      for (int16_t zx = 0; zx < MIDLX; zx++)
        zeds(zx, zy) = zeds(zx + 1, zy );

      for (int16_t zx = MATRIX_WIDTH - 1; zx >= MIDLX; zx--)
        zeds(zx, zy) = zeds(zx - 1, zy );
    }
}



void BouncingBalls(int Ballz) {
  if (counter == 0) {
    // solid4();

    for (int i = 0 ; i < Ballz ; i++) {
      ClockTimeSinceLastBounce[i] = millis();

      Positiony[i] = 0;
      ImpactVelocity[i] = ImpactVelocityStart;
      TimeSinceLastBounce[i] = 0;
      Dampening[i] = 0.95 - 0.020 * i;
      fcolor[i] = blender + 255 / Ballz * i;
      fvelo[i] = random8();
      fcountr[i] = random(2, 6) * 2; //radius
      Heighty[i] = StartHeighty;
      xfire[i] = MIDLX;
      xslope[i] = random(2, 7); //speed in pix/second
      if (random8() < 128)
        xslope[i] = -xslope[i];
    }
  }

  for (int i = 0 ; i < Ballz  ; i++) {
    TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
    Heighty[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;
    xfire[i] = xfire[i] + TimeSinceLastBounce[i] / 1000.0 * xslope[i];
    Positionx[i] = round(xfire[i]);
    if (Positionx[i] > MATRIX_WIDTH - fcountr[i]  || Positionx[i] < fcountr[i]  ) {
      xslope[i] = -xslope[i] * Dampening[i];
      xfire[i] = xfire[i] + TimeSinceLastBounce[i] / 1000.0 * xslope[i];
      Positionx[i] = round(xfire[i]);
    }
    if ( Heighty[i] < 0 ) {
      Heighty[i] = 0;
      ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
      ClockTimeSinceLastBounce[i] = millis();

      if ( ImpactVelocity[i] < 0.01 ) {
        ImpactVelocity[i] = ImpactVelocityStart;
        xslope[i] = random(2, 7); //speed in pix/second
        if (random8() < 128)
          xslope[i] = -xslope[i];
        xfire[i] = constrain( xfire[i], fcountr[i] , MATRIX_WIDTH - fcountr[i] );
      }
    }
    Positiony[i] = round( Heighty[i] * (MATRIX_HEIGHT) / StartHeighty);
    Positiony[i] =  MATRIX_HEIGHT -  (fcountr[i]) - Positiony[i] - 1;
  }
  //fill_solid( leds, NUM_LEDS, CRGB::Black);
  for (int i = 0 ; i < Ballz ; i++) {
    zeds.DrawFilledCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i] - 16, 255 - fvelo[i] / 2, 200));
    if ( flop[1])
      zeds.DrawCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i], fvelo[i] / 4 + 192, 255));
    else
      zeds.DrawCircle(Positionx[i], Positiony[i], fcountr[i],  CRGB::White);

  }
}


void Bouncingtri(int Ballz) {
  if (counter == 0) {
    // solid4();

    for (int i = 0 ; i < Ballz ; i++) {
      ClockTimeSinceLastBounce[i] = millis();

      Positiony[i] = 0;
      ImpactVelocity[i] = ImpactVelocityStart * .93;
      TimeSinceLastBounce[i] = 0;
      Dampening[i] = 0.95 - 0.05 * i;
      fcolor[i] = blender + 255 / Ballz * i;
      fvelo[i] = random8();
      fcountr[i] = random(5, 12); //radius
      Heighty[i] = StartHeighty;
      xfire[i] = MIDLX;
      xslope[i] = random(2, 7); //speed in pix/second
      if (random8() < 128)
        xslope[i] = -xslope[i];
    }
  }

  for (int i = 0 ; i < Ballz  ; i++) {
    TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
    Heighty[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i] / 1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i] / 1000;
    xfire[i] = xfire[i] + TimeSinceLastBounce[i] / 1000.0 * xslope[i];
    Positionx[i] = round(xfire[i]);
    if (Positionx[i] > (MATRIX_WIDTH - fcountr[i])   || Positionx[i] < (fcountr[i] ) ) {
      xslope[i] = -xslope[i] * Dampening[i];
      xfire[i] = xfire[i] + TimeSinceLastBounce[i] / 1000.0 * xslope[i];
      Positionx[i] = round(xfire[i]);
    }
    if ( Heighty[i] < 0 ) {
      Heighty[i] = 0;
      ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
      ClockTimeSinceLastBounce[i] = millis();

      if ( ImpactVelocity[i] < 0.01 ) {
        ImpactVelocity[i] = ImpactVelocityStart * .90;
        xslope[i] = random(2, 7); //speed in pix/second
        if (random8() < 128)
          xslope[i] = -xslope[i];
        xfire[i] = constrain( xfire[i], fcountr[i] , MATRIX_WIDTH - fcountr[i] - 1 );
      }
    }
    Positiony[i] = round( Heighty[i] * (MATRIX_HEIGHT) / StartHeighty);

    Positiony[i] =  MATRIX_HEIGHT -  (fcountr[i]) - Positiony[i] - 1;

  }
  //fill_solid( leds, NUM_LEDS, CRGB::Black);
  for (int i = 0 ; i < Ballz ; i++) {
    //zeds.DrawFilledCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i] + 64, fvelo[i] / 3 + 160, 225));
    if (i % 2 == 0)
      drawstar(Positionx[i], Positiony[i], fcountr[i], fcountr[i] / 4, 6, h, fcolor[i]); // random multipoint star
    else
      drawstar(Positionx[i], Positiony[i], fcountr[i], fcountr[i] / 3, 5, h, fcolor[i]); // random multipoint star

    zeds.DrawCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i], fvelo[i] / 4 + 192, 255));
    zeds.DrawCircle(Positionx[i], Positiony[i], fcountr[i] + 1,  CRGB::White);
  }
}



void snow(int16_t ccc) {
  if (counter == 0 || counter % 1400 == 0)
  {
    flop[3] = !flop[3];
    solid4();
    howmany = MATRIX_WIDTH * 1.5; //how many dots,
    for (int16_t i = 0; i < howmany; i++)
    {
      xslope[i] = i; //starting x location
      yslope[i] = random(0, MATRIX_HEIGHT);
      if (flop[3])
        fcolor[i] = ccc;
      else
        fcolor[i] = h;
      fvelo[i] = random8();
      zeds(xslope[i], yslope[i]) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255);
      if (i % 7 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::White;
      if (i % MIDLX == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Blue;
      if (i % 67 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Aqua;
    }
  }

  for (int16_t i = 0 ; i < howmany; i++)
  {
    //test to see if anything below, if thre is, make a new one, if not move down.
    if ((zeds(xslope[i], yslope[i] + 1).red > 0 || zeds(xslope[i], yslope[i] + 1).green > 0 || zeds(xslope[i], yslope[i] + 1).blue > 0) && yslope[i] > 0)
    {

      xslope[i] = random(MATRIX_WIDTH); //starting x location
      yslope[i] = 0;

      if (flop[3])
        fcolor[i] = ccc;
      else
        fcolor[i] = h;
      zeds(xslope[i], yslope[i]) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255);
      if (i % 7 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::White;
      if (i % MIDLX == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Blue;
      if (i % 67 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Teal;
    }
    else {
      zeds(xslope[i] , yslope[i]) = CRGB::Black;
      yslope[i]++;
      zeds(xslope[i] , yslope[i]) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255);
      if (i % 7 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::White;
      if (i % MIDLX == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Blue;
      if (i % 67 == 0 && flop[3])
        zeds(xslope[i], yslope[i]) = CRGB::Teal;
    }
  }
}



void VORTEX() {
  if (counter == 0) {// counter increments with each pass through the loop, so this runs the first time you call drops()
    howmany = random(MATRIX_WIDTH / 2, MATRIX_WIDTH ); //how many dots,

    if (flop[2])
      howmany = howmany / 4;
    how = howmany;
    blender = random8();
    if (flop[5]) blender = 80;//flop[52] is set prior to deciding to run drops() , if flop2 is  false, makes for a bias towards green, otherwise blender is random8()

    for (int16_t i = 0; i < howmany; i++) { //set up all the drops with initial values
      fcolor[i] = random8(); // picks colors 'close' to blender
      if (flop[4])
        fcolor[i] = blender + random(98);
      fvelo[i] = random8();
      xslope[i] = random (MATRIX_WIDTH);//starting x location
      yslope[i] = random(MATRIX_HEIGHT); //starting y location
      fcount[i] = random(2, 9);
      if (xslope[i] < MIDLX && yslope[i] < MIDLY )//zone 4
      {
        if (xslope[i] < yslope[i])//h
        {
          xvort[i] = 0;
          yvort[i] = 1;
        }
        else {//g
          xvort[i] = -1;
          yvort[i] = 0;

        }
      }

      if (xslope[i] < MIDLX && yslope[i] >= MIDLY )//zone 3
      {
        if (xslope[i] < MATRIX_HEIGHT - yslope[i] )//e
        {
          xvort[i] = 0;
          yvort[i] = 1;
        }
        else {//f
          xvort[i] = 1;
          yvort[i] = 0;
        }
      }

      if (xslope[i] >= MIDLX && yslope[i] >= MIDLY )//zone 2
      {
        if (xslope[i]  < yslope[i])//c
        {
          xvort[i] = 1;
          yvort[i] = 0;
        }
        else {//d
          xvort[i] = 0;
          yvort[i] = -1;
        }
      }
      if (xslope[i] >= MIDLX && yslope[i] < MIDLY )//zone 1
      {
        if (xslope[i] < MATRIX_HEIGHT - yslope[i]) //b
        {
          xvort[i] = -1;
          yvort[i] = 0;
        }
        else {//a
          xvort[i] = 0;
          yvort[i] = -1;
        }
      }
    }
  }
  // Fix division by 0 in counter % below
  //if (flop[2])
    howmany = beatsin16(2, 1, how, 0);
  //else
  //  howmany = beatsin16(2, 1, MATRIX_WIDTH, 0);
  for (int16_t i = 0 ; i < howmany; i++) {//draw all the drops
    //it is always your turn...
    if ( counter % fcount[i] == 0) {
      xslope[i] = xslope[i] + xvort[i];
      yslope[i] = yslope[i] + yvort[i];
    }

    if (xslope[i] < MIDLX && yslope[i] < MIDLY )//zone 4
    {
      if (xslope[i] - 1 == yslope[i]) //b  turn early
      {
        xvort[i] = 0;
        yvort[i] = 1;
      }
    }

    if (xslope[i] < MIDLX && yslope[i] >= MIDLY )//3
    {
      if (xslope[i] == MATRIX_WIDTH - yslope[i] ) //d
      {
        xvort[i] = 1;
        yvort[i] = 0;
      }
    }

    if (xslope[i] >= MIDLX && yslope[i] >= MIDLY )//2
    {
      if (xslope[i]  == yslope[i] )//e
      {
        xvort[i] = 0;
        yvort[i] = -1;
      }
    }

    if (xslope[i] >= MIDLX && yslope[i] < MIDLY )//1
    {
      if (xslope[i]  == MATRIX_HEIGHT - yslope[i]) //g
      {
        xvort[i] = -1;
        yvort[i] = 0;
      }
    }

    if (flop[2])
    {
      zeds(xslope[i] , yslope[i]) = CHSV(fcolor[i], fvelo[i] / 4 + 192, 255); //
      if (i % (23) == 0)
        zeds(xslope[i] , yslope[i]) = CRGB::White; //toss in a white one every so often
    }
    else
    {
      zeds.DrawFilledCircle(xslope[i] , yslope[i], dot - 1,  CHSV(fcolor[i], fvelo[i] / 4 + 192, 255)); //
      if (i % (23) == 0)
        zeds.DrawFilledCircle(xslope[i] , yslope[i], dot - 1,  CRGB::White);

    }
    if (abs(xslope[i] - MIDLX) < 2  && abs(yslope[i] - MIDLY ) < 1) {
      xslope[i] = 0;
      yslope[i] = 0;
      xvort[i] = 0;
      yvort[i] = 1;
    }
  }
}

void Fire()
{
  if (flop[5])
    ccc = h;
  else
    ccc = blender;
  dot = random(4, MIDLX);
  for (int16_t nn = 0; nn < MATRIX_WIDTH; nn++)
  {
    // Step 1.  Cool down every cell a little
    for (int16_t ii = 0; ii < MATRIX_HEIGHT; ii++)
      heatz[nn][ii] = qsub8( heatz[nn][ii],  random(1, fcool[ii]));

    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int16_t kk = MATRIX_HEIGHT - 1; kk >= 2; kk--)
      heatz[nn][kk] = (heatz[nn][kk - 1] + heatz[nn][kk - 2] + heatz[nn][kk - 2] ) / 3;

    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if (random8() > sparky ) {
      int16_t zz = random(4);
      heatz[nn][zz] = qadd8(heatz[nn][zz], random(190, 255));
    }
    // Step 4.  Map from heat cells to LED colors
    for (int jj = 0; jj < MATRIX_HEIGHT; jj++) {
      if (flop[3] && flop[2]) {
        zeds(nn, MATRIX_HEIGHT - jj) = CHSV( ccc + jj, 195 + jj, heatz[nn][jj]);
      }
      else {

        if (nn % 3 == 0)
          zeds(nn, MATRIX_HEIGHT - jj) = CHSV(6 + jj / 2, 222 + jj / 2 , heatz[nn][jj]); //orange
        else
          zeds(nn, MATRIX_HEIGHT - jj)  = CHSV(30 + jj / 3, 222 + jj / 2, heatz[nn][jj]); //
        if (nn % dot == 0)
          zeds(nn, MATRIX_HEIGHT - jj)  = CHSV( jj , 222 + jj / 2, heatz[nn][jj]); //red
      }

    }

  }
}
// vim:sts=2:sw=2
