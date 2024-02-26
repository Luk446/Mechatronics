/*  
    C MOTOR CONTROL CODE 
    Created by Luke Edgecombe (2450027)
    Syntax derived from the arduiniogetstarted.com site

*/

// init motor control pins from the shield

// speed determinant 
const int ENA = 1;

// actuation control pins
const int IN = 2;
const int OUT = 3;

void setup() {
  
// Init the previously declared pins into a certain type
  pinMode(ENA, OUTPUT);
  pinMode(IN, OUTPUT);
  pinMode(OUT, OUTPUT);

// set speed
digitalWrite(ENA, HIGH);

}

void loop() {
// basic test loops infinite 

// extend motor

  digitalWrite(IN, LOW);
  digitalWrite(OUT, HIGH);

// pause at the top
  delay(20000);

// retract
  digitalWrite(IN, LOW);
  digitalWrite(OUT, HIGH);

//wait
  delay(20000);
}

