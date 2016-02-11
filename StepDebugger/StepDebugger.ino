
#include <Servo.h>
const int switchPin = 4; //active low
const int servoPin = 9;

int closedPos = 175;    // variable to store the servo position
int openPos = 90;
bool boxOpen = true;

bool lastRead = false;

Servo servo;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  servo.attach(servoPin); 
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

void toggleBoxLid() {
  boxOpen = !boxOpen;
  setBoxLid(boxOpen);
}

void loop() {
  if(buttonPressed()) {
    toggleBoxLid();
  }
}
