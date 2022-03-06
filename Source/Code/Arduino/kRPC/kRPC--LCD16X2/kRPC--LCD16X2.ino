/*
 *  This test code uses one LCD Display and a joystick, to control the display
 *  
 */


#include <krpc.h>
#include <krpc/services/krpc.h>

#include <LiquidCrystal.h>

//Hardware Serial for kRPC
HardwareSerial * conn;

// Set up LCD LiquidCrystal 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Y_PIN A0
#define X_PIN A1

void setup() {
  
  conn = &Serial;
  // Open the serial port connection
  krpc_open(&conn, NULL);
  // Set up communication with the server
  krpc_connect(conn, "Arduino Example");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  lcd_print_all_page();

  pinMode(Y_PIN, INPUT);
  pinMode(X_PIN, INPUT);
}

int last_mill = millis();
int last_x_read = analogRead(X_PIN);
int last_y_read = analogRead(Y_PIN);

#define _update_delay 100
#define JOYSTICK_CHECK_HIGH_THRESHOLD 700
#define JOYSTICK_CHECK_LOW_THRESHOLD 300

void loop() {

  int relative_x = analogRead(X_PIN) - last_x_read;
  int relative_y = analogRead(Y_PIN) - last_y_read;
  
  if (analogRead(X_PIN) > JOYSTICK_CHECK_HIGH_THRESHOLD && millis() - last_mill >  _update_delay)
  {
    lcd.scrollDisplayLeft();
    last_mill = millis();
  }
  
  if (analogRead(X_PIN) < JOYSTICK_CHECK_LOW_THRESHOLD && millis() - last_mill > _update_delay)
  {
    lcd.scrollDisplayRight();
    last_mill = millis();
  }
}

void lcd_print_all_page(){
  // print all static screen interface
  lcd.setCursor(1, 2);
  lcd.print("Kontroller - Kerbal Space Program");
  lcd.setCursor(40, 2);
  lcd.print("this works!");
}
