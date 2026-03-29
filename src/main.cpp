#include <Arduino.h>


int IDLE_STATE = 0;
int MANUAL_STATE = 1;
int AUTO_STATE = 2;
bool safety_check = true;

//ride is idle, has been turned on, but no buttons have been pressed on control panel
int key = IDLE_STATE;


const int liftSensorPin = 1;
const int brakeSensorPin = 2;


const int switchPin = 3;
const int BlueButtonPin = 4;
const int GreenButtonPin = 5;
const int YellowButtonPin = 6;
const int AutokeySwitchLED = 10;
const int ManualkeySwitchLED = 11;
const int RedButtonPin = 18; 
const int LiftMotorPin = 8;
const int BrakeMotorPin = 9;

void cycle_once();
void brake_stop();
void jog_lift();
void cycle_cont();
void E_stop();
void cycle_brakes();
void updateLED();

void setup(){

  //Activating pin used Auto Key switch LED
  pinMode(AutokeySwitchLED, OUTPUT);

  //Activating pin used Auto Key switch LED
  pinMode(ManualkeySwitchLED, OUTPUT);

  //Activating pin used for lift sensor
  pinMode(liftSensorPin, OUTPUT);


  //Activating pin used for brake run sensor
  pinMode(brakeSensorPin, OUTPUT);


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

  //For safety, when the system is turned on, the lift motors are off and the brakes are on 
  digitalWrite(LiftMotorPin,  LOW);
  digitalWrite(BrakeMotorPin, HIGH);

}
  
//While LED next to either key switch is on, the ride is in that mode, when LED is off ride is in idle mode
void updateLED(){
  if (key == IDLE_STATE) {  
    digitalWrite(ManualkeySwitchLED, LOW);
    digitalWrite(AutokeySwitchLED, LOW);
    digitalWrite(BrakeMotorPin, HIGH);
  }
    else if (switchState == HIGH){
      digitalWrite(ManualkeySwitchLED, HIGH);
      digitalWrite(AutokeySwitchLED, LOW);
    }
    else if(switchState == LOW){
      digitalWrite(AutokeySwitchLED, HIGH);
      digitalWrite(ManualkeySwitchLED, LOW);
  }
  else{
    return;
  }
}

//Waits for cart to trip brake sensor and then activates brakes and changes state to idle
void brake_stop(){
  digitalWrite(BrakeMotorPin, HIGH);
    key = AUTO_STATE; //needs to stay in auto otherwise operator can't do anything cause they don't have a key
    updateLED();
  }

//While brake button is held, brakes are active
void cycle_brakes(){
  while(digitalRead(BlueButtonPin) == HIGH){
    digitalWrite(BrakeMotorPin, LOW);
  }
    digitalWrite(BrakeMotorPin, HIGH);
}

//Complete one cycle of the ride then stop and change state to idle 
  void cycle_once(){
      digitalWrite(BrakeMotorPin, LOW);
      digitalWrite(LiftMotorPin, HIGH);
      delay(15000); //However long lift takes to get to the top
      digitalWrite(LiftMotorPin, LOW); 
      brake_stop();
      key = IDLE_STATE;
      updateLED();
  }

//Activates lift while button is held
void jog_lift(){
  while(digitalRead(YellowButtonPin) == HIGH){
  digitalWrite(LiftMotorPin, HIGH);
  }
}

//Lets the ride run continuoulsy until brake button is pressed, then changes state to idle
void cycle_cont(){
  delay(1000); 
  digitalWrite(BrakeMotorPin, LOW);
  while (digitalRead(BlueButtonPin) == LOW){
      digitalWrite(LiftMotorPin, HIGH);
      brake_stop();
      delay(8000); 
      digitalWrite(BrakeMotorPin, LOW);
      digitalWrite(LiftMotorPin, HIGH);
      delay(15000); //However long lift takes to get to the top
      digitalWrite(LiftMotorPin, LOW);
    }
          key = IDLE_STATE;
          updateLED();
}

// E_stop function
  void E_stop() {
      digitalWrite(LiftMotorPin, LOW);
      digitalWrite(BrakeMotorPin, HIGH);
      delay(30000); //whatever total runtime is 
      key = IDLE_STATE;
      updateLED();
      digitalWrite(safety_check, false);
}

void loop() {
  
  int switchState = digitalRead(switchPin);
  
  if (digitalRead(RedButtonPin) == HIGH){
    E_stop();
  }

  if (switchState == HIGH){
    key = MANUAL_STATE;
    safety_check = true;
  }

  if (switchState == LOW && safety_check == true){ //safety check is to prevent operator touching thigs after an E-stop
    key = AUTO_STATE;
    safety_check = false;
  }

// While light is on ride is in idle mode, Idle light takes priority over auto mode light, 
//when light is off ride is in either auto or manual mode depending on key switch position
if (key == IDLE_STATE) {  
    digitalWrite(IdlekeySwitchLED, HIGH);
    digitalWrite(BrakeMotorPin, HIGH);
    else {
      digitalWrite(IdlekeySwitchLED, LOW);
    }
  }

  if (key == AUTO_STATE && digitalRead(YellowButtonPin) == HIGH){
      brake_stop();
    }
    else if (key == MANUAL_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_once();
    }
    else if (key == MANUAL_STATE && digitalRead(YellowButtonPin) == HIGH){
      jog_lift();
    }
    else if (key == AUTO_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_cont();
    }
    else if (key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH){
      cycle_brakes();
    }
    else if (key == AUTO_STATE && digitalRead(BlueButtonPin) == HIGH){
       return;
     }
     else{
        return;
     }
   
  }

  
  
  






