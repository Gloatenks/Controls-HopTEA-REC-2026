#include <Arduino.h>

int IDLE_STATE = 0;
int MANUAL_STATE = 1;
int AUTO_STATE = 2;

//ride is idle, has been turned on, but no buttons have been pressed on control panel
int key = IDLE_STATE;

bool dispatch = false;
bool estop = false;
bool misc = false;

//initializing break-beam sensors
bool lift_sensor = false;
bool break_sensor = false;

int cycle_once();
int break_run();
int jog_lift();
int cycle_cont();
int interrupt();

void loop() {
/* Up here include attachlnterrupt (digitalPinToInterrupt (buttonPin), (name of function we want activated), 
FALLING (or rising depending on button type)); */
  //manual mode
  if (switch is flipped to manual){
    key == MANUAL_STATE;
  }

  //auto mode
  if (switch is flipped to auto){
    key = AUTO_STATE;
  }
  
  if (key == MANUAL_STATE && dispatch == true){
    cycle_once;
    }

    if (break_sensor == true){
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
    if (break_sensor == true){
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

//Represent sending the signal for the e-stop to stop the ride
int interrupt(){
  return 1;
}

