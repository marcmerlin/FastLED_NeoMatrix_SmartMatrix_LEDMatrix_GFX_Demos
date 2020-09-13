// Arduino gcc may allow referencing functions before they are defined,
// but gcc in ArduinoOnPC, does not, so copy all the signatures here.
void newpattern();
void whatami();
void runpattern();
void stopred();
void ADCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
void ADFCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
void ADFRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void adjustme();
void Adrawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler);
void ADRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void art();

void audio10();
void audio11();
void audio12();
void audio13();
void audio2();
void audio3();
void audio8();
void audio9();
void audiofireball();
void audioprocess();
void audocheckers();
void audochess();
void Bargraph();
void beatflash(int16_t brit);
void beatsolid(int16_t brit);
void bkboxer();
void bkringer();
void bkstarer();
void bluefado(int16_t bbc);
void bouncey();
void bouncez();
void BouncingBalls(int Ballz);
void bouncingmix(int Ballz);
void Bouncingtri(int Ballz);
void boxer();
void bubbles();
void bubbles2();
void circlearc();
void circleaudio();
void circleaudio2();
void circleaudio3();
void confetti();
void confetti2();
void confetti3();
void confetti4();
void DALine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void dash();
void DCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
void DFCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col);
void DFRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void diagonally();
void Diamondhole();
void DLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void drawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler);
void drawtriangle();
void DRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col);
void drifter();
void drip();
void drips();
void drops();
void dualwind();
void eastwestwind();
void fakenoise();
void Fire();
void fire2();
void fireball();
void fireworks();
void fuzzy();
void ghosts();
void greenfado(int16_t bbc);
void homer();
void homer2();
void homer3();
void hypnoduck();
void hypnoduck2();
void hypnoduck3();
void hypnoduck4();
void Inca(int16_t brit);
void koi();
void LaudioRoger();
void lfado(int16_t bbc);
void magictime();
void mirror();
void noisetest();
void nringer(int16_t i);

void pyrimid();
void Raudio2();
void Raudio2a();
void Raudio3();
void Raudio3a();
void Raudio3b();
void Raudio4();
void Raudio5();
void Raudio5a();
void Raudio6();
void Raudio7();
void Raudio7a();
void Raudio8();
void Raudio8a8();
void Raudio9a9();
void RaudioRoger();
void redfado(int16_t bbc);
void ringer();
void Ringo();
void rmagictime();
void roger();
void rogerv();
void Roundhole();
void scales();
void scales2();
void seasick();
void seasick2();
void seasick3();
void seasick4();
void seasick5();
void seasick6();
void seasickness();
void sinx();
void siny();
void slowmo();
void smile();
void smile2();
void smile3();
void smile4();
void snow(int16_t ccc);
void solid2(int16_t brit);
void solid3(int16_t brit);
void solid4();
void solid5();
void solid6();
void solid6(int16_t klr);
void solidblack();
void solid(int16_t brit);
void solidpyrimid();
void spin2();
void spiral2();
void spiral3();
void spiralwind();
void spiraly();
void spiralz();
void spire();
void spire2();
void spire3();
void spire5();
void splat();
void spoker();
void spoker3();
void STARbubbles();
void starbounce();
void starbubbles88();
void starer();
void starz();
void starz2();
void starz3();
void sticks();
void streaker();
void swirl2();
void swirl3();
void swirl4();
void swirl4a();
void swirl5();
void swirly();
void swirlz();
void tinybubbles();
void tinybubbles2();
void tinybubbles3();
void triangle(int16_t xloc, int16_t yloc, int16_t bigg, int16_t angle, int16_t kolor);
void triangler();
void triforce();
void triple();
void tuber();
void tuber2();
void twister();
void volcano(int16_t brit);
void VORTEX();
void warp();
void web();
void wheelz();
void wheelz2();
void whitestar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler);
void whitewarp();
void spin1();


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

  if (readchar == 'n') {
    local_pattern++;
    Serial.println("Serial => next");
  }
  else if (readchar == 'p') {
    local_pattern--;
    Serial.println("Serial => previous");
  }
  else if (!new_pattern) {
    // when set to true, plays the patterns in random order, if not, they increment, I start with increment and eventually flip this flag to make the progression random
    if (mixit) local_pattern = random(mpatterns); else local_pattern++;
  }

#ifdef BESTPATTERNS
  // wrap around from 0 to last pattern.
  if (!new_pattern) {
    if (local_pattern >= 250) local_pattern = numbest - 1;
    if (local_pattern >= numbest) local_pattern = 0;

    pattern = bestpatterns[local_pattern];
    Serial.print("Mapping best pattern idx ");
    Serial.print(local_pattern);
    Serial.print(" to ");
    Serial.println(pattern);
  }
#else
  if (local_pattern >= 250) local_pattern = lastpatindex - 1;
  if (local_pattern >= lastpatindex) local_pattern = 0;

  pattern = local_pattern;
#endif
  if (new_pattern) pattern = new_pattern;

#ifdef CLEAR_BETWEEN_PATTERNS
  matrix->clear(); // without clear, some pattern transitions via blending look weird
#endif

#ifdef SHOW_PATTERN_NUM
  print_width = 1;
  if (pattern > 9)  print_width = 2;
  if (pattern > 99) print_width = 3;
#endif



#ifdef TME_AUDIO
  digitalWrite(LATCH, LOW);
#endif
  velo = random8();
  nextsong = false;
  quietcount = 0;
  targetfps = random(slowest, fastest);
  bfade = random(1, 9);// do not let this be zero ever!!
  wind = random8(69);
  fancy = random8(69);
  dot = random(2, 6);// controls the size of a circle in many animations
  dot2 = random(2, 6);
  dot3 = random(1, 4);
  adjunct = random(40);//controls which screen wide effect is used if any.  this uses bigger value than number of adjuncts so allows the default to do naught.
  dwell = 1000 * (random(TIMING , TIMING * 2)); //set how long the pattern will play
  ringdelay = random(30, 80);//sets how often one of the effects will happen
  bringdelay = random(70, 110);//sets how often one of the effects will happen
  counter = 0;// reset the counter with each new pattern
  steper = random(1, 9);//color tempo
  shifty = random(2, 13); //how often the drifter moves (2,20)
  ccoolloorr = random8();
  blender = random8();
  xblender = random8();
  poffset = random8();
  pointyfix = random(4, 9);
  for (int8_t g = 0; g < 12; g++) {
    flop[g] = false;
    if (random8() < 128)
      flop[g] = true;
  }
  cool = random (10, 18);
  /*
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
    fcool[i] = random (9, 21);
    }
  */

  for (int i = 0; i < BallCount; i++) {
    kind[i] = random8(7);
  }
  slowme = false;
#ifdef RANDOMSLOWME
  if (random8() > 96)
    slowme = true;
#endif
  hue += random(64);//picks the next color basis
  h = hue;
  // new drift factors for x and y drift
  cangle = random(25, 85) / 100.0;
  sangle = random(25, 85) / 100.0;
  if (random8() > 128) cangle = -cangle;
  if (random8() > 128) sangle = -sangle;


  whatami();//write to screen the lebels (if present) and set some parameters specific to the given pattern
}

void tellit() {

  Serial.print(", Time (s) ");
  Serial.print((dwell) / 1000, 1);
  Serial.print(", Step: ");
  Serial.print(steper);
  Serial.print(", dot: ");
  Serial.print(dot);
  Serial.print(", dot2: ");
  Serial.print(dot2);
  Serial.print(", dot3: ");
  Serial.print(dot3);
  Serial.print(", Adjunct ");
  Serial.print(adjunct);
  Serial.print(" Wind: ");
  Serial.print(wind);
  Serial.print(" Fancy: ");
  Serial.print(fancy);
  Serial.print(" Fader: " );
  Serial.print(bfade);
  Serial.print(" Target FPS: " );
  Serial.print(targetfps);
#ifdef TME_AUDIO
  Serial.print(" Scale: " );
  Serial.print(music.scale);
#endif
  Serial.print(" Velo: " );
  Serial.print(velo);
  if (slowme)
    Serial.print(", Slowmo on, ");
  Serial.print(", Gmusic: ");
  Serial.println(gmusic);

  for (int8_t g = 0; g < 12; g++) {

    Serial.print ("Flop-");
    Serial.print(g);
    Serial.print(":  ");
    Serial.print(flop[g]);
    Serial.print(", ");
  }
}

DEFINE_GRADIENT_PALETTE( pal1 ) {
  0,     0,  0,  0,   //black
  64,   0,  255,  0,  // green
  170, 200, 0, 255, //purple
  255,   255, 255, 255  // white
};


DEFINE_GRADIENT_PALETTE( pal2 ) {
  0,     0,  0,  0,   //black
  32,   255,  0,  0,  // red
  190, 255, 255, 0, //yellow
  255,   255, 255, 255  // white
};

DEFINE_GRADIENT_PALETTE(pal3 ) {    //
  0,    0,  0,  0,   //black

  32, 0, 255, 0,//blue
  190,  0, 255, 255, //teal
  220, 0, 0, 255,//blue
  255,  0, 0, 100  //deep blue
};

DEFINE_GRADIENT_PALETTE( pal4 ) {
  0,     0,  0,  0,   //black
  32,   0,  0,  255,  // blue
  190, 255, 255, 0, //yellow
  255,   255, 255, 255  // white
};
DEFINE_GRADIENT_PALETTE( pal5 ) {
  0,     0,  0,  0,   //black
  32,  255,  0,  0,  // red
  190, 0, 255, 255, //teal
  255,   255, 255, 255  // white
};
DEFINE_GRADIENT_PALETTE( pal6 ) {
  0,     0,  0,  0,   //black
  32,   255,  0,  205,  // pink
  170, 0, 0, 255, //blue
  255,   255, 255, 255  // white
};
void checkshifty() {
  if (counter % shifty == 0) {
    driftx =  driftx + cangle;//move the x center every so often
    if (driftx > (MATRIX_WIDTH - 1 - MIDLX / 4)) { //change direction of drift if you get near the right 1/4 of the screen
      cangle = 0 - fabs(cangle);
      driftx =  driftx + cangle;//move the x center every so often
    }
    if (driftx < MIDLX / 4) { //change direction of drift if you get near the right 1/4 of the screen
      cangle = fabs(cangle);
      driftx =  driftx + cangle;//move the x center every so often
    }
    drifty =  drifty + sangle;//move the y center every so often
    if (drifty > ( MATRIX_HEIGHT - 1 - MIDLY / 4)) { // if y gets too big, reverse
      sangle = 0 - fabs(sangle);
      drifty =  drifty + sangle;//move the y center every so often
    }
    if (drifty < MIDLY / 4) {// if y gets too small reverse
      sangle = fabs(sangle);
      drifty =  drifty + sangle;//move the y center every so often
    }
  }
  driftx = constrain(driftx, MIDLX / 4, MATRIX_WIDTH - 1 - MIDLX / 4); //constrain the center, probably never gets evoked any more but was useful at one time to keep the graphics on the screen....
  drifty = constrain(drifty, MIDLY / 4, MATRIX_HEIGHT - 1 - MIDLY / 4);
}
void checktempo() {
  if (counter % 8 == 0) {
    fps = 8000.00 / (millis() - lasttest);
    lasttest = millis();

    // adjust frame rate if it is too high or low
    if (fps > targetfps)
      waiter++;

    if (fps > targetfps + 10)
      waiter += 3;

    if (fps > targetfps + 25)
      waiter += 5;

    if (fps <= targetfps && waiter > 0)
      waiter--;

    if (fps <= targetfps - 12 && waiter > 3)
      waiter -= 3;

    if (fps <= targetfps - 25 && waiter > 5)
      waiter -= 5;
  }
}

void checkfader() {
  switch (bfade)
  {
    case 0:
      break;

    case 6:
      redfado(20 + (random8() >> 3));
      break;
    case 7:
      greenfado(20 + (random8() >> 3));
      break;
    case 8:
      bluefado(20 + (random8() >> 3));
      break;
    case 99:
      break;
    case 100:

      lfado(6); //almost none  8/256 or 2%
      break;
    case 101:

      lfado(3); //almost none  12/256 or 3.1%
      break;

    case 108:
      bluefado(26);
      break;
    case 109:
      greenfado(26);
      break;
    case 110:
      redfado(26);
      break;
    default:
      lfado(8 + (bfade << 4)); //
      break;
  }
}

void checkfancy()
{
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
      nringer(counter % BIGGER);
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

    case 25:
      audioprocess();
      beatflash(48);
      break;

    case 26:
      audioprocess();
      beatsolid(64);
      break;

    default:
      break;
  }
}
void checkwind() {
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
}

