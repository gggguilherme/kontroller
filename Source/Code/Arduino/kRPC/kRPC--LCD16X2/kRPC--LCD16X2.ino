/*
 *  This test code uses one LCD Display and a joystick, to control the display
 */

#include <krpc.h>
#include <krpc/services/krpc.h>
#include <krpc/services/space_center.h>

#include <LiquidCrystal.h>

//Hardware Serial for kRPC
HardwareSerial * conn;

// Set up LCD LiquidCrystal 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define Y_PIN A0
#define X_PIN A1

krpc_SpaceCenter_Vessel_t vessel;
krpc_SpaceCenter_Flight_t flight;

double vessel_altitude;

void setup() {
  
  conn = &Serial;
  // Open the serial port connection
  krpc_open(&conn, NULL);
  // Set up communication with the server
  krpc_connect(conn, "Arduino Example");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  krpc_SpaceCenter_ActiveVessel(conn, &vessel);

  krpc_SpaceCenter_Vessel_set_Name(conn, vessel, "My Vessel");

  // Get a handle to a Flight object for the vessel
  krpc_SpaceCenter_Vessel_Flight(conn, &flight, vessel, KRPC_NULL);
  // Get the altiude
  krpc_SpaceCenter_Flight_MeanAltitude(conn, &vessel_altitude, flight);

  //lcd_print_all_page();

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

  bool right = relative_x < 0;

  //lcd_scroll(right, abs(relative_x));

  krpc_SpaceCenter_Flight_MeanAltitude(conn, &vessel_altitude, flight);

  lcd.setCursor(1,0);
  lcd.print(vessel_altitude);
  
}

void lcd_scroll(bool right, int scroll_speed){
  if (right)
  {
    for (int i = 0; i < scroll_speed; i ++)
    {
      lcd.scrollDisplayRight();
    }
  }
  else
  {
    for (int i = 0; i < scroll_speed; i ++)
    {
      lcd.scrollDisplayLeft();
    }
  }
}

void lcd_print_all_page(){
  // print all static screen interface
  lcd.setCursor(0, 1);
  lcd.print("Kontroller - Kerbal Space Program");
  lcd.setCursor(40, 1);
  lcd.print("this works!");
}
