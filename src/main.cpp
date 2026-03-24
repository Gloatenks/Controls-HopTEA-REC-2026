#include <Arduino.h>


int IDLE_STATE = 0;
int MANUAL_STATE = 1;
int AUTO_STATE = 2;


//ride is idle, has been turned on, but no buttons have been pressed on control panel
int key = IDLE_STATE;


bool dispatch = false;
bool misc = false;


const int liftSensorPin = 1;
const int breakSensorPin = 2;


const int switchPin = 3;
const int BlueButtonPin = 4;
const int GreenButtonPin = 5;
const int YellowButtonPin = 6;
const int IdlekeySwitchLED = 7;
const int AMkeySwitchLED = 10;
const int RedButtonPin = 18; 
const int LiftMotorPin = 8;
const int BreakMotorPin = 9;


int cycle_once();
int brake_stop();
int jog_lift();
int cycle_cont();
int interrupt();


void setup(){

  //Activating pin used Idle Key switch LED
  pinMode(IdlekeySwitchLED, OUTPUT);

  //Activating pin used AM Key switch LED
  pinMode(AMkeySwitchLED, OUTPUT);

  //Activating pin used for lift sensor
  pinMode(liftSensorPin, OUTPUT);


  //Activating pin used for break run sensor
  pinMode(breakSensorPin, OUTPUT);


  //Activating pinn used for Key-Lock switch
  pinMode(switchPin, INPUT_PULLUP);


  //Activating pin used for blue button on control panel
  pinMode(BlueButtonPin, INPUT_PULLUP);


  //Activating pin used for green button on control panel
  pinMode(GreenButtonPin, INPUT_PULLUP);


  //Activating pin used for yellow button on control panel
  pinMode(YellowButtonPin, INPUT_PULLUP);


  //Activating pin used for red button on control panel
  pinMode(RedButtonPin, INPUT_PULLUP);


  //Interrupt for emergency stop button
  attachInterrupt(digitalPinToInterrupt(18), E_stop, FALLING);

  //Represents sending the signal for ride to run 1 time
}

  int cycle_once(){
  if (digitalRead(GreenButtonPin) == HIGH){
    digitalWrite(LiftMotorPin, HIGH);
    calculated timer when to turn off lift motor
    break_stop();
    key = IDLE_STATE;
  }
    digitalWrite(LiftMotorPin, LOW);
  if(digitalRead(breakSensorPin) == HIGH){
    digitalWrite(BreakMotorPin, HIGH);
      return 0;
    }
  return 1;
}

//Represent sending the signal for breaks to activate
int break_stop(){
  if (digitalRead(breakSensorPin) == HIGH){
      digitalWrite(BreakMotorPin, HIGH);
    }
  if (digitalRead(breakSensorPin) == LOW){
      digitalWrite(BreakMotorPin, LOW);
    }
  }

//Represents sending the signal for lift to be manually activated
//maybe change to while statement
int jog_lift(){
  if (digitalRead(YellowButtonPin) == HIGH){
    digitalWrite(LiftMotorPin, HIGH);
  else if (digitalRead(YellowButtonPin) == LOW){
      digitalWrite(LiftMotorPin, LOW);    
    }
  }
  return;
}


//Represents sending the signal for ride to run continously
int cycle_cont(){
  if (digitalRead(liftSensorPin) == HIGH){
      digitalWrite(LiftMotorPin, HIGH);
      timer for experimentally found time
      return 0;
    }
  return 1;
}



// E_stop function definition
  void E_stop() {
    while (RedButtonPin == HIGH){
      if (digitalRead(breakSensorPin) == HIGH){
        digitalWrite(LiftMotorPin, LOW);
        brake_stop(); 
        key = IDLE_STATE;
      }
    }
      if (RedButtonPin == LOW){
      return;
      }
  }

void loop() {
  
  int switchState = digitalRead(switchPin);
  

  //manual mode state
  if (switchState == HIGH){
    key = MANUAL_STATE;
  }

  //auto mode state
  if (switchState == LOW){
    key = AUTO_STATE;
  }
  //Manual mode functions
  if (key == MANUAL_STATE){
    if(dispatch == true){
    cycle_once();
    dispatch = false;
    }
// While light is on ride is in idle mode, Idle light takes priority over auto mode light, 
//when light is off ride is in either auto or manual mode depending on key switch position
if (key == IDLE_STATE) {  
    digitalWrite(IdlekeySwitchLED, HIGH);
    else {
      digitalWrite(IdlekeySwitchLED, LOW);
    }
  }
      //While light is on ride is in auto mode, when light is off ride is in manual mode ignore if in idle mode
if (key == AUTO_STATE){
      digitalWrite(AMkeySwitchLED, HIGH);
    else {
      digitalWrite(AMkeySwitchLED, LOW);
}
  }
    if (digitalRead(breakSensorPin) == HIGH){
      brake_stop();
    }
//maybe change to if statement see while testing
  while(misc == true){
    jog_lift();
  }
  }

  //Auto mode functions
  if (key == AUTO_STATE && dispatch == true) {
  while (!misc) {
    cycle_cont();
    if (digitalRead(breakSensorPin) == HIGH){
      break_stop();
    }
  }
  //Change dispatch to false when cycle_cont is done
  }
  if (key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH){
      break_stop();
    }
    else if (key == MANUAL_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_once();
    }
    else if (key == MANUAL_STATE && digitalRead(YellowButtonPin) == HIGH){
      jog_lift();
    }
    else if (key == AUTO_STATE && digitalRead(BlueButtonPin) == HIGH){
      break_stop();
    }
    else if (key == AUTO_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_cont();
    }
    else {
      return;
    }
  }






