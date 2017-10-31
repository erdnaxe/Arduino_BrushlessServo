// Brushless motor library
// copyright Alexandre Iooss, 2017-2018
// Please see README.txt for license information

#include "BrushlessServo.h"

void BrushlessServo::attach(int p1, int p2, int p3)
{
  // Set output pins
  pins[0] = p1;
  pins[1] = p2;
  pins[2] = p3;
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);

  // Generate sin table for faster control
  sinArray.generate();
}

void BrushlessServo::write(float angle)
{
  float real_angle = n_cycles * angle;

  int pwm1 = (float)power * (sinArray.getSinDegree(real_angle) + 1.) / 2.;
  int pwm2 = (float)power * (sinArray.getSinDegree(real_angle + 120) + 1.) / 2.;
  int pwm3 = (float)power * (sinArray.getSinDegree(real_angle + 240) + 1.) / 2.;

  // Set PWMs
  analogWrite(pins[0], pwm1);
  analogWrite(pins[1], pwm2);
  analogWrite(pins[2], pwm3);
}

void BrushlessServo::setOutputPower(int p)
{
  power = p;
}

void BrushlessServo::setCycles(int n)
{
  n_cycles = n;
}
