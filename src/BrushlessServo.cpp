// Brushless motor library
// copyright Alexandre Iooss, 2017-2018
// Please see README.txt for license information

#include "BrushlessServo.h"
#include "Arduino.h"

unsigned int BrushlessServo::sinTable[PRECISION];
bool BrushlessServo::sinTableEmpty = true;


BrushlessServo::BrushlessServo() {
}


void BrushlessServo::attach(int p1, int p2, int p3) {
  // Set output pins
  pin1 = p1;
  pin2 = p2;
  pin3 = p3;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);

  // Generate sin table for faster control
  if (sinTableEmpty) {
    for (int i=0; i<PRECISION; i++) {
      float angle = i*2.*M_PI/(float)PRECISION;
      sinTable[i] = round((sin(angle)+1.)/2.*FLOAT_RESOLUTION);
    }
    sinTableEmpty = false;
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
  analogWrite(pin1, (float)power*sinTable[offset1]/FLOAT_RESOLUTION);
  analogWrite(pin2, (float)power*sinTable[offset2]/FLOAT_RESOLUTION);
  analogWrite(pin3, (float)power*sinTable[offset3]/FLOAT_RESOLUTION);
}


void BrushlessServo::write(float degree) {
  int offset = degree*PRECISION*n_cycles/360;
  writeOffset(offset);
}


void BrushlessServo::setOutputPower(int p) {
  power = p;
}


void BrushlessServo::setCycles(int n) {
  n_cycles = n;
}

