/*
  Quick demo of major drawing operations on a single DMD
 */

#include <SPI.h>
#include <DMD2.h>
#include <fonts/ARIAL_BLACK_16_H>
#define pin_A 16
#define pin_B 12
#define pin_sclk 0
#define pin_clk 14
#define pin_r 13
#define pin_noe 15

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
SPIDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH, pin_noe, pin_A, pin_B, pin_sclk); // DMD controls the entire display

void setup() {
  dmd.setBrightness(255);
  dmd.selectFont(ARIAL_BLACK_16_H);
  dmd.begin(); 

  // Circle with a line at a tangent to it
  dmd.drawCircle(24,8,5);
  dmd.drawLine(14,9,28,15);

  // Outline box containing a filled box
  dmd.drawBox(6,10,11,15);
  dmd.drawFilledBox(8,12,9,13);
}

int n = 123;

// the loop routine runs over and over again forever:
void loop() {
  dmd.drawString(0,0,String(n));
  n = n + 1;
  delay(1000);

  if(n % 2 == 0) {
    dmd.drawFilledBox(0,11,4,15, GRAPHICS_OFF);
    dmd.drawBox(0,11,4,15);
  } else {
    dmd.drawFilledBox(0,11,4,15);
  }
}
