int LDR0 = A0;      // LDRs siguelíneas
int LDR1 = A1;
int LDR2 = A2;
int LDR3 = A3;
int LDR4 = A4;
int BIA = 6;        // Pines módulo L9110
int BIB = 7;
int AIA = 8;
int AIB = 9;
int speed = 255;
char btcode;        // Info incoming by serial.
float kp=.04;       // PID
float ki=0.00002;
float kd=50;
float p,d;
float i=0;
float p_old=0;
int u;

void setup() {
  pinMode(LDR0, INPUT);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);
  pinMode(AIA, OUTPUT); // LEFT
  pinMode(AIB, OUTPUT); // LEFT
  pinMode(BIA, OUTPUT); // RIGHT
  pinMode(BIB, OUTPUT); // RIGHT
  Serial.begin(9600);
}

void loop() {

// Bloque PID siguelíneas  
p= 2*analogRead(LDR0) + analogRead(LDR1) - analogRead(LDR3) - 2*analogRead(LDR4); // WTF con sensor central?
i=i+p;
d=p-p_old;
p_old=p;
if ((p*i)<0) i=0; // corrects overshooting - integral windup
  u=kp*p+ki*i+kd*d; // Suma PID
  if (u>0){ // turn right
    lforward()
    rbackward()
  }
    if (u<0){ // turn left
      lbackward()
      rforward()
    }

/* Bloque mando a distancia
 *       F
 *    G     I
 *  L    S    R
 *    H     J
 *       B               */
if (Serial.available() > 0) {
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

// Bloque movimientos L9110  
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
