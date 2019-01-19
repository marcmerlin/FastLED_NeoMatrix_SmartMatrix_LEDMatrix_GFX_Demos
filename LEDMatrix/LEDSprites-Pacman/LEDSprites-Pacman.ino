#define LEDMATRIX
#include "config.h"
#include <LEDSprites.h>
#define leds ledmatrix

cLEDSprites Sprites(&leds);

#define MY_SPRITE_WIDTH  11
#define MY_SPRITE_HEIGHT 10
#define PACMAN_FRAMES  3
#define PINKY_FRAMES  2

#define maxx (MATRIX_WIDTH - MY_SPRITE_WIDTH - 1)
#define maxy (MATRIX_HEIGHT - MY_SPRITE_HEIGHT -1)

// How long before the pill appears?
uint8_t pacman_loops = 3;

#define POWER_PILL_SIZE	4
const uint8_t PowerPillData[] = 
{
  B8_1BIT(01100000),
  B8_1BIT(11110000),
  B8_1BIT(11110000),
  B8_1BIT(01100000)
};
const struct CRGB PowerPillColTab[] =  {  CRGB(48, 48, 255)  };

const uint8_t PacmanRightData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(11111000),B8_2BIT(00000000),
  B8_2BIT(21111110),B8_2BIT(00000000),
  B8_2BIT(01111111),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(11111200),B8_2BIT(00000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const uint8_t PacmanRightMask[] = 
{
  // Pacman Open
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(00000000),
  B8_1BIT(11111110),B8_1BIT(00000000),
  B8_1BIT(11111000),B8_1BIT(00000000),
  B8_1BIT(11111000),B8_1BIT(00000000),
  B8_1BIT(11111110),B8_1BIT(00000000),
  B8_1BIT(01111111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Half
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111100),B8_1BIT(00000000),
  B8_1BIT(11111100),B8_1BIT(00000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Closed
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000)
};
const struct CRGB PacmanRightColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t PinkyData[] = 
{
  // Pinky Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Pinky Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122212),B8_2BIT(22000000),
  B8_2BIT(11122312),B8_2BIT(23100000),
  B8_2BIT(11122212),B8_2BIT(22100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000),
};
const uint8_t PinkyMask[] = 
{
  // Pinky Frame 1
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11001110),B8_1BIT(01100000),
  // Pinky Frame 2
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(10011011),B8_1BIT(00100000),
};
const struct CRGB PinkyColTab[] =  {  CRGB(255, 0, 0), CRGB(255, 255, 255), CRGB(0, 0, 255)  };

