#include <EEPROM.h>

#include <Wire.h>

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#include <Servo.h>

Adafruit_7segment matrix = Adafruit_7segment();

const int switchPin = 10; //active low
const int servoLidPin = 8;
const int servoFingerPin = 5;

Servo servoLid;
int closedPos = 175;
int openPos = 70;
bool boxOpen = false;

Servo servoFinger;
int fingerOutPos = 168;
int fingerInPos = 85;
bool fingerExtended = false;

bool lastRead = false;
int usage = 0;

void setBoxLid(bool isBoxOpen) {
  boxOpen = isBoxOpen;
  if (boxOpen)
    servoLid.write(openPos);
  else
   servoLid.write(closedPos);
}

void setFingerExtended(bool isExtended){
  fingerExtended = isExtended;
  if(fingerExtended)
    servoFinger.write(fingerOutPos);
  else
    servoFinger.write(fingerInPos);
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
  matrix.begin(0x70);
  
  //Serial.begin(9600);
  pinMode(switchPin, INPUT_PULLUP);
  servoLid.attach(servoLidPin);
  servoFinger.attach(servoFingerPin);

  EEPROM.get(0, usage);
  if(usage < 0){
    usage = 0;
  }
  matrix.println(usage);
  matrix.writeDisplay();
      
  setFingerExtended(false);
  delay(500);
  setBoxLid(false);
}

void loop() {
  if(buttonPressed()){
    EEPROM.put(0, usage);
    matrix.println(usage);
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
      usage++;
  }
  delay(100);
}
