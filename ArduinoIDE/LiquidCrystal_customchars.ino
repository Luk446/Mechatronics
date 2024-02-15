
#include <LiquidCrystal.h>

//init liquid crystal positions and connection 

const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Define custom characters
byte heart[] = {
  B01110,
  B01010,
  B01110,
  B01010,
  B01010,
  B11111,
  B10001,
  B11111
};

byte smiley[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  // Define the custom characters at positions 0 and 1
  lcd.createChar(0, heart);
  lcd.createChar(1, smiley);

  // Initialize the LCD with 16 columns and 2 rows
  lcd.begin(16, 2);

  // text
  lcd.setCursor(0, 0);
  lcd.print("Prosthetic Hand Exp");
  lcd.setCursor(0,1);
  lcd.print("Luke and Jam");

  // first char 
  //lcd.setCursor(15, 0);
  //lcd.write((uint8_t)0);

  // Set the cursor to the 15th  position of the second line
  //lcd.setCursor(15, 1);
  //lcd.write((uint8_t)1);
}

void loop() {
  // Your main code goes here
}