void whatami()// set some parameters specific to the pattern and send some data to the serial port for trouble shooting/ tweaking
{
  Serial.print("Case: ");
  Serial.print(pattern);
  Serial.print(",  ");
  lastmillis = millis();
  switch (pattern)
  {
    case 0:
      Serial.print("Dhole ");//label
      adjunct = random(2, 5); //specify the screen effect as 2 which in this case means HorizontalMirror()  followed by VerticalMirror()  if not specified, it will be what ever was assigned randomly for this pattern
      break;
    case 1:
      Serial.print("Inca ");
      adjunct = random(2, 5);
      if (flop[8])
        fancy = 0;
      break;
    case 2:
      Serial.print("Ringo ");
      fancy = random(10);
      if (flop[5]) {
        Serial.print (" & spire2");
        fancy = 0;
        flop[2] = true;
      }
      targetfps = random(10, 40);
      break;
    case 3:
      Serial.print("Diag ");
      targetfps = random(10, 40);
      break;
    case 4:
      Serial.print("Rhole ");
      if (flop[5])
        Serial.print(" & spin2");
      targetfps = random(10, 40);
      fancy = 0;
      break;
    case 5:
      Serial.print("Drfter ");
      if (flop[5])
        Serial.print(" & spin2");
      targetfps = random(10, 40);

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
      targetfps = 88;
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
      Serial.print("fireball ");
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
      Serial.print("Volc ");
      targetfps = 88;
      if (flop[5])
        Serial.print(" & spire2");

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
      bfade = random(1, 3);
      Serial.print("Siny ");
      break;
    case 19:
      //adjunct = 0;
      Serial.print("Sinx ");
      targetfps = 40;
      bfade = random(1, 4);
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
      targetfps = 40;
      break;
    case 22:
      adjunct = 5;
      steper = mstep;
      Serial.print("BarG mirror");
      break;
    case 23:
      if (flop[5])
        fancy = 25;
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
      targetfps = random(15, 30);
      break;

    case 25:
      Serial.print("spire ");
      adjunct = 0;
      targetfps = random(15, 30);
      break;
    case 26:
      //adjunct = 0;
      //fancy = 0;
      Serial.print("Sinx ");
      steper = mstep;
      targetfps = random(15, 30);
      if (flop[6]) // cool shit
      { Serial.print(" + c0ol chit ");
        bfade = 3;
        adjunct = 3;
        wind = 2;
        fancy = 0;
      }
      break;


    //=======================================================================

    case 27:
      bfade = random(108, 111);
      dwell = 3 * dwell;
      //adjunct = 0;
      //fancy = 0;
      Serial.print("Audio 12");
      targetfps = 80;
      wind = 9;
      slowme = false;//no slowmo.
      break;


    case 28:
      dwell = 2 * dwell;

      bfade = random(1, 5);
      fancy = 0;

      Serial.print("Raudio9a9");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;


    case 29:
      dwell = 2 * dwell;

      bfade = random(2, 6);
      fancy = 0;

      Serial.print("Raudio9a9");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;

    case 30:
      bfade = random(1, 4);
      dwell = 3 * dwell;
      flop[10] = true;
      if (!flop[0]) {
        adjunct = 11;  //wow this is cool
        wind = 8;
        bfade = 3;
        Serial.print("Audio 2 Quad Bot Tri Mir");
      }
      else {
        adjunct = 5;
        Serial.print("Audio2 V mirror");
      }
      fancy = 0;
      slowme = false;//no slowmo.

      targetfps = 80;
      break;

    case 31:
      bfade = random(1, 4);
      dwell = 3 * dwell;
      fancy = 0;
      if (wind < 9) {
        if (flop[1])
          wind = random (1, 3);
        else
          wind = random(7, 11);
      }
      Serial.print("Audio3");
      flop[10] = true;
      targetfps = 80;
      slowme = false;//no slowmo.
      break;

    case 32:
      bfade = random(1, 3);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      if ( flop[0])
        wind = 9;
      else
        wind = 0;
      Serial.print("Audio8 stereo");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;

    case 33:
      bfade = random(1, 3);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      wind = 10;
      slowme = false;//no slowmo.
      Serial.print("RAudio2");
      targetfps = 80;
      break;

    case 34:
      bfade = random(2, 5);
      dwell = 10 * dwell;
      adjunct = 0;
      fancy = 0;
      if (flop[2] || !flop[1])
        wind = 9;

      slowme = false;//no slowmo.
      Serial.print("RAudio 3");
      targetfps = 80;

      break;

    case 35:
      bfade = random(1, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      // fancy = 0;
      slowme = false;//no slowmo.
      Serial.print("RAaudio 4");
      targetfps = 80;
      break;

    case 36:
      bfade = random(2, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      //fancy = 0;
      slowme = false;//no slowmo.
      Serial.print("RAudio 5");
      targetfps = 80;
      break;

    case 37:
      bfade = random(2, 4);
      dwell = 3 * dwell;
      fancy = 0;

      if (wind % 2 != 0) wind --;
      slowme = false;//no slowmo.
      Serial.print("RAudio");
      targetfps = 80;
      break;

    case 38:
      bfade = random(2, 4);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      slowme = false;//no slowmo.
      Serial.print("2x raudio4");
      targetfps = 80;
      break;

    case 39:
      bfade = random(2, 5);
      dwell = 10 * dwell;
      adjunct = 0;
      slowme = false;//no slowmo.
      Serial.print("raudio 2a & 3");
      targetfps = 80;
      break;

    case 40:
      if (!flop[0])
        adjunct = 3;//quad triangle
      else
        adjunct = 11;//triangle mirrow
      slowme = false;//no slowmo.
      bfade = random(1, 4);
      dwell = 3 * dwell;
      Serial.print("Raudio6 adj");
      targetfps = 80;
      break;

    case 41:
      bfade = random(1, 4);
      dwell = 3 * dwell;
      slowme = false;//no slowmo.
      if (flop[1] && flop[2])
        adjunct = 12;
      else {
        adjunct = random(1, 7);
        if (flop[9]) {
          adjunct = 4;
          wind = 15;
          fancy = 62;
        }
      }
      Serial.print("RAudio7");
      targetfps = 80;
      break;

    case 42:
      dwell = 3 * dwell;
      // adjunct = 0;
      fancy = 0;
      slowme = false;//no slowmo.
      Serial.print("RAudio 5a");

      if ( flop[0])
      {
        adjunct = 11;
        wind = 6;

      }
      else if (flop[1])
        adjunct = 12;
      else
        adjunct = 0;


      targetfps = 80;
      break;

    case 43:
      Serial.print("RAudio5 ");
      dwell = 3 * dwell;
      if ( flop[0])
      {
        adjunct = 11;
        wind = 6;
        Serial.print(" adj=11");
      }

      else {
        if (flop[1]) {
          adjunct = 12;
          Serial.print(" adj=12");
        }
        else {
          adjunct = 0;
          Serial.print(" adj = 0");
        }
      }
      slowme = false;//no slowmo.
      //fancy = 0;


      targetfps = 80;
      if (wind < 9)
        bfade = 4;

      break;

    case 44:
      dwell = 3 * dwell;
      bfade = random(2, 5);
      fancy = 0;
      slowme = false;//no slowmo.
      Serial.print("Raud4 & Raud5");
      targetfps = 80;

      break;

    case 45:
      dwell = 3 * dwell;
      fancy = 0;
      wind = 0;
      slowme = false;//no slowmo.
      Serial.print("checkers");
      targetfps = 80;
      break;

    case 46:
      dwell = 3 * dwell;
      bfade = random(2, 5);
      fancy = 0;
      adjunct = 0;
      Serial.print("raud7 and raud5");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;

    case 47:
      bfade = random(2, 5);
      dwell = 3 * dwell;

      fancy = 0;
      slowme = false;//no slowmo.
      if (adjunct == 6) adjunct = 7;
      Serial.print("2x raudio4 and raudio5");
      targetfps = 80;
      break;

    case 48:
      dwell = 3 * dwell;
      bfade = random(3, 6);
      fancy = 0;
      wind = 0;
      adjunct = 0;
      Serial.print("spin1 raud4");
      targetfps = 80;
      slowme = false;//no slowmo.
      dot++;
      break;

    case 49:
      dwell = 3 * dwell;
      bfade = random(3, 6);
      fancy = 0;

      adjunct = 12;
      Serial.print("raudio 5 ");
      targetfps = 80;
      slowme = false;//no slowmo.
      //dot++;
      flop[2] = true;
      break;

    case 50:
      bfade = random(1, 4);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      if (wind < 9)
        wind = random(1, 4);

      Serial.print("Audio9");
      slowme = false;//no slowmo.
      targetfps = 80;
      break;

    case 51:
      dwell = 3 * dwell;
      fancy = 0;
      wind = 0;
      slowme = false;//no slowmo.
      Serial.print("chess");
      targetfps = 80;
      break;

    case 52:
      bfade = random(3, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      if (wind < 9)
        wind = random(1, 4);

      Serial.print("Audio10");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;
    //======================================
    case 53:
      Serial.print("seasick 2 adj wind");
      bfade = random(2, 6);
      targetfps = 50;
      fancy = 0;
      if (flop[6])
        adjunct = 10;
      //wind = 0;
      break;
    case 54:
      Serial.print("splat ");
      dwell = dwell / 2;
      targetfps = random (6, 15);
      bfade = random(1, 4);
      break;
    case 55:
      Serial.print("seasick");
      bfade = random(2, 6);
      targetfps = 50;
      fancy = 0;
      wind = 0;
      break;
    case 56:
      Serial.print("bounce ");
      fancy = random(1, 29);//more likely
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
      targetfps = random (16, 40);
      Serial.print("warp, effects and wind");

      fancy = random(1, 23);
      wind = random(1, 11);
      break;
    case 62:
      Serial.print("warp and confetti 4");
      targetfps = random(15, 35);
      fancy = random(1, 17);
      break;
    case 63:
      bfade = 100;
      wind = random(1, 11);
      targetfps = random(5, 25);
      fancy = random(1, 23);
      Serial.print("confetti 4");
      break;
    case 64:
      bfade = 100;
      wind = random(1, 11);
      targetfps = random(5, 25);
      if (flop[4])
        adjunct = random(4, 8);
      //fancy = random(1, 23);
      Serial.print("triple");
      break;
    case 65:
      Serial.print("slow web");
      targetfps = random (5, 10);
      //wind = 0;
      break;

    case 66:
      targetfps = random (15, 45);
      if (wind % 2 != 0)
        wind--;
      Serial.print("hypnoduck");
      break;

    case 67:
      targetfps = random (15, 45);
      adjunct = 0;
      //  fancy = 0;
      Serial.print("hypnoduck 2");
      break;
    case 68:
      targetfps = random (15, 45);
      // adjunct = 0;
      //  fancy = 0;
      Serial.print("Roger");
      break;

    case 69:
      targetfps = random (13, 30);
      Serial.print("drops with someeffects ");

      //fancy = random(1, 17);
      break;
    case 70:
      Serial.print("spin2 ");
      //targetfps = random (5, 15);
    break; case 71:
      Serial.print("spin1 ");
      targetfps = random (5, 15);
      break;
    case 72:
      Serial.print("homer ");
      targetfps = random (6, 10);
      bfade = random(1, 4);
      break;
    case 73:
      Serial.print("homer2 - egg ");
      targetfps = random (15, 25);
      wind = 0;
      break;
    case 74:
      Serial.print("fireball w/ eff ");
      // targetfps = random (5, 15);
      adjunct = 3;
      if (flop[4]) {
        adjunct = 4;
        wind = 2;
        fancy = 0;
      }
      break;
    case 75:
      Serial.print("seasick");
      bfade = random(2, 5);
      targetfps = random(8, 30);
      fancy = 0;
      break;
    case 76:
      targetfps = random(5, 12);
      Serial.print("seasick2");
      bfade = random(2, 6);
      fancy = 0;
      break;
    case 77:
      Serial.print("whtwarp ");
      targetfps = random(8, 27);
      wind = 0;
      fancy = random(15, 19);
      break;

    case 78:
      Serial.print("tri warp ");
      targetfps = random(15, 32);
      if (flop[4] || flop[5])
        wind = 0;
      fancy = 0;
      break;

    case 79:
      Serial.print("stars3");
      targetfps = random(30, 52);
      wind = 0;
      break;
    case 80:
      Serial.print("starz ");
      if (flop[5]) Serial.print ("Trans ");
      targetfps = random(18, 40);
      break;
    case 81:
      Serial.print("starz2 ");
      targetfps = random(18, 40);
      wind = 2 * wind + 1;// less likely
      break;

    case 82:
      Serial.print("swirl 2 ");
      targetfps = random(18, 25);
      wind = 0;
      fancy = 0;
      bfade = random (6, 9); //color fade

      break;
    case 83:
      if (flop[4] || flop[5])
        adjunct = 9;
      Serial.print("circlearc ");
      fancy = fancy / 2;
      targetfps = random(15, 35);
      break;

    case 84:
      Serial.print("fireball ");
      targetfps = random(20, 45);
      break;
    case 85:
      Serial.print("wheelz ");
      targetfps = random(10, 35);
      fancy = 0;
      wind = 0;
      bfade ++;
      break;
    case 86:
      Serial.print("starbounce ");
      fancy = 18;
      //targetfps = random (5, 15);
      bfade = random(2, 5);
      break;
    case 87:
      Serial.print("wheels2 ");
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
      if (flop[4] || flop[5] || flop[6])
        wind = 0;
      fancy = 0;
      if (flop[7] || flop[8])
        slowme = false;
      break;
    case 91:
      Serial.print("swirl with fancy");
      fancy = random(1, 17);
      targetfps = random(8, 15);
      bfade = random (2, 6);
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
      bfade = random (1, 4);
      wind = 0;
      fancy = 0;
      targetfps = random (10, 20);
      break;

    case 95:
      Serial.print("dual drip");
      if (flop[4] || flop[5]) {
        wind = 0;
        fancy = 0;
      }

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
      if (flop[7])
        bfade = 1;
      targetfps = random(15, 25);
      Serial.print("spin1");
      break;

    case 98:
      dwell = dwell * 2;
      targetfps = random (10, 20);
      Serial.print("swirl5");
      bfade = random (1, 5);
      if (flop[3])
        wind = wind * 2 + 1;//less likely and odd
      fancy = 0;
      break;

    case 99:
      targetfps = random (10, 25);
      Serial.print("spoke?");
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
      if (flop[4] || flop[5])
        wind = 3;
      bfade = random (1, 5);
      fancy = 0;
      break;
    case 103:
      Serial.print("hypnoduck3");
      if (flop[7] && flop[9])
        Serial.print(" and whitewarp");
      wind = 0;
      fancy = 0;
      break;

    case 104:
      Serial.print("circlearc");

      break;
    case 105:
      wind = 0;
      Serial.print("hypnoduck4");
      targetfps = random(10, 52);
      fancy = 0;
      break;
    case 106:
      Serial.print("circlearc");
      targetfps = random (10, 30);
      adjunct = 3;
      fancy = 0;
      wind = 3;

      break;
    case 107:
      Serial.print("floaty star, Rmag, bkstar");
      if (flop[9] || flop[8])
        fancy = random(6, 9);//avoid bk-starer
      targetfps = random(10, 30);
      break;

    case 108:
      Serial.print("white warp rmagic adjust");
      targetfps = random(8, 20);
      adjunct = random(2, 10);
      break;

    case 109:
      Serial.print("spin1, warp");
      //targetfps = random(15, 30);
      break;
    case 110:
      Serial.print("bubbles ");
      targetfps = random(18, 42);
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
      bfade = random(2, 6);
      fancy = 0;
      if (wind < 9)
        wind = 3;
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
      targetfps = random(10, 60);
      bfade = 3;
      break;
    case 117:
      Serial.print("streaker triangle  ");
      wind = 0;
      targetfps = random(10, 50);
      //bfade = 4;
      break;
    case 118:
      Serial.print("drops & spin2");
      targetfps = random(9, 30);
      bfade = random (1, 4);
      if (flop[0] || flop[1])
        wind = 0;
      fancy = 0;
      break;

    case 119:
      Serial.print("spin2 ");
      targetfps = random(9, 30);
      bfade = random (1, 4);
      if ( flop[0])wind = 8;
      else
        wind = 9;
      break;

    case 120:
      Serial.print("windy drops ");
      targetfps = random(25, 38);
      bfade = random (1, 5);
      wind = random(2, 5);
      if (BIGGER == 64) adjunct = 11 ;

      fancy = 0;
      break;

    case 121:
      Serial.print("round dr0ps wind ");
      targetfps = random(25, 38);
      bfade = random (3, 6);
      wind = random(2, 5);
      if (BIGGER == 64) adjunct = 11 ;

      fancy = 0;
      break;

    case 122:
      Serial.print("round drops ");
      targetfps = random(15, 28);
      bfade = random (2, 5);
      if (flop[0] && flop[1])
        wind = 6;
      else if (flop[2])
        wind = 3;
      else wind = 0;
      adjunct = 0;

      fancy = 0;
      break;

    case 123:
      if (flop[4]) bfade = 99;//leave trails
      fancy = 0;
      wind = 0;
      targetfps = random(15, 25);
      Serial.print("tiny bubbles 2");
      break;

    case 124:
      fancy = 0;

      Serial.print("tiny bubbles");
      break;
    case 125:
      // fancy = 0;
      // wind = 0;
      Serial.print("tiny bubbles 2");
      break;

    case 126:
      fancy = 0;
      wind = 0;
      Serial.print("whitewarp fireworks");
      break;
    case 127:
      Serial.print("seasick 3");
      targetfps = random(5, 60);
      bfade = 1;
      break;
    case 128:
      Serial.print("magictime");
      targetfps = random(5, 20);
      bfade = 2;
      fancy = random(1, 17);
      break;
    case 129:
      Serial.print("audio roger");
      bfade = random(2, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      targetfps = 80;
      slowme = false;//no slowmo.
      break;

    case 130:
      Serial.print("double audio roger");
      bfade = random(2, 5);
      dwell = 3 * dwell;
      adjunct = random(64);
      targetfps = 80;
      slowme = false;//no slowmo.
      break;
    case 131:
      Serial.print("seasick6");
      targetfps = random(20, 60);
      bfade = random (108, 111);
      if (flop[2] || flop[3])
        fancy = 0;
      break;
    case 132:
      bfade = random (108, 111);
      Serial.print("spiral moving");
      targetfps = random(10, 30);
      adjunct = random8();
      wind = 0;
      fancy = random8();

      break;


    case 133:
      Serial.print("spiral2 fixed");
      targetfps = random(6 , 20);
      if (flop[3])
        adjunct = random8() / 2;
      wind = wind * 2 + 1;
      fancy = random8();


      break;
    case 134:
      Serial.print("spiral fixed");
      targetfps = random(6 , 30);
      if (flop[3])
        adjunct = random8() / 2;
      wind = wind * 2 + 1;
      if (flop[6])
        fancy = 0;
      bfade = random(2, 5);

      break;
    case 135:
      Serial.print("spiral2 moving");
      targetfps = random(6 , 20);
      bfade = random(2, 5);
      wind = wind * 2 + 1;
      fancy = random8();
      break;

    case 136:
      Serial.print("spire3, conf2 ");
      targetfps = random(10 , 24);
      fancy = 0;
      bfade = 1;
      adjunct = 3;
      flop[0] = true;
      flop[1] = false;
      flop[2] = true;
      break;

    case 137:
      bfade = random(3, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      wind = 10;
      Serial.print("Audio 11");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;


    case 138:
      bfade = random(3, 5);
      dwell = 3 * dwell;
      adjunct = 0;
      fancy = 0;
      Serial.print("Audio 10");
      targetfps = 80;
      wind = 9;
      slowme = false;//no slowmo.
      break;

    case 139:
      Serial.print("spiral3 fixed");
      targetfps = random(8 , 24);
      adjunct = random8();
      wind = wind * 2 + 1;
      fancy = random8();


      break;

    case 140:
      Serial.print("spire3, conf2 wild ");
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
      pointyfix = 1400;
      targetfps = random(fastest * 2, 3 * fastest);
      slowme = false;//no slowmo.
      break;


    case 142:
      Serial.print("Crazy Snow");
      dwell = 1 * dwell;
      pointyfix = 1400;
      bfade = 0;
      if (flop[6] || flop[7]) {
        adjunct  = 3;
        pointyfix = 290;
      }
      // adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = random(fastest / 2, 3 * fastest + 12);
      slowme = false;//no slowmo.

      break;

    case 143:
      Serial.print("bouncer");


      bfade = random(2, 5);


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

      if (flop[2])
        directn = 0;
      else
        directn = 1;
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
      if ( flop[0])
        directn = 0;
      else
        directn = 1;
      break;

    case 146:
      Serial.print("dashes");
      // dwell = 1.5 * dwell;
      bfade = 101;
      adjunct = 0;
      fancy = 0;
      wind = 0;
      targetfps = 6;
      waiter = 100;
      slowme = false;//slowmo.
      break;

    case 147:
      adjunct = 12;
      targetfps = random(8, 20);
      Serial.print("Wt warp  much adjustment");
      break;

    case 148:
      targetfps = random(6, 20);
      bfade = random(2, 6);
      Serial.print("swirl4 ");
      if (flop[4] || flop[5] || flop[6])
        wind = 0;
      fancy = 0;
      slowme = false;
      break;
    case 149:
      targetfps = random(10, 30);
      bfade = 1;
      if (flop[7] && flop[8])
        bfade = 101;
      Serial.print("VORTEX ");
      if (flop[7] || !flop[6]) {
        wind = 0;
      }
      if (flop[1] || !flop[8]) {
        adjunct = 0;
      }
      fancy = 0;
      slowme = false;
      if (flop[2] && flop[3] && flop[4])
        slowme = true;
      break;

    case 150:
      targetfps = random(20, 30);
      Serial.print("Fire  ");
      wind = 0;



      adjunct = 0;


      fancy = 0;
      slowme = false;

      break;
    case 151:
      bfade = random(3, 5);
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

    case 153://49
      dwell = 3 * dwell;
      bfade = 3;
      fancy = 0;
      adjunct = 12;
      Serial.print("fuzzy raudio 5 and  Raudio9a9");
      targetfps = 80;
      slowme = false;//no slowmo.
      dot++;
      flop[2] = true;
      break;

    case 154:
      dwell = 3 * dwell;
      bfade = 0;
      fancy = 0;
      //adjunct = 12;
      Serial.print("Raudio8a8 and solid5");
      targetfps = 80;
      slowme = false;//no slowmo.
      //  dot++;
      //   flop[2] = true;
      break;

    case 155:
      bfade = 99;
      fancy = 0;
      wind = 0;
      targetfps = random(10, 20);
      Serial.print("star bubbles");
      break;
    case 156:
      bfade = 99;
      fancy = 0;
      wind = 0;
      targetfps = random(8, 15);
      Serial.print("squarebubbles");
      break;

    case 157:
      dwell = 3 * dwell;
      bfade = 2;
      fancy = 0;

      Serial.print("audiofireball");
      targetfps = 80;
      slowme = false;//no slowmo.
      break;
    case 158:
      targetfps = random(6, 20);
      shifty = 1;
      slowme = false;//no slowmo.
      Serial.print("tuber ");
      fancy = random(15);
      if (random8() > 128)
        adjunct = 5;
      bfade = random(108, 111);
      break;


    case 159:
      bfade = random(3, 5);
      dwell = 3 * dwell;
      //adjunct = 0;
      fancy = 0;
      Serial.print("Audio 12");
      if (flop[5] || flop[8]) {
        Serial.print(" & Solid 5");
        bfade = 0;
      }
      targetfps = 80;

      slowme = false;//no slowmo.
      break;

    case 160:
      Serial.print("seasick 2 adj with wind");
      //bfade = random(2, 6);

      fancy = 0;

      break;

    case 161:
      Serial.print("seasick 2 adj");
      bfade = random(2, 6);

      fancy = 0;
      wind = 0;
      break;

    case 162:
      Serial.print("Audio 13");
      Serial.print(" & Solid 2");
      //dwell = 5 * dwell;
      //adjunct = 0;
      fancy = 0;

      bfade = 0;

      targetfps = 2;
      //wind = 9;
      slowme = false;//no slowmo.
      break;

    case 163:
      Serial.print("art");
      targetfps = 30;
      // dwell = 2 * dwell;
      fancy = 0;
      bfade = 0;
      wind = 0;
      slowme = true;
      adjunct = 0;
      break;

    case 164:
      Serial.print("art traditional");
      targetfps = 30;
      // dwell = 2 * dwell;
      fancy = 0;
      bfade = 0;
      wind = 0;
      slowme = true;
      adjunct = 0;
      blender = 0;
      velo = 4;
      break;

    case 165:
      Serial.print("circ audio");
      targetfps = 80;
      dwell = 3 * dwell;
      fancy = 0;
      bfade = random(1, 5);
      // wind = 0;
      slowme = false;
      //adjunct = 0;
      break;

    case 166:
      Serial.print("circ audio 2");
      targetfps = 80;
      dwell = 3 * dwell;
      fancy = 0;
      bfade = random(1, 5);
      //  wind = 0;
      slowme = false;
      //adjunct = 0;
      break;
    //========================



    case 167:
      Serial.print("aurora // waves: ");
      item = 7;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 27;
      }
      break;

    case 168:
      Serial.print("aurora cube: ");
      item = 8;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 27;
      }
      break;

    case 169:
      Serial.print("aurora //waves: ");
      item = 7;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 3;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 26;
      }
      break;

    case 170:
      Serial.print("aurora worm: ");
      item = 4;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      fancy = 0;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 26;
      }
      break;
    case 171:
      Serial.print("aurora pattern: cube");
      item = 2;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
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
      Serial.print("aurora whirlly: ");
      item = 0;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
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
    case 173:
      Serial.print("tiny bubbles3 ");
      targetfps = random(5, 12);
      bfade = 10;//lots
      fancy = 0;
      slowme = false;
      break;

    case 174:
      Serial.print("web ");
      targetfps = random(5, 12);
      bfade = random(2, 7); //lots
      fancy = 0;
      slowme = false;
      if (flop[9])
        wind = 0;
      break;

    case 175:
      Serial.print("aurora cube:");

      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 2;
      bfade = 2;
      Serial.print(item);
      patternz = items[item];
      patternz->start();

      fancy = 26;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 0;
        fancy = 0;
      }
      break;
    case 176:
      Serial.print("aurora worms: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 4;
      bfade = 0;
      adjunct = 0;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      fancy = 26;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;
    case 177:
      Serial.print("aurora circ wave: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 5;
      bfade = 101;
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 1;
      fancy = 26;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;
    case 178:
      Serial.print("aurora sin wave: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 12;
      bfade = 101;
      Serial.print(item);
      patternz = items[item];
      patternz->start();

      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 26;
      }
      break;

    case 179:
      Serial.print("aurora flock: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
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

    case 180:
      Serial.print("aurora incrementaldrift2: ");

      item = 6;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      patternz->start();
      bfade = 0;
      fancy = 27;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;
    case 181:
      Serial.print("aurora spiral: ");

      item = 9;
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      fancy = 27;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;
    case 182:
      Serial.print("aurora wave: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 12;

      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      wind = 2;
      fancy = 27;
      if ( flop[3] || flop[4]) {

        bfade = 101;
        fancy = 0;
      }
      break;
    case 183:
      Serial.print("aurora swirl: ");
      solidblack();
      matrix->show();
      solidblack();
      matrix->show();
      item = 11;

      Serial.print(item);
      patternz = items[item];
      patternz->start();
      bfade = 0;
      fancy = 27;
      if ( flop[3] || flop[4]) {
        wind = 0;
        bfade = 1;
        fancy = 0;
      }
      break;
    case 184:
      Serial.print("circ audio 3");
      targetfps = 80;
      dwell = 2 * dwell;
      fancy = 0;
      bfade = random(1, 5);
      //  wind = 0;
      slowme = false;
      //adjunct = 0;
      break;
    //========================
    case 185:
      Serial.print("fire2");
      targetfps = 80;

      fancy = 0;
      //  bfade = random(1, 5);
      wind = 0;
      slowme = false;
      flop[1] = true;
      adjunct = 0;
      break;
    //========================
    case 186:
      Serial.print("fire2");
      targetfps = 80;

      fancy = 0;
      // bfade = random(1, 5);
      wind = 0;
      slowme = false;
      adjunct = 0;
      flop[1] = false;
      break;
    //========================

    case 187:
      Serial.print("ghost");

      bfade = random(3, 5);


      break;
    //========================
    case 188:
      Serial.print("ghost adjust");
      bfade = random(3, 5);

      break;

    //========
    default:
      Serial.print("D - fault");
      adjunct = 0;
      fancy = 0;
      bfade = 3;
#ifdef MIXIT_AFTER_FIRST_PASS
      mixit = true; //after  you get here the first time, it all gets random.
#endif
      break;
  }
  tellit();
}


void runpattern() {//here the actuall effect is called based on the pattern number,  sometimes more than one is called, sometimes the logical switches, dictate what is called
#ifdef SHOW_PATTERN_NUM
  // delete the number in case the screen is used for transformation/mirroring
  matrix->fillRect(0, 0, 4 * print_width, 7, 0);
#endif
#ifdef DISPLAY_FPS
  // Make dark overlay for the white font to be visible
  matrix->fillRect(MATRIX_WIDTH - 1 - 4 * 3, 0, 4 * 3 + 1, 7, 0);
#endif
  switch (pattern) {
    case 0:
      Diamondhole();

      adjustme();// apply the screenwide effect
      break;
    case 1:
      Inca(255 - blender / 8);

      zeds.QuadrantBottomTriangleMirror();
      break;
    case 2:
      Ringo();
      if ( flop[0])
        zeds.QuadrantBottomTriangleMirror();
      if (flop[5]) {


        spire3();
      }
      else if (flop[3])
        spin2();
      break;
    case 3:
      drifter();
      if (flop[5])
        spire();
      else {
        if (flop[7])
          spin2();
        else if (flop[9])
          spin1();
      }
      adjustme();
      break;
    case 4:
      Roundhole();
      if (flop[5])
        spin2();
      else if (flop[7])
        spire3();
      adjustme();
      break;
    case 5:
      drifter();
      if (flop[5])
        spin2();
      else {
        if (flop[7])
          spin1();
        else if (flop[9])
          spire2();
      }
      adjustme();
      break;
    case 6:
      drip();
      break;
    case 7:
      if (flop[2] || flop[1])
        solid5();

      volcano(255 - blender / 8);

      adjustme();
      break;
    case 8:

      solid5();
      pyrimid();

      adjustme();
      break;
    case 9:
      solidpyrimid();
      adjustme();
      break;
    case 10:

      fireball();
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
      if (flop[2] || flop[1])
        solid5();
      volcano(255 - blender / 8);
      adjustme();
      if (flop[5])
        spire2();
      else if (flop[7])
        spin2();
      break;

    case 14:

      spire2();
      if (flop[0] && flop[1])
        adjustme();
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
      if (flop[0] && flop[2])
        adjustme();
      break;
    case 19:
      sinx();
      if (flop[0] && !flop[2])
        adjustme();
      break;
    case 20:

      triple();
      if (flop[3]  || (flop[4] && flop[8]) )
        adjustme();
      break;

    case 21:
      spire5();
      twister();
      if (flop[7])
        adjustme();
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
      if (flop[4])
        solid5();
      Bargraph();
      break;

    case 25:
      spire();
      if (flop[2])
        adjustme();
      break;

    case 26:
      sinx();
      if (flop[7] || flop[5] || !flop[2])
        adjustme();
      break;


    case 27:
      audio12();
      if (flop[7] || flop[5])
        adjustme();
      break;

    // start of audio sectionnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn

    case 28:
      if (flop[5]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      Raudio9a9();
      twister();
      break;

    case 29:
      driftx = MIDLX ;
      drifty = MIDLY ;
      Raudio9a9();

      if (flop[1] && wind < 9)
        twister();
      break;

    case 30:

      if (!flop[0] && !flop[1])
        solid2(128);
      audio2();
      adjustme();

      break;

    case 31:
      //digitalWrite(LATCH, HIGH);
      if (flop[6] || flop[2])
        solid3(48);
      else if (flop[5])
        solid2(48);
      audio3();

      break;

    case 32:
      if (flop[0] || flop[4])
        solid5();
      audio8();

      break;

    case 33:
      //digitalWrite(LATCH, HIGH);
      if (flop[6]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      Raudio2();
      break;

    case 34:
      if (flop[1]) {
        driftx = MIDLX ;

      }
      if (flop[2]) {

        drifty = MIDLY ;
      }

      if ( flop[0])
        Raudio3();
      else
        Raudio3b();
      break;


    case 35:
      //digitalWrite(LATCH, HIGH);
      if (flop[1]) {
        driftx = MIDLX ;

      }
      if (flop[2]) {

        drifty = MIDLY ;
      }
      if (!flop[0] && flop[2]) {
        bfade = 0;
        solid5();
      }

      Raudio4();
      break;

    case 36:
      //digitalWrite(LATCH, HIGH);
      if (flop[1]) {
        driftx = MIDLX ;

      }
      if (flop[2]) {

        drifty = MIDLY ;
      }
      if (flop[1] && flop[2] && !flop[0]) {
        solid3(78);
        bfade = 0;
      }
      Raudio5();
      break;

    case 37:
      if (flop[9] && flop[2]) {
        solid5();
        bfade = 0;
      }
      if (flop[7]) {
        driftx = MIDLX ;
      }
      if (flop[5]) {
        drifty = MIDLY ;
      }
      Raudio9a9();
      adjustme();
      break;

    case 38:
      flop[3] = ! flop[3];
      driftx = MATRIX_WIDTH / 3;
      drifty = MATRIX_HEIGHT / 3;
      Raudio4();
      flop[3] = ! flop[3];
      driftx = MATRIX_WIDTH * 2 / 3;
      drifty = MATRIX_HEIGHT * 2 / 3;
      Raudio4();
      if (flop[1] && wind < 9)
        twister();
      break;

    case 39:

      if (flop[1] && wind < 9)
        twister();
      Raudio3a();
      Raudio2a();
      break;

    case 40:
      driftx = MIDLX ;
      drifty = MIDLY ;

      Raudio6();
      adjustme();
      break;

    case 41:
      if (flop[6] || flop[7]) {
        beatflash(78);
      }
      if (flop[1] || flop[3]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      if ( flop[0] || flop[8])
        Raudio7a();
      else
        Raudio7();
      if (flop[5] || flop[4])
        adjustme();
      break;

    case 42:
      driftx = MIDLX ;
      drifty = MIDLY ;
      Raudio5a();
      adjustme();
      break;

    case 43:
      driftx = MIDLX ;
      drifty = MIDLY ;
      Raudio5();
      adjustme();
      break;

    case 44:
      if (flop[6]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      Raudio4();
      Raudio5();
      if (flop[7] && flop[5])
        adjustme();
      break;


    case 45:
      audocheckers();

      break;

    case 46:
      if (flop[1] || flop[0]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      Raudio7();
      Raudio5();
      break;

    case 47:
      flop[3] = ! flop[3];
      driftx = MATRIX_WIDTH * 2 / 3;
      drifty = MATRIX_HEIGHT * 2 / 3;
      Raudio4();
      flop[3] = ! flop[3];
      driftx = MATRIX_WIDTH / 3;
      drifty = MATRIX_HEIGHT  / 3;
      Raudio4();
      if (flop[1] && wind < 9)
        twister();
      adjustme();
      Raudio5();
      break;

    case 48:
      driftx = MIDLX ;
      drifty = MIDLY ;
      spin1();
      Raudio4();
      fireworks();
      adjustme();
      break;

    case 49:
      driftx = MIDLX ;
      drifty = MIDLY ;
      Raudio5();
      adjustme();
      break;



    case 50:
      solid2(128);
      audio9();
      adjustme();

      break;

    case 51:
      audochess();
      break;

    case 52:
      audio10();
      adjustme();
      break;
    // end of audio sectionnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnn

    case 53:
      seasick2();
      adjustme();
      break;

    case 54:


      splat();

      break;

    case 55:
      seasick();
      break;

    case 56:

      bouncey();
      if (flop[6] || flop[5])
        adjustme();
      break;

    case 57:
      bouncey();
      adjustme();
      break;

    case 58:
      whitewarp();
      adjustme();
      if (flop[1] && wind < 9)
        twister();
      break;


    case 59:
      fireball();

      break;

    case 60:

      if (flop[0] || flop[1] )
        confetti4();
      fireball();
      adjustme();
      break;


    case 61:
      EVERY_N_SECONDS(dot3 + dot2 * dot) {
        fancy = random(1, 23);
        adjunct = random (12);
      }
      warp();
      adjustme();

      break;

    case 62:
      warp();
      if (flop[2])
        confetti4();
      adjustme();

      break;

    case 63:
      confetti();
      confetti4();

      if (wind < 9)
        twister();
      adjustme();
      break;

    case 64:
      triple();
      adjustme();
      break;

    case 65:
      web();
      if (flop[9])
        adjustme();
      break;

    case 66:
      hypnoduck();
      if (flop[9])
        adjustme();
      break;

    case 67:
      hypnoduck2();
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
      if (!flop[0] || flop[1]) adjustme();
      break;

    case 71:
      spin1();

      break;

    case 72:
      homer();
      break;

    case 73:
      homer2();
      if (flop[1] && flop[2] && wind < 9)
        twister();
      break;

    case 74:

      fireball();
      adjustme();
      break;

    case 75:
      seasick6();
      break;

    case 76:
      seasick2();
      break;

    case 77:

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
      if (flop[1] && flop[2] && wind < 9)
        twister();
      circlearc();
      adjustme();
      break;

    case 84:
      if (flop[1] && flop[2] && wind < 9)
        twister();
      fireball();
      break;

    case 85:
      wheelz();
      if (flop[5] || flop[6])
        adjustme();
      break;

    case 86:
      if (flop[7])
        solid2(128);
      starbounce();
      if (flop[5] && flop[6])
        adjustme();
      break;

    case 87:
      wheelz2();
      if (flop[5] || flop[6])
        adjustme();
      break;

    case 88:
      if (!flop[2])
        warp();

      triforce();
      if (flop[4])
        adjustme();

      break;

    case 89:
      swirly();
      break;

    case 90:
      swirl4a();
      break;

    case 91:
      swirl3();
      EVERY_N_SECONDS(5 + 3 * dot)
      fancy = random(1, 22);
      if (flop[2] || flop[3])
        adjustme();
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
      spin1();
      break;

    case 98:
      swirl5();
      break;

    case 99:
      spoker3();
      break;

    case 100:
      if (flop[7])
        solid5();
      EVERY_N_SECONDS(2 + 3 * dot)
      fancy = random(1, 22);
      adjustme();
      //confetti2();
      break;


    case 101:
      confetti4();
      if (flop[0] || flop[1] || flop[2])
        warp();

      break;

    case 102:
      seasick4();
      break;

    case 103:
      if (flop[7] && flop[9])
        whitewarp();
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
      for (int j = 1; j < MATRIX_WIDTH - 8; j++)//0
        drawstar(driftx, drifty, j, j / 2, 7, 2 * h, h + j * 4);
      if (flop[0])
        rmagictime();
      bkstarer();
      adjustme();
      break;


    case 108:
      whitewarp();
      rmagictime();
      if (flop[1] && flop[2] && wind < 9)
        twister();
      break;

    case 109:
      warp();
      spin1();

      if (flop[0] && !flop[5])
        adjustme();
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
      if (flop[5]) {
        audioprocess();
        beatflash(255);
      }
      streaker();
      drawtriangle();

      break;

    case 118:
      drops();
      spin2();
      // adjustme();
      break;

    case 119:
      spin2();
      break;


    case 120:
      drops();
      twister();
      if (flop[5])
        adjustme();
      break;

    case 121:
      drips();
      twister();
      adjustme();

      break;

    case 122:
      drips();

      break;

    case 123:
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
      if (flop[6] && flop[7])
        adjustme();
      break;


    case 127:
      seasick3();
      break;

    case 128:

      magictime();
      adjustme();
      if (flop[2])confetti2();
      else
        confetti4();

      break;

    case 129:

      locusy = MATRIX_HEIGHT * 0.333;
      locusx = MIDLX;

      RaudioRoger();
      if (flop[1]) {
        locusy = MATRIX_HEIGHT;
        LaudioRoger();
      }
      rogerv();
      break;

    case 130:
      // beatflash(255);
      locusy = 0;
      locusx = 0;
      RaudioRoger();
      locusx = MATRIX_WIDTH ;
      LaudioRoger();
      locusy = MATRIX_HEIGHT + MIDLY / 4;
      locusx = MIDLX;
      RaudioRoger();
      rogerv();
      adjustme();
      break;

    case 131:
      seasick6();
      break;

    case 132:

      spiraly();
      adjustme();
      break;

    case 133:
      if (flop[5]) {
        drifty = MIDLY;
        driftx = MIDLX;
      }
      spiral2();// add a spiral
      if (flop[3])
        adjustme();
      break;

    case 134:
      if (flop[7] ) {
        drifty = MIDLY;
        driftx = MIDLX;
      }
      spiraly();// add a spiral
      if (flop[5])
        adjustme();
      break;
    case 135:

      spiral2();// add a spiral
      if (flop[4])
        adjustme();
      break;

    case 136://i love this
      drifty = MIDLY;
      driftx = MIDLX;
      if (flop[6])
        solid5();
      spire3();
      confetti2();
      twister();
      adjustme();
      break;

    case 137:
      if (flop[5])
        solid2(96);
      audio11();
      break;

    case 138:
      audio10();
      break;


    case 139:
      spiral3();
      if (flop[7])
        adjustme();
      break;

    case 140:
      //i love this
      drifty = MIDLY;
      driftx = MIDLX;
      spire5();
      confetti2();
      twister();
      adjustme();
      break;


    case 141:
      if (flop[2])
        snow(138);
      else
        snow(random8());

      break;

    case 142:
      if (flop[4])
        snow(blender);
      else
        snow(random8());
      adjustme();
      break;

    case 143:
      if (flop[3])
        solid5();
      BouncingBalls(dot + dot3);
      if (flop[6])
        adjustme();
      break;

    case 144:
      solid5();
      BouncingBalls(12);
      break;

    case 145:

      if (flop[4])
        Inca(128);
      bouncingmix(dot + dot2);
      break;

    case 146:
      dash();
      zeds.VerticalMirror();
      break;

    case 147:
      whitewarp();
      adjustme();
      EVERY_N_SECONDS(10 * dot) {
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
      fire2();
      break;

    case 151:
      tinybubbles3();
      break;

    case 152://i love this

      spire3();
      confetti2();
      twister();
      adjustme();
      break;

    case 153:

      if (flop[5] || flop[6]) {
        driftx = MIDLX ;
        drifty = MIDLY ;
      }
      Raudio9a9();
      Raudio5();

      adjustme();
      break;

    case 154:
      solid5();
      Raudio8a8();
      if (flop[4])
        adjustme();
      break;

    case 155://123
      if (flop[5] || flop[7]) {
        solid5();
        driftx = MIDLX;
        drifty = MIDLY;
      }

      else if (flop[6])
        solidblack();//black
      starbubbles88();
      break;

    case 156://123
      driftx = MIDLX;
      drifty = MIDLY;
      if (flop[5] || flop[3]) {
        solid5();
      }
      else
        solidblack();//black
      STARbubbles();
      break;

    case 157:
      audiofireball();
      // Raudio2();
      if (flop[4])
        adjustme();
      break;
    case 158:
      if (flop[5])
        solid5();
      tuber();
      adjustme();
      break;


    case 159:
      if (flop[5] || flop[8])
        solid5();

      audio12();

      break;


    case 160:

      seasick2();
      adjustme();

      break;


    case 161:

      seasick2();
      adjustme();
      break;


    case 162:
      if (flop[5])
        solid2(96);
      audio13();

      adjustme();
      break;
    case 163:
      art();
      break;

    case 164:
      art();
      break;

    case 165:
      circleaudio();
      adjustme();
      break;
    case 166:
      circleaudio2();
      adjustme();
      break;
    case 167:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 168:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 169:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 170:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 171:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 172:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 173:
      tinybubbles3();
      break;
    case 174:
      web();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 175:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 176:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 177:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 178:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();
      break;
    case 179:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 180:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 181:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 182:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 183:
      patternz->drawFrame();
      if (flop[5] && flop[9])
        adjustme();

      break;
    case 184:
      circleaudio3();
      adjustme();
      break;
    case 185:
      fire2();
      break;
    case 186:
      fire2();
      break;
    case 187:
      ghosts();
      break;
    case 188:
      ghosts();
      adjustme();
      break;


    default:
      if (flop[0] && flop[1] ) {
        confetti2();
        streaker();
      }
      else {
        spiral2();
      }
      break;
  }


#ifdef SHOW_PATTERN_NUM
  // Make dark overlay for the white font to be visible
  matrix->fillRect(0, 0, 4 * print_width, 7, 0);
  matrix->setCursor(1, 6);
  matrix->print(pattern);
#endif
#ifdef DISPLAY_FPS
  // Make dark overlay for the white font to be visible
  matrix->fillRect(MATRIX_WIDTH - 1 - 4 * 3, 0, 4 * 3 + 1, 7, 0);
  matrix->setCursor(MATRIX_WIDTH - 4 * 3, 6);
  matrix->print(matrix->fps());
#endif
}


void Diamondhole()//eff 0
{
  // ** Fill LED's with diagonal stripes

  dot = beatsin8(dot2, 1, 5, 0);
  cool = beatsin8(dot2, 2, 5, blender);

  for (int x = 0; x < (BIGGER * 2); x += dot)
  {
    DLine(x - BIGGER - 1, BIGGER - 1, x, 0, CHSV(h * 2 + x * cool, 255 - velo / 5, 255 - 2 * x));

  }

}

void Inca(int16_t brit)//eff 1
{
  // ** Fill LED's with horizontal stripes


  if (flop[4])
    dot = beatsin8(3, 1, 3, 0);
  else
    dot = beatsin8(8, 1, 3, 0);

  cool = beatsin8(dot2, 3, 6 , blender);

  for (int y = 0; y < BIGGER - 1; y += dot )
  {
    if (flop[1])
      DLine(0, y, BIGGER  - 1, y, CHSV(h  + y * cool , 255 - velo / 5, brit));
    else
      DLine(0, y, BIGGER  - 1, y, CHSV(y * dot + h,  222 + cool * 4 , brit));

  }

}

void Ringo()// eff 2
{
  if (flop[7] || flop[5] || flop[3])
    dot2 = beatsin8(4, 4, 8, 0);

  for (int x = 0; x < (BIGGER * 2); x ++)
    if (flop[2] || flop[7] || flop[8])
      DLine(x - BIGGER, BIGGER - 1, x, 0, CHSV( dot2 * x - h , 255 , 255));
    else
      DLine(x - BIGGER, BIGGER - 1, x, 0, CHSV(blender + dot2 * x,  255 , 255));
}


void tuber2()//
{
  if (flop[7] || flop[5] || flop[3])
    dot = beatsin8(dot2, 1, 7, 0);

  for (int x = 0; x < (BIGGER * 3 / 2 ); x += dot2 + 2)
    if (!flop[2])
      DCircle(driftx, drifty, (counter % (dot2 + 3)) + x, CHSV(h - x * dot , 255 -  velo / 4, 255));
    else
      DCircle(driftx, drifty, (counter % (dot2 + 3)) + x, CRGB::White);
}

void diagonally()// eff 3
{

  for (int y = 0; y <= BIGGER * 4 / 3  ; y ++)
    if ( !flop[8] )
      DCircle(driftx, drifty , MATRIX_HEIGHT * 4 / 3 + 3 - y, CHSV(h  + y * steper, 255 - velo / 5, 205 -  y));
    else
      DCircle(driftx, drifty , MATRIX_HEIGHT * 4 / 3 + 3 - y, CHSV(h  + y * steper, 255 -  y / 2, 225));

}


void Roundhole()// eff 4
{
  if (counter == 0) {
    radius3 = random(6, 13);
    shifty = shifty / 2;
  }
  if (flop[7] && (flop[6] || flop[3]))
    DFCircle(driftx + (radius3 * ((cos8( 2 * h ) - 128)) >> 7) , drifty + ((radius3 * (sin8( 2 * h) - 128)) >> 7), MATRIX_HEIGHT + 9, CHSV(blender - h * 2 , 255 , 130));
  for (int y = 0; y < BIGGER - 1 ; y += dot3)

    DCircle(driftx + (radius3 * ((cos8(4 * y + 2 * h ) - 128)) >> 7) , drifty + ((radius3 * (sin8(4 * y + 2 * h) - 128)) >> 7), MATRIX_HEIGHT - y, CHSV(blender + y * dot2 - h * 3 , 255 -  velo / 8, 255));
}

void drifter()//pattern=5
{
  if (counter == 0) {
    radius3 = random(6, 13);
    shifty = shifty / 2;
  }
  if (flop[7] && (flop[6] || flop[3]))
    DFCircle(driftx + (radius3 * ((cos8(- 3 * h ) - 128)) >> 7) , drifty + ((radius3 * (sin8(- 3 * h) - 128)) >> 7), MATRIX_HEIGHT + 9, CHSV(blender - h * 2 , 255 , 130));
  for (int y = 0; y < MATRIX_HEIGHT - 1 ; y += dot)

    DCircle(driftx + (radius3 * ((cos8(4 * y - 3 * h ) - 128)) >> 7) , drifty + ((radius3 * (sin8(4 * y - 3 * h) - 128)) >> 7), MATRIX_HEIGHT - y, CHSV(blender + y * dot2 - h * 3 , 255 -  velo / 5, 255));
}




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


void volcano(int16_t brit)//pattern=7
{

  for (int y = 0; y <  BIGGER; y++)
    DFCircle(driftx , drifty  ,  MATRIX_WIDTH + 2  - y, CHSV( 3 * h - y * 4, 255 - velo / 3, 255));
}

void pyrimid()//pattern=8
{


  dot = beatsin8(dot3 , 1, 4, 0);

  for (int y = 0; y < BIGGER; y += dot )
    DFCircle(driftx, drifty,  BIGGER + 2  - y, CHSV(2 * h  - y * 4, 255 - velo / 5, 255));

}

void solidpyrimid()//pattern=9
{

  for (int y = dot; y < BIGGER; y += dot3 )
    DRectangle(driftx - y,  drifty - y  , driftx  + y  , drifty + y , CHSV(-h + y * 7 , 255 - velo / 5, 255 ));
}

void solid2(int16_t brit)//solid colors rotate
{
  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(h, 255 - velo / 5, brit));
}


void solid3(int16_t brit)//solid random color
{
  if (counter == 0)
    rr = random8();
  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(rr + h, beatsin8(5, 160, 255, 0), brit));
}


void solidblack()//solid black
{

  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CRGB::Black);
}

void solid(int16_t brit)//colors rotate forward
{
  if (counter == 0)
    rr = random8();
  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(rr + beatsin8(15, 0, 96, 0), 255 - velo / 5, brit));
}

void solid5()//colors rotate forward
{
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_HEIGHT; j++)
      zeds(i, j) = CHSV(i * dot2 + dot / 2 * j +  h, 255, 132);
}
void solid6()//colors rotate forward
{
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_HEIGHT; j++)
      zeds(i, j) = CHSV(i * dot2 + dot / 2 * j +  h, 255, mmax(mmax(music.peakL, music.peakR) / 2, 128));
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



void audiofireball() {// with colored dots in pairs sometimes
  if (counter == 0)
  {
    for (int u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = random(1, 5);

      yslope[u] = (cos8(xblender) - 128.0) / 128.0;
      xslope[u] = (sin8(xblender) - 128.0) / 128.0;
      fvelo[u] = random8();
      if ( flop[0])
        fcolor[u] = blender + random(64);
      else
        fcolor[u] = random8();
    }
  }

  howmany =  BIGGER * music.raudio[dot3] / 32.0;
  for (int u = 0; u < howmany; u++) {
    zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
    xfire[u] = xfire[u] + xslope[u];
    yfire[u] = yfire[u] + yslope[u];
    fcount[u] = 0;
    if (yfire[u] < 0 || yfire[u] > MATRIX_HEIGHT - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      if ( flop[0])
        fcolor[u] = blender + random(64);
      else
        fcolor[u] = random8();

      xblender = random8();
      yslope[u] = (cos8(xblender) - 128.0) / 128.0;
      xslope[u] = (sin8(xblender) - 128.0) / 128.0;

    }

  }
  zeds(driftx, drifty) = CHSV(ccoolloorr - 96, 255 - velo / 5, 225);

  audioprocess();
  if (counter % 100 == 0 && bigmax > 0)bigmax--;
}


void tuber()//
{
  if (counter == 0)
  {
    for (int u = 0; u < BIGGER; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = u * dot3;//diameter
      fcolor[u] = u * 5;
    }
  }

  dot = beatsin8(3, 4, 7, 2);
  solidblack();//black
  for (int u = 0; u < BIGGER; u ++) {
    fpeed[u]++;
    if (fpeed[u] > MATRIX_WIDTH + dot3 - 1) {
      fpeed[u] = 8;
      xfire[u] = driftx;
      yfire[u] = drifty;
    }

    if (!flop[3])
      DCircle(xfire[u], yfire[u], fpeed[u],  CHSV(fcolor[u] + h  , 255 -  velo / 6, 255));
    else
      drawstar(xfire[u], yfire[u], fpeed[u], fpeed[u] / 3, dot, h, fcolor[u] + h);

  }
}

void fireball() {// with colored dots in pairs sometimes
  if (counter == 0)
  {
    howmany = random(BIGGER  ,  BIGGER * 2);
    how = howmany;
    for (int u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      fpeed[u] = random(1, 5);
      yslope[u] = (cos8(random8()) - 128.0) / 128.0;
      xslope[u] = (sin8(random8()) - 128.0) / 128.0;
      fvelo[u] = random8();
      if (flop[0])
        fcolor[u] = blender + random(69);
      else
        fcolor[u] = random8();
    }
  }
  if (flop[4] || flop[5])
    howmany = beatsin8(4, how / 8, how, 0);
  for (int u = 0; u < howmany; u++) {
    zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], 255 - fvelo[u] / 4, 255);
    xfire[u] = xfire[u] + xslope[u];
    yfire[u] = yfire[u] + yslope[u];
    //fcount[u] = 0;
    if (yfire[u] < 0 || yfire[u] > MATRIX_HEIGHT - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1) {
      xfire[u] = driftx;
      yfire[u] = drifty;
      if (flop[0])
        fcolor[u] = blender + random(64);
      else
        fcolor[u] = random8();

      xblender = random8();
      yslope[u] = (cos8(xblender) - 128.0) / 128.0;
      xslope[u] = (sin8(xblender) - 128.0) / 128.0;

    }

  }
  zeds(driftx, drifty) = CHSV(ccoolloorr - 96, 255 - velo / 5, 225);//the moving source
}


void fireworks() {// with colored dots in pairs sometimes
  if (counter == 0)
  {
    flop[3] = true;
    firedelay = random8() + 20;

    howmany =  random(BIGGER+8 , BIGGER * 2);

    for (int u = 0; u < howmany; u++) {
      xfire[u] = driftx;
      yfire[u] =   drifty;
      fpeed[u] = random(1, 5);
      blender = random8();
      yslope[u] = (cos8(blender) - 128.0) / 128.0;
      xslope[u] = (sin8(blender) - 128.0) / 128.0;
      fvelo[u] = random8();
      if ( flop[0])
        fcolor[u] = ccoolloorr + random(38);
      else
        fcolor[u] = random8();
    }
  }
  if (flop[3]) {
    for (int u = 0; u < howmany; u++) {
      zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
      zeds(xfire[u] + 1, yfire[u] - 1) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
      xfire[u] = xfire[u] + xslope[u];
      yfire[u] = yfire[u] + yslope[u];
      // fcount[u] = 0;
      if (yfire[u] < 0 || yfire[u] > MATRIX_HEIGHT - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1) {
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
    zeds(driftx, drifty) = CHSV(ccoolloorr - 96, 255 - velo / 5, 255);//the lpne target
  }
  if (counter >= firedelay) {
    firedelay = counter + random8() + 20;
    flop[3] = ! flop[3];
  }
}



void streaker() {
  if (counter == 0)
  {


    howmany =  BIGGER * 3 / 2;
    how = howmany;
    for (int u = 0; u < howmany; u++) {
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
  if (flop[4] || flop[6])
    howmany = beatsin8(4, how / 5, how / 2, 0);
  for (int u = 0; u < howmany; u++)
  {
    zeds(xfire[u], yfire[u]) = CHSV(fcolor[u], fvelo[u] / 4 + 192, 255);
    xfire[u] = xfire[u] + xslope[u] * fpeed[u];
    yfire[u] = yfire[u] + yslope[u] * fpeed[u];
    fcount[u] = 0;

    if (yfire[u] < 0 || yfire[u] >  MATRIX_HEIGHT - 1 || xfire[u] < 0 || xfire[u] >  MATRIX_WIDTH - 1)
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
    if (counter - ringdelay <= BIGGER)
    {
      if (flop[0] || flop[1])
        DCircle(driftx, drifty , counter - ringdelay, CHSV( h + 85, 255 - velo / 5, 255));
      else
        DCircle(driftx, drifty , counter - ringdelay, CRGB::White);
    }
    else
      ringdelay = counter + random(targetfps * 5, targetfps * 10);
  }
}

void bkringer() {
  if (counter >= bringdelay)
  {
    if (counter - bringdelay <= BIGGER + 13)
    {
      DCircle(driftx, drifty , (BIGGER + 12 - counter + bringdelay), CHSV(h + 60, 255 - velo / 5, 255));
      DCircle(driftx, drifty, (BIGGER + 8 - counter + bringdelay), CHSV(h + 70 , 255 - velo / 5, 255));
      DCircle(driftx, drifty , (BIGGER + 4 - counter + bringdelay), CHSV(h + 80 , 255 - velo / 5, 255));
      DCircle(driftx, drifty , (BIGGER  - counter + bringdelay), CHSV(h + 90 , 255 - velo / 5, 255));
    }
    else {
      bringdelay = counter + random(targetfps * 4, targetfps * 15);

    }
  }
}

void sinx() {
  if (counter == 0) {
    radius2 = random((BIGGER >> 2) + 4, (BIGGER >> 1) + 8) + 8;
    radius3 = random (BIGGER >> 3, BIGGER >> 2) + 4;
  }
  if (flop[7] || flop[5] )
    dot = beatsin8(6, 3, 12, 128);
  else
    dot = 5;

  for (int j = radius2 >> 1; j < radius2 + 4; j += dot) {

    DCircle(driftx + ((radius3 * (cos8(h  ) - 128)) >> 7), drifty + ((radius3 * (sin8(h ) - 128)) >> 7), j, CHSV(h + dot2 * j , velo / 8 + 223, 255));
    DCircle(driftx + (radius3 * ((cos8(h  + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h  + 128) - 128)) >> 7), j, CHSV(h + dot2 * j + 128 , velo / 8 + 223, 255));
    if (flop[2]) {
      DCircle(driftx + ((radius3 * (cos8(h * 2) - 128)) >> 7), drifty + ((radius3 * (sin8(h * 2) - 128)) >> 7), j * 3 / 2, CHSV(h + dot2 * j + 128 , velo / 8 + 223, 255));
      DCircle(driftx + (radius3 * ((cos8(h * 2 + 128) - 128)) >> 7) , drifty + ((radius3 * (sin8(h * 2 + 128) - 128)) >> 7), j * 3 / 2, CHSV(h + dot2 * j , velo / 8 + 223, 255));
    }
    if (!flop[1]) {
      DCircle(driftx + ((3 * radius3 * (cos8(-h * 2) - 128)) >> 7), drifty + ((3 * radius3 * (sin8(-h * 2) - 128)) >> 7), j * 2  , CHSV(h + dot2 * j + 128 , velo / 8 + 223, 255));
      DCircle(driftx + ((3 * radius3 * (cos8(-h * 2 + 128) - 128)) >> 7), drifty + ((3 * radius3 * (sin8(-h * 2 + 128) - 128)) >> 7), j * 2  , CHSV(h  + dot2 * j, velo / 8 + 222, 255));
    }
  }
}

void drip() {
  if (counter == 0)
  {
    // DFRectangle(0, 0, MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(h * 2,velo+196, 100));

    if (flop[1])
      ccoolloorr = 40;
    for (howmany = 0; howmany < MATRIX_WIDTH; howmany++)
    {
      xslope[howmany] = ccoolloorr + random(70);//color
    }

  }
  for (xx = 0; xx < MATRIX_WIDTH; xx++)
  {
    if (random8() < 40)
      for (yy = 0; yy < MATRIX_HEIGHT - 1; yy++)
      {
        zeds(xx, yy) = zeds (xx, yy + 1);
      }

    if (random8() > 178) {
      xslope[xx] = xslope[xx] + 1;
      zeds(xx, MATRIX_HEIGHT - 1) =  CHSV(xslope[xx], 255 - velo / 7 , 255);
    } else
      zeds(xx, MATRIX_HEIGHT - 1) = CRGB::Black;

  }
}

void mirror() {
  for (xx = 0; xx < MATRIX_WIDTH; xx++)
    for (yy = 0; yy < MIDLY; yy++)
      zeds(xx, yy) = zeds(xx, MATRIX_HEIGHT - yy - 1);

}

void roger()
{


  if (flop[4] && flop[5]) {
    DFRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h  + 128, 255 - velo / 5, 100));
    DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) , CHSV(h , 255 - velo / 5, 255));

    DLine(MIDLX, MATRIX_HEIGHT - 2, 0, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 1, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 4, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 5, 2, CRGB::Black);
    DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(h , 235, 135));
    zeds.HorizontalMirror();
  }
  if (flop[4] && !flop[5]) {
    DFRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h  + 128, 255 - velo / 5, 190));
    DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) , CHSV(h , 255 - velo / 5, 255));

    DLine(MIDLX, MATRIX_HEIGHT - 2, 0, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 1, 2, CRGB::Black);

    DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CRGB::Black);
    if ((counter / 16) % 2 == 0) {
      DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(h , 255 - velo / 5, counter % 32 * 8));
      DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h + 30 , 255 - velo / 5, counter % 32 * 8));
    }
    else {
      DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(h , 255 - velo / 5, 2565 - (counter % 32) * 8));
      DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h + 30 , 255 - velo / 5, 255 - (counter % 32) * 8));
    }
    DLine(MIDLX, MATRIX_HEIGHT - 2, 4, 2, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 5, 2, CRGB::Black);
    DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CRGB::Black);
    zeds.HorizontalMirror();
  }
  if (!flop[4] && flop[5]) {

    DFRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CHSV(h + 84 , 255 - velo / 5, 190));


    DCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(h  - 45, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 0, 5, CHSV(h  + 30, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 1, 4, CHSV(h  + 15, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 3, CHSV(h  , 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 2, CHSV(h  - 15, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 4, 1, CHSV(h  - 30, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 5, 0, CHSV(h  - 45, 255 - velo / 5, 255));
    DCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CRGB::Black);
    zeds.HorizontalMirror();
  }
  if (!flop[4] && !flop[5])
  {
    // DFRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);
    DLine(MIDLX, MATRIX_HEIGHT - 2, 0, 0, CHSV(ccoolloorr  + 45, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 1, 1, CHSV(ccoolloorr  + 22, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 2, CHSV(ccoolloorr  , 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 3, CHSV(ccoolloorr  - 15, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 4, 4, CHSV(ccoolloorr  - 30, 255 - velo / 5, 255));
    DLine(MIDLX, MATRIX_HEIGHT - 2, 5, 5, CHSV(ccoolloorr  - 45, 255 - velo / 5, 255));
    if ((counter / 200) % 2 == 0) {
      DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(ccoolloorr - 45, 255 - velo / 5, 55 + counter % 200));
      DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(ccoolloorr + 45 , 255 - velo / 5, 255 - counter % 200));
    }
    else {
      DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CHSV(ccoolloorr - 45, 255 - velo / 5, 255 - counter % 200));
      DFCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CHSV(ccoolloorr + 45, 255 - velo / 5, 55 + counter % 200));
    }
    zeds.HorizontalMirror();
  }
}

void rogerv() {
  DLine(MIDLX, MATRIX_HEIGHT - 2, 0, 0, CHSV(h  + 20, 255 - velo / 5, 255));
  DLine(MIDLX, MATRIX_HEIGHT - 2, 1, 0, CHSV(h  + 10, 255 - velo / 5, 255));
  DLine(MIDLX, MATRIX_HEIGHT - 2, 2, 0, CHSV(h  , 255 - velo / 5, 255));
  DLine(MIDLX, MATRIX_HEIGHT - 2, 3, 0, CHSV(h  - 10, 255 - velo / 5, 255));
  DLine(MIDLX, MATRIX_HEIGHT - 2, 4, 0, CHSV(h  - 20, 255 - velo / 5, 255));
  DLine(MIDLX, MATRIX_HEIGHT - 2, 5, 0, CHSV(h  - 30, 255 - velo / 5, 255));
  DCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2), CRGB::White);
  // DCircle(MIDLX, MIDLY * .6666, (MIDLY >> 2) - 1, CRGB::White);
  zeds.HorizontalMirror();

}

