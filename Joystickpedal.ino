// Requires Arduino Joystick Library https://github.com/MHeironimus/ArduinoJoystickLibrary
#include <Joystick.h>
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  1, 0,                  // Button Count, Hat Switch Count
  true, true, true,   // No X, Y, Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  true, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
 
int PedaleR;
int PedaleM;
int PedaleL;
int minR;
int minL;
int minM;




void setup() {

  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);

minR = analogRead(A0);
minM = analogRead(A1);
minL = analogRead(A3);
minR= minR+10;
minM= minM+10;
minL= minL+10;
  


// Initialize Joystick Library
  Joystick.begin();
    Joystick.setXAxisRange(0, 1024);
    Joystick.setYAxisRange(0, 1024);
    Joystick.setZAxisRange(0, 1024);
    Joystick.setRudderRange(-512, 512);
}

void loop() {

///PedaleMitte
PedaleR= analogRead(A0);
if(PedaleR< minR){PedaleR=minR;}
if(PedaleR > 690){PedaleR = 690;}
PedaleR=map( PedaleR,minR,690,0,1024);
if(PedaleR > 500){Joystick.setButton(0, 1);}
else{Joystick.setButton(0, 0);}

///PedaleLinks
PedaleM= analogRead(A1);
if(PedaleM< minM){PedaleM=minM;}
if(PedaleM > 690){PedaleM = 690;}
PedaleM=map( PedaleM,minM,690,0,1024);



///PedaleRechts
PedaleL= analogRead(A3);
if(PedaleL< minL){PedaleL=minL;}
if(PedaleL > 1015){PedaleL = 690;}
PedaleL=map(PedaleL,minL,690,0,1024);
   
// Output Controls
  Joystick.setYAxis(PedaleR);
  Joystick.setXAxis(PedaleM);
  Joystick.setZAxis(PedaleL);
  Joystick.setRudder((PedaleM/2)-(PedaleL/2));
  

  Joystick.sendState();


} 
