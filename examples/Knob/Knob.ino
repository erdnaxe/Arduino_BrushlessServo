/*
 Controlling a brushless servo position using a potentiometer (variable resistor)
 original program by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 10 Jul 2017
 by Alexandre Iooss
*/

#include <BrushlessServo.h>

BrushlessServo myservo;  // create servo object to control a brushless servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9, 10, 11);  // attaches PWM pins to the brushless servo object
}

void loop() {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  
  int angle = map(val, 0, 1023, 0, 180);   // scale it to use it with the servo (value between 0 and 180)
  myservo.write(angle);           // sets the brushless position according to the scaled value
  
  delay(15);                           // waits for the brushless servo to get there
}