void confetti() {
  if (random8() < 224)
    ADCircle(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), random(1, 7), CHSV(random8(), 255 - velo / 5, 255));
  else
    ADFCircle(random(MATRIX_WIDTH), random(MATRIX_HEIGHT), random(1, 7), CHSV(h + 128 , 255 - velo / 7, 255));
}

void confetti3() {
  if (counter == 0)
    if (flop[1] || flop[2]) blender = 164;
  if (random8() < blender) {
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(random8(), 255 - velo / 5, 255);
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(random8(), 255 - velo / 5, 255);
  }

  else
  {
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
  }
}

void confetti4() {
  if (!flop[2]) {
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(blender + random(64), 255 - velo / 5, 190 + (random(64)));
    if (counter % 27 == 0)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
  }
  else
  {
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) = CRGB::White;
    if (counter % 27 == 0)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(blender + random(64), 255 - velo / 5, 190 + (random(64)));
  }
  int holder = beatsin16(4, 6, MATRIX_WIDTH);
  drawstar(driftx, drifty, holder, holder / (dot3 + 1), dot3 + 2, h,  h); // random multipoint star
}

void confetti2() {
  if (random8() > blender)
    for (int16_t hijk = 0; hijk < 2 * dot + 2; hijk++)
      zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(h + random(32), 255 - velo / 5, 255);
  else {
    int16_t sizeit = random(2, 9);
    int16_t wider =  random(MATRIX_WIDTH);
    int16_t heighter = random(MATRIX_HEIGHT);
    if (random8() > 128) {
      DCircle(wider, heighter, sizeit, CHSV(h, 235, 255));
      DCircle(wider, heighter, sizeit + 1, CHSV(h   , 200 , 255));
      DCircle(wider, heighter, sizeit + 2, CHSV(h   , 170 , 255));
    }
    else
    {
      DCircle(wider, heighter, sizeit, CHSV(h   , 235, 255));
      DCircle(wider, heighter, sizeit + 1, CHSV(h + 16   , 235 , 255));
      DCircle(wider, heighter, sizeit + 2, CHSV(h + 32   , 235, 255));

    }
    zeds(random(MATRIX_WIDTH), random(MATRIX_HEIGHT)) += CHSV(h + random(32), 255 - velo / 5, 255);
  }
}



