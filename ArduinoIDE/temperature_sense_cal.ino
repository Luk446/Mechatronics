#include <Servo.h>
#include <LiquidCrystal.h>

//init liquid crystal positions and connection 

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// custom character 

byte customChar[8] = {
	0b00000,
	0b01110,
	0b10001,
	0b10001,
	0b10001,
	0b01110,
	0b00000,
	0b00000
};

Servo myservo;

//init. emg sensors

const int arminPin = A15;
int arminValue = 0;
int filteredValue = 0;
const int filterStrength = 4;

//init motor and buzz

int val;
int tact;
int buzz = 22;

//init temp display

int tempPin = A7;
int intempValue = 0;
float inputVoltage = 0;
float tempmath1 = 0;
float tempmath2 = 0;

//init extension display

int emgdisplay = 0;
int valemgdisplay =0;


void setup() {

  //start the print

  Serial.begin(9600);

  //init lcd config and base text

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp =");
  lcd.setCursor(15, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("pos. =");
  lcd.createChar(0, customChar);
  lcd.setCursor(15, 1);
  lcd.write((byte)0);


  //attach servo and define the buzz and pressure sensor pin function

  myservo.attach(40);
  pinMode(buzz, OUTPUT);
  pinMode(tact, INPUT);
  
}

void loop() {

  //temp sense and print

  intempValue = analogRead(tempPin);
  inputVoltage = intempValue * 5.0 / 1024;
  tempmath1 = inputVoltage / -0.0522;
  tempmath2 = tempmath1 + 73.26425;

  lcd.setCursor(10, 0);
  lcd.print(tempmath2);

  //position sense and print


  valemgdisplay = analogRead(A15);

  valemgdisplay = map(valemgdisplay, 0, 1023, 0, 180);

  //Serial.println(valemgdisplay);

  lcd.setCursor(10, 1);
  lcd.print(valemgdisplay);
  delay(100);
  lcd.setCursor(10,1);
  lcd.print("   ");

  //pressure sensor read

  int sensorValue2 = analogRead(A12);

  tact = analogRead(A12);
  tact = map(tact, 0, 970, 0, 970);

  Serial.println(tact);
  
  //filter and read for emg

  arminValue = analogRead(arminPin);
  filteredValue = (filteredValue * (filterStrength - 1) + arminValue) / filterStrength;  // apply low-pass filter
  filteredValue = constrain(filteredValue, 0, 1023);                                     // constrain filtered value to [0, 1023]
  int servoValue = map(filteredValue, 0, 1023, 0, 180);                                  // map filtered value to servo value


    //tactile feedback

  if(tact>100){

    digitalWrite(buzz,HIGH);
    delay(10);
    digitalWrite(buzz,LOW);

    }


  //temperature overheat loops + stopper

  if (tempmath2 < 30) {

    myservo.write(servoValue);


  }

  //cooldown period for temp

  else {
    delay(100);
  }

  //Serial.println(servoValue);
  //Serial.println(arminPin);
  delay(15);
}
