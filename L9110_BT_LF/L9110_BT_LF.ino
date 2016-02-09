/*

             ARDUINO PRO MICRO

                |TX0   RAW| Batteries V+
                |RX1   GND| Batteries GND
Breadboard GND  |GND   RST|
Breadboard GND  |GND   VCC| Breadboard 5V
BT Rx           |2~    #A3| Input for outer left LDR sensor
BT Tx           |3     #A2| Input for center left LDR sensor
                |4#    #A1| Input for center right LDR sensor
                |5~    #A0| Input for outer right LDR sensor
                |6~#    15| L9110 BIA
                |7      14| L9110 BIB
                |8#     16| L9110 AIA
                |9~#  #~10| L9110 AIB 

~ PWM
# Analog

*/

#include <SoftwareSerial.h> // Virtual serial library
SoftwareSerial BT1(2,3);    // Rx,Tx
int LDR0 = A0;      // LDRs linefollower
int LDR1 = A1;
int LDR2 = A2;
int LDR3 = A3;
int BIA = 15;        // L9110 pins
int BIB = 14;
int AIA = 16;
int AIB = 10;
int speed = 255;
char btcode;        // Info incoming by serial
float kp=.04;       // PID
float ki=0.00002;
float kd=50;
float p,d;
float i=0;
float p_old=0;
int u;

void setup() {
  Serial.begin(9600);   // Begins serial comunication with PC
  BT1.begin(9600);      // Begins serial comunication with BT
  pinMode(LDR0, INPUT);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(AIA, OUTPUT); // LEFT Motor
  pinMode(AIB, OUTPUT); // LEFT Motor
  pinMode(BIA, OUTPUT); // RIGHT Motor
  pinMode(BIB, OUTPUT); // RIGHT Motor

}

void loop() {

// Bloque PID siguelíneas  
p= 2*analogRead(LDR0) + analogRead(LDR1) - analogRead(LDR2) - 2*analogRead(LDR3); 
i=i+p;
d=p-p_old;
p_old=p;
if ((p*i)<0) i=0; // corrects overshooting - integral windup
  u=kp*p+ki*i+kd*d; // PID 
  if (u>0){ // turn right
    lforward()
    rbackward()
  }
    if (u<0){ // turn left
      lbackward()
      rforward()
    }

/* Remote control
 *       F
 *    G     I
 *  L    S    R
 *    H     J
 *       B               */
if (BT1.available() > 0) {
    btcode = Serial.read();
  }
  switch (btcode)
  {
    case 'F':
      lforward()
      rforward()
      break;

    case 'B':
      lbackward()
      rbackward()
      break;

    case 'R':
      lforward()
      rbackward()
      break;

    case 'L':
      lbackward()
      rforward()
      break;
  }
}

// L9110 movements
void lforward() {
  analogWrite(AIA, 0);
  analogWrite(AIB, speed);
}

void lbackward() {
  analogWrite(AIA, speed);
  analogWrite(AIB, 0);
}

void rforward() {
  analogWrite(BIA, 0);
  analogWrite(BIB, speed);
}

void rbackward() {
  analogWrite(BIA, speed);
  analogWrite(BIB, 0);
}