void bubbles() {
  if (counter == 0)
  {


    howmany = random ((BIGGER /4) , BIGGER / 2 ) - 8;
    for (int u = 0; u < howmany; u++) {
      xfire[u] = random(MATRIX_WIDTH);
      yfire[u]  = random(MATRIX_HEIGHT);
      fvelo[u] = random8(32);
      if (flop[2] || flop[5])
        fcolor[u] = random8(); //color
      else
        fcolor[u] = 110 + random(99);
      fpeed[u] = random(1, 8); //speed

      fcount[u] = random(3, (MIDLX >> 1) - 4); //radius
      if (random8() > 128)
        rimmer[u] = true;
      else
        rimmer[u] = false;
    }
  }

  for (int u = 0; u < howmany; u++)
  {
    ADFCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CHSV(fcolor[u], 255 - fvelo[u] , 205));
    if (u % 7 ==  0)
      DFCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CRGB::Black);

    if (rimmer[u])
      ADCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CHSV(fcolor[u] + 85 , 255 - fvelo[u] , 255));
    else
      ADCircle(xfire[u],  yfire[u] - fcount[u] / 2, fcount[u], CRGB::White);

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
    howmany = random ((BIGGER >> 2) - 4, BIGGER / 2 - 8);

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 2, MIDLX * 3 / 2 );
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

  for (int u = 0; u < howmany; u++) {
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

    if (flop[3])
      ADFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + h , fvelo[u] / 4 + 192, 255));

    if (u % 2 == 0)DFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + h , fvelo[u] / 4 + 192, 255));
    if (rimmer[u])
      DCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + h + 128, fvelo[u] / 4 + 192, 255));
    else
      DCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void tinybubbles() {
  if (counter == 0)
  {
    howmany = BIGGER * 1.5;

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 2, MIDLX * 3 / 2 );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(3,  10); //radius
      fpeed[u] = random(1, 4); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 128) {
        rimmer[u] = true;
        xbouncer[u] = false;
      }
      else {
        rimmer[u] = false;
        xbouncer[u] = true;
      }
      if (random8() < 128) {

        ybouncer[u] = false;

      }
      else {

        ybouncer[u] = true;
      }
    }
  }

  for (int u = 0; u < howmany; u++) {
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


    if (flop[6] && flop[7]) {
      DFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u]  , fvelo[u] / 4 + 192, 255));
      if (flop[7] || flop[8])
        if (u % (4 + dot2) == 0)
          drawstar(xfire[u], yfire[u], fcount[u], fcount[u] / 3, 7, h, fcolor[u] + 128);
      if (rimmer[u])
        DCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u]  + 128, fvelo[u] / 4 + 192, 255));
      else
        DCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
    }
    else
    {
      DFRectangle(xfire[u],  yfire[u] , xfire[u] + fcount[u] + dot, yfire[u] + fcount[u] + dot, CHSV(fcolor[u]  , fvelo[u] / 4 + 192, 255));
      if (flop[7] || flop[8]) {

        if (rimmer[u])
          DRectangle(xfire[u],  yfire[u] , xfire[u] + fcount[u] + dot, yfire[u] + fcount[u] + dot, CHSV(fcolor[u] +  128, fvelo[u] / 4 + 128, 255));
        else
          DRectangle(xfire[u],  yfire[u] , xfire[u] + fcount[u] + dot, yfire[u] + fcount[u] + dot, CRGB::White);
      }
    }
  }
}

void STARbubbles() {//square

  if (counter == 0)
  {
    howmany = BIGGER / 2 - 16;

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 3, MIDLX * 5 / 3 );
      yfire[u]  = random(MIDLY / 3, MIDLY * 5 / 3);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(MIDLX / 4,  MIDLX / 2 ); //radius
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

  for (int u = 0; u < howmany; u++) {
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

    //DFCircle(xfire[u], yfire[u], fcount[u] - 1, CRGB(fcolor[u], 255 - velo / 5, 255));
    for (int j = 0; j < fcount[u]; j++)
      drawstar(xfire[u], yfire[u], j * 1.4142, j, 4 , h * 2 + fvelo[u], fcolor[u]);


  }
}

void starbubbles88() {

  if (counter == 0)
  {
    howmany = random(BIGGER / 8, BIGGER / 4);

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 2, MIDLX * 3 / 2 );
      yfire[u]  = random(MIDLY / 2, MIDLY * 3 / 2);
      fcolor[u] = random8(); //color
      fvelo[u] = random8();
      fcount[u] = random(7,  2 + MIDLX / 2); //radius size
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

  for (int u = 0; u < howmany; u++) {
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

    // DFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    for (int j = 0; j < fcount[u]; j++)
      if (flop[9] && flop[8])
        drawstar(xfire[u], yfire[u], j, j / 3, 3 + (u % 5), h * 2 + fvelo[u], fcolor[u] + 6 * j + h);
      else
        drawstar(xfire[u], yfire[u], j, j / 3, 3 + (u % 5), h * 2 + fvelo[u], fcolor[u] + 6 * j);

  }
}

void tinybubbles2() {
  if (counter == 0)
  {
    howmany = BIGGER * 2 / 3;

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 2, MIDLX * 3 / 2 );
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

  for (int u = 0; u < howmany; u++) {
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
      for (int j = 0; j < fcount[u]; j++)
        drawstar(xfire[u], yfire[u], j, j / 3, 4 + (u % 4), h, fcolor[u]);
    else
      DFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));


    if (rimmer[u])
      DCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      DCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void web() {
  if (counter == 0)
  {
    howmany = BIGGER  / 3;
    dot = random(6, 12);
    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 4, MATRIX_WIDTH - MIDLX / 4 );
      yfire[u]  = random(MIDLY / 4, MATRIX_HEIGHT - MIDLY / 4);
      fcolor[u] = poffset + random8(8) * 32; //color
      fvelo[u] = random8();

      fpeed[u] = random(1, 5); //speed
      xslope[u] = random(13, 52) + random(4) * 64; //angle avoiding square
      if (random8() > 128) {
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
  if (flop[5])
    howmany = beatsin8(2, 4, dot, 0);
  else
    howmany = beatsin8(4, 4, 6, 0);


  for (int u = 0; u < howmany; u++) {
    if (xbouncer[u])
      xfire[u] = xfire[u] + fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;
    else
      xfire[u] = xfire[u] - fpeed[u] * (sin8(xslope[u]) - 128.0) / 128.0;

    if (ybouncer[u])
      yfire[u] = yfire[u] + fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;
    else
      yfire[u] = yfire[u] - fpeed[u] * (cos8(xslope[u]) - 128.0) / 128.0;

    if (xfire[u] > MATRIX_WIDTH   || xfire[u] < 0 )
      xbouncer[u] = !xbouncer[u];

    if (yfire[u] > MATRIX_HEIGHT  || yfire[u] < 0 )
      ybouncer[u] = !ybouncer[u];
  }
  for (int u = 0; u < howmany; u++)
    for (int q = u; q < howmany; q++)
      DLine(xfire[u],  yfire[u] , xfire[q],  yfire[q], CHSV(fcolor[u] + h, 255 - fvelo[u] / 6 , 255));

}


void tinybubbles3() {
  if (counter == 0)
  {
    howmany = BIGGER * 2 / 3;

    for (int u = 0; u < howmany; u ++) {
      xfire[u] = random(MIDLX / 2, MIDLX * 3 / 2 );
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

  howmany = beatsin16(2, 1, -1 + BIGGER * 2 / 3, 0);

  for (int u = 0; u < howmany; u++) {
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

    DFCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h, fvelo[u] / 4 + 192, 255));
    if (rimmer[u])
      DCircle(xfire[u],  yfire[u] , fcount[u], CHSV(fcolor[u] + 2 * h + 128, fvelo[u] / 4 + 192, 255));
    else
      DCircle(xfire[u],  yfire[u], fcount[u], CRGB::White);
  }
}

void sticks() {

  ccoolloorr = random8();
  if (random8() > 22)
  { DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 5, 255));
    DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 5, 255));
    DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CHSV(ccoolloorr, 255 - velo / 5, 255));
  }
  else
  { DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
    DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
    DLine(driftx, drifty, random(MATRIX_WIDTH), random(MATRIX_HEIGHT), CRGB::White);
  }
}

void Bargraph() {
  if (counter == 0)
    for (int hhh = 0; hhh < MATRIX_WIDTH ; hhh++) {
      fcolor[hhh] = random(MIDLY / 2, MATRIX_HEIGHT - MIDLY / 2 - 1);
      if (pattern == 22 || pattern == 27)
        fcolor[hhh] = random(MIDLY >> 2, MIDLY - 1);
      fpeed[hhh] = random(4, 9);
      fcount[hhh] = 0;
      poffset = random8();
    }


  for (int hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
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

    DLine(hhh, 0, hhh, fcolor[hhh], CHSV(h + poffset + hhh * steper, 255 - velo / 5, 255));

  }
}

void adjustme() {  // applies the screen wide effect
  switch (adjunct) {
    case 0://no effect
      break;
    case 1://no effect
      break;
    case 2:
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
    case 13:
      mirror();
      break;

    default:// no effect
      break;
  }
}

void spire2() {

  if (counter == 0)
  {
    radius =  BIGGER / 2 ;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot + 5 + random(5);
  }

  if (h % 24 == 0)
  {
    if (radius < 4)
      flop[0] = 1 - flop[0];
    if (radius > BIGGER * 2 / 3)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;

    if (radius2 < 4)
      flop[1] = 1 - flop[1];
    if (radius2 > BIGGER * 2 / 3)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }

  float xer = driftx + radius * (cos8(h * 2) - 128.0) / 128.0;
  float yer = drifty + radius * (sin8(h * 2) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h , 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h + 128, 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx + radius * (cos8(h * 2 + 85) - 128.0) / 128.0;
  yer = drifty + radius * (sin8( h * 2 + 85) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h + 85, 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2 + 85) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2 + 85) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h + 128 + 85, 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);

  xer = driftx + radius * (cos8(h * 2 + 174) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(h * 2 + 174) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h + 174, 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);
  xer = driftx - radius2 * (cos8( h * 2 + 174) - 128.0) / 128.0;
  yer = drifty - radius2 * (sin8( h * 2 + 174) - 128.0) / 128.0;
  DFCircle(xer, yer, dot, CHSV(h + 128 + 174, 255 - velo / 5, 255));
  if (flop[2])  DCircle(xer, yer, dot + 1, CRGB::White);
}

void spire3() {

  if (counter == 0)
  {
    radius =  BIGGER / 2 + 7;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot  + random(2, 6);
    howmany = random (4, 8);
  }


  if (h % 16 == 0)
  {

    if (radius < 4)
      flop[0] = 1 - flop[0];
    if (radius > 8 + BIGGER / 2)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;


    if (radius2 < 4)
      flop[1] = 1 - flop[1];
    if (radius2 > 8 + BIGGER / 2)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }
  for (int i = 0; i < howmany; i++) {
    float xer = driftx + radius * (cos8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    float yer = drifty + radius * (sin8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      DCircle(xer, yer, dot + 1, CHSV(h + i * 256 / howmany, 255 - velo / 5, 255));
    else {
      DFCircle(xer, yer, dot, CHSV(h + i * 256 / howmany, 255 - velo / 5, 205));
      DCircle(xer, yer, dot, CHSV(85 + h + i * 256 / howmany, 255 - velo / 5, 255));
    }
    xer = driftx - radius2 * (cos8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    yer = drifty - radius2 * (sin8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      DCircle(xer, yer, dot + 1, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 5, 255));
    else {
      DFCircle(xer, yer, dot, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 5, 205));

      DCircle(xer, yer, dot, CHSV(85 + h + 32 + i * 256 / howmany, 255 - velo / 5, 255));
    }
  }
}


void spire5() {

  if (counter == 0)
  {
    radius =  BIGGER / 2 + 7;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot  + random(2, 6);
    howmany = random (4, 8);
  }


  if (h % 16 == 0)
  {

    if (radius < 4)
      flop[0] = 1 - flop[0];
    if (radius > 9 + BIGGER / 2)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;


    if (radius2 < 4)
      flop[1] = 1 - flop[1];
    if (radius2 > 8 + BIGGER / 2)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }
  for (int i = 0; i < howmany; i++) {
    float xer = driftx + radius * (cos8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    float yer = drifty + radius * (sin8(2 * h + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      DCircle(xer, yer, dot + 1, CHSV(h + i * 256 / howmany, 255 - velo / 5, 255));
    else {
      ADFCircle(xer, yer, dot, CHSV(h + i * 256 / howmany, 255 - velo / 5, 205));
      DCircle(xer, yer, dot, CHSV(85 + h + i * 256 / howmany, 255 - velo / 5, 255));
    }
    xer = driftx - radius2 * (cos8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    yer = drifty - radius2 * (sin8(2 * h + 128 / howmany + i * 256 / howmany) - 128.0) / 128.0;
    if (!flop[2])
      DCircle(xer, yer, dot + 1, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 5, 255));
    else {
      ADFCircle(xer, yer, dot, CHSV(h + 32 + i * 256 / howmany, 255 - velo / 5, 205));

      DCircle(xer, yer, dot, CHSV(85 + h + 32 + i * 256 / howmany, 255 - velo / 5, 255));
    }
  }
}
void spire() {

  if (counter == 0)
  {
    radius =  BIGGER / 2 ;
    flop[0] = true;
    radius2 =  5;
    flop[1] = false;
    dot = dot + 3 + random(5);
  }

  if (h % 16 == 0)
  {
    if (radius < 2)
      flop[0] = 1 - flop[0];
    if (radius > BIGGER * 2 / 3)
      flop[0] = 1 - flop[0];
    if ( flop[0])
      radius --;
    else
      radius++;

    if (radius2 < 2)
      flop[1] = 1 - flop[1];
    if (radius2 > BIGGER * 2 / 3)
      flop[1] = 1 - flop[1];
    if (flop[1])
      radius2 --;
    else
      radius2++;
  }

  float xer = driftx + radius * (cos8(2 * h) - 128.0) / 128.0;
  float yer = drifty + radius * (sin8(2 * h) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h, 255 - velo / 5, 255));
  xer = driftx - radius * (cos8(2 * h) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h + 128, 255 - velo / 5, 255));

  xer = driftx + radius * (cos8(2 * h + 84) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(2 * h + 84) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h + 84, 255 - velo / 5, 255));
  xer = driftx - radius * (cos8(2 * h + 84) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h + 84) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h - 84, 255 - velo / 5, 255));

  xer = driftx + radius * (cos8(2 * h + 42) - 128.0) / 128.0;
  yer = drifty + radius * (sin8(2 * h + 42) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h + 42, 255 - velo / 5, 255));
  xer = driftx - radius * (cos8(2 * h + 42) - 128.0) / 128.0;
  yer = drifty - radius * (sin8(2 * h + 42) - 128.0) / 128.0;
  DCircle(xer, yer, dot, CHSV(h - 42, 255 - velo / 5, 255));
}

void triple() {
  if (counter == 0) {
    radius2 = random(BIGGER / 5 , BIGGER / 2) - 3;
  }
  dot2 = beatsin8(6, 4, 10, 0);
  radius3 = beatsin8(5, radius2 / 2 , radius2 * 3 / 2, 0);
  for (int i = radius2 ; i > 1 ; i--) {
    DFCircle(driftx + ((radius3 * (cos8(h * dot) - 128)) >> 7), drifty + ((radius3 * (sin8(h * dot) - 128)) >> 7), i, CHSV( h + dot3 * i, 255 - velo / 5, 255));
    DFCircle(driftx + ((radius3 * (cos8(h * dot + 85) - 128) ) >> 7), drifty + ((radius3 * (sin8(h * dot + 85 ) - 128) ) >> 7), i, CHSV(h + dot3 * i + 85 , 255 - velo / 5, 255));
    DFCircle(driftx + (( radius3 * (cos8(h * dot - 85) - 128)) >> 7), drifty + ((radius3 * (sin8(h * dot - 85 ) - 128) ) >> 7), i, CHSV(h + dot3 * i - 85  , 255 - velo / 5, 255));
    if (!flop[2]) {
      DFCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot + 42) - 128)) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot + 42) - 128)) >> 7), i * 2 / 3, CHSV(h + dot3 * i + 128 , 255 - velo / 5, 255));
      DFCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot + 85 + 42) - 128) ) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot + 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot3 * i + 128 + 85  , 255 - velo / 5, 255));
      DFCircle(driftx + ((dot / 2 * radius3 * (cos8(h * dot - 85 + 42) - 128)) >> 7), drifty + ((dot / 2 * radius3 * (sin8(h * dot - 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot3 * i + 128 - 85   , 255 - velo / 5, 255));
    }
    else
    {
      DFCircle(driftx + ((dot  * radius3 * (cos8(h * dot + 42) - 128)) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot + 42) - 128)) >> 7), i * 2 / 3, CHSV(h + dot2 * i + 128 , 255 - velo / 5, 255));
      DFCircle(driftx + ((dot  * radius3 * (cos8(h * dot + 85 + 42) - 128) ) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot + 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot3 * i + 128 + 85  , 255 - velo / 5, 255));
      DFCircle(driftx + ((dot  * radius3 * (cos8(h * dot - 85 + 42) - 128)) >> 7), drifty + ((dot  * radius3 * (sin8(h * dot - 85 + 42) - 128) ) >> 7), i * 2 / 3, CHSV(h + dot3 * i + 128 - 85   , 255 - velo / 5, 255));
    }
  }
}

void ghosts() {

  if (flop[3]) {
    driftx = MIDLX;
    drifty = MIDLY;
  }
  if (counter == 0) {
    radius2 = random(BIGGER * .2, BIGGER * .6);
    radius3 = random(radius2  , radius2 * 3 / 2 );
  }
  dot2 = 3;
  radius3 = beatsin8(6, radius2 * 2 / 3 , radius2 * 2, 0 );
  for (int i = 0 ; i < 6 ; i++) {
    float mcentrx = driftx + ((radius3 * (cos8(h * 3 + i * 42) - 128)) >> 7);
    float mcentry =  drifty + ((radius3 * (sin8(h * 3 + i * 42) - 128)) >> 7);
    float scentrx = driftx + ((radius3 * (cos8(-h  + i * 42) - 128)) >> 7);
    float scentry =  drifty + ((radius3 * (sin8(-h  + i * 42) - 128)) >> 7);
    for (int xxxx = 0; xxxx < MATRIX_WIDTH; xxxx++)
      for (int yyyy = 0; yyyy < MATRIX_HEIGHT; yyyy++)
        if (((xxxx - mcentrx) * (xxxx - mcentrx) + (yyyy - mcentry) * (yyyy - mcentry) < radius2 * radius2) && ((xxxx - scentrx) * (xxxx - scentrx) + (yyyy - scentry) * (yyyy - scentry) > radius2 * radius2))
          zeds(xxxx, yyyy) +=  CHSV(i * 43 + h  , 255 - velo / 8, 185);

  }
}




void siny() {

  if (counter == 0) {
    radius2 = random(BIGGER >> 2, (BIGGER >> 1) - 4);
    radius3 = random (4, BIGGER/4 - 4 );
    ringdelay = ringdelay * random(2, 5);
  }
  if (flop[1]) {
    DCircle(MIDLX + ((radius3 * (cos8(-h * 3) - 128)) >> 7), MIDLY + ((radius3 * (sin8(-h * 3) - 128)) >> 7), radius2 + 1, CHSV(h * 2 , 255 - velo / 5, 255));
    DCircle(MIDLX + ((radius3 * (cos8(-h * 3 + 128) - 128)) >> 7), MIDLY + ((radius3 * (sin8(-h * 3 + 128) - 128)) >> 7), radius2 - 1, CHSV(h * 2 + 128 , 255 - velo / 5, 255));
  }
  else {
    DCircle(MIDLX + ((radius3 * (cos8(h * 3) - 128)) >> 7), MIDLY + ((radius3 * (sin8(h * 3) - 128)) >> 7), radius2 + 1, CHSV(h * 2 , 255 - velo / 5, 255));
    DCircle(MIDLX + ((radius3 * (cos8(h * 3 + 128) - 128)) >> 7), MIDLY + ((radius3 * (sin8(h * 3 + 128) - 128)) >> 7), radius2 - 1, CHSV(h * 2 + 128 , 255 - velo / 5, 255));
  }
}
void whitewarp() {
  if (counter == 0 )
  {
    howmany = random (BIGGER / 2 + 8 , BIGGER + 8 );

    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random8(90);
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
      zeds(xfire[i], yfire[i]) = CHSV(fcolor[i] , fvelo[i] / 4 + 192, 255); //one shade of color
    else
      zeds(xfire[i], yfire[i]) = CRGB::White;

    if (xfire[i] < 0 || yfire[i] < 0 || xfire[i] > MATRIX_WIDTH || yfire[i] > MATRIX_HEIGHT) {
      xfire[i] = driftx;
      yfire[i] = drifty;
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random8(99);
      fvelo[i] = random8();
      fpeed[i] = random8(2, 12);
    }
  }

  for (int i = 1; i < howmany / 2; i++)
    if (flop[6]) {
      zeds(xfire[howmany - i] - 1, yfire[howmany - i] - 1) = CHSV(fcolor[howmany - i] , 255, 255); //many color
      // zeds(xfire[howmany - i] - 2, yfire[howmany - i] - 2) = CHSV(fcolor[howmany - i] , 255, 255); //many color
    }
    else {
      zeds(xfire[howmany - i] - 1, yfire[howmany - i] - 1) = CRGB::White;
      //  zeds(xfire[howmany - i] - 2, yfire[howmany - i] - 2) = CRGB::White;
    }

  if (flop[6]) { //contrast
    zeds(xfire[howmany - 1] , yfire[howmany - 1] ) = CRGB::White;
    zeds(xfire[howmany - 1] - 1 , yfire[howmany - 1] + 1 ) = CRGB::White;
  }
  else {
    zeds(xfire[howmany - 1] , yfire[howmany - 1 ] ) = CHSV(fcolor[howmany - 1] , fvelo[howmany ] / 255, 255); //many color
    zeds(xfire[howmany - 1] + 1 , yfire[howmany - 1] - 1 ) = CHSV(fcolor[howmany - 1] , fvelo[howmany ] / 255, 255); //many color
  }
}

void warp() {
  if (counter == 0 )
  {
    howmany = random (BIGGER * 2 / 3, BIGGER * 3 / 2);

    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random(75);//color
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
    if (flop[0])
      zeds(xfire[i], yfire[i]) += CHSV(fcolor[i], fvelo[i] / 2 + 128, 255); //selected colors
    else {
      if (flop[1])
        zeds(xfire[i], yfire[i]) += CRGB::White;
      else
        zeds(xfire[i], yfire[i]) += CHSV(blender , fvelo[i] / 2 + 128, 255); //one shade of color
    }
    if (xfire[i] < 0 || yfire[i] < 0 || xfire[i] > MATRIX_WIDTH || yfire[i] > MATRIX_HEIGHT) {
      xfire[i] = driftx;
      yfire[i] = drifty;
      fcount[i] = random8(); //angle
      fcolor[i] = random8();;
      fpeed[i] = random8(2, 8);
    }
  }
  if (flop[0]) {
    zeds(xfire[howmany - 1], yfire[howmany - 1]) = CHSV(fcolor[howmany - 1] + 128  , fvelo[howmany - 1] / 2 + 128, 255);
    zeds(xfire[howmany - 3], yfire[howmany - 3]) = CHSV(fcolor[howmany - 3] + 128 , fvelo[howmany - 4] / 2 + 128, 255);
    zeds(driftx, drifty) = CRGB::White;
  }
  else {
    if (!flop[1])
    {
      zeds(xfire[howmany - 1], yfire[howmany - 1]) = CHSV(fcolor[howmany - 1] + 128  , fvelo[howmany - 1] / 2 + 128, 255);
      zeds(xfire[howmany - 4], yfire[howmany - 4]) = CHSV(fcolor[howmany - 4] + 128 , fvelo[howmany - 4] / 2 + 128, 255);
      zeds(driftx, drifty) = CHSV(xblender   , fvelo[howmany - 4] / 2 + 128, 255);
    }
    else
    {
      zeds(xfire[howmany - 1], yfire[howmany - 1]) = CHSV(blender + 128  , fvelo[howmany - 1] / 2 + 128, 255);
      zeds(xfire[howmany - 4], yfire[howmany - 4]) = CHSV(blender + 128 , fvelo[howmany - 4] / 2 + 128, 255);
      zeds(driftx, drifty) = CHSV(blender + 128 , fvelo[howmany - 4] / 2 + 128, 255);
    }
  }
}


void spiraly() {
  if (counter == 0 )
  {
    howmany = random(BIGGER / 6, BIGGER / 4);
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle and color
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int jj = 0; jj < MATRIX_WIDTH ; jj++) {

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
        zeds(xx, yy) += CHSV(blender + jj * dot3 + h , 245, 235); //
    }

  }
  zeds(driftx, drifty) = CHSV(blender + 128 * 2 + h , 205, 255);
  DRectangle(0, 0, MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CRGB::Black);
}

void spiral2() {
  if (counter == 0 )
  {
    howmany = random(BIGGER / 6,  BIGGER / 4);
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int jj = 0; jj < 8 + triwave8(counter % 256) / 4  ; jj++)
    {

      if (flop[1]) {//crazy helix
        xx =  driftx + jj  * (sin8(fcount[i] + h + 2 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] - h - (dot - 2) * jj ) - 128.0) / 128.0;
      }
      else {//clasic spiral
        xx =  driftx + jj  * (sin8(fcount[i] + h + 3 * jj ) - 128.0) / 128.0;
        yy = drifty + jj  * (cos8(fcount[i] + h + 3 * jj ) - 128.0) / 128.0;
      }
      if (!flop[2])
        zeds(xx, yy) += CHSV(blender + fcount[i] + h , 255, 255);
      else
        zeds(xx, yy) += CHSV(blender + jj * 2 + h , 255, 255);


    }
  }

  for (int i = 0; i < howmany / 2; i++)
  {
    for (int jj = 0; jj < 8 + triwave8(counter % 128) / 2 ; jj++) {

      xx =  driftx + jj  * (sin8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;
      yy = drifty + jj  * (cos8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;

      if (!flop[2])
        zeds(xx, yy) += CHSV(128 + blender + fcount[i] + h , 255, 255); //
      else
        zeds(xx, yy) += CHSV(128 + blender + jj * 3 + h , 255, 255); //




    }
  }
  if (flop[5])zeds(driftx, drifty) = CHSV(blender + 128 * 2 + h , 205, 255);
  DRectangle(0, 0, MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CRGB::Black);

}


void spiral3() {
  if (counter == 0 )
  {
    howmany = random(BIGGER / 6,  BIGGER / 4);
    for (int i = 0; i < howmany; i++)
      fcount[i] = i * 255 / howmany; //angle
  }

  for (int i = 0; i < howmany; i++)
  {
    for (int jj = 0; jj < 32 + triwave8(counter % 255) / 8  ; jj++)
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
        zeds(xx, yy) += CHSV(blender + fcount[i] + h , 255 - velo / 5, 255); //
      else
        zeds(xx, yy) += CHSV(blender + jj * 3 + h , 255 - velo / 5, 255); //

    }
  }

  for (int i = 0; i <  (howmany / 2); i++)
  {
    for (int jj = 0; jj < 16 + triwave8((counter + blender) % 255) / 6  ; jj++)
    {
      xx =  driftx + jj  * (sin8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;
      yy = drifty + jj  * (cos8(fcount[i] * 2 - h + 2 * jj ) - 128.0) / 128.0;

      if (!flop[2])
        zeds(xx, yy) += CHSV(128 + blender + fcount[i] + h , 255 - velo / 5, 255); //
      else
        zeds(xx, yy) += CHSV(128 + blender + jj * 3 + h , 255 - velo / 5, 255); //

    }
  }

  DRectangle(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, CRGB::Black);
}

void lfado(int16_t bbc)
{
  for (int hhh = 0; hhh < MATRIX_WIDTH; hhh++)
    for (int jjj = 0; jjj < MATRIX_HEIGHT; jjj++)
      zeds(hhh, jjj).fadeToBlackBy(bbc + 2); //% = bbc/255
  //zeds(hhh, jjj) -= CRGB(bbc, bbc, bbc); //
}


void redfado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (flop[2])
        zeds(hhh, jjj) -= CRGB((bbc / 3), (bbc), (bbc));//leave more red
      else
        zeds(hhh, jjj) -= CRGB((bbc / 3), (bbc / 3), (bbc));// leave more yellow
}

void greenfado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (flop[2])
        zeds(hhh, jjj) -= CRGB((bbc ), (bbc / 3), (bbc));
      else
        zeds(hhh, jjj) -= CRGB((bbc), (bbc / 3), (bbc / 3)); // leave more teal
}