const uint8_t PacmanLeftData[] = 
{
  // Pacman Open
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00000011),B8_2BIT(11100000),
  B8_2BIT(00001111),B8_2BIT(11200000),
  B8_2BIT(00011111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Half
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(00000211),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000),
  // Pacman Closed
  B8_2BIT(00021112),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(21111111),B8_2BIT(11200000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(00021112),B8_2BIT(00000000)
};
const uint8_t PacmanLeftMask[] = 
{
  // Pacman Open
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(11000000),
  B8_1BIT(00001111),B8_1BIT(11100000),
  B8_1BIT(00000011),B8_1BIT(11100000),
  B8_1BIT(00000011),B8_1BIT(11100000),
  B8_1BIT(00001111),B8_1BIT(11100000),
  B8_1BIT(00011111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Half
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(00000111),B8_1BIT(11100000),
  B8_1BIT(00000111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000),
  // Pacman Closed
  B8_1BIT(00011111),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(00011111),B8_1BIT(00000000)
};
const struct CRGB PacmanLeftColTab[] =  {  CRGB(255, 255, 0), CRGB(100, 100, 0), CRGB(255, 255, 255)  };

const uint8_t GhostData[] = 
{
  // Ghost Frame 1
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11001110),B8_2BIT(01100000),
  // Ghost Frame 2
  B8_2BIT(00001110),B8_2BIT(00000000),
  B8_2BIT(00111111),B8_2BIT(10000000),
  B8_2BIT(01111111),B8_2BIT(11000000),
  B8_2BIT(01122122),B8_2BIT(11000000),
  B8_2BIT(11122122),B8_2BIT(11100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(11131313),B8_2BIT(11100000),
  B8_2BIT(11313131),B8_2BIT(31100000),
  B8_2BIT(11111111),B8_2BIT(11100000),
  B8_2BIT(10011011),B8_2BIT(00100000)
};
const uint8_t GhostMask[] = 
{
  // Ghost Frame 1
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11001110),B8_1BIT(01100000),
  // Ghost Frame 2
  B8_1BIT(00001110),B8_1BIT(00000000),
  B8_1BIT(00111111),B8_1BIT(10000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(01111111),B8_1BIT(11000000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(11111111),B8_1BIT(11100000),
  B8_1BIT(10011011),B8_1BIT(00100000)
};
const struct CRGB GhostColTab[] =  {  CRGB(0, 0, 255), CRGB(255, 255, 255), CRGB(255, 90, 120)  };

const uint8_t S200Data[] = 
{
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(01000100),B8_1BIT(01000000),
  B8_1BIT(10101010),B8_1BIT(10100000),
  B8_1BIT(10101010),B8_1BIT(10100000),
  B8_1BIT(00101010),B8_1BIT(10100000),
  B8_1BIT(01001010),B8_1BIT(10100000),
  B8_1BIT(11100100),B8_1BIT(01000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000)
};
const struct CRGB S200ColTab[] =  {  CRGB(0, 192, 255)  };

const uint8_t EyesData[] = 
{
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(11111011),B8_2BIT(11100000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(11122011),B8_2BIT(12200000),
  B8_2BIT(01110001),B8_2BIT(11000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000),
  B8_2BIT(00000000),B8_2BIT(00000000)
};
const uint8_t EyesMask[] = 
{
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(01110001),B8_1BIT(11000000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(11111011),B8_1BIT(11100000),
  B8_1BIT(01110001),B8_1BIT(11000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000),
  B8_1BIT(00000000),B8_1BIT(00000000)
};
const struct CRGB EyesColTab[] =  {  CRGB(255, 255, 255), CRGB(0, 0, 255), CRGB(0, 0, 0)  };

cSprite SprPacmanRight(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanRightData, PACMAN_FRAMES, _2BIT, PacmanRightColTab, PacmanRightMask);
cSprite SprPinky(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PinkyData, PINKY_FRAMES, _2BIT, PinkyColTab, PinkyMask);
cSprite SprPacmanLeft(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, PacmanLeftData, PACMAN_FRAMES, _2BIT, PacmanLeftColTab, PacmanLeftMask);
cSprite SprGhost(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, GhostData, PINKY_FRAMES, _2BIT, GhostColTab, GhostMask);
cSprite SprPill(POWER_PILL_SIZE, POWER_PILL_SIZE, PowerPillData, 1, _1BIT, PowerPillColTab, PowerPillData);
cSprite Spr200(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, S200Data, 1, _1BIT, S200ColTab, S200Data);
cSprite SprEyes(MY_SPRITE_WIDTH, MY_SPRITE_HEIGHT, EyesData, 1, _2BIT, EyesColTab, EyesMask);


void setup()
{
    matrix_setup();

    // Rate is a divider, higher rate is slower.
    SprPacmanRight.SetPositionFrameMotionOptions(0/*X*/, -10/*Y*/, 0/*Frame*/, 4/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
    Sprites.AddSprite(&SprPacmanRight);
    SprPinky.SetPositionFrameMotionOptions(     0 /*X*/, -62/*Y*/, 0/*Frame*/, 2/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 1/*YChange*/, 1/*YRate*/, SPRITE_Y_KEEPIN | SPRITE_DETECT_EDGE);
    Sprites.AddSprite(&SprPinky);
    Serial.print("Top X for sprite: ");
    Serial.print(maxx);
    Serial.print(". Top Y for sprite: ");
    Serial.println(maxy);
}

void loop()
{
    static uint8_t inmaze = 0;
    static uint8_t pinmaze = 0;
    static uint8_t ginmaze = 0;
    static bool ghostdead = false;

    uint8_t pcmr = SprPacmanRight.GetFlags();

    int8_t pcmrx = SprPacmanRight.m_X;
    int8_t pcmry = SprPacmanRight.m_Y;
    int8_t pcmlx = SprPacmanLeft.m_X;
    int8_t pcmly = SprPacmanLeft.m_Y;
    int8_t gx = SprGhost.m_X;
    int8_t gy = SprGhost.m_Y;
    int8_t px = SprPinky.m_X;
    int8_t py = SprPinky.m_Y;
    int8_t ex = SprEyes.m_X;
    int8_t ey = SprEyes.m_Y;

    matrix->clear();
    leds.DrawLine (leds.Width()/2, MY_SPRITE_HEIGHT, leds.Width()/2, leds.Height() - 1 - MY_SPRITE_HEIGHT, CRGB::Grey);
    Sprites.UpdateSprites();
    Sprites.DetectCollisions();
    Serial.print("rx: ");
    Serial.print(pcmrx);
    Serial.print(" ry: ");
    Serial.print(pcmry);
    Serial.print(" / ");

    Serial.print("lx: ");
    Serial.print(pcmlx);
    Serial.print(" ly: ");
    Serial.print(pcmly);
    Serial.print(" / ");

    Serial.print("px: ");
    Serial.print(px);
    Serial.print(" py: ");
    Serial.print(py);
    Serial.print(" | ");

    Serial.print("gx: ");
    Serial.print(gx);
    Serial.print(" gy: ");
    Serial.print(gy);
    Serial.print(" / ");

    Serial.print(pcmr & SPRITE_EDGE_X_MIN);
    Serial.print(pcmr & SPRITE_EDGE_X_MAX);
    Serial.print(pcmr & SPRITE_EDGE_Y_MIN);
    Serial.print(pcmr & SPRITE_EDGE_Y_MAX);
    Serial.print(" ");
    Serial.print(pcmr, HEX);
    Serial.print(" ");
    Serial.println(inmaze);

    // So you are going to ask "why are you not using the edge detection code"
    // First, SPRITE_X|Y_KEEPIN does not work if you want your sprite to go around
    // the screen like I'm doing
    // Second, the edge detection is buggy-ish and triggered either right at the 
    // boundary or one pixel too late. That's not a big deal if you use it to
    // bounce back, but it breaks things if you change direction at the edge, like
    // I'm doing.
    // On top of that, I have a small state machine to keep track of what kind
    // of bouncing I'm doing depending on which time around it is, so there you go
    // the code below is what I need...

    // void SetMotion XRate, int8_t YChange, uint8_t YRate);
    // Sets the X & Y change values and the rate of change. If the XRate and/or
    // YRate is '0' then the appropriate axis motion will be disabled.
    // The higher the rate, the more the sprite slows down
    if (gy < 1 && ginmaze == 6) {
	Serial.println("Ghost hit bottom/left wall2");
	SprGhost.SetMotion(1, 2, 0, 0);
	ginmaze = 7;
    }
    else if (gx > maxx && ginmaze == 7) {
	Serial.println("Ghost hit bottom/right wall2");
	SprGhost.SetMotion(0, 0, 1, 2);
	ginmaze = 8;
    }
    else if (gy > maxy && ginmaze == 8) {
	SprGhost.SetMotion(-1, 2, 0, 0);
	Serial.println("Ghost hit top/right wall2");
	ginmaze = 9;
    }
    else if (gx < 1 && ginmaze == 9) {
	Serial.println("Ghost hit top/left wall3");
	SprGhost.SetMotion(0, 0, -1, 2);
	ginmaze = 10;
    }


    if (pcmry >= maxy && !inmaze) inmaze = 1;
    if (pcmry >= maxy && inmaze == 1) {
	SprPacmanRight.SetMotion(1, 1, 0, 0);
	Serial.println("Pacman hit top/left wall");
	inmaze = 2;
    }
    else if (pcmrx >= maxx && inmaze == 2) {
	Serial.println("Pacman hit top/right wall");
	SprPacmanRight.SetMotion(0, 0, -1, 1);
	inmaze = 3;
    }
    else if (pcmry <= 1 && inmaze == 3) {
	Serial.println("Pacman hit bottom/right wall");
	SprPacmanRight.SetMotion(-1, 1, 0, 0);
	inmaze = 4;
	if (pacman_loops == 0) {
	    SprPill.SetPositionFrameMotionOptions(3 /*X*/, MATRIX_HEIGHT - 7/*Y*/, 0/*Frame*/, 0/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, 0/*YChange*/, 0/*YRate*/, 0);
	    Sprites.AddSprite(&SprPill);
	} else { pacman_loops--; }
    }
    else if (pcmrx <= 1 && inmaze == 4) {
	Serial.println("Pacman hit bottom/left wall");
	SprPacmanRight.SetMotion(0, 0, 1, 1);
	inmaze = 1;
    }

    if (inmaze<6 && SprPacmanRight.GetFlags() & SPRITE_COLLISION)
    {
	Serial.println("Pill Collision");
	inmaze = 6;
	ginmaze = 6;
	Sprites.RemoveSprite(&SprPinky);
	Sprites.RemoveSprite(&SprPacmanRight);
	Sprites.RemoveSprite(&SprPill);
	SprPacmanLeft.SetPositionFrameMotionOptions(SprPacmanRight.m_X, SprPacmanRight.m_Y, 0/*Frame*/, 4/*FrameRate*/, 0/*XChange*/, 0/*XRate*/, -1/*YChange*/, 1/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
	Sprites.AddSprite(&SprPacmanLeft);
	SprGhost.SetPositionFrameMotionOptions(SprPinky.m_X, SprPinky.m_Y, 0/*Frame*/, 3/*FrameRate*/, 0/*XChange*/, 2/*XRate*/, -1/*YChange*/, 2/*YRate*/, SPRITE_DETECT_EDGE | SPRITE_DETECT_COLLISION);
	Sprites.AddSprite(&SprGhost);
    }
    else if (pcmly <= 1 && inmaze == 6) {
	Serial.println("Pacman hit bottom/left wall2");
	SprPacmanLeft.SetMotion(1, 1, 0, 0);
	inmaze = 7;
    }
    else if (pcmlx >= maxx && inmaze == 7) {
	Serial.println("Pacman hit bottom/right wall2");
	SprPacmanLeft.SetMotion(0, 0, 1, 1);
	inmaze = 8;
    }
    else if (pcmly >= maxy && inmaze == 8) {
	SprPacmanLeft.SetMotion(-1, 1, 0, 0);
	Serial.println("Pacman hit top/right wall2");
	inmaze = 9;
    }
    else if (pcmlx <= 1 && inmaze == 9) {
	Serial.println("Pacman hit top/left wall3");
	SprPacmanLeft.SetMotion(0, 0, -1, 1);
	inmaze = 10;
    }


    if (py >= maxy && !pinmaze) pinmaze = 1;
    if (py >= maxy && pinmaze == 1) {
	SprPinky.SetMotion(1, 1, 0, 0);
	Serial.println("Pinky hit top/left wall");
	pinmaze = 2;
    }
    else if (px >= maxx && pinmaze == 2) {
	Serial.println("Pinky hit top/right wall");
	SprPinky.SetMotion(0, 0, -1, 1);
	pinmaze = 3;
    }
    else if (py <= 1 && pinmaze == 3) {
	Serial.println("Pinky hit bottom/right wall");
	SprPinky.SetMotion(-1, 1, 0, 0);
	pinmaze = 4;
    }
    else if (px <= 1 && pinmaze == 4) {
	Serial.println("Pinky hit bottom/left wall");
	SprPinky.SetMotion(0, 0, 1, 1);
	pinmaze = 1;
    }

    if (!ghostdead && SprGhost.GetFlags() & SPRITE_COLLISION)
    {
	Serial.println("Ghost killed");
	Sprites.RemoveSprite(&SprGhost);
	Spr200.SetPositionFrameMotionOptions(SprGhost.m_X+1, SprGhost.m_Y, 0, 0, 0, 0, 0, 0);
	Sprites.AddSprite(&Spr200);

	ghostdead = true;
	SprEyes.SetPositionFrameMotionOptions(SprGhost.m_X, SprGhost.m_Y, 0, 0, 0, 0, -1, 3, 0);
	Sprites.AddSprite(&SprEyes);
    }

    if (ghostdead && SprEyes.m_Y < 1) {
	Serial.println("Eye Bounce #1");
	SprEyes.m_Y = 1;
	SprEyes.SetMotion(0, 0, 1, 3);
    }
    else if (SprEyes.m_Y > MATRIX_HEIGHT) {
	Serial.println("Ghost eyes left the building, stopping");
	delay(10000);
    }

    Sprites.RenderSprites();
    matrix->show();
    delay(30);
}
// vim:sts=4:sw=4
