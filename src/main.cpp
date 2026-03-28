#include <Arduino.h>


int IDLE_STATE = 0;
int MANUAL_STATE = 1;
int AUTO_STATE = 2;
int Timer = 0;

//ride is idle, has been turned on, but no buttons have been pressed on control panel
int key = IDLE_STATE;


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


void cycle_once();
void brake_stop();
void jog_lift();
void cycle_cont();
void E_stop();


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

}

//Represent sending the signal for breaks to activate
void break_stop(){
  while(digitalRead(breakSensorPin) == LOW){
    delay(1);
    }
    delay(1000); //timer if necessary for when sensors senses cart to when breaks clamp down
    digitalWrite(BreakMotorPin, HIGH);
    key = IDLE_STATE;
  }

//Complete one cycle of the ride then stop and change state to idle 
  void cycle_once(){
  if (digitalRead(GreenButtonPin) == HIGH){
      digitalWrite(BreakMotorPin, LOW);
      digitalWrite(LiftMotorPin, HIGH);
      delay(15000); // calculated timer when to turn off lift motor
      digitalWrite(LiftMotorPin, LOW); 
      break_stop();
      key = IDLE_STATE;
  }
}
//Represents sending the signal for lift to be manually activated
void jog_lift(){
  digitalWrite(LiftMotorPin, HIGH);
}


//Represents sending the signal for ride to run continously
void cycle_cont(){
  delay(1000); 
  digitalWrite(BreakMotorPin, LOW);
  while (key == AUTO_STATE && digitalRead(BlueButtonPin) == LOW){
      digitalWrite(LiftMotorPin, HIGH);
      break_stop();
      delay(8000);
      digitalWrite(BreakMotorPin, LOW);
      digitalWrite(LiftMotorPin, HIGH);
      delay(15000); //experimentally found time to bring to top
      digitalWrite(LiftMotorPin, LOW);
    }
          key = IDLE_STATE;
}



// E_stop function
  void E_stop() {
      digitalWrite(LiftMotorPin, LOW);
      if (digitalRead(breakSensorPin) == HIGH){
        break_stop();
        while (!(key == MANUAL_STATE && digitalRead(BlueButtonPin) == LOW && digitalRead(GreenButtonPin) == LOW && digitalRead(YellowButtonPin) == LOW)){
         if(key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH && digitalRead(GreenButtonPin) == HIGH && digitalRead(YellowButtonPin) == HIGH){
            break;
          }
          delay(1);
          if (switchState == HIGH){
          key = MANUAL_STATE;
        }
        Timer = 0;
      }
      if (digitalRead(breakSensorPin) == LOW && Timer < 15){
        delay(1000); 
        Timer += 1;
      }
    }
      else if (digitalRead(breakSensorPin) == LOW && Timer >= 15){
        while (!(key == MANUAL_STATE && digitalRead(BlueButtonPin) == LOW && digitalRead(GreenButtonPin) == LOW && digitalRead(YellowButtonPin) == LOW)){
          if(key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH && digitalRead(GreenButtonPin) == HIGH && digitalRead(YellowButtonPin) == HIGH){
            break;
          }
          delay(1);
          if (switchState == HIGH){
          key = MANUAL_STATE;
          }
          if (digitalRead(breakSensorPin) == HIGH){
          digitalWrite(BreakMotorPin, HIGH);
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
    digitalWrite(BreakMotorPin, HIGH);
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
  }

  
  //Change dispatch to false when cycle_cont is done
  


  if (key == MANUAL_STATE && digitalRead(BlueButtonPin) == HIGH){
      break_stop();
    }
    else if (key == MANUAL_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_once();
    }
    //Physically unselect when done
    else if (key == MANUAL_STATE && digitalRead(YellowButtonPin) == HIGH){
      jog_lift();
    }
    else if (key == AUTO_STATE && digitalRead(GreenButtonPin) == HIGH){
      cycle_cont();
    }

    else if (key == AUTO_STATE && digitalRead(BlueButtonPin) == HIGH){
      break_stop();
    }
   
  }