void bluefado(int16_t bbc) {
  for ( int16_t hhh = 0; hhh < MATRIX_WIDTH ; hhh++)
    for (int jjj = 0; jjj < MATRIX_HEIGHT ; jjj++)
      if (flop[2])
        zeds(hhh, jjj) -= CRGB((bbc), (bbc), (bbc / 3));
      else
        zeds(hhh, jjj) -= CRGB((bbc / 3 ), (bbc), (bbc / 3)); //leave more purple

}

void audocheckers()
{

  for (int16_t i = 0; i < 4; i++)
    for (int16_t qq = 0; qq < 4; qq++) {
      //radius2 = 64.0 / maxiaud;
      radius3 = MATRIX_WIDTH / 4;
      ccoolloorr = blender + (i * 4 + qq) * 14;
      sizzer = music.laudio[(i * 4) + qq]; //
      sizzer = constrain (sizzer, 0, 64); //size of square
      if (flop[2]) {
        DFRectangle(i * radius3, qq * radius3, (sizzer / 64.0 + i) * radius3, (qq + sizzer / 64.0) *radius3, CHSV(ccoolloorr, 255 - velo / 5, 160));
        DRectangle(i * radius3, qq * radius3, (1 + i) * radius3, (qq + 1) * radius3, CHSV(ccoolloorr, 255 - velo / 4, 255));
      }
      else {
        DFRectangle(i * radius3, qq * radius3, (sizzer / 64.0 + i) * radius3, (qq + sizzer / 64.0) *radius3, CHSV(ccoolloorr, 255 - velo / 5, 255));
        DRectangle(i * radius3, qq * radius3, (1 + i) * radius3, (qq + 1) *radius3, CRGB::White);
      }
    }

  audioprocess();
}


void audochess()
{

  solid2(128);
  for (int16_t i = 0; i < 4; i++)
    for (int16_t qq = 0; qq < 4; qq++) {
      radius2 = 1; // maxiaud
      radius3 = MATRIX_WIDTH / 4;
      ccoolloorr = blender + (i * 4 + qq) * 14;
      sizzer = music.laudio[(i * 4) + qq]  * radius2; //brightness
      //sizzer = constrain (sizzer, 0, 64); //brightness
      if (flop[2]) {
        DFCircle(i * radius3 + 8, qq * radius3 + 8,  radius3 / 2 - 1, CRGB::Black);
        DFCircle(i * radius3 + 8, qq * radius3 + 8, (sizzer / 64.0) * radius3 / 2 - 1,  CHSV(ccoolloorr, 255 - velo / 5, 160));
        DCircle(i * radius3 + 8, qq * radius3 + 8,  radius3 / 2 - 1, CHSV(ccoolloorr, 255 - velo / 4, 255));
      }
      else {
        DFCircle(i * radius3 + 8, qq * radius3 + 8,  radius3 / 2 - 1, CRGB::Black);
        DFCircle(i * radius3 + 8, qq * radius3 + 8, (sizzer / 64.0) * radius3 / 2 - 1, CHSV(ccoolloorr, 255 - velo / 5, 255));
        DCircle(i * radius3 + 8, qq * radius3 + 8,  radius3 / 2 - 1, CRGB::White);
      }
    }

  audioprocess();
}

void audio8()//stereo
{

  for (int i = 0; i < MATRIX_HEIGHT; i++)
  {
    if (flop[2]) {
      DLine(i, 0 , i, LLaudio[i * 64 / MATRIX_WIDTH] / 2, CHSV(i * mstep +  h, 255 - velo / 5, 255));
      DLine(i, MATRIX_HEIGHT - 1 , i, MATRIX_HEIGHT - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 2, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    }
    else {
      DLine(i, MATRIX_HEIGHT - 1 , i, MATRIX_HEIGHT - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 2, CHSV(i * mstep +  h, 255 - velo / 5, 255));
      DLine(i, 0 , i, LLaudio[i * 64 / MATRIX_WIDTH] / 2, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    }

    if (i > 0)
    {
      if (!flop[1]) {
        DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] / 2, i - 1, LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2  ,   CHSV(i * mstep +  h + 128, 255 - velo / 5, 255));
        DLine(i, MATRIX_HEIGHT - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 2, i - 1, MATRIX_HEIGHT - 1 - RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2  ,   CHSV(i * mstep +  h + 128, 255 - velo / 5, 255));
      }
      else {
        if ( flop[0]) {
          DLine(i, MATRIX_HEIGHT - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 2 , i - 1, MATRIX_HEIGHT - 1 - RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2 ,  CHSV(blender, 255 - velo / 4, 255));
          DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] / 2 , i - 1, LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2 ,  CHSV(blender, 255 - velo / 4, 255));
        }
        else {
          DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] / 2 , i - 1, LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2 ,  CRGB::White);
          DLine(i, MATRIX_HEIGHT - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 2 , i - 1, MATRIX_HEIGHT - 1 - RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2 ,  CRGB::White);
        }
      }
    }
  }
  audioprocess();
}

void audio9()//stereo
{

  for (int i = 0; i < MATRIX_WIDTH; i++)
  {
    DLine(i, MIDLY, i, MIDLY + LLaudio[i * 64 / MATRIX_WIDTH] / 2.0, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    DLine(i, MIDLY - 1, i, MIDLY - 1 - RRaudio[i * 64 / MATRIX_WIDTH] / 2.0, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    if (i > 0) {
      if (!flop[2]) {
        DLine(i, MIDLY + LLaudio[i * 64 / MATRIX_WIDTH] / 2.0, i - 1, MIDLY + LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2.0  ,   CHSV(h, 255 - velo / 5, 255)); // last 2
        DLine(i, MIDLY - 1 - RRaudio[i * 64 / MATRIX_WIDTH] / 2.0, i - 1, MIDLY - 1 - RRaudio[-1 + i * 64 / MATRIX_WIDTH] / 2.0  ,   CHSV(h, 255 - velo / 5, 255));
      } // last 2
      else {
        DLine(i, MIDLY + LLaudio[i * 64 / MATRIX_WIDTH] / 2.0 , i - 1, MIDLY + LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2.0 ,  CRGB::White); // last 2
        DLine(i, MIDLY - 1 - RRaudio[i * 64 / MATRIX_WIDTH] / 2.0 , i - 1, MIDLY - 1  - RRaudio[-1 + i * 64 / MATRIX_WIDTH] / 2.0 ,  CRGB::White);
      } // last 2
    }
  }
  audioprocess();
}

void audio10()//stereo display
{
  if (flop[2] && flop[1]) solid3(52);
  if ( flop[0]) {
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      DLine(i, MIDLY, i, MIDLY + LLaudio[i * 64 / MATRIX_WIDTH] / 1.8, CHSV(i * mstep / dot3 +  h, 255 - velo / 4, 255));
      DLine(i, MIDLY - 1, i, MIDLY - 1 - RRaudio[i * 64 / MATRIX_HEIGHT] / 1.8, CHSV(i * mstep / dot3 +  h, 255 - velo / 5, 255));
    }
  }
  else
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      DLine(i, MIDLY, i, MIDLY + LLaudio[MATRIX_WIDTH - i] / 2.0, CHSV(i * mstep / dot3 +  h, 255 - velo / 5, 255));
      DLine(i, MIDLY - 1, i, MIDLY - 1 - RRaudio[MATRIX_WIDTH - i] / 2.0, CHSV(i * mstep / dot3 +  h, 255 - velo / 4, 255));
    }
  audioprocess();
}

void audio11()// stereo from the sides.
{

  for (int i = 0; i < MATRIX_HEIGHT; i++)
  {
    if (!flop[1]) {
      DLine(i, 0 , i, RRaudio[i * 64 / MATRIX_HEIGHT] / 2, CHSV(i * mstep +  h + 128, 255 - velo / 5, 255));
      DLine(i, MATRIX_HEIGHT - 1 , i, MATRIX_HEIGHT - 1 - LLaudio[i * 64 / MATRIX_WIDTH] / 2, CHSV(i * mstep +  h + 128, 255 - velo / 5, 255));
    }
    else {
      DLine(i, 0 , i, RRaudio[i * 64 / MATRIX_HEIGHT] / 2, CHSV(blender +  h + 128, 255 - velo / 5, 255));
      DLine(i, MATRIX_HEIGHT - 1 , i, MATRIX_HEIGHT - 1 - LLaudio[i * 64 / MATRIX_WIDTH] / 2, CHSV(blender +  h + 128, 255 - velo / 5, 255));
    }
    if (i > 0)
    {
      if (!flop[1]) {
        DLine(i, RRaudio[i * 64 / MATRIX_HEIGHT] / 2, i - 1, RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2  ,   CHSV(i * mstep +  h , 255 - velo / 5, 255)); // last 2
        DLine(i, MATRIX_HEIGHT - 1 - LLaudio[i * 64 / MATRIX_WIDTH] / 2, i - 1, MATRIX_HEIGHT - 1 - LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2  ,   CHSV(i * mstep +  h , 255 - velo / 5, 255)); // last 2
      }
      else {
        if ( flop[0]) {
          DLine(i, RRaudio[i * 64 / MATRIX_HEIGHT] / 2, i - 1, RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2  ,   CHSV(blender, 255 - velo / 5, 255)); // last 2
          DLine(i, MATRIX_HEIGHT - 1 - LLaudio[i * 64 / MATRIX_WIDTH] / 2, i - 1, MATRIX_HEIGHT - 1 - LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2  ,   CHSV(blender, 255 - velo / 5, 255)); // last 2
        }

        else {
          DLine(i, RRaudio[i * 64 / MATRIX_HEIGHT] / 2 , i - 1, RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 2 ,  CRGB::White); // last 2
          DLine(i, MATRIX_HEIGHT - 1 - LLaudio[i * 64 / MATRIX_WIDTH] / 2, i - 1, MATRIX_HEIGHT - 1 - LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 2  ,   CRGB::White); // last 2
        }
      }
    }
  }
  audioprocess();
}

void audio12()//stereo display
{
  if (flop[2] && flop[1]) solid5();
  if (flop[0]) {
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      DLine(i, MIDLY / 2, i, MIDLY / 2 + LLaudio[i * 64 / MATRIX_WIDTH] / 3.6, CHSV(i * mstep +  h, 255 - velo / 4, 255));
      DLine(i, MIDLY / 2, i, MIDLY / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / 3.6, CHSV(i * mstep +  h, 255 - velo / 4, 255));
      DLine(i, MIDLY * 3 / 2, i, MIDLY * 3 / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6, CHSV(i * mstep +  h, 255 - velo / 5, 255));
      DLine(i, MIDLY * 3 / 2, i, MIDLY * 3 / 2 + RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    }
  }
  else
    for (int i = 0; i < MATRIX_WIDTH; i++)
    {
      DLine(i, MIDLY / 2, i, MIDLY / 2 + LLaudio[i * 64 / MATRIX_WIDTH] / 3.6, CHSV(i * mstep -  h, 255 - velo / 4, 255));
      DLine(i, MIDLY / 2, i, MIDLY / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / 3.6, CHSV(i * mstep -  h, 255 - velo / 4, 255));
      DLine(i, MIDLY * 3 / 2, i, MIDLY * 3 / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6, CHSV(i * mstep -  h + 128, 255 - velo / 5, 255));
      DLine(i, MIDLY * 3 / 2, i, MIDLY * 3 / 2 + RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6, CHSV(i * mstep -  h + 128, 255 - velo / 5, 255));
    }
  for (int i = 1; i < MATRIX_WIDTH; i++)
    if (!flop[7]) {
      DLine(i, MIDLY / 2 + LLaudio[i * 64 / MATRIX_WIDTH] / 3.6 , i - 1, MIDLY / 2 + LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 3.6  ,  CRGB::White);
      DLine(i, MIDLY / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / 3.6 , i - 1, MIDLY / 2 - LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 3.6  ,  CRGB::White);
      DLine(i, MIDLY * 3 / 2 + RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6 , i - 1, MIDLY * 3 / 2 + RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 3.6  ,  CRGB::White);
      DLine(i, MIDLY * 3 / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6 , i - 1, MIDLY * 3 / 2 - RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 3.6  ,  CRGB::White);
    }
    else {
      DLine(i, MIDLY / 2 + LLaudio[i * 64 / MATRIX_WIDTH] / 3.6 , i - 1, MIDLY / 2 + LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 3.6  ,  CHSV(h, 255 - velo / 5, 255));
      DLine(i, MIDLY / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / 3.6 , i - 1, MIDLY / 2 - LLaudio[-1 + i * 64 / MATRIX_WIDTH] / 3.6  ,  CHSV(h, 255 - velo / 5, 255));
      DLine(i, MIDLY * 3 / 2 + RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6 , i - 1, MIDLY * 3 / 2 + RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 3.6  ,  CHSV(h + 128, 255 - velo / 5, 255));
      DLine(i, MIDLY * 3 / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / 3.6 , i - 1, MIDLY * 3 / 2 - RRaudio[-1 + i * 64 / MATRIX_HEIGHT] / 3.6  ,  CHSV(h + 128, 255 - velo / 5, 255));
    }
  audioprocess();
}


void audio13()//stereo display crossed....do it..
{
  if (flop[2] && flop[1])
    solid5();

  for (int i = 0; i < MATRIX_WIDTH; i++)
  {
    DLine(MIDLX, i, MIDLX + LLaudio[i * 64 / MATRIX_WIDTH] / 1.8, i, CHSV(i * mstep +  h, 255 - velo / 4, 255));
    DLine(i, MIDLY , i, MIDLY  - RRaudio[i * 64 / MATRIX_HEIGHT] / 1.8, CHSV(i * mstep +  h, 255 - velo / 5, 255));
    DLine(MIDLX, i, MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / 1.8, i, CHSV(i * mstep +  h, 255 - velo / 4, 255));
    DLine(i, MIDLY , i, MIDLY  + RRaudio[i * 64 / MATRIX_HEIGHT] / 1.8, CHSV(i * mstep +  h, 255 - velo / 5, 255));
  }


  for (int i = 1; i < MATRIX_WIDTH; i++)
  {
    DLine(i, MIDLY + RRaudio[i * 64 / MATRIX_WIDTH] / 2 , i - 1, MIDLY  + RRaudio[i - 1 * 64 / MATRIX_HEIGHT] / 2,  CRGB::White);
    DLine(MIDLX + LLaudio[i * 64 / MATRIX_WIDTH] / 2, i, MIDLX + LLaudio[i - 1 * 64 / MATRIX_WIDTH] / 2, i - 1,  CRGB::White);
    DLine(i, MIDLY - RRaudio[i * 64 / MATRIX_WIDTH] / 2 , i - 1, MIDLY  - RRaudio[i - 1 * 64 / MATRIX_HEIGHT] / 2,  CRGB::White);
    DLine(MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / 2, i, MIDLX - LLaudio[i - 1 * 64 / MATRIX_WIDTH] / 2, i - 1,  CRGB::White);
  }

  audioprocess();
}

void audio2()
{

  for (int i = 0; i < MATRIX_WIDTH; i++)
  {
    DLine(i, 0, i, LLaudio[i * 64 / MATRIX_WIDTH] , CHSV(i * mstep + blender, 255 - velo / 5, 255));
    if (LLaudio[i * 64 / MATRIX_WIDTH] > MATRIX_HEIGHT * 0.50 )
      DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] - 4, i, LLaudio[i * 64 / MATRIX_WIDTH] ,  CHSV(i * mstep / dot3 + 85 + blender, 255 - velo / 5, 255));
    if (LLaudio[i * 64 / MATRIX_WIDTH] > MATRIX_HEIGHT * 0.70 ) {
      DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] - 2, i, LLaudio[i * 64 / MATRIX_WIDTH] ,  CHSV(i * mstep / dot3 - 85 + blender, 255 - velo / 5, 255));
    }
  }
  audioprocess();
}

void audio3()// different S on big hits
{

  for (int i = 0; i < MATRIX_WIDTH; i++)
  {
    DLine(i, 0, i, LLaudio[i * 64 / MATRIX_WIDTH] , CHSV(i * mstep + blender, 255, 255));
    if (LLaudio[i * 64 / MATRIX_WIDTH] > MATRIX_HEIGHT * 0.50 )
      DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] - 4, i, LLaudio[i * 64 / MATRIX_WIDTH] ,  CHSV(i * mstep  + blender, 196, 255));
    if (LLaudio[i * 64 / MATRIX_WIDTH] > MATRIX_HEIGHT * 0.70 ) {
      DLine(i, LLaudio[i * 64 / MATRIX_WIDTH] - 2, i, LLaudio[i * 64 / MATRIX_WIDTH] ,  CHSV(i * mstep  + blender + 32, 128, 255));
    }
  }
  audioprocess();
}

void Raudio9a9()  // 2 stereo rotating ring,  dots  , freq rotates, colors do not
{


  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  +  h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  +  h ) - 128.0) / 128.0;
    if (flop[2])
    {
      zeds(MIDLX + xangle * (MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , MIDLY + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep / 2 + blender , 255 - velo / 5, 255);
      zeds(MIDLX + xangle * (1 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale) , MIDLY + yangle * (1 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale)) = CHSV(i * mstep / 2 + xblender + 128, 255 - velo / 5, 255);
    }
    else {
      if (flop[1])
      {
        zeds(MIDLX + xangle * (MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , MIDLY + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep / 2 + blender , 255 - velo / 5, 255);
        zeds(MIDLX + xangle * (1 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale) , MIDLY + yangle * (1 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale)) = CRGB::White;
      }
      else {
        if ( flop[0])
        {
          zeds(MIDLX + xangle * (MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , MIDLY + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CRGB::White;;
          zeds(MIDLX + xangle * (1 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale) , MIDLY + yangle * (1 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale)) = CRGB::White;;
        }
        else
        {
          zeds(MIDLX + xangle * (MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , MIDLY + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep / 2 + blender, 255 - velo / 5, 255);
          zeds(MIDLX + xangle * (1 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale) , MIDLY + yangle * (1 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale)) = CHSV(i * mstep / 2 + blender, 255 - velo / 5, 255);
        }
      }
    }
  }
  audioprocess();
}

void circleaudio()// a circular spectrograph
{

  if (flop[10]) {
    driftx = MIDLX;
    drifty = MIDLY;
  }

  if (flop[9]) {
    dot = 1;
    dot2 = MIDLX / 2;
  }
  else {
    dot = 2;
    dot2 = MIDLX / 4;
  }
  // solid2(84);
  for (int16_t j = 0; j < 16; j++) {
    for (int i = 0; i < LLaudio[j] ; i++) {
      xangle =  (sin8(i * 2) - 128.0 ) / 128.0;
      yangle =  (cos8(i * 2) - 128.0 ) / 128.0;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(1 + i * 2) - 128.0 ) / 128.0;
      yangle =  (cos8(1 + i * 2) - 128.0 ) / 128.0;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(-1 + i * 2) - 128.0 ) / 128.0;
      yangle =  (cos8(-1 + i * 2) - 128.0 ) / 128.0;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
    }
    for (int i = 0; i < RRaudio[j] ; i++) {
      xangle =  (sin8(128 + i * 2) - 128.0 ) / 128.0;
      yangle =  (cos8(128 + i * 2) - 128.0 ) / 128.0;;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(128 + i * 2 + 1) - 128.0 ) / 128.0;
      yangle =  (cos8(128 + i * 2 + 1) - 128.0 ) / 128.0;;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(128 + i * 2 - 1) - 128.0 ) / 128.0;
      yangle =  (cos8(128 + i * 2 - 1) - 128.0 ) / 128.0;;
      zeds( driftx + (dot2 + dot * j)*xangle  , drifty + (dot2 + dot * j)* yangle) = CHSV(j * 4 * dot * mstep + blender , 255 - velo / 5, 255);
    }
  }
  audioprocess();
}


void circleaudio2()// a circular spectrograph
{
  // solid2(84);
  for (int16_t j = 0; j < 16; j++) {
    for (int i = 0; i < LLaudio[j] ; i++) {
      xangle =  (sin8(i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(1 + i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(1 + i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(-1 + i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(-1 + i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) += CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);

    }
    for (int i = 0; i < RRaudio[j] ; i++) {
      xangle =  (sin8(-i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3) - 128.0 ) / 128.0;;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(-i * 3 - 1) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3 - 1) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j )*xangle  , MIDLY + (MIDLY / 4 + 2 * j - 1)* yangle) = CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);
      xangle =  (sin8(-i * 3 + 1) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3 + 1) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j )*xangle  , MIDLY + (MIDLY / 4 + 2 * j - 1)* yangle) += CHSV(j * 8 * mstep + blender , 255 - velo / 5, 255);

    }
  }
  audioprocess();
}

void circleaudio3()// a circular spectrograph
{
  // solid2(84);
  for (int16_t j = 0; j < 16; j++) {
    for (int i = 0; i < LLaudio[j] ; i++) {
      xangle =  (sin8(i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender + i * 4, 255 - velo / 5, 255);
      xangle =  (sin8(1 + i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(1 + i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender + i * 4 , 255 - velo / 5, 255);
      xangle =  (sin8(-1 + i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(-1 + i * 3) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) += CHSV(j * 8 * mstep + blender + i * 4, 255 - velo / 5, 255);

    }
    for (int i = 0; i < RRaudio[j] ; i++) {
      xangle =  (sin8(-i * 3) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3) - 128.0 ) / 128.0;;
      zeds( MIDLX + (MIDLX / 4 + 2 * j)*xangle  , MIDLY + (MIDLY / 4 + 2 * j)* yangle) = CHSV(j * 8 * mstep + blender + i * 4 , 255 - velo / 5, 255);
      xangle =  (sin8(-i * 3 - 1) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3 - 1) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j )*xangle  , MIDLY + (MIDLY / 4 + 2 * j - 1)* yangle) = CHSV(j * 8 * mstep + blender + i * 4, 255 - velo / 5, 255);
      xangle =  (sin8(-i * 3 + 1) - 128.0 ) / 128.0;
      yangle =  (cos8(-i * 3 + 1) - 128.0 ) / 128.0;
      zeds( MIDLX + (MIDLX / 4 + 2 * j )*xangle  , MIDLY + (MIDLY / 4 + 2 * j - 1)* yangle) += CHSV(j * 8 * mstep + blender + i * 4 , 255 - velo / 5, 255);

    }
  }
  audioprocess();
}

void Raudio8a8()// ring, lines, colors rotate, freq does not rotate  black
{
  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep + h) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep + h) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale)), CHSV(i * mstep + h  , 255 - velo / 2, 255));
    zeds( MIDLX + xangle * (MIDLX - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale))) = CHSV(i * mstep + h  , 255 - velo / 2, 255);
    xangle =  (sin8(i * mstep + mstep / 2 + h) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep + mstep / 2 + h) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)), CHSV(i * mstep + h  , 255 - velo / 8, 255));
    zeds( MIDLX + xangle * (MIDLX - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale))) = CHSV(i * mstep + h  , 255 - velo / 8, 255);
  }
  audioprocess();
}

void Raudio2()// ring, lines, colors rotate, freq does not rotate
{
  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  ) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.6 * mscale)), CHSV(i * mstep + blender  , 255 - velo / 5, 255));
    xangle =  (sin8(i * mstep + mstep / 2 ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep + mstep / 2 ) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)) , MIDLY + yangle * (MIDLY - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.6 * mscale)), CHSV(i * mstep + blender  , 255 - velo / 5, 255));
  }
  audioprocess();
}

void Raudio2a()// ring, lines, colors rotate, freq does not rotate
{

  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / (1.7 * mscale)) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.7 * mscale)), CHSV(i * mstep + poffset , 255 - velo / 5, 255));
    xangle =  (sin8(i * mstep  + mstep / 2  ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  + mstep / 2) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.7 * mscale)) , MIDLY + yangle * (MIDLY - RRaudio[i * 64 / MATRIX_HEIGHT] / (1.7 * mscale)), CHSV(i * mstep + poffset , 255 - velo / 5, 255));
  }
  // audioprocess();
}

void Raudio3()//star shaped colors rotate
{

  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep   ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  ) - 128.0) / 128.0;
    DLine( driftx + xangle * 3 , drifty + yangle * 3 , driftx  + xangle * ( 3 + (LLaudio[i * 64 / MATRIX_WIDTH] ) / (2 * mscale)) , drifty  + yangle * (3 + (LLaudio[i * 64 / MATRIX_WIDTH] ) / (2 * mscale)), CHSV(i * mstep + blender , 255 - velo / 5, 255));
    DLine( driftx + xangle * 24 , drifty + yangle * 24 , driftx  + xangle * ( 24 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)) , drifty  + yangle * (24 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)), CHSV(i * mstep + xblender , 255 - velo / 5, 255));
  }

  audioprocess();
}

void Raudio3b()//star shaped colors rotate
{

  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  + h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h  ) - 128.0) / 128.0;
    DLine( driftx + xangle * 3 , drifty + yangle * 3 , driftx  + xangle * ( 3 + (LLaudio[i * 64 / MATRIX_WIDTH] ) / (2 * mscale)) , drifty  + yangle * (3 + (LLaudio[i * 64 / MATRIX_WIDTH] ) / (2 * mscale)), CHSV(i * mstep + blender + h, 255 - velo / 5, 255));
    DLine( driftx + xangle * 24 , drifty + yangle * 24 , driftx  + xangle * ( 24 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)) , drifty  + yangle * (24 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)), CHSV(i * mstep + xblender + h , 255 - velo / 5, 255));
  }

  audioprocess();
}

void Raudio3a()//roving star shaped colors rotate
{
  if (counter == 0)
    poffset = random8();
  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep - h  ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    DLine( driftx + xangle * 5 ,  drifty + yangle * 5 , driftx  + xangle * ( 5 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)) , drifty  + yangle * (5 + (RRaudio[i * 64 / MATRIX_HEIGHT] ) / (2 * mscale)), CHSV(i * mstep + poffset , 255 - velo / 5, 255));
  }

  audioprocess();
}

void Raudio4() // multi color hollow star witht variable height outward non rotational frequency or colors rotate
{
  int16_t floyd;
  floyd = mstep ;
  if (flop[6])
    floyd = floyd / dot3;

  for (int i = 0; i < MATRIX_WIDTH  ; i++) {
    if (flop[3]) {
      xangle =  (sin8(i * mstep + h ) - 128.0) / 128.0;
      yangle =  (cos8(i * mstep + h ) - 128.0) / 128.0;
    }
    else
    {
      xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
      yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    }

    DLine(driftx + (dot + 1) * xangle, drifty + (dot + 1)* yangle, driftx + xangle * (dot + 1 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + yangle * (dot + 1 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)), CHSV(i * floyd + poffset , 255 - velo / 8, 255));
  }
  audioprocess();
}



void Raudio5()  // multi color  ring witht variable height  colors stay with freq, freq rotates
{
  int16_t floyd;
  floyd = mstep;
  if (flop[6])
    floyd = floyd / dot3;
  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  - h ) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / (1.4 * mscale )) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.4 * mscale )), CHSV(i * floyd , 255 - velo / 5, 255));
  }
  audioprocess();
}

