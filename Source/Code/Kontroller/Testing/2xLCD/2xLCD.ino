#include "Display.h"
#define BUTTON1_PIN 9
#define BUTTON2_PIN 8

const int rs1 = 15, en1 = 14, d41 = 13, d51 = 12, d61 = 11, d71 = 10;
const int rs2 = 16, en2 = 17, d42 = 18, d52 = 19, d62 = 20, d72 = 21;

Display lcd1(rs1, en1, d41, d51, d61, d71, 20, 4);
Display lcd2(rs2, en2, d42, d52, d62, d72, 16, 2);

void setup() {
  Serial.begin(9600);
  lcd1._init();
  lcd2._init();
}

void loop() {
  lcd1._loop();
  lcd2._loop();
}
