// Brushless motor library
// copyright Alexandre Iooss, 2017-2018
// Please see README.txt for license information

#ifndef BRUSHLESS_SERVO_h
#define BRUSHLESS_SERVO_h

#include "Arduino.h"
#include "SinArray.h"

#ifndef PWMRANGE     //PWMRANGE is defined on some microcontrollers such as ESP8266
#define PWMRANGE 255 // Default for ATMEGA328
#endif

class BrushlessServo
{
public:
  void attach(int p1, int p2, int p3); // Initialization
  void write(float angle);             // Move to a angle in degree
  void setOutputPower(int p);          // Set a power multiplier between 0 (min) and PWMRANGE (max)
  void setCycles(int n);               // Set how many sinusoide period are needed for a revolution

private:
  SinArray sinArray;
  int pins[3];
  int power = PWMRANGE;
  int n_cycles = 8;
};

#endif
