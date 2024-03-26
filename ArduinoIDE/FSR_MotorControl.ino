/*

  Articulation of a DC motor using FSR

  Structure as follows : init -> setup() -> loop()

  initialise pins and math vars

  start printing and then define the mode of op of pins

  read sensors and organise FSR vals for relevance 
  if loop with three cases depending on serial value of FSR 


*/

const int fsrPin = A0;          // Analog pin connected to FSR
const int motorSpeedPin = 9;    // PWM pin for motor speed control
const int fsrThreshold = 10;   

// pins for motor shield
int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;

// binary direction state
bool directionState;

int tact;
int val;

void setup() {

  // begin printing
  Serial.begin(9600);

  // define press sen pin func
  pinMode(tact,INPUT);

  // motor shield pin mode set
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

}


void loop() {
  // Read the analog value from FSR
  //int fsrReading = analogRead(A0);

  // read pressure sense
  tact = analogRead(A0);
  // map to match PWM
  tact = map(tact,0,20,0,255);


  // print for debug + app linkage
  Serial.println("PV: ");
  Serial.println(tact);
  Serial.println("TV ");
  Serial.println(10); 
  delay(100); // flooding delay


  if(tact>500){
    analogWrite(pwmPin, 255);
    digitalWrite(directionPin, LOW);
    delay(5);
    digitalWrite(brakePin, LOW);
    delay(500);
  }
  else if(tact >= 100 && tact <= 499){
    delay(10);
    analogWrite(pwmPin, 80);
    digitalWrite(directionPin, HIGH);
    delay(5);
    digitalWrite(brakePin, LOW);
    delay(500);
  }
  else{
    delay(10);
    analogWrite(pwmPin, 0);
    digitalWrite(directionPin, LOW);
    delay(5);
    digitalWrite(brakePin, LOW);
    delay(10);    
  }

}
