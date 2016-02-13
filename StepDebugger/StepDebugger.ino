
#include <Servo.h>
const int switchPin = 4; //active low
const int servoPin = 9;
const int servoFingerPin = 8;

int closedPos = 175;    // variable to store the servo position
int openPos = 70;
bool boxOpen = false;

int fingerOutPos = 180;
int fingerInPos = 100;

Servo servo_finger;
bool fingerExtended = false;
bool lastRead = false;
bool start = true;
int stage = 0;
Servo servo;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  servo.attach(servoPin);
  servo_finger.attach(servoFingerPin);
}

bool buttonPressed() {
  if(digitalRead(switchPin) != lastRead)
  {
    if(lastRead == true)
    {
      lastRead = false;
      return true;
    }
    else
    {
     lastRead = true;
    }
  }
  return false;
}

void setBoxLid(bool isBoxOpen) {
  boxOpen = isBoxOpen;
  if (boxOpen)
    servo.write(openPos);  // HIGH (switch is off)
  else
   servo.write(closedPos);  // LOW (switch is on)

  delay(500);
}

void setFingerExtended(bool isExtended){
  fingerExtended = isExtended;
  if(fingerExtended)
    servo_finger.write(fingerOutPos);
  else
    servo_finger.write(fingerInPos);

  delay(500);
}

void toggleBoxLid() {
  boxOpen = !boxOpen;
  setBoxLid(boxOpen);
}

void toggleFinger() {
  fingerExtended = !fingerExtended;
  setFingerExtended(fingerExtended);
}

void loop() {
  if(start) {
    start = false;
    setBoxLid(false);
    setFingerExtended(false);
  }

  if(buttonPressed()){
    stage = stage + 1;
    if(stage == 1) {
      setBoxLid(false);
      setFingerExtended(false);
      return;
    }
    else if(stage == 2){
      setBoxLid(true);
      return;
    }
    else if(stage == 3){
      setFingerExtended(true);
      return;
    }
    else if(stage == 4){
      setFingerExtended(false);
      setBoxLid(false);
      stage = 1;
      return;
    }
    
  }
}