void Raudio5a()  // multi color  ring witht variable height  colors stay with freq, freq rotates
{


  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  - h ) - 128.0) / 128.0;
    if (flop[0] || flop[1])
      yangle =  (cos8(i * mstep  - h ) - 128.0) / 128.0;
    else
      yangle =  (cos8(i * mstep  + h ) - 128.0) / 128.0;
    DLine(MIDLX + MIDLX * xangle, MIDLY + MIDLY * yangle, MIDLX + xangle * (MIDLX - LLaudio[i * 64 / MATRIX_WIDTH] / (1.4 * mscale )) , MIDLY + yangle * (MIDLY - LLaudio[i * 64 / MATRIX_WIDTH] / (1.4 * mscale )), CHSV(i * mstep / dot3 - h , 255 - velo / 5, 255));
  }
  audioprocess();
}

void Raudio6()  // color ring of dots, roughly circular ,
{
  if (counter == 0)
    poffset = random8();
  for (int i = 0; i < MATRIX_WIDTH ; i++) {
    xangle =  (sin8(i * mstep  - h  ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep  - h ) - 128.0) / 128.0;
    if (flop[1] || flop[2] )//mostly stereo
    {
      zeds( driftx + xangle * ( MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , drifty + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep + poffset + h , 255 - velo / 5, 255);
      zeds( driftx + xangle * (-2 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_WIDTH] / mscale) , drifty + yangle * (-2 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_HEIGHT] / mscale)) = CHSV(i * mstep + poffset + 128 + h, 255 - velo / 5, 255);
    }
    else//sometimes  but not stereo
    {
      zeds( driftx + xangle * ( MATRIX_WIDTH / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale) , drifty + yangle * (MATRIX_HEIGHT / 2 - LLaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep + poffset , 255 - velo / 5, 255);
      zeds( driftx + xangle * (-2 + MATRIX_WIDTH / 2 - RRaudio[i * 64 / MATRIX_WIDTH] / mscale) , drifty + yangle * (-2 + MATRIX_HEIGHT / 2 - RRaudio[i * 64 / MATRIX_WIDTH] / mscale)) = CHSV(i * mstep + poffset + 128 , 255 - velo / 5, 255);
      ;
    }
  }
  audioprocess();
}


void Raudio7() // radiatng rotating planet pair stereo
{
  if (counter == 0) {
    poffset = random8();
    radius3 = random (MIDLX / 2 - 5, MIDLX - 6 );
  }

  locusy = ((radius3 * (cos8(h ) - 128)) >> 7);
  locusx = ((radius3 * (sin8(h ) - 128)) >> 7);
  for (int i = 0; i < MATRIX_WIDTH  ; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    DLine(driftx + locusx + (MIDLX / 4) * xangle, drifty + locusy + (MIDLY / 4)* yangle, driftx + locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep / (dot3) + blender , 255 - velo / 5, 255));
    DLine(driftx - locusx + (MIDLX / 4) * xangle, drifty - locusy + (MIDLY / 4)* yangle, driftx - locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty - locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep / (dot3) + blender , 255 - velo / 5, 255));

  }
  audioprocess();
}


void Raudio7a() // radiatng rotating planet pair about rotating center that rotates rotationally
{
  if (counter == 0) {
    poffset = random8();
    radius3 = random (MIDLX / 2 - 5, MIDLX - 7 );
    radius2 = random (MIDLX / 3 - 4, MIDLX / 3 + 4 );
  }

  locusy = ((radius3 * (cos8(h ) - 128)) >> 7);
  locusx = ((radius3 * (sin8(h ) - 128)) >> 7);
  drifty = MIDLX + ((radius2 * (cos8(h + poffset) - 128)) >> 7);
  driftx = MIDLX + ((radius2 * (sin8(h + poffset) - 128)) >> 7);
  for (int i = 0; i < MATRIX_WIDTH; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep + h ) - 128.0) / 128.0;
    DLine(driftx + locusx + (MIDLX / 4) * xangle, drifty + locusy + (MIDLY / 4)* yangle, driftx + locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + locusy + yangle * (MIDLY / 4 + LLaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep / dot3 + poffset , 255 - velo / 5, 255));
    DLine(driftx - locusx + (MIDLX / 4) * xangle, drifty - locusy + (MIDLY / 4)* yangle, driftx - locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty - locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep / dot3 + poffset , 255 - velo / 5, 255));

  }
  audioprocess();
}

void Raudio8() // whiteness
{
  if (counter == 0) {
    poffset = random8();
    radius3 = random (MIDLX / 2 - 2, MIDLX - 2 );
  }

  locusy = ((radius3 * (cos8(h ) - 128)) >> 7);
  locusx = ((radius3 * (sin8(h ) - 128)) >> 7);
  for (int i = 0; i < MATRIX_WIDTH  ; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;

    if (flop[4]) {

      if (flop[3]) {
        DFCircle(driftx + locusx, drifty + locusy, MIDLY / 4, CHSV(h + 64, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty - locusy, MIDLY / 4, CHSV(h - 64, 255 - velo / 5, 220));
      }
      else
      {
        DFCircle(driftx + locusx, drifty + locusy, MIDLY / 4, CHSV(h + 85, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty - locusy, MIDLY / 4, CHSV(h - 85, 255 - velo / 5, 220));
      }
      DLine(driftx + locusx + (MIDLX / 4) * xangle, drifty + locusy + (MIDLY / 4)* yangle, driftx + locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);
      DLine(driftx - locusx + (MIDLX / 4) * xangle, drifty - locusy + (MIDLY / 4)* yangle, driftx - locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty - locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);

    }
    else
    {

      if (flop[3]) {
        DFCircle(driftx + locusx, drifty + locusy, MIDLY / 4, CHSV(h + 32, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty - locusy, MIDLY / 4, CHSV(h + 64, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty + locusy, MIDLY / 4, CHSV(h - 32, 255 - velo / 5, 220));
        DFCircle(driftx + locusx, drifty - locusy, MIDLY / 4, CHSV(h - 64, 255 - velo / 5, 220));
      }
      else
      {
        DFCircle(driftx + locusx, drifty + locusy, MIDLY / 4, CHSV(h + 42, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty - locusy, MIDLY / 4, CHSV(h + 84, 255 - velo / 5, 220));
        DFCircle(driftx + locusx, drifty - locusy, MIDLY / 4, CHSV(h - 84, 255 - velo / 5, 220));
        DFCircle(driftx - locusx, drifty + locusy, MIDLY / 4, CHSV(h - 42, 255 - velo / 5, 220));
      }
      DLine(driftx + locusx + (MIDLX / 4) * xangle, drifty + locusy + (MIDLY / 4)* yangle, driftx + locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);
      DLine(driftx - locusx + (MIDLX / 4) * xangle, drifty - locusy + (MIDLY / 4)* yangle, driftx - locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty - locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);
      DLine(driftx - locusx + (MIDLX / 4) * xangle, drifty + locusy + (MIDLY / 4)* yangle, driftx + locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty + locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);
      DLine(driftx + locusx + (MIDLX / 4) * xangle, drifty - locusy + (MIDLY / 4)* yangle, driftx - locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , drifty - locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CRGB::White);

    }
  }

  audioprocess();
}

void RaudioRoger() // radiatng rotating centered in roger's hole
{
  if (counter == 0) {
    poffset = random8();

  }


  for (int i = 0; i < MATRIX_WIDTH  ; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    DLine(locusx + (MIDLX / 4) * xangle,  locusy + (MIDLY / 4)* yangle,  locusx + xangle * (MIDLX / 4 + RRaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , locusy + yangle * (MIDLY / 4 + RRaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep + poffset , 128 + blender / 2, 255));

  }
  audioprocess();
}
void LaudioRoger() // radiatng rotating centered in roger's hole
{
  if (counter == 0) {
    poffset = random8();
  }

  for (int i = 0; i < MATRIX_WIDTH  ; i++) {
    xangle =  (sin8(i * mstep - h ) - 128.0) / 128.0;
    yangle =  (cos8(i * mstep - h ) - 128.0) / 128.0;
    DLine(locusx + (MIDLX / 4) * xangle,  locusy + (MIDLY / 4)* yangle,  locusx + xangle * (MIDLX / 4 + LLaudio[i * 64 / MATRIX_WIDTH] / (mscale)) , locusy + yangle * (MIDLY / 4 + LLaudio[i * 64 / MATRIX_HEIGHT] / (mscale)), CHSV(i * mstep + poffset , 128 + blender / 2, 255));

  }
  audioprocess();
}

void spin1()  // many fingers moving in arc to middle
{
  if (counter == 0) {

    dot = random(3, 6);

    hhowmany = random(3, 11);
    raad = 256.0 / hhowmany;
    radius = 3;
    flop[3] = true;
  }

  if ((counter % (3 * BIGGER))  == 0) { //-5
    dot = random(3, 6);
    ccoolloorr =  random8();
    hhowmany = random(3, 8);
    raad = 256 / hhowmany;
    radius2 = random(2, 6);//spin speed
    if (random8() > 128) flop[3] = !flop[3];
    // Serial.println(flop[3]);
  }

  for (int q = 0; q < hhowmany; q++) {
    if (flop[3] == true) {
      eeksangle =  (sin8((radius2 * h + raad * q)) - 128.0) / 128.0;
      whyangle =  (cos8((radius2 * h +  raad * q)) - 128.0) / 128.0;
      if (flop[9])

        DFCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CHSV(ccoolloorr +  h, 255 - velo / 5, 255));
      else
        DFCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CHSV(q * 255 / hhowmany + ccoolloorr +  h, 255 - velo / 5, 255));

      if (ccoolloorr % 10 == 0)
        DFCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CRGB::White);
    }
    else
    {
      eeksangle =  (sin8((  raad * q - radius2 * h)) - 128.0) / 128.0;
      whyangle =  (cos8((  raad * q - radius2 * h)) - 128.0) / 128.0;
      DFCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CHSV(ccoolloorr + 2 * h, 255 - velo / 5, 255));
      if (ccoolloorr % 10 == 0)
        DFCircle(driftx + eeksangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_WIDTH)), drifty + whyangle * (2 * MATRIX_WIDTH  - counter % (2 * MATRIX_HEIGHT)) , dot, CRGB::White);
    }

  }
  if ( flop[0]) {
    if (counter % (2 * MATRIX_WIDTH) - 2 == 0)
      DFCircle(driftx  , drifty  , dot , CHSV(ccoolloorr + 21, 255 - velo / 5, 255));
    if (counter % (2 * MATRIX_WIDTH) - 3 == 0)
      DFCircle(driftx  , drifty  , dot - 1, CHSV(ccoolloorr + 42, 255 - velo / 5, 255));
    if (counter % (2 * MATRIX_WIDTH) - 4 == 0) {
      DFCircle(driftx  , drifty  , dot - 2, CHSV(ccoolloorr + 63, 255 - velo / 5, 255));

    }
  }
}

void spin2()  // 4 meteriorw moving in ovals
{
  if (counter == 0)
  {
    dot += 3;
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
  DFCircle(MIDLX + xangle * (MIDLX / 2), MIDLY + yangle * (MIDLY ) , dot + dot3, CHSV(h + 2 * ccoolloorr, velo / 4 + 106, 180));
  DCircle(MIDLX + xangle * (MIDLX / 2), MIDLY + yangle * (MIDLY ) , dot + dot3, CHSV(h + 2 * ccoolloorr - 16, 255 - velo / 4, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) + 64) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) + 64) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) + 64) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) + 64) - 128.0) / 128.0;
  }
  DFCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot + dot3, CHSV(h , velo / 4 + 106, 180));
  DCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot + dot3, CHSV(h - 16, 255 - velo / 4, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) + 128) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) + 128) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) + 128) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) + 128) - 128.0) / 128.0;
  }
  DFCircle(MIDLX + xangle * (MIDLX / 2), MIDLY + yangle * (MIDLY ) , dot + dot3, CHSV(h + ccoolloorr, velo / 4 + 106, 180));
  DCircle(MIDLX + xangle * (MIDLX / 2), MIDLY + yangle * (MIDLY ) , dot + dot3, CHSV(h + ccoolloorr - 16, 255 - velo / 5, 255));
  if (!flop[8]) {
    xangle =  (sin8(2 * (h ) - 64) - 128.0) / 128.0;
    yangle =  (cos8(2 * (h ) - 64) - 128.0) / 128.0;
  }
  else {
    xangle =  (sin8(-2 * (h ) - 64) - 128.0) / 128.0;
    yangle =  (cos8(-2 * (h ) - 64) - 128.0) / 128.0;
  }

  DFCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot + dot3, CHSV(h - ccoolloorr, velo / 4 + 106, 180));
  DCircle(MIDLX + xangle * (MIDLX ), MIDLY + yangle * (MIDLY / 2) , dot + dot3, CHSV(h - ccoolloorr - 16, 255 - velo / 5, 255));
}

