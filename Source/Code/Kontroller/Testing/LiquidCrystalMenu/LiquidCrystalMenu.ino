#include <LiquidMenu.h>
#include <krpc.h>
#include <krpc/services/space_center.h>

// Starting lcds
const int rs1 = 12, en1 = 11, d41 = 5, d51 = 4, d61 = 3, d71 = 2;
const int rs2 = 35, en2 = 37, d42 = 41, d52 = 43, d62 = 45, d72 = 47;

LiquidCrystal lcd1(rs1, en1, d41, d51, d61, d71);
LiquidCrystal lcd2(rs2, en2, d42, d52, d62, d72);

//Defining variables that will be updated later
char* vesselStatus;
char* vesselName;
float vesselMass = 23.31;
float vesselDeltaV = 403.3;
double vesselAltitude =  64.0;
bool vesselIsRecoverable = true;
float distanceToKSC = 532.0;
char* vesselBiome;
float vesselPeriapsis = 0.0;
float vesselApoapsis = 0.0;

String current_display_state = "Vessel";

bool iskRPCConnected;

//Main Menu

//Welcome Screen
LiquidLine welcome1(0, 0, "Kontroller");
LiquidLine welcome2(0, 1, "Kerbal Space Program");
LiquidLine welcome3(0, 2, "Starting...");
LiquidLine welcome4(0, 3, "2022 by @g");
LiquidScreen welcomeScreen(welcome1, welcome2, welcome3, welcome4);
//Vessel Screen
LiquidLine statusLine(0, 0, "Status:", vesselStatus);
LiquidLine nameLine(0, 1, "Name:", vesselName);
LiquidLine massLine(0, 2, "Mass:", vesselMass);
LiquidLine deltaVLine(0, 3, "dV:", vesselDeltaV);
LiquidScreen vesselScreen(statusLine, nameLine, massLine, deltaVLine);

//Data Showing Menu

//Position Landed1 Screen
LiquidLine altitudeLine(0, 0, "Alt:", vesselAltitude, "m");
LiquidLine isRecoverableLine(0, 1, "Recoverable:", vesselIsRecoverable);
LiquidScreen vesselScreenPositionLanded1(altitudeLine, isRecoverableLine);

//Position Landed2 Screen
LiquidLine KSCDistanceLine(0, 0, "KSC:", distanceToKSC, "m");
LiquidLine biomeLine(0, 1, "Biome:", vesselBiome);
LiquidScreen vesselScreenPositionLanded2(KSCDistanceLine, biomeLine);

//Position Orbiting1 Screen
LiquidLine periapsisLine(0, 0, "Pe:", vesselPeriapsis);
LiquidLine apoapsisLine(0, 0, "Ap:", vesselApoapsis);
LiquidScreen vesselScreenPositionOrbiting1(periapsisLine, apoapsisLine);

/*
  LiquidScreen vesselScreenPositionOrbiting2();
  LiquidScreen vesselScreenPositionFlying();
  LiquidScreen vesselScreenPositionRoving();
  LiquidScreen vesselScreenPositionSubOrbital();
*/

LiquidLine isConnectedLine(0, 0, "Is connected:", iskRPCConnected);
LiquidLine connectButton(0, 3, "CONNECT");
LiquidScreen kRPCScreen(isConnectedLine, connectButton);


// Declaring Menus
LiquidMenu menu1(lcd1, welcomeScreen, kRPCScreen, vesselScreen, 1);
LiquidMenu menu2(lcd2, vesselScreenPositionLanded1, 1);
/*
  menu2.add_screen(vesselScreenPositionOrbiting2);
  menu2.add_screen(vesselScreenPositionFlying);
  menu2.add_screen(vesselScreenPositionRoving);
  menu2.add_screen(vesselScreenPositionSubOrbital);
*/

//Button Handling
#define BUTTON_R_PIN 9
#define BUTTON_L_PIN 8

int button_r_hold;
int button_l_hold;
bool button_r_released;
bool button_l_released;

//temporary for button visualization on displays
LiquidLine buttonLine(0, 0, "button:", button_r_hold);
LiquidScreen buttonScreen(buttonLine);

//kRPC Initialization
HardwareSerial* conn;

void cycle_current_data_screens()
{
  return;
}

void krpc_get_shown_data()
{
  if (current_display_state == "Vessel")
  {
    krpc_SpaceCenter_Vessel_t vessel;
    krpc_SpaceCenter_Flight_t flight;
    krpc_SpaceCenter_ActiveVessel(conn, &vessel);
    krpc_SpaceCenter_ReferenceFrame_t reference;
    krpc_SpaceCenter_Vessel_Flight(conn, &flight, vessel, krpc_SpaceCenter_Vessel_SurfaceReferenceFrame(conn, &reference, vessel));


    krpc_SpaceCenter_Vessel_Name(conn, &vesselName, vessel);
    //krpc_SpaceCenter_Vessel_Situation(conn, &vesselStatus, vessel);
    krpc_SpaceCenter_Vessel_Mass(conn, &vesselMass, vessel);

    krpc_SpaceCenter_Vessel_Recoverable(conn, &vesselIsRecoverable, vessel);
    krpc_SpaceCenter_Flight_MeanAltitude(conn, &vesselAltitude, vessel);
    distanceToKSC = 532.0;
    vesselBiome = "Shores";
    vesselPeriapsis = 0.0;
    vesselApoapsis = 0.0;
  }
}

void connect_to_krpc()
{
  conn = &Serial;

  krpc_open(&conn, NULL);
  krpc_connect(conn, "Kontroller");

  iskRPCConnected = true;
}

void setup() {
  lcd1.begin(20, 4);
  lcd2.begin(16, 2);
  //  menu2.add_screen(vesselScreenPositionLanded2);
  //  menu2.add_screen(vesselScreenPositionOrbiting1);
  menu2.add_screen(buttonScreen);
  menu1.update();
  menu2 .update();

  delay(3000);
  menu1.next_screen();
  menu2.next_screen();
  menu2.update();
  menu1.update();

  connectButton.attach_function(0, connect_to_krpc);
}

int _millis = millis();
int __millis = millis();
int ___millis = millis();


void loop() {
  if (millis() - _millis > 1000)
  {
    krpc_get_shown_data();
    menu1.update();
    menu2.update();
    _millis = millis();
  }

  if (millis() - __millis > 5000)
  {
    cycle_current_data_screens();
    __millis = millis();
  }

  bool button_r_read = digitalRead(BUTTON_R_PIN);
  bool button_l_read = digitalRead(BUTTON_L_PIN);

  //getting if buttons are pressed and for how long
  if (button_r_read)
  {
    button_r_hold = millis() - ___millis;
  }
  else
  {
    button_r_hold = -1;
    ___millis = millis();
  }
  if (button_l_read)
  {
    button_l_hold = millis() - ___millis;
  }
  else
  {
    button_l_hold = -1;
    ___millis = millis();
  }

  //right button interactions
  if (button_r_hold < 500 && button_r_hold != -1)
  {
    menu1.switch_focus(true); //switch line focus foward
  }
  else // if it's a longer press
  {
    menu1.call_function(0);
  }
  // left button interactions
  if (button_r_hold < 500 && button_r_hold != -1)
  {
    menu1.switch_focus(false); //switch line focus backward
  }
  else // if it's a longer press
  {
    menu1.previous_screen();
  }
}
