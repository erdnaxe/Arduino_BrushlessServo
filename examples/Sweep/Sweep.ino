/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified on 11 Jul 2017
 by Alexandre Iooss
*/

#include <BrushlessServo.h>

BrushlessServo myservo;  // create servo object to control a brushless motor as a servo

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9, 10, 11);  // attaches PWM pins 9, 10, 11 to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}

