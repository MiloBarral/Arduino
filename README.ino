/* # Arduino
Arduino sketches

Temporary edit on readme.md, this should be a separate file.

Code not checked, only a draft:
Resources
http://arduino.cc/en/Reference/analogRead
http://arduino.cc/en/pmwiki.php?n=Reference/Map
http://arduino.cc/en/tutorial/knob
http://arduino.cc/en/Tutorial/LiquidCrystal
*/

#include <LiquidCrystal.h>
#include <servo.h>

joystick_x = A0;
joystick_y = A1;

Servo servo_x;
Servo servo_u;

void setup() { 
  servo_x.attach(9);
  servo_y.attach(10);
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
  lcd.begin(16, 2);
}

void loop() {
  int valx = analogRead(joystick_x);	// Scaling analog value from joystick to the servo angle.
   val_x = map(valx, 0, 1023, 0, 179);

  int valy = analogRead(joystick_y);    // Scaling analog value from joystick to the servo angle.
   val_y = map(valy, 0, 1023, 0, 179);

  analogWrite(servo_x, val_x);		 
  analogWrite(servo_y, val_y);		

  lcd.setCursor(0, 1);
  lcd.println(val_x);
  lcd.print(val_y);
}
