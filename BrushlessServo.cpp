// Brushless motor library
// copyright Alexandre Iooss, 2017-2018
// Please see README.txt for license information

#include "BrushlessServo.h"
#include "Arduino.h"


BrushlessServo::BrushlessServo() {
  _power = PWMRANGE;
}


void BrushlessServo::attach(int pin1, int pin2, int pin3) {
  // Set output pins
  _pin1 = pin1;
  _pin2 = pin2;
  _pin3 = pin3;
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  pinMode(_pin3, OUTPUT);

  // Generate sin table for faster control
  for (int i=0; i<PRECISION; i++) {
    float angle = i*2.*M_PI/(float)PRECISION;
    _sinTable[i] = round((sin(angle)+1.)/2.*32767);  // 32768 because 16 bits
  }
}


void BrushlessServo::writeOffset(int offset) {
  // Offset must be positive
  offset = offset%PRECISION;
  if (offset < 0)
    offset = PRECISION + offset;

  // Calculate each offset
  int offset1 = offset;
  int offset2 = (offset+(PRECISION*2/3))%PRECISION;
  int offset3 = (offset+(PRECISION*4/3))%PRECISION;

  // Set PWM
  analogWrite(_pin1, _power * _sinTable[offset1]/32767.);
  analogWrite(_pin2, _power * _sinTable[offset2]/32767.);
  analogWrite(_pin3, _power * _sinTable[offset3]/32767.);
}


void BrushlessServo::write(float degree) {
  int offset = degree/360.*1024;
  write(offset);
}


void BrushlessServo::setOutputPower(int power) {
  _power = power*PWMRANGE/1024.;
}


