#include <Arduino.h>
#include <Button.h>

#include "FootPedal.h"


#define TERMINATOR '\n';
static unsigned long LONGPRESSDUR = 1000;
bool released = true;

Button pedal = Button(9, true, false, 50, sendPedalString, false);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  Serial.println("INIT PEDAL");
  for (int i = 0; i<3; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(150);
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
  }
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if (!pedal.isPressed(true)) released = true;
  delay(50);
}



void sendPedalString() {
  if (released) {
    released = false;
    unsigned long startTime = millis();
    unsigned long stopTime = millis();
    while (pedal.isPressed(false)) {
      stopTime = millis();
      if (stopTime-startTime > LONGPRESSDUR) {
        Serial.println("pLP");
        return;
      }
    }
    Serial.println("p1P"); 
  }
}

//EOF