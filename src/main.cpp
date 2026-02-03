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


int cycle_once();
int break_run();
int jog_lift();
int cycle_cont();
int interrupt();

void setup(){

  //Activating pin used for lift sensor
  pinMode(liftSensorPin, INPUT);

  //Activating pin used for break run sensor
  pinMode(breakSensorPin, INPUT);

  //Activating pinn used for Key-Lock switch
  pinMode(switchPin, INPUT_PULLUP);

  //Activating pin used for blue button on control panel
  pinMode(BlueButtonPin, INPUT);

  //Activating pin used for green button on control panel
  pinMode(GreenButtonPin, INPUT);

  //Activating pin used for yellow button on control panel
  pinMode(YellowButtonPin, INPUT);
}

void loop() {
/* Up here include attachlnterrupt (digitalPinToInterrupt (buttonPin), (name of function we want activated), 
FALLING (or rising depending on button type)); */
  //manual mode

  int switchState = digitalRead(switchPin);
  if (switchState = HIGH){
    key = MANUAL_STATE;
  }

  //auto mode
  if (switchState = LOW){
    key = AUTO_STATE;
  }
  
  if (key == MANUAL_STATE && dispatch == true){
    cycle_once;
    }

    if (digitalRead(breakSensorPin) == HIGH){
      break_run;
    }
    return;

  while(key == MANUAL_STATE && misc == true){
    jog_lift;
    return;
  }

  if (key == AUTO_STATE && dispatch == true) {

  while (!misc) {
    cycle_cont;
    if (digitalRead(breakSensorPin) == HIGH){
      break_run;
    }
  }
  return;
}

}

//Represents sending the signal for ride to run 1 time
int cycle_once(){
  if (estop == true){
      interrupt;
      return 0;
    }
  return 1;
}

//Represent sending the signal for breaks to activate
int break_run(){
  if (estop == true){
      interrupt;
      return 0;
    }
  return 1;
}

//Represents sending the signal for lift to be manually activated
int jog_lift(){
  return 1;
}

//Represents sending the signal for ride to run continously
int cycle_cont(){
  if (estop == true){
      interrupt;
      return 0;
    }
  return 1;
}

