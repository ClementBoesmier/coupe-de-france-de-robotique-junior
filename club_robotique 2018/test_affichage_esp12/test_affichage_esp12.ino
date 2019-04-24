#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#define pin_A 16
#define pin_B 12
#define pin_sclk 0
#define pin_clk 14
#define pin_r 13
#define pin_noe 15

#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
SPIDMD dmd(DISPLAYS_WIDE, DISPLAYS_HIGH, pin_noe, pin_A, pin_B, pin_sclk);


int score(0);


void setup() {
  dmd.setBrightness(255);
  dmd.selectFont(SystemFont5x7);
  dmd.begin(); 
}

void loop() {
  dmd.drawString(1,3,String(score));
  delay(100);
  score++;
}
