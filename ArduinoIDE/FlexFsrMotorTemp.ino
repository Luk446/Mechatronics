/*

  Articulation of a DC motor using FSR

  Structure as follows : init -> setup() -> loop()

  initialise pins and math vars

  start printing and then define the mode of op of pins

  read sensors and organise FSR vals for relevance 
  if loop with three cases depending on serial value of FSR 

  now iteration with flex bend sensor


*/

// flex bend math vars init + flex pin init
const int flexPin = A2; // pin
const float VCC = 5;			// using 5v from shield
const float R_DIV = 10000.0;	// R in voltage divider
const float flatResistance = 25000.0;	// R at  flat
const float bendResistance = 100000.0;	// R at 90 deg

// define pin ints
const int fsrPin = A0;          // Analog pin connected to FSR
const int motorSpeedPin = 9;    // PWM pin for motor speed control
const int fsrThreshold = 10; 

// pins for motor shield
int directionPin = 12;
int pwmPin = 3;
int brakePin = 9;

// binary direction state
bool directionState;

// integers for math lines
int tact;
int tact2;
int val;

// temperature setup
int TempPin =A5; 
int inputValue = 0; // integer value from ADC
float inputVoltage = 0; //float value of voltage measured
float tempmath1 = 0;    // float value for tempmath1
float tempmath2 = 0;    // float value for tempmath2

void setup() {

  // begin printing
  Serial.begin(9600);

  // define press sen pin func
  pinMode(tact,INPUT);

  // motor shield pin mode set
  pinMode(directionPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(brakePin, OUTPUT);

  // flex sensor pinmode
  pinMode(flexPin, INPUT);

}


void loop() {

  // flex read and calc
  int ADCflex = analogRead(flexPin);
	float Vflex = ADCflex * VCC / 1023.0;
	float Rflex = R_DIV * (VCC / Vflex - 1.0);
  float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);


  // fsr read and map
  tact = analogRead(fsrPin); // read pressure sense
  tact2 = analogRead(fsrPin);
  tact = map(tact,0,20,0,255); // map to match PWM

  // temp maths
  inputValue = analogRead(TempPin); // reads value from analogue pin A7
  inputVoltage = inputValue * 5.0/1024; // converts raw reading to voltage
  tempmath1 = inputVoltage / -0.0522;  
  tempmath2 = tempmath1 +118.5;

  // print for debug + app linkage
  Serial.print("PV: "); // signal
  Serial.println(tact2); // fsr val

  Serial.print("TV: "); // signal
  int tempclean = (int)tempmath2; // clean signal for C# proc
  Serial.println(tempclean); // temp val

  Serial.print("AV: ");
  int angleclean = (int)angle;
  Serial.println(angleclean);

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
    digitalWrite(directionPin, LOW);
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