void magictime()
{
  if (counter == 0)
  {
    locusx = driftx;
    locusy = drifty;
    raad = random(BIGGER / 2, BIGGER * 2 / 3);
    ringdelay = 50;
  }

  if (raad > 1)
  {
    DFCircle(locusx, locusy , raad, CHSV(h * 3 , 255 - (counter % 128), 255));
    raad = raad - 1;
  }

  if (raad == 2)
  {
    ringdelay = random(20, 70);
    // DFCircle(locusx, locusy , raad, CHSV(ccoolloorr ,velo+196, 255));
    //  zeds( locusx, locusy)  = CRGB::White;
    raad = raad - 1;
  }
  if (raad == 1) {
    ringdelay--;
  }

  if (ringdelay == 0)
  {
    raad = random(BIGGER / 2, BIGGER * 2 / 3);
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

  }

  if (raad < BIGGER - dot)
  {
    DCircle(driftx, drifty , raad, CHSV(blender + h , 255 - velo / 5, 255));
    DCircle(driftx, drifty , raad + 1, CHSV(blender + h , 255 - velo / 4, 255));
    DCircle(driftx, drifty , raad - 1, CHSV(blender + h , 255 - velo / 5, 255));
    raad++;
  }

  if (raad == BIGGER - dot) {
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
  xsizer = random(MATRIX_WIDTH / 5, MATRIX_WIDTH / 2);
  ysizer = random(MATRIX_HEIGHT / 5, MATRIX_HEIGHT / 2);
  raad =  random(BIGGER / 6, BIGGER / 2);
  locusx = random(2, MATRIX_WIDTH - 2);
  locusy = random(2, MATRIX_HEIGHT - 2);

  ccoolloorr = random8();
  for (int16_t tt = 0; tt < dot2; tt++)
    zeds(random16(MATRIX_WIDTH) , random16(MATRIX_HEIGHT)) = CHSV(blender + random8(99), random(190, 255), random(199, 255));


  switch (random(10))
  {
    case 0:
      for (int16_t tt = 0; tt < dot2; tt++)
        DRectangle(locusx - tt, locusy + tt , locusx + xsizer + tt , locusy + ysizer + tt, CHSV(blender , 255 - (counter % 64), 255));
      break;
    case 1:
      for (int16_t tt = 0; tt < dot2; tt++)
        DCircle(locusx, locusy , raad + tt, CHSV(ccoolloorr , 255 - velo / 5, 255));
      break;
    case 2:
      for (int16_t tt = 0; tt < dot2; tt++)
        DFRectangle(locusx - tt, locusy - tt , locusx + xsizer + tt , locusy + ysizer + tt, CHSV(blender + 5 * tt, 255 - (counter % 64), 255));
      break;

    case 3:
      for (int16_t tt = 0; tt < dot2; tt++)
        DFCircle(locusx + 2 * yy, locusy - 2 * tt , raad + tt, CHSV(blender , 255 - velo / 5, 255));
      break;
    case 4:
      DFRectangle(locusx, locusy , locusx + xsizer , locusy + ysizer, CHSV(blender , 255 - (counter % 40), 255));
      break;

    case 5:
      for (int16_t i = 7; i > 0 ; i--)
        DFRectangle(locusx - i, locusy - i , locusx + 2 * i , locusy + 2 * i, CHSV(blender + i * steper, 255 - (counter % 32), 255));
      break;

    case 6:
      for (int i = raad; i > 0; i--)
        DFCircle(locusx, locusy , i, CHSV(xblender + i * steper , 255 - (counter % 50), 255));
      break;

    case 7:
      for (int16_t tt = 0; tt < dot2; tt++)
        triangle(locusx + tt, locusy - tt, raad, h, blender);
      break;

    case 8:
      for (int16_t tt = 0; tt < dot2; tt++)
        sticks();

      break;

    case 9:
      zeds(locusx, locusy) = CHSV(ccoolloorr, 255 - velo / 5, 255);
      for (int16_t tt = 0; tt < dot2; tt++)
        zeds(random16(MATRIX_WIDTH) , random16(MATRIX_HEIGHT)) = CHSV(blender + random8(64), random(150, 255), random(199, 255));

      break;

  }

}

void bouncey()
{

  if (counter == 0)
  {
    locusx = MIDLX;
    locusy = MIDLY;
    raad =  random(BIGGER / 3,  3 + BIGGER / 2);
    yangle = random(10, 54);
    xangle = (sin8(yangle) - 128.0) / 128.0;
    yangle = (cos8(yangle) - 128.0) / 128.0;
  }

  locusx =  locusx + xangle;
  locusy =  locusy + yangle;
  driftx = locusx;
  drifty = locusy;

  if (locusx > BIGGER  || locusx < 0 ) {
    xangle = 0 - xangle;
  }
  if (locusy > MATRIX_HEIGHT  || locusy < 0  ) {
    yangle = 0 - yangle;

  }
  for (int16_t gg = 0; gg < raad - 6; gg++)
    DFCircle(locusx, locusy , raad - gg, CHSV(h + xblender + gg * 8, 255 - velo / 8 , 255));

  DFCircle(locusx, locusy , 6, CRGB::Black);

}

//void triangle(int16_t xloc, int16_t yloc, int16_t bigg, int16_t angle, int16_t kolor)
void starbounce()
{
  if (counter == 0)
  {
    locusx = driftx;
    locusy = drifty;
    raad =  BIGGER * 4 / 5; //size
    howmany = random (6, 8);
    dot = random(raad / 2 + 2, raad);
    radius2 = random(16, 48);
    xangle = (sin8(radius2) - 128.0) / 128.0;
    yangle = (cos8(radius2) - 128.0) / 128.0;
    ccoolloorr = random8();
  }

  locusx = driftx;
  locusy = drifty;

  if (locusx > BIGGER - raad / 2  || locusx < raad / 2 ) {
    xangle = 0 - xangle;
  }
  if (locusy > MATRIX_HEIGHT - raad / 2  || locusy < raad / 2  ) {
    yangle = 0 - yangle;

  }
  for (int16_t qq = 0; qq < dot; qq ++)  {
    if (flop[4]) {
      drawstar(locusx, locusy, raad -  qq, raad / 2 -  qq / 2, howmany, h , ccoolloorr + qq * 8 +  h); // random multipoint star
      drawstar(locusx, locusy, raad -  qq - 1, raad / 2 -  qq / 2 - 1, howmany - dot3, -h * 2, ccoolloorr +  h + qq * 8); // random multipoint star
    }
    else
    {
      drawstar(locusx, locusy, raad -  qq, raad / 2 -  qq / 2, howmany - dot3, 2 * h , ccoolloorr + qq * 8 + 2 * h); // random multipoint star
      drawstar(locusx, locusy, raad -  qq - 1, raad / 2 -  qq / 2 - 1, howmany, -h , ccoolloorr  +  h + qq * 8); // random multipoint star
    }
  }
}

void triforce() {
  if (flop[0] &&  flop[2])
    solid2(96);
  else if (flop[0] && !flop[1])
    solid(85);
  if (flop[9])
    for (int i = 0; i < MIDLX + 6 * dot; i ++ ) {
      triangle(MIDLX, MIDLY,  8 + i, h,  h + 8 * i );
      if (i % dot == 0)
        triangle(MIDLX, MIDLY, 8 + i, h,  h + 8 * i + 128);
    }
  else
    for (int i = 0; i < MIDLX + 6 * dot; i ++ ) {
      triangle(driftx, drifty,  8 + i, 2 * h,  h + 8 * i );
      if (i % dot == 0)
        triangle(driftx, drifty, 8 + i, 2 * h,  h + 8 * i + 128);
    }

}
void seasick3()
// horizontal waves
{
  if (counter == 0)
    sinewidth = random(7, 15);
  if (flop[1])
    solid5();


  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    DLine((MIDLX / 2 - (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 * MIDLX * 0.50 ), jj, 0, jj, CHSV(h + jj + 128, 255 - velo / 5, 255));
    DLine( (MIDLX * 3 / 2 - (sin8(- h + jj * sinewidth) - 128) / 128.0 * MIDLX * 0.50 ), jj, MATRIX_HEIGHT - 1, jj, CHSV(h + jj , 255 - velo / 5, 255));
  }
}
void seasick6()
// full size waves overlapping with minimal fade...
{
  if (counter == 0)
    sinewidth = random(5, 9);
  for (int jj = 0; jj < MATRIX_WIDTH; jj++) {

    for (int ii = -2 * dot2; ii < 2 * dot2 ; ii++)
      zeds(jj , ii +  MIDLY + (sin8(3 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.70) += CHSV(h  - 44, 255 - velo / 5, 255);



    for (int ii = -3 * dot; ii < 3 * dot ; ii++)
      zeds( ii +  MIDLX + (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.70, jj) += CHSV(h  + 44, 255 - velo / 5, 255);
  }
}



void seasick()
// horizontal waves
{
  if (counter == 0)
    sinewidth = random(5, 12);


  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    for (int gg = 0; gg < 2 + MIDLY / 2 - (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.45 ; gg++)
      zeds(jj, gg) = CRGB::Red;
    for (int gg = 0; gg < 8 + MIDLY / 2 - (sin8(h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.65 ; gg++)
      zeds(jj, gg)  += CHSV(h + 128  , 255 - velo / 6 , 255);



    for (int gg =  -2 + MIDLY * 3 / 2 - (sin8(2 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.45 ; gg < MATRIX_HEIGHT ; gg++)
      zeds(jj, gg) = CRGB::Blue;

    for (int gg =  -8 + MIDLY * 3 / 2 - (sin8(- h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.65 ; gg < MATRIX_HEIGHT ; gg++)
      zeds(jj, gg)  += CHSV(h   , 255 - blender / 6  , 255);


  }
}
void seasick2()
// horizontal waves
{
  if (counter == 0)
    sinewidth = random(4, 10);
  if (flop[1] && flop[3])
    solid5();


  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    for (int gg = 0; gg <  MIDLY / 2 - (sin8(-3 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.65 ; gg++)
      zeds(jj, gg) += CHSV(h + jj / 2 + 80, 255 - velo / 6, 255);
    for (int gg =  MIDLY * 3 / 2 - (sin8(- h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.65 ; gg < MATRIX_HEIGHT ; gg++)
      zeds(jj, gg) += CHSV(h + jj / 2, 255 - velo / 6, 255);
  }
}

void seasick5()
// horizontal waves
{
  if (counter == 0) {
    sinewidth = random(MIDLX / 6, MIDLX / 3 );
    dot2 = random(6, 13);
    dot = random(6, 13);
  }

  bfade = 2;
  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {
    DLine(jj, (3 + MIDLY / 2 - (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.525 ), jj, 0, CHSV(h  + 85, 255, 255));
    DLine(jj, (-3 + MIDLY * 3 / 2 - (sin8(h + jj * (sinewidth)) - 128) / 128.0 * MIDLY * 0.525 ), jj, MATRIX_HEIGHT, CHSV(h  , 255, 255));
  }


  for (int jj = 0; jj < MATRIX_WIDTH; jj++) {
    if (flop[3] || flop[5])
      for (int ii = -dot2; ii < dot2 ; ii++)
        zeds(jj , ii +  MIDLY + (sin8(4 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.60) += CHSV(h  - 85, 255 , 255);

    else
      for (int ii = -dot; ii <  dot; ii++)
        zeds( ii +  MIDLX + (sin8(-4 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.60, jj) += CHSV(h  - 85, 255 , 255);
  }
}


void seasick4()
// horizontal waves
{

  if (counter == 0) {
    sinewidth = random(MIDLX / 6, MIDLX / 3);
    dot2 = random(5, 12);
    dot = random(5, 12);
  }

  bfade = 2;

  for (int jj = 0; jj < MATRIX_WIDTH; jj++)
  {

    DLine(jj, (2 + MIDLY / 2 - (sin8(-2 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.50 ), jj, 0, CHSV(h + jj  , 215, 255));

    DLine(jj, (-2 + MIDLY * 3 / 2 - (sin8( h + jj * (sinewidth)) - 128) / 128.0 * MIDLY * 0.50 ), jj, MATRIX_HEIGHT, CHSV(h - jj, 225, 255));
  }


  for (int jj = 0; jj < MATRIX_WIDTH; jj++) {
    if (flop[3] || flop[5])
      for (int ii = -dot2; ii < dot2 ; ii++)
        zeds(jj , ii +  MIDLY + (sin8(4 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.70) = CHSV(h + jj + 128, 155 , 230);
    else
      for (int ii = -dot; ii <  dot ; ii++)
        zeds( ii +  MIDLX + (sin8(-4 * h + jj * sinewidth) - 128) / 128.0 * MIDLY * 0.70, jj) = CHSV(h + jj + 128, 155  , 230);
  }
}

void hypnoduck() {
  // pair of  spiral discs - hyponic light
  if (counter == 0) {
    dot = random(2, 5);
    radius = random (BIGGER * .2, BIGGER * .4);
    quash = -20 + dot;
  }

  if (flop[9] || flop[8]) {
    xxx = MIDLX + radius * (sin8(h) - 128.0) / 128.0;
    yyy = MIDLY + radius * (cos8(h) - 128) / 128.0;
  }
  else
  {
    xxx = driftx + radius * (sin8(h) - 128.0) / 128.0;
    yyy = drifty + radius * (cos8(h) - 128) / 128.0;
  }


  for (int jj = 0; jj < 400; jj += 5)
  {
    poffset = 0;
    if (flop[2] )
      poffset = jj / 2;
    else if (flop[4])
      poffset = jj / 4;
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    DFCircle(xxx + xangle * (jj /  17) , yyy + yangle * (jj / 17), dot, CHSV(poffset + h - 64, 255 - velo / 5, 255));

    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    DFCircle(xxx + xangle * (jj /  17) , yyy + yangle * (jj / 17), dot, CHSV(poffset + h + 64, 255 - velo / 2, 255));
  }
  //DFCircle(xxx, yyy,  dot, CHSV(poffset + h , 255 - velo / 4, 255));

  // 2nd spiral

  if (flop[9] || flop[8]) {
    xxx = MIDLX + radius * (sin8(h + 128) - 128.0) / 128.0;
    yyy = MIDLY + radius * (cos8(h + 128) - 128) / 128.0;
  }
  else
  {
    xxx = driftx + radius * (sin8(h + 128) - 128.0) / 128.0;
    yyy = drifty + radius * (cos8(h + 128) - 128) / 128.0;
  }
  for (int jj = 0; jj < 400; jj += 5)
  {
    poffset = 0;
    if (flop[2] )
      poffset = jj / 2;
    else if (flop[4])
      poffset = jj / 4;
    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    DFCircle(xxx + xangle * (jj /  17) , yyy + yangle * (jj / 17), dot, CHSV(poffset + h + 128, 255 - velo / 4, 255));
    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    DFCircle(xxx + xangle * (jj /  17) , yyy + yangle * (jj / 17), dot, CHSV(poffset + h , 255 - velo / 2, 255));
  }
  //DFCircle(xxx , yyy , dot, CHSV(poffset + h + 42 , 255 - velo / 5, 255));
}

void hypnoduck3()  // growing spirals
{
  if (counter == 0) {
    dot = random(2, 5);
    quash = -12 - dot;
  }

  for (int jj = 20; jj < beatsin16(6, 190, 850, 0); jj += 5)
  {
    poffset = 0;
    if (flop[2] )
      poffset = jj / 2;
    else if (flop[4])
      poffset = jj / 4;

    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    DFCircle( driftx + xangle * (jj /  (19 - dot)) , drifty + yangle * (jj / (19 - dot)), dot, CHSV(poffset - h - 100, 255 - velo / 5, 255));
    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    DFCircle( driftx + xangle * (jj /  (19 - dot)) ,  drifty + yangle * (jj / (19 - dot)), dot, CHSV(poffset - h , 255 - velo / 2, 255));
  }
}


void hypnoduck2()
// spirals with speckles of hyponic light random direction based on flop[1]
{
  if (counter == 0) {
    dot = random8(2, 5);

    quash = -9;
  }
  if (flop[2] || flop[5])
    solid5();
  else

    solid2(129);

  for (int jj = 0; jj < beatsin16(4, 220, 880, 400) ; jj += 5)
  {
    poffset = 0;
    if (flop[2] )
      poffset = jj / 2;
    else if (flop[4])
      poffset = jj / 4;

    xangle =  (sin8(jj + quash * h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h) - 128.0) / 128.0;
    DFCircle( driftx + xangle * jj / 15 , drifty + yangle * jj / 15, dot, CHSV(-h + ccoolloorr - 85 + poffset, 255 - velo / 5 , 255));

    xangle =  (sin8(jj + quash * h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * h + 128) - 128.0) / 128.0;
    DFCircle( driftx + xangle * jj / 15 ,  drifty + yangle * jj / 15, dot, CHSV(-h + ccoolloorr + 85 + poffset, 255 - velo / 2, 255));
  }

}


void hypnoduck4()
// spiral inward with the hyponic light
{

  if (counter == 0) {
    dot = random8(2, 5);

    quash = 9;
  }

  if (flop[2])
    DFRectangle(0, 0, MATRIX_WIDTH  - 1, MATRIX_HEIGHT  - 1, CRGB::Black);
  else if (flop[0])
    solid5();
  for (int jj = beatsin16(4, 4, 1300, 0) ; jj > 0; jj -= 5)//
  {
    poffset = 0;
    if (flop[2] )
      poffset = jj / 2;
    else if (flop[4])
      poffset = jj / 3;

    xangle =  (sin8(jj + quash * -h) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * -h) - 128.0) / 128.0;
    DFCircle(driftx + xangle * (jj /  22) , drifty + yangle * (jj / 22), dot, CHSV(poffset + h + 64, 255 - velo / 5, 255));

    xangle =  (sin8(jj + quash * -h + 128) - 128.0) / 128.0;
    yangle =  (cos8(jj + quash * -h + 128) - 128.0) / 128.0;
    DFCircle(driftx + xangle * (jj /  22) , drifty + yangle * (jj / 22), dot, CHSV(poffset + h - 64, 255 - velo / 5, 255));
  }

}

//format drawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler)// random multipoint star

void starer() {
  if (counter == 0)
    pointy = random(4, 9);
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= BIGGER)
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
    if (counter - bringdelay <= BIGGER + 10)
    {
      //format drawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler)// random multipoint star
      drawstar(driftx, drifty, 2 * (BIGGER - (counter - bringdelay) + 15), 15 + BIGGER - (counter - bringdelay), pointyfix, blender - h, h  - 60);
      drawstar(driftx, drifty, 2 * (BIGGER - (counter - bringdelay) + 10), 10 + BIGGER - (counter - bringdelay), pointyfix, blender - h, h  - 50);
      drawstar(driftx, drifty, 2 * (BIGGER - (counter - bringdelay) + 5), 5 + BIGGER - (counter - bringdelay), pointyfix, blender - h, h  - 40);
      drawstar(driftx, drifty, 2 * (BIGGER - (counter - bringdelay)), BIGGER - (counter - bringdelay), pointyfix, blender - h, h - 30  );
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
    if (counter - ringdelay <= BIGGER + 10)
    {
      for (int16_t gg = 0; gg < 18; gg += 3)
        triangle(driftx  , drifty ,  (counter - ringdelay + gg), 3 * h, h * 8);
      triangle(driftx  , drifty ,  (counter - ringdelay + 21), 3 * h + 128, h * 8 + 128);

    }
    else
      ringdelay = counter + random(targetfps * 4, targetfps * 12);
  }
}

void boxer() {
  if (counter >= ringdelay)
  {
    if (counter - ringdelay <= BIGGER)
    {
      DRectangle(driftx - (counter - ringdelay) , drifty - (counter - ringdelay) , driftx + (counter - ringdelay), drifty + (counter - ringdelay), CHSV(h * 2 + 128, 255 - (counter % 64), 255));
    }
    else
      ringdelay = counter + random(targetfps * 3, targetfps * 15);
  }
}

void bkboxer() {
  if (counter >= bringdelay)
  {
    if (counter - bringdelay <= BIGGER + 10)
    {
      DRectangle(driftx - 12 - (counter - bringdelay) , drifty - 12 - (counter - bringdelay) , driftx + 12 + (counter - bringdelay), drifty + 12 + (counter - bringdelay), CHSV(h, 255 - (counter % 64), 255));
      DRectangle(driftx - 8 - (counter - bringdelay) , drifty - 8 - (counter - bringdelay) , driftx + 8 + (counter - bringdelay), drifty + 8 + (counter - bringdelay), CHSV(h +   steper * 4, 255 - (counter % 64), 255));
      DRectangle(driftx - 4 - (counter - bringdelay) , drifty - 4 - (counter - bringdelay) , driftx + 4 + (counter - bringdelay), drifty + 4 + (counter - bringdelay), CHSV(h +  steper * 8, 255 - (counter % 64), 255));
      DRectangle(driftx - (counter - bringdelay) , drifty - (counter - bringdelay) , driftx + (counter - bringdelay), drifty + (counter - bringdelay), CHSV(h + steper * 12, 255 - (counter % 64), 255));
    }
    else {
      bringdelay = counter + random(targetfps * 4, targetfps * 12);

    }
  }
}


void homer() {
  if (counter == 0 )
  {
    howmany = random (BIGGER , BIGGER * 2 );
    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random8(64); //color
      fpeed[i] = random(1, 7);// bigger = slower

      ccoolloorr = random8();
      xpoffset[i] = random8();
    }
  }

  for (int i = 0; i < howmany; i++)
  {
    if ( flop[0])
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0 , drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) =  CHSV(fcolor[i], 255 - velo / 5, 255);

    else
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0, drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) = CHSV(xblender, 255 - velo / 5, 255);


  }
  zeds(driftx , drifty ) = CRGB::White;
}

void homer2() {// growing egg
  if (counter == 0 )
  {
    howmany = random (BIGGER / 2 + 8, 1.5 * BIGGER );
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
  DCircle( MIDLX  , MIDLY, dot + 1, CRGB::White);
  for (int i = 0; i < howmany; i++)
  {
    if ( flop[0])
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0 , MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) =  CHSV(fcolor[i], 255 - velo / 5, 255);
    else if (!flop[1])
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0 , MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) =  CRGB::Orange;
    else
      zeds(MIDLX +  (dot + MIDLX - ((counter + xpoffset[i]) % MIDLX) / fpeed[i]) * (sin8(fcount[i] + 2 * h ) - 128.0) / 128.0, MIDLY +  (dot + MIDLY - ((counter + xpoffset[i]) % MIDLY) / fpeed[i]) * (cos8(fcount[i] + 2 * h ) - 128.0) / 128.0) = CHSV(h, 255 - velo / 5, 255);
  }
  DFCircle( MIDLX  , MIDLY, dot - 1 , CHSV(h, 255 - velo / 5, 55 + 100 * dot / MIDLX));
}

void homer3() {
  if (counter == 0 )
  {
    howmany = random (BIGGER * 1.5, BIGGER * 2 );
    for (int i = 0; i < howmany; i++) {
      fcount[i] = random8(); //angle
      fcolor[i] = blender + random8(64);//color
      fpeed[i] = random(1, 6);// bigger = slower

      xpoffset[i] = random8();
    }
  }

  for (int i = 0; i < howmany; i++)
  {
    if ( flop[0])
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0 , drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) =  CHSV(fcolor[i], 255 - velo / 5, 255);

    else
      zeds(driftx +  (MATRIX_WIDTH - ((counter + xpoffset[i]) % MATRIX_WIDTH) / fpeed[i]) * (sin8(fcount[i] + h ) - 128.0) / 128.0, drifty +  (MATRIX_HEIGHT - ((counter + xpoffset[i]) % (MATRIX_HEIGHT)) / fpeed[i]) * (cos8(fcount[i] + h ) - 128.0) / 128.0) = CHSV(xblender, 255 - velo / 5, 255);


  }
  zeds(driftx , drifty ) = CRGB::White;
}

void nringer(int16_t i) {

  if (flop[0] && flop[1] && !flop[2])
  {
    DFCircle(driftx, drifty , i , CRGB::Black);
    DCircle(driftx, drifty , i, CRGB::White);
    
  }
  else
  {
       DFCircle(driftx, drifty , i , CRGB::Black);
    DCircle(driftx, drifty , i, CHSV(h * dot, 255 - velo / 5, 255));
 
  }
}

void drawtriangle()//solid triangle
{
  for (int i = 0; i < BIGGER/2; i ++)
  {
    DLine(i, i, MATRIX_WIDTH - i, i, CHSV(h + i * 4, 255 - velo / 5, 255));
    DLine(i, i, MIDLX, MATRIX_HEIGHT - i, CHSV(h + i * 4, 255 - velo / 5, 255));
    DLine(MATRIX_WIDTH - i, i, MIDLX, MATRIX_HEIGHT - i, CHSV(h + i * 4, 255 - velo / 5, 255));
  }
}

void triangle(int16_t xloc, int16_t yloc, int16_t bigg, int16_t angle, int16_t kolor)
{
  int16_t ax = xloc + bigg * (sin8(angle) - 128.0) / 128;
  int16_t ay = yloc + bigg * (cos8(angle) - 128.0) / 128;
  int16_t bx = xloc + bigg * (sin8(angle + 85) - 128.0) / 128;
  int16_t by = yloc + bigg * (cos8(angle + 85) - 128.0) / 128;
  int16_t cx = xloc + bigg * (sin8(angle - 85) - 128.0) / 128;
  int16_t cy = yloc + bigg * (cos8(angle - 85) - 128.0) / 128;
  DLine(ax, ay, bx, by, CHSV(kolor, 255 - (counter % 64), 255));
  DLine(cx, cy, bx, by, CHSV(kolor, 255 - (counter % 64), 255));
  DLine(ax, ay, cx, cy, CHSV(kolor, 255 - (counter % 64), 255));
}

void drawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler)// random multipoint star
{
  if (counter == 0) {
    //shifty = 3;//move quick
  }
  radius2 = 255 / points;
  for (int i = 0; i < points; i++)
  {
    DLine(xlocl + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
    DLine(xlocl + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
  }
}

void Adrawstar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler)// random multipoint star
{
  if (counter == 0) {
    //shifty = 3;//move quick
  }
  radius2 = 255 / points;
  for (int i = 0; i < points; i++)
  {
    DALine(xlocl + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
    DALine(xlocl + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CHSV(koler , 255 - velo / 5, 255));
  }
}

void whitestar(int16_t xlocl, int16_t ylocl, int16_t biggy, int16_t little, int16_t points, int16_t dangle, int16_t koler)// random multipoint star
{
  if (counter == 0) {
    //shifty = 3;//move quick
  }
  radius2 = 255 / points;
  for (int i = 0; i < points; i++)
  {
    DLine(xlocl + ((little * (sin8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 + radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CRGB::White);
    DLine(xlocl + ((little * (sin8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), ylocl + ((little * (cos8(i * radius2 - radius2 / 2 - dangle) - 128.0)) / 128), xlocl + ((biggy * (sin8(i * radius2 - dangle) - 128.0)) / 128), ylocl + ((biggy * (cos8(i * radius2 - dangle) - 128.0)) / 128), CRGB::White);
  }
}

void starz()//stars spin in a circle
{
  if (counter == 0) {
    howmany = random (3, 9);
    inner = random(BIGGER / 10, BIGGER / 4);
    radius2 = 255 / howmany;
  }

  xcen = MIDLX * (sin8(-2 * h - 85) - 128.0) / 128;
  ycen = MIDLY  * (cos8(-2 * h - 85 ) - 128.0) / 128;

  if (h % 16 == 0) {
    inner = inner + flipme;
    if (inner > MIDLY / 2 || inner < MIDLY / 5)
      flipme = -flipme;
  }

  for (int i = 0; i < howmany; i++)
    for (int j = 2; j < inner; j += 1)
      if (flop[5])
      {
        DLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 4 , 255));
        DLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 4 , 255));
      }
      else
      {
        DALine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
        DALine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
      }

  xcen = MIDLX  * (sin8(-2 * h + 85) - 128.0) / 128;
  ycen = MIDLY  * (cos8(-2 * h + 85) - 128.0) / 128;
  for (int i = 0; i < howmany; i++)
    for (int j = 2; j < inner; j += 2)
      if (flop[5])
      {
        DLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 3 , 255));
        DLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 3 , 255));
      }
      else
      {
        DALine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
        DALine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
      }
  xcen = MIDLX  * (sin8(-2 * h) - 128) / 128;
  ycen = MIDLY  * (cos8(-2 * h) - 128) / 128;

  for (int i = 0; i < howmany; i++)
    for (int j = 2; j < inner; j += 3)
      if (flop[5])
      {
        DLine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 3 , 255));
        DLine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 3 , 255));
      }
      else
      {
        DALine(driftx + xcen + ((j * (sin8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 + radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
        DALine(driftx + xcen + ((j * (sin8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), drifty + ycen + ((j * (cos8(i * radius2 - radius2 / 2 +  h) - 128.0)) / 128), driftx + xcen + ((MIDLX * (sin8(i * radius2 +  h) - 128.0)) / 128), drifty + ycen + ((MIDLY * (cos8(i * radius2 +  h) - 128.0)) / 128), CHSV(h - 85 + dot  * j , 255 - velo / 8 , 255));
      }
}

void starz3()// random multipoint star
{
  if (counter == 0) {
    dot = random(5, 9);
    howmany = random (3, 11);
    inner = random(BIGGER / 2 , BIGGER );
  }
  for (int i = 0; i < howmany; i++)
    for (int j = 0; j < inner; j++)
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


  for (int j = 0; j < inner; j++)
  {
    drawstar(driftx, drifty,  j, j / 3, dot2, h, h + j * dot );
  }


}


void spoker()//
{
  if (counter == 0) {
    howmany = random (3, 8);
    radius2 = BIGGER / howmany;

    poffset = random(60, 98);
  }
  for (int i = 0; i < howmany * 4; i++)
  {
    DLine(-MIDLX / 2,  -MIDLY / 2, (( beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64)) - 128.0)) / 128),  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64)) - 128.0)) / 128), CHSV(h  , 255 - velo / 5, 255));
    DLine(MATRIX_WIDTH + MIDLX / 2 , MATRIX_HEIGHT + MIDLY / 2,  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, dot2) * (sin8(i * radius2  +  (h % 64) + 128) - 128.0)) / 128),  ((beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, dot2) * (cos8(i * radius2  + (h % 64) + 128) - 128.0)) / 128), CHSV(h  + poffset , 255 - velo / 5, 255));
  }
}

void spoker3()//
{
  if (counter == 0) {
    howmany = random (3, 7);
    radius2 = BIGGER / howmany;
    poffset = random(60, 98);
  }
  for (int i = 0; i < howmany * 4; i++)
  {
    DLine(-MIDLX / 2,  -MIDLY / 2, (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64)) - 128.0)) / 128,  (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64)) - 128.0)) / 128, CHSV(h  , 255 - velo / 5, 255));
    DLine(MATRIX_WIDTH + MIDLX / 2 , MATRIX_HEIGHT + MIDLY / 2,  MATRIX_WIDTH - (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2  +  (h % 64) + 128) - 128.0)) / 128,  MATRIX_HEIGHT - (beatsin16(dot, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2  + (h % 64) + 128) - 128.0)) / 128, CHSV(h  + poffset / 2 , 255 - velo / 5, 255));

    DLine(-MIDLX / 2,  MATRIX_HEIGHT + MIDLY / 2, (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2 -  (h % 64) + 64) - 128.0)) / 128,  MATRIX_HEIGHT - (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2 -  (h % 64) + 64) - 128.0)) / 128, CHSV(h + poffset  , 255 - velo / 5, 255));
    DLine(MATRIX_WIDTH + MIDLX / 2 , -MIDLY / 2,  MATRIX_WIDTH - (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (sin8(i * radius2  +  (h % 64) - 64) - 128.0)) / 128,  (beatsin16(dot2, MATRIX_WIDTH / 2, MATRIX_WIDTH * 1.2, 0) * (cos8(i * radius2  + (h % 64) - 64) - 128.0)) / 128, CHSV(h  - poffset / 2 , 255 - velo / 5, 255));
  }
}

void circlearc()// arc of circles
{
  if (counter == 0)
  {
    howmany = random (3, 8);
    radius2 = BIGGER / howmany;//index angle
    radius3 = random (BIGGER * .75, BIGGER * 1.25);
    poffset = random(0, 6);//which version to play
    inner = random(6,  MIDLX / 2);
    directn = 1;

  }

  radius3 = beatsin16(5, MATRIX_WIDTH * .75, MATRIX_WIDTH * 1.5, 0);


  switch (poffset)
  {

    case 0:  // four -all headed in different direcitons solid
      for (int i = 0; i < howmany * 4; i++)
      {
        DFCircle( radius3 * (sin8(i * radius2 -  (h )) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  (h )) - 128.0) / 128, inner, CHSV(h + 8 * i, 255 - velo / 5, 255));
        if (flop[1])
          DFCircle( radius3 * (sin8(i * radius2 - (h  ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h  ) - 64) - 128.0) / 128, inner, CHSV(h + 8 * i + 64, 255 - velo / 5, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h  ) + 128) - 128.0) / 128, inner, CHSV(h + 4 * i  + 128, 255 - velo / 5, 255));
        if (flop[1])
          DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h  ) + 64) - 128.0) / 128, inner, CHSV(h + 4 * i  - 64, 255 - velo / 5, 255));
      }
      break;

    case 1:  // four -all headed in different direcitons hollow
      for (int i = 0; i < howmany * 4; i++)
      {
        DCircle( radius3 * (sin8(i * radius2 -  h % 64) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h % 64) - 128.0) / 128, inner, CHSV(h, 255 - velo / 5, 255));
        if (flop[1])
          DCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner, CHSV(h + 8 * i + 64, 255 - velo / 5, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h ) + 128) - 128.0) / 128, inner, CHSV(h + 4 * i  + 128, 255 - velo / 5, 255));
        if (flop[1])
          DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h  ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h  ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 5, 255));
      }
      break;

    case 2:// white rim 2 or 4
      for (int i = 0; i < howmany * 4; i++)
      {
        if (flop[1]) {
          DFCircle( radius3 * (sin8(i * radius2 -  h % 64) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h % 64) - 128.0) / 128, inner, CHSV(h, 255 - velo / 5, 255));
          DCircle( radius3 * (sin8(i * radius2 - h % 64) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h % 64) - 128.0) / 128, inner, CRGB::White);
        }
        DFCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 5, 255));
        DCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner, CRGB::White);

      }
      for (int i = 0; i < howmany * 4; i++)
      {
        if (flop[1]) {
          DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 5, 255));
          DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128, inner, CRGB::White);
        }
        DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 5, 255));
        DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner, CRGB::White);
      }

      break;
    case 3:// solids small sometimes with rings
      for (int i = 0; i < howmany * 4; i++)
      {
        DFCircle( radius3 * (sin8(i * radius2 -  h ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h ) - 128.0) / 128, inner / 2, CHSV(h, 255 - velo / 5, 255));

        if (flop[1])
          DCircle( radius3 * (sin8(i * radius2 -  h ) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h ) - 128.0) / 128, inner , CHSV(h - 32, 255 - velo / 5, 255));

        if (flop[2]) {
          DFCircle( radius3 * (sin8(i * radius2 - (h ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h  ) - 64) - 128.0) / 128, inner / 2, CHSV(h + 85, 255 - velo / 5, 255));

          if (flop[1])
            DCircle( radius3 * (sin8(i * radius2 - (h  ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h  ) - 64) - 128.0) / 128, inner, CHSV(h + 85 - 32, 255 - velo / 5, 255));
        }
      }
      for (int i = 0; i < howmany * 4; i++)
      {

        DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128, inner / 2, CHSV(h  - 85, 255 - velo / 5, 255));
        if (flop[1])
          DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128, inner , CHSV(h  - 85 - 32, 255 - velo / 5, 255));

        if (flop[2]) {
          DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner / 2, CHSV(h  - 85 + 32, 255 - velo / 5, 255));
          if (flop[1])
            DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner, CHSV(h  + -85 - 32, 255 - velo / 5, 255));
        }
      }

      break;
    case 4:// 8  opposite directions  littles
      for (int i = 0; i < howmany * 4; i++)
      {
        DFCircle( radius3 * (sin8(i * radius2 -  h % 64) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h % 64) - 128.0) / 128, inner / 2, CHSV(h, 255 - velo / 5, 255));
        if ( flop[0])
          DFCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner / 2, CHSV(h + 64, 255 - velo / 5, 255));
        else
          DFCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 5, 255));

      }
      for (int i = 0; i < howmany * 4; i++)
      {
        DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  - (h % 64 ) + 128) - 128.0) / 128, inner / 2, CHSV(h  + 128, 255 - velo / 5, 255));
        if (flop[0])
          DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner / 2, CHSV(h  - 64, 255 - velo / 5, 255));
        else
          DFCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  - (h % 64 ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 5, 255));
      }
      break;
    default:// four headed together
      for (int i = 0; i < howmany * 4; i++)
      {
        DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  + (h % 64 ) + 128) - 128.0) / 128,  MATRIX_HEIGHT - radius3 * (cos8(i * radius2  + (h % 64 ) + 128) - 128.0) / 128, inner, CHSV(h  + 128, 255 - velo / 5, 255));
        if (flop[1])
          DCircle( MATRIX_WIDTH - radius3 * (sin8(i * radius2  + (h % 64 ) + 64) - 128.0) / 128,  radius3 * (cos8(i * radius2  + (h % 64 ) + 64) - 128.0) / 128, inner, CHSV(h  - 64, 255 - velo / 5, 255));
      }
      for (int i = 0; i < howmany * 4; i++)
      {
        DCircle( radius3 * (sin8(i * radius2 -  h % 64) - 128.0) / 128,   radius3 * (cos8(i * radius2 -  h % 64) - 128.0) / 128, inner, CHSV(h, 255 - velo / 5, 255));
        if (flop[1])
          DCircle( radius3 * (sin8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128,   MATRIX_HEIGHT - radius3 * (cos8(i * radius2 - (h % 64 ) - 64) - 128.0) / 128, inner, CHSV(h + 64, 255 - velo / 5, 255));
      }

      break;
  }
}

void wheelz()// circles and stars filled circles in a circle
{
  if (counter == 0) {
    howmany = random (7, 22);
    inner = 8 + random(BIGGER / 4 , BIGGER / 2  );
    radius2 = 255 / howmany;
    dot2 = random(2, 6);
  }

  if (flop[3]) {
    driftx = MIDLX;
    drifty = MIDLY;
  }

  for (int i = 0; i < howmany * 2.5; i++)
  {
    if (inner - 2 * i > 0) {
      DFCircle(driftx + (((inner + dot2) * (sin8(i * radius2 / 2 -  h) - 128.0)) / 128), drifty + (((inner + dot2) * (cos8(i * radius2 / 2 -   h) - 128.0)) / 128), inner - 2 * i , CHSV(h  + radius2 * i , 230, 255));
      DCircle(driftx + (((inner + dot2) * (sin8(i * radius2 / 2 -  h) - 128.0)) / 128), drifty + (((inner + dot2) * (cos8(i * radius2 / 2 -   h) - 128.0)) / 128), inner - 2 * i , CHSV(h  + radius2 * i + 85 , 255, 255));
    }
  }

}

void wheelz2()// circles and stars filled circles in a circle
{
  if (counter == 0) {
    howmany = random (12, 25);
    inner = 4 + random(BIGGER / 4 , BIGGER / 2  );
    radius2 = 255 / howmany;
    dot2 = random(2, 8);
  }

  if (flop[3]) {
    driftx = MIDLX;
    drifty = MIDLY;
  }

  for (int i = 0; i < howmany * 2; i++)
  {
    if (inner - 2 * i > 0) {
      DFCircle(driftx + (((inner + dot2) * (sin8(i * radius2 / 2 -  h) - 128.0)) / 128), drifty + (((inner + dot2) * (cos8(i * radius2 / 2 -   h) - 128.0)) / 128), inner - 2 * i , CHSV(h  + radius2 * i , 255, 255));
      DCircle(driftx + (((inner + dot2) * (sin8(i * radius2 / 2 -  h) - 128.0)) / 128), drifty + (((inner + dot2) * (cos8(i * radius2 / 2 -   h) - 128.0)) / 128), inner - 2 * i , CHSV(h  + radius2 * i - 85 , 200, 255));
    }
  }

}

