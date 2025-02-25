#include "Infrared.h"
#include "Arduino.h"

void Infrared::Attach(pin measurePin, bool longRange) {
  this->measurePin = measurePin;
  this->longRange = longRange;

  if (longRange) {
    pinMode(measurePin, INPUT);
  }
}

Infrared::Color Infrared::GetColor() {
  // Measure pin and return color (Infrared::WHITE, Infrared::GRAY, Infrared::BLACK)

  if (!longRange) {
    int total = 0;

    for (int i = 0; i < 10; i++) {
      total += analogRead(this->measurePin);
    }

    int measurement = total / 10;

    if (measurement < THRESH_GRAY) {
      return BLACK;
    } else if (measurement >= THRESH_GRAY && measurement < THRESH_WHITE) {
      return GRAY;
    }

    return WHITE;
  } else {
    return digitalRead(this->measurePin) == HIGH ? BLACK : WHITE;
  }
}


