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
const int RedButtonPin = 7; //verify if this is an interrupt pin
const int LiftMotorPin = 8;
const int BreakMotorPin = 9;


int cycle_once();
int brake_stop();
int jog_lift();
int cycle_cont();
int interrupt();


void setup(){


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
  attachInterrupt(digitalPinToInterrupt(7), E_stop, FALLING);

  //Represents sending the signal for ride to run 1 time
}

  int cycle_once(){
  if (digitalRead(GreenButtonPin) == HIGH){
    digitalWrite(LiftMotorPin, HIGH);
    calculated timer when to turn off lift motor
    break_stop();
    key = IDLE_STATE; //some kind of light that is only lit for idle state?
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
        //Set state to idle but then issue of having key in wrong state when e_stop is released
        //Include in protocol to remove key frrom switch and then put it back in to reset the state of the system
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