void swirly() {//not round orbits
  if (counter == 0)
  {
    howmany = random(BIGGER * 2 / 3, BIGGER * 3 / 2 );
    blender = random8();
    for ( int16_t i = 0; i < howmany; i++)
    {
      xfire[i] = random(4, MIDLX + 9); //xradius
      yfire[i] =  random(xfire[i] - 2, xfire[i] + 2); //yradius

      //if (i % 5 == 0)// make some round
      //yfire[i] = xfire[i];
      fpeed[i] = random(1, 8); //speed
      fcolor[i] = blender + random(84); //color
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
    xhowmany = random(BIGGER * 2 / 3, BIGGER * 3 / 2 );

    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(3, MIDLX + 19); //radius
      fpeed[i] = random(1, 6); //speed
      xpoffset[i] = xblender + random(94); //color
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
    xhowmany = random(BIGGER , BIGGER * 2);
    how = xhowmany;
    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(4, MIDLX * 3 / 2); //radius
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
      xslope[i] = MIDLX * 3 / 2;
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
    xhowmany = random(BIGGER * 1.5 , BIGGER * 2 );

    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(6, 18); //radius
      fpeed[i] = random(2, 16); //speed
      xpoffset[i] = blender + random(84); //color
      fvelo[i] = random8();
      fcountr[i] = random8(); //poffset
    }
  }
  EVERY_N_SECONDS(dot + 15) {
    flop[9] = !flop[9];
    /* if (flop[9])
      DFCircle(driftx, drifty,MIDLX / 7, CHSV(blender - 30, 155, 255));
      else
      DFCircle(driftx, drifty, 16 + MATRIX_WIDTH / 2, CHSV(blender - 30, 155, 255));*/
  }

  for ( int16_t i = 0; i < xhowmany; i++) {
    if (flop[9]) {
      if (counter % int( fpeed[i]  ) == 0  && xslope[i] < MIDLY + dot )
        xslope[i]++;
    }
    else if (counter % int( fpeed[i] ) == 0  && xslope[i] > dot + 1)
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
    xhowmany = random(BIGGER  , BIGGER * 2 );

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
  EVERY_N_SECONDS(20 + dot) {
    flop[9] = !flop[9];
    /* if (flop[9])
      DFCircle(driftx, drifty,MIDLX / 7, CHSV(blender - 30, 155, 255));
      else
      DFCircle(driftx, drifty, 16 + MATRIX_WIDTH / 2, CHSV(blender - 30, 155, 255));*/
  }

  for ( int16_t i = 0; i < xhowmany; i++) {
    if (flop[9]) {
      if (counter % int( fpeed[i]  ) == 0  && xslope[i] < MIDLX)
        xslope[i]++;
    }
    else if (counter % int( fpeed[i]) == 0  && xslope[i] > 6)
      xslope[i]--;




    zeds(driftx + xslope[i] * (sin8(h * fpeed[i] + fcountr[i]) - 128.0) / 128 , drifty + xslope[i] * (cos8(h * fpeed[i] + fcountr[i]) - 128.0) / 128) = CHSV(xpoffset[i], 255 - fvelo[i] / 3, 255);
    if (i % (13 + dot) == 0)
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
    xhowmany = random(BIGGER, BIGGER * 2);

    for ( int16_t i = 0; i < xhowmany; i++)
    {
      xslope[i] = random(4, MIDLX + 8 ); //radius
      fcolor[i] = xblender + random(80);
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
    howmany = random(BIGGER * 1.5, BIGGER * 2 ); //how many dots,
    if (!flop[2]) blender = 80;//flop[2] is set prior to deciding to run drops() , if false, makes for a bias towards green, otherwise blender is random8()
    else   blender = random8();


    for (int i = 0; i < howmany; i++) { //set up all the drops with initial values
      xslope[i] = random (MATRIX_WIDTH);//starting x location
      yslope[i] = MIDLY - random(MATRIX_HEIGHT); //starting y location, builds in some delay by putting them well off screen
      fpeed[i] = random(1, 7);// here higher ##s are slower
      fcountr[i] = random(2, 6);//  now long is the tail....
      fcolor[i] = blender + random(82); // picks colors close to blender
      fvelo[i] = random8();
    }
    if (!flop[1])fcolor[MIDLY] = blender - 152;
  }
  for (int i = 0 ; i < howmany; i++) {//draw all the drops
    if (counter % fpeed[i] == 0)//only move if it is your turn
      yslope[i] ++;                           //y position = current value of y + the random speed variable
    if (yslope[i] > MATRIX_HEIGHT + fcountr[i]) {              //If the y value plus the tail exceeds the height of the matrix, then give y a new value
      fcountr[i] = random(2, 5);//tail
      yslope[i] = 0 - random(5, MATRIX_HEIGHT / 4);// new location well off the edge
      xslope[i] = random (MATRIX_WIDTH);
      fpeed[i] = random(1, 7);//higher = slower
      //fcolor[i] = blender + random(40); // color
    }
    DLine(xslope[i] , yslope[i] , xslope[i] , yslope[i] - fcountr[i], CHSV(fcolor[i], 255- fvelo[i] / 5, 255)); //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
    if (i % 19 == 0)
      DLine(xslope[i] , yslope[i] , xslope[i] , yslope[i] - fcountr[i], CHSV(fcolor[i], 155- fvelo[i] / 5, 255));//toss in a white one every so often
  }
}

void drips() {
  if (counter == 0) {// counter increments with each pass through the loop, so this runs the first time you call drops()
    howmany =  random(BIGGER +8 , BIGGER * 2 ); //how many dots
    how = howmany;
    if (!flop[2]) blender = 60;//flop[2] is set prior to deciding to run drops() , if false, makes for a bias towards green, otherwise blender is random8()
    else if (flop[7]) blender = 200;


    for (int i = 0; i < howmany; i++) { //set up all the drops with initial values
      xslope[i] = random (MATRIX_WIDTH + 2 * dot) - dot; //starting x location
      yslope[i] = MIDLY - random(MATRIX_HEIGHT); //starting y location, builds in some delay by putting them well off screen
      fpeed[i] = random(1, 7);// here higher ##s are slower
      //  fcountr[i] = random(2, 5);//  now long is the tail....
      fcolor[i] = blender + random(109); // picks colors close to blender
      fvelo[i] = random8();
    }
    if (!flop[1]) fcolor[MIDLY] = blender - 158;
  }
  if (flop[5])
    howmany = beatsin16(dot / 2, MATRIX_WIDTH, how, 0);

  if (flop[9])
    poffset = h;
  else
    poffset = 0;
  for (int i = 0 ; i < howmany; i++) {//draw all the drops
    if (counter % fpeed[i] == 0)//only move if it is your turn
      yslope[i] ++;                           //y position = current value of y + the random speed variable
    if (yslope[i] > MATRIX_HEIGHT + 5) {              //If the y value plus the tail exceeds the height of the matrix, then give y a new value
      //fcountr[i] = random(2, 5);//tail
      yslope[i] = 0 - random(0, MATRIX_HEIGHT / 2);// new location well off the edge
      xslope[i] = random (MATRIX_WIDTH + 2 * dot) - dot;
      fpeed[i] = random(1, 7);//higher = slower
      fcolor[i] = blender + random(60); // color
    }
    if (flop[6]) {
      DCircle(xslope[i] , yslope[i] , dot + 1, CHSV(fcolor[i] + poffset, 255 - fvelo[i] / 4, 255)); //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
      if (i % MIDLX == 0)
        DCircle(xslope[i] , yslope[i] , dot + 1, CRGB::White); //toss in a white one every so often
    }
    else
    {
      DFCircle(xslope[i] , yslope[i] , dot + 1, CHSV(fcolor[i] + poffset, 255 - fvelo[i] / 2 , 255)); //Draw a line from (x0, y0) to (x0, y0+2) The y+2 will make the raindrop 3 pixels tall
      if (i % MIDLX == 0)
        DFCircle(xslope[i] , yslope[i] , dot + 1, CRGB::White); //toss in a white one every so often
    }
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
  for (int zx = 0; zx < MATRIX_WIDTH; zx++) {
    for (int zy = 0; zy < MATRIX_HEIGHT / 2; zy++) {
      zeds(zx, zy) = zeds(zx, zy + 1);
    }
    for (int zy = MATRIX_HEIGHT - 1; zy >= MIDLY; zy--) {
      zeds(zx, zy) = zeds(zx, zy - 1);
    }
  }

}

void dash() {
  if (counter == 0) {
    sdot = random(4, 12);
    poffset = 1;
  }
  if (counter % (sdot - 2) == 0)

  {
    poffset = 1 - poffset;
    for ( int16_t i = 0; i < MATRIX_WIDTH; i++) {
      if ((i + sdot / 2 * poffset) % sdot == 0) {
        DCircle(i, -sdot, sdot, CHSV(blender - i + 3 * h, 255 - velo / 7, 255));

      }
    }
  }
  zeds.ShiftUp();



}

void scales2() {
  if (counter == 0) {
    sdot = random(4, 12);
    poffset = 1;
  }
  if (counter % (sdot - 2) == 0)

  {
    poffset = 1 - poffset;
    for ( int16_t i = 0; i < MATRIX_WIDTH; i++) {
      if ((i + sdot / 2 * poffset) % sdot == 0) {
        DCircle(i, -sdot, sdot, CHSV(blender + h, 255 - velo / 7, 255));
        // DFRectangle(0, 0, MATRIX_WIDTH, 1, CRGB::Black);
      }
    }
  }
  zeds.ShiftUp();



}
void eastwestwind() {
  for (int zy = 0; zy < MATRIX_HEIGHT; zy++) {
    for (int zx = 0; zx < MIDLX; zx++)
      zeds(zx, zy) = zeds(zx + 1, zy );

    for (int zx = MATRIX_WIDTH - 1; zx >= MIDLX; zx--)
      zeds(zx, zy) = zeds(zx - 1, zy );
  }
}

void spiralwind() {
  if (counter % 2 == 0)
    for (int zx = 0; zx < MATRIX_WIDTH; zx++) {
      for (int zy = 0; zy < MATRIX_HEIGHT / 2; zy++) {
        zeds(zx, zy) = zeds(zx, zy + 1);
      }
      for (int zy = MATRIX_HEIGHT - 1; zy >= MIDLY; zy--) {
        zeds(zx, zy) = zeds(zx, zy - 1);
      }
    }
  else
    for (int zy = 0; zy < MATRIX_HEIGHT; zy++) {
      for (int zx = 0; zx < MIDLX; zx++)
        zeds(zx, zy) = zeds(zx + 1, zy );

      for (int zx = MATRIX_WIDTH - 1; zx >= MIDLX; zx--)
        zeds(zx, zy) = zeds(zx - 1, zy );
    }
}



void BouncingBalls(int Ballz) {
  if (counter == 0) {
    // solidblack();

    for (int i = 0 ; i < Ballz ; i++) {
      ClockTimeSinceLastBounce[i] = millis();

      Positiony[i] = 0;
      ImpactVelocity[i] = ImpactVelocityStart;
      TimeSinceLastBounce[i] = 0;
      Dampening[i] = 0.95 - 0.020 * i;
      fcolor[i] = blender + 24 * i;
      fvelo[i] = random8();
      fcountr[i] = random(3, 12); //radius
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
    DFCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i] - 18, 255 - fvelo[i] / 5, 255));
    if ( flop[1])
      DCircle(Positionx[i], Positiony[i], fcountr[i],  CHSV(fcolor[i], fvelo[i] / 6 + 188, 255));
    else
      DCircle(Positionx[i], Positiony[i], fcountr[i],  CRGB::White);

  }
}


void bouncingmix(int Ballz) {
  if (counter == 0) {

    for (int i = 0 ; i < Ballz ; i++) {
      ClockTimeSinceLastBounce[i] = millis();

      Positiony[i] = 0;
      ImpactVelocity[i] = ImpactVelocityStart * .93;
      TimeSinceLastBounce[i] = 0;
      Dampening[i] = 0.98 - 0.05 * i;
      fcolor[i] = blender + 64 * random(5);
      fvelo[i] = random8();
      fcountr[i] = random(4, 12); //radius
      Heighty[i] = StartHeighty;
      xfire[i] = MIDLX;
      kind[i] = i % 6;
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
    Positiony[i] = round( Heighty[i] * (MATRIX_HEIGHT) / StartHeighty) + 1;
  }
  //fill_solid( leds, NUM_LEDS, CRGB::Black);
  for (int i = 0 ; i < Ballz ; i++) {
    switch (kind[i]) {
      case 0:
        ADFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 250, 200));
        break;
      case 1:
        DFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 250, 255));

        DCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i] ,  CHSV(fcolor[i] + 128, 210, 255));
        break;
      case 2:
        DFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 250, 245));

        DCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i] ,  CHSV(fcolor[i] + 128, 230, 245));
        break;
      case 3:
        ADFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 250, 200));

        DCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i] ,  CRGB::White);
        break;
      case 4:
        ADFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 250, 200));
        DCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i] ,  CRGB::White);
        break;
      case 5:
        DFRectangle(Positionx[i] - fcountr[i]  , Positiony[i] - 1 , Positionx[i] + 0.5 * fcountr[i] , Positiony[i]  + 1.5 * fcountr[i] - 1 ,  CHSV(fcolor[i], 240, 255));
        DRectangle(Positionx[i] - fcountr[i]  , Positiony[i] - 1 , Positionx[i]  + 0.5 * fcountr[i] , Positiony[i]  + 1.5 * fcountr[i] - 1  ,  CRGB::White);
        break;
      default:
        DFCircle(Positionx[i], Positiony[i] + fcountr[i], fcountr[i],  CHSV(fcolor[i], 220, 255));
        break;
    }
  }
}

void snow(int16_t ccc) {
  if (counter == 0 || counter % pointyfix == 0)
  {
    flop[3] = !flop[3];
    solidblack();
    howmany = BIGGER * 1.5; //how many dots,
    for (int i = 0; i < howmany; i++)
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

  for (int i = 0 ; i < howmany; i++)
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
    howmany = random(BIGGER / 2, BIGGER  ); //how many dots,

    for (int i = 0; i < howmany; i++) { //set up all the drops with initial values

      if (flop[5])
        fcolor[i] = blender + random(80);
      else
        fcolor[i] = random8();
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


  for (int i = 0 ; i < howmany; i++) {//draw all the drops
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

    if (xslope[i] < MIDLX && yslope[i] >= MIDLY )//z3
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


    ADFCircle(xslope[i] , yslope[i], dot3 ,  CHSV(fcolor[i], 255 - fvelo[i] / 4, 255)); //
    if (i % (23) == 0)
      DFCircle(xslope[i] , yslope[i], dot3 ,  CRGB::White);


    if (abs(xslope[i] - MIDLX) < 2  && abs(yslope[i] - MIDLY ) < 1) {
      xslope[i] = 0;
      yslope[i] = 0;
      xvort[i] = 0;
      yvort[i] = 1;
    }
  }
}

void art() {
  if (flop[9]) h = 0;
  if (counter == 0 || counter % 300 == 0) {
    if (blender > 0) {
      blender = random8();
      velo = random8();
    }

    for (int16_t i = 1; i < 8; i++) {
      xvort[i] = random((i - 1) * MATRIX_WIDTH / 7 + 2, (i ) * MATRIX_WIDTH / 7 - 2);
      yvort[i] = random((i - 1) * MATRIX_HEIGHT / 7 + 2, (i ) * MATRIX_HEIGHT / 7 - 2);
      flop[i] =  false;
      if (random8() > 128)
        flop[i] =  true;


    }
    xvort[0] = 0;
    yvort[0] = 0;
    xvort[8] = MATRIX_WIDTH - 1;
    yvort[8] = MATRIX_HEIGHT - 1;
    yvort[9] = MATRIX_HEIGHT - 1;
    xvort[9] = MATRIX_WIDTH - 1;
    dot2 = random (3, 7);
    dot = random (3, 7);
  }
  if (counter == 0) {
    flop[3] = true;
    flop[4] = true;
  }
  if (flop[3] && flop[4]) {
    xvort[dot]  = beatsin8(2, xvort[dot - 1], xvort[dot + 1], 0);
    yvort[dot2] = beatsin8(3, yvort[dot2 - 1], yvort[dot2 + 1], 0);
  }
  DFRectangle(0, 0, MATRIX_WIDTH, MATRIX_HEIGHT, 0x969696);
  DLine(xvort[0], yvort[dot2], xvort[8], yvort[dot2], CRGB::Black);//j
  DLine(xvort[dot], yvort[0], xvort[dot], yvort[8], CRGB::Black); //j
  if (flop[1]) {
    DFRectangle(xvort[dot], yvort[dot2], xvort[dot + 2], yvort[dot2 + 2], CHSV(blender + h, 255 - velo / 3, 255)); //1
    DRectangle(xvort[dot], yvort[dot2], xvort[dot + 2], yvort[dot2 + 2], CRGB::Black);//1
  }
  else  {
    DFRectangle(xvort[dot], yvort[dot2], xvort[dot + 2], yvort[dot2 + 2], CHSV(blender + h + 170, 255 - velo / 3, 255)); //1
    DRectangle(xvort[dot], yvort[dot2], xvort[dot + 2], yvort[dot2 + 2], CRGB::Black);//1
  }

  if (flop[2]) {
    DFRectangle(xvort[dot], yvort[dot2], xvort[dot - 2], yvort[dot2 - 2],  CHSV(blender + h + 170, 255 - velo / 3, 255)); //1
    DRectangle(xvort[dot], yvort[dot2], xvort[dot - 2], yvort[dot2 - 2], CRGB::Black);//1
  }
  else  {
    DFRectangle(xvort[dot], yvort[dot2], xvort[dot - 2], yvort[dot2 - 2],  CHSV(blender + h + 55, 255 - velo / 3, 255)); //1
    DRectangle(xvort[dot], yvort[dot2], xvort[dot - 2], yvort[dot2 - 2], CRGB::Black); //1
  }

  if (flop[1] && flop[2]) {
    DFRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CHSV(blender + h + 55, 255 - velo / 3, 255)); //1
    DRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CRGB::Black);//1
  }
  else  {
    if (flop[1]) {
      DFRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CHSV(blender + h + 170, 255 - velo / 6, 255)); //1
      DRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CRGB::Black);//1
    }
    else
    {
      DFRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CHSV(blender + h, 255 - velo / 6, 255)); //1
      DRectangle(xvort[dot], yvort[dot2], xvort[0], yvort[8], CRGB::Black);//1
    }
  }
  DRectangle(0, 0, MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, 0x000000);


}



void beatsolid(int16_t brit)//colors rotate forward
{
  if (music.bighit && counter - hitcounter > 10) {
    phew = random8();
    hitcounter = counter;
  }
  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(phew, 255 - velo / 5, mmax(music.peakL, music.peakR) / 2.0 + 128));
}

void beatflash(int16_t brit)//colors rotate forward
{
  if (music.bighit && counter - hitcounter > 10) {
    phew = random8();
    hitcounter = counter;
  }
  DFRectangle(0 , 0,  MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1, CHSV(phew, 255 - velo / 5, brit));
}


void noisetest() {
  gmusic = false;
#ifdef TME_AUDIO
  if (audi)
    while (ETin.receiveData() == false)
    { digitalWrite(LATCH, LOW);
      delay(1);
      digitalWrite(LATCH, HIGH);
    }
#endif
  /*if (music.laudio[0] == 0) music.laudio[0] = music.laudio[1] ;*/
  if (music.peakL >= 8 || music.peakR >= 8)
    gmusic = true;
}

void fakenoise() {
  if (counter == 0)
  {
    for (int16_t i = 0; i < 32; i++)
      bpm[i] =   random8(4, 250);
  }
  for (int16_t i = 0; i <= 16; i++) {
    music.laudio[i] = beatsin8(bpm[i], 2, 60, bpm[i + 16] / 2);
    music.raudio[i] = beatsin8(bpm[i + 16], 2, 60, bpm[i] / 3);
    if (music.raudio[i] > maxiaud) maxiaud = music.raudio[i];
    if (music.laudio[i] > maxiaud) maxiaud = music.laudio[i];
  }

}

void audioprocess()
{
#ifdef TME_AUDIO
  quiet = 0;
  maxiaud = 0;
  digitalWrite(LATCH, HIGH);
  delay(1);
  EVERY_N_SECONDS(5) {
    noisetest();
  }
  if (gmusic == false)
    fakenoise();
  else
    while (ETin.receiveData() == false)
    { digitalWrite(LATCH, LOW);
      delay(1);
      digitalWrite(LATCH, HIGH);
    }
  /*if (music.laudio[0] == 0) music.laudio[0] = music.laudio[1] ;*/
  for (int16_t ppp = 0; ppp < 16; ppp ++)
  {



    LLaudio[ppp * 4] =  music.laudio[ppp];
    LLaudio[ppp * 4 + 1] =  music.laudio[ppp] * .75 + .25 * music.laudio[ppp + 1] ;
    LLaudio[ppp * 4 + 2] = music.laudio[ppp] * 0.5 + music.laudio[ppp + 1] * 0.5 ;
    LLaudio[ppp * 4 + 3] =  music.laudio[ppp] * 0.25 + music.laudio[ppp + 1] * 0.75;

    RRaudio[ppp * 4] =  music.raudio[ppp];
    RRaudio[ppp * 4 + 1] =  music.raudio[ppp] * .75 + .25 * music.raudio[ppp + 1] ;
    RRaudio[ppp * 4 + 2] = music.raudio[ppp] * 0.5 + music.raudio[ppp + 1] * 0.5 ;
    RRaudio[ppp * 4 + 3] =  music.raudio[ppp] * 0.25 + music.raudio[ppp + 1] * 0.75;
  }

  LLaudio[63] = music.laudio[16];
  RRaudio[63] = music.raudio[16];

  quiet = mmax(music.peakL, music.peakR);
  maxiaud =  quiet / 4;
  if (maxiaud > bigmax)
    bigmax = maxiaud;
  if (quiet <= 60 ) //
    quietcount++;

  else
  {
    quietcount = 0;
    // Serial.println("q# reset");

  }
  if (quietcount > 20 && counter > 1800) {
    nextsong = true;
    quietcount = 0;
  }
  //digitalWrite(LATCH, LOW);
#else // TME_AUDIO
  fakenoise();
#endif
}

void DFCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col)
{
  int16_t x = r;
  int16_t y = 0;
  int16_t e = 1 - x;
  while (x >= y)
  {
    DLine(xc + x, yc + y, xc - x, yc + y, Col);
    DLine(xc + y, yc + x, xc - y, yc + x, Col);
    DLine(xc - x, yc - y, xc + x, yc - y, Col);
    DLine(xc - y, yc - x, xc + y, yc - x, Col);
    ++y;
    if (e >= 0)
    {
      --x;
      e += 2 * ((y - x) + 1);
    }
    else
      e += (2 * y) + 1;
  }
}

void ADFCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col)
{
  int16_t x = r;
  int16_t y = 0;
  int16_t e = 1 - x;
  while (x >= y)
  {
    DALine(xc + x, yc + y, xc - x, yc + y, Col);
    DALine(xc + y, yc + x, xc - y, yc + x, Col);
    DALine(xc - x, yc - y, xc + x, yc - y, Col);
    DALine(xc - y, yc - x, xc + y, yc - x, Col);
    ++y;
    if (e >= 0)
    {
      --x;
      e += 2 * ((y - x) + 1);
    }
    else
      e += (2 * y) + 1;
  }
}

void DLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  if (abs(dx) >= abs(dy))
  {
    int32_t y = ((int32_t)y0 << 16) + 32768;
    // Support a single dot line without diving by 0 and crashing below
    if (!dx) {
      zeds(x0, (y >> 16)) = Col;
    } else {
      int32_t f = ((int32_t)dy << 16) / (int32_t)abs(dx);
      if (dx >= 0)
      {
        for (; x0 <= x1; ++x0, y += f)
          zeds(x0, (y >> 16)) = Col;
      }
      else
      {
        for (; x0 >= x1; --x0, y += f)
          zeds(x0, (y >> 16)) = Col;
      }
    }
  }
  else
  {
    int32_t f = ((int32_t)dx << 16) / (int32_t)abs(dy);
    int32_t x = ((int32_t)x0 << 16) + 32768;
    if (dy >= 0)
    {
      for (; y0 <= y1; ++y0, x += f)
        zeds((x >> 16), y0) = Col;
    }
    else
    {
      for (; y0 >= y1; --y0, x += f)
        zeds((x >> 16), y0) = Col;
    }
  }
}

void DALine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  int16_t dx = x1 - x0;
  int16_t dy = y1 - y0;
  if (abs(dx) >= abs(dy))
  {
    int32_t y = ((int32_t)y0 << 16) + 32768;
    // Support a single dot line without diving by 0 and crashing below
    if (!dx) {
      zeds(x0, (y >> 16)) += Col;
    } else {
      int32_t f = ((int32_t)dy << 16) / (int32_t)abs(dx);
      if (dx >= 0)
      {
        for (; x0 <= x1; ++x0, y += f)
          zeds(x0, (y >> 16)) += Col;
      }
      else
      {
        for (; x0 >= x1; --x0, y += f)
          zeds(x0, (y >> 16)) += Col;
      }
    }
  }
  else
  {
    int32_t f = ((int32_t)dx << 16) / (int32_t)abs(dy);
    int32_t x = ((int32_t)x0 << 16) + 32768;
    if (dy >= 0)
    {
      for (; y0 <= y1; ++y0, x += f)
        zeds((x >> 16), y0) += Col;
    }
    else
    {
      for (; y0 >= y1; --y0, x += f)
        zeds((x >> 16), y0) += Col;
    }
  }
}
void DRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  DLine(x0, y0, x0, y1, Col);
  DLine(x0, y1, x1, y1, Col);
  DLine(x1, y1, x1, y0, Col);
  DLine(x1, y0, x0, y0, Col);
}

void ADRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  DALine(x0, y0, x0, y1, Col);
  DALine(x0, y1, x1, y1, Col);
  DALine(x1, y1, x1, y0, Col);
  DALine(x1, y0, x0, y0, Col);
}

void DCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col)
{
  int16_t x = -r;
  int16_t y = 0;
  int16_t e = 2 - (2 * r);
  do
  {
    zeds(xc + x, yc - y) = Col;
    zeds(xc - x, yc + y) = Col;
    zeds(xc + y, yc + x) = Col;
    zeds(xc - y, yc - x) = Col;
    int16_t _e = e;
    if (_e <= y)
      e += (++y * 2) + 1;
    if ((_e > x) || (e > y))
      e += (++x * 2) + 1;
  }
  while (x < 0);
}

void ADCircle(int16_t xc, int16_t yc, uint16_t r, CRGB Col)
{
  int16_t x = -r;
  int16_t y = 0;
  int16_t e = 2 - (2 * r);
  do
  {
    zeds(xc + x, yc - y) += Col;
    zeds(xc - x, yc + y) += Col;
    zeds(xc + y, yc + x) += Col;
    zeds(xc - y, yc - x) += Col;
    int16_t _e = e;
    if (_e <= y)
      e += (++y * 2) + 1;
    if ((_e > x) || (e > y))
      e += (++x * 2) + 1;
  }
  while (x < 0);
}

void DFRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  int16_t y = mmin(y0, y1);
  for (int16_t c = abs(y1 - y0); c >= 0; --c, ++y)
    DLine(x0, y, x1, y, Col);
}

void ADFRectangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, CRGB Col)
{
  int16_t y = mmin(y0, y1);
  for (int16_t c = abs(y1 - y0); c >= 0; --c, ++y)
    DALine(x0, y, x1, y, Col);
}

void fire2() {
  if (counter == 0) {

    dot = random(7);
    switch (dot) {
      case 0:
        thepal = pal1;
        break;

      case 1:
        thepal = pal3;
        break;
      case 2:
        thepal = pal4;
        break;
      case 3:
        thepal = pal5;
        break;
      case 4:
        thepal = pal6;
        break;

      default:
        thepal = pal2;
        break;

    }// switch
  }
  //counter 0
  int  ace = millis();
  for (int i = 0; i < MATRIX_WIDTH; i++)
    for (int j = 0; j < MATRIX_HEIGHT; j++)
      zeds(MATRIX_WIDTH - 1 - i, MATRIX_HEIGHT - 1 - j) = ColorFromPalette (thepal, qsub8 (inoise8 (i * 50 , j * 50 + ace , ace / 3), abs8(j - (MATRIX_HEIGHT - 1)) * 255 / (MATRIX_HEIGHT - 1)), 255);

  if (flop[2])//lava
    zeds.VerticalMirror();
}//end fire2

void stopred()
{
  if ((pattern > 166 && pattern < 173) || (pattern > 174 && pattern < 184))
    if (zeds[0, 0] > 0 && zeds[0, MATRIX_HEIGHT - 1] > 0 && zeds[MATRIX_WIDTH - 1, 0] > 0 && zeds[MATRIX_WIDTH - 1, MATRIX_HEIGHT - 1] > 0) {
      Serial.println("avoiding the red");
      newpattern();
    }
}
