#include <Arduino.h>


int IDLE_STATE = 0;
int MANUAL_STATE = 1;
int AUTO_STATE = 2;
int Timer = 0;

//ride is idle, has been turned on, but no buttons have been pressed on control panel
int key = IDLE_STATE;


const int liftSensorPin = 1;
const int brakeSensorPin = 2;


const int switchPin = 3;
const int BlueButtonPin = 4;
const int GreenButtonPin = 5;
const int YellowButtonPin = 6;
const int IdlekeySwitchLED = 7;
const int AMkeySwitchLED = 10;
const int RedButtonPin = 18; 
const int LiftMotorPin = 8;
const int BrakeMotorPin = 9;


void cycle_once();
void brake_stop();
void jog_lift();
void cycle_cont();
void E_stop();
void cycle_brakes();


void setup(){

  //Activating pin used Idle Key switch LED
  pinMode(IdlekeySwitchLED, OUTPUT);

  //Activating pin used AM Key switch LED
  pinMode(AMkeySwitchLED, OUTPUT);

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

}

//Waits for cart to trip brake sensor and then activates brakes and changes state to idle
void brake_stop(){
  while(digitalRead(brakeSensorPin) == LOW){
    delay(1);
  }
    delay(1000); 
    digitalWrite(BrakeMotorPin, HIGH);
    key = IDLE_STATE;
  }

//While brake button is held, brakes are active
void cycle_brakes(){
  while(digitalRead(BlueButtonPin) == HIGH){
    digitalWrite(BrakeMotorPin, HIGH);
  }
    digitalWrite(BrakeMotorPin, LOW);
}

//Complete one cycle of the ride then stop and change state to idle 
  void cycle_once(){
  if (digitalRead(GreenButtonPin) == HIGH){
      digitalWrite(BrakeMotorPin, LOW);
      digitalWrite(LiftMotorPin, HIGH);
      delay(15000); 
      digitalWrite(LiftMotorPin, LOW); 
      brake_stop();
      key = IDLE_STATE;
  }
}
//Activates lift while button is held
void jog_lift(){
  digitalWrite(LiftMotorPin, HIGH);
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
      delay(15000); 
      digitalWrite(LiftMotorPin, LOW);
    }
          key = IDLE_STATE;
}



// E_stop function
  void E_stop() {
      digitalWrite(LiftMotorPin, LOW);
      if (digitalRead(brakeSensorPin) == HIGH){
        brake_stop();
        while (!(key == MANUAL_STATE && digitalRead(BlueButtonPin) == LOW && digitalRead(GreenButtonPin) == LOW && digitalRead(YellowButtonPin) == LOW)){
         if(key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH && digitalRead(GreenButtonPin) == HIGH && digitalRead(YellowButtonPin) == HIGH){
            return;
          }
          delay(1);
          if (switchState == HIGH){
          key = MANUAL_STATE;
        }
        Timer = 0;
      }
      if (digitalRead(brakeSensorPin) == LOW && Timer < 15){
        delay(1000); 
        Timer += 1;
      }
    }
      else if (digitalRead(brakeSensorPin) == LOW && Timer >= 15){
        while (!(key == MANUAL_STATE && digitalRead(BlueButtonPin) == LOW && digitalRead(GreenButtonPin) == LOW && digitalRead(YellowButtonPin) == LOW)){
          if(key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH && digitalRead(GreenButtonPin) == HIGH && digitalRead(YellowButtonPin) == HIGH){
            return;
          }
          delay(1);
          if (switchState == HIGH){
          key = MANUAL_STATE;
          }
          if (digitalRead(brakeSensorPin) == HIGH){
          digitalWrite(BrakeMotorPin, HIGH);
        }
        }
        Timer = 0;
      }
      if (key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH){
        key = IDLE_STATE;
      }
}

void loop() {
  
  int switchState = digitalRead(switchPin);
  

  //manual mode state del
  if (switchState == HIGH){
    key = MANUAL_STATE;
  }

  //auto mode state del
  if (switchState == LOW){
    key = AUTO_STATE;
  }
  //Maybe del
  if (key == MANUAL_STATE){
    if(dispatch == true){
    cycle_once();
    dispatch = false;
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
      //While light is on ride is in auto mode, when light is off ride is in manual mode ignore if in idle mode
if (key == AUTO_STATE){
      digitalWrite(AMkeySwitchLED, HIGH);
    else {
      digitalWrite(AMkeySwitchLED, LOW);
}
  }
    if (digitalRead(brakeSensorPin) == HIGH){
      brake_stop();
    }
  }

  
  //Change dispatch to false when cycle_cont is done
  


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
    else if (key == AUTO_STATE && digitalRead(BlueButtonPin) == HIGH){
      cycle_brakes();
    }
    else if (key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH){
       return;
     }
     else{
        return;
     }
   
  }






