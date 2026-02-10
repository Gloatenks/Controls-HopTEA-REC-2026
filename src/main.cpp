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
const int RedButtonPin = 7;
const int LiftMotorPin = 8;
const int BreakMotorPin = 9;


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


  //Activating pin used for red button on control panel
  pinMode(RedButtonPin, INPUT);


  //Interrupt for emergency stop button
  attachInterrupt(digitalPinToInterrupt(7), E-stop, FALLING);


  // E-stop function definition
  void E-stop() {
    while (RedButtonPin == HIGH){
      if (digitalRead(breakSensorPin) == HIGH){
      break_run; //double check what e-stop is supposed to do
      stop lift; //keep from falling back
      }
    }
      if (RedButtonPin == LOW){
      return;
      }
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

    if (digitalRead(breakSensorPin) == HIGH){
      break_run();
    }
//maybe change to if statement see while testing
  while(misc == true){
    jog_lift();
  }
  }

  //Auto mode functions
  if (key == AUTO_STATE && dispatch == true) {
  while (!misc) {
    cycle_cont;
    if (digitalRead(breakSensorPin) == HIGH){
      break_run;
    }
  }
  //Change dispatch to false when cycle_cont is done
  }
}


}


//Represents sending the signal for ride to run 1 time
int cycle_once(){
  if (digitalRead(GreenButtonPin) == HIGH){
    digitalWrite(LiftMotorPin, HIGH);
    calculated timer when to turn off lift motor
    digitalWrite(LiftMotorPin, LOW);
  if(digitalRead(breakSensorPin) == HIGH){
    digitalWrite(BreakMotorPin, HIGH);
      return 0;
    }
  return 1;
}
}
//Represent sending the signal for breaks to activate
int break_run(){
  if (digitalRead(breakSensorPin) == HIGH){
      digitalWrite(BreakMotorPin, HIGH);
      return 0;
    }
  return 1;
}


//Represents sending the signal for lift to be manually activated
//maybe change to while statement
int jog_lift(){
  if (digitalRead(YellowButtonPin) == HIGH){
    digitalWrite(LiftMotorPin, HIGH);
  if (digitalRead(YellowButtonPin) == LOW){
      return 0;
    }
  }
  return 1;
}


//Represents sending the signal for ride to run continously
int cycle_cont(){
  if (digitalRead(liftsensorPin) == HIGH){
      digitalWrite(LiftMotorPin, HIGH);
      timer for experimentally found time
      return 0;
    }
  return 1;
}



