#include <Wire.h>

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <Servo.h>

Adafruit_7segment matrix = Adafruit_7segment();

const int switchPin = 10; //active low
const int servoPin = 8;
const int servoFingerPin = 5;

int closedPos = 175;    // variable to store the servo position
int openPos = 70;
bool boxOpen = false;

int fingerOutPos = 168;
int fingerInPos = 85;

Servo servo_finger;
bool fingerExtended = false;
bool lastRead = false;
bool start = true;
int stage = 0;
int pos = 0;
int usage = 0;
Servo servo;


void setBoxLid(bool isBoxOpen) {
  boxOpen = isBoxOpen;
  if (boxOpen)
    servo.write(openPos);
  else
   servo.write(closedPos);
}

void setFingerExtended(bool isExtended){
  fingerExtended = isExtended;
  if(fingerExtended)
    servo_finger.write(fingerOutPos);
  else
    servo_finger.write(fingerInPos);
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

void setup() {
  Serial.println("7 Segment Backpack Test");
  matrix.begin(0x70);
  
  pinMode(switchPin, INPUT_PULLUP);
  servo.attach(servoPin);
  servo_finger.attach(servoFingerPin);
  Serial.begin(9600);
  
  start = false;
  setFingerExtended(false);
  delay(500);
  setBoxLid(false);
}

void debugLoop(){
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

void loop() {
  if(buttonPressed()){
      matrix.println(usage++);
      matrix.writeDisplay();
  }
  
  if(digitalRead(switchPin) == LOW){
      setBoxLid(false);
      delay(700);
  }
  else{
      setBoxLid(true);
      delay(700);
      setFingerExtended(true);
      delay(320);
      setFingerExtended(false);
  }
  delay(100);
}
