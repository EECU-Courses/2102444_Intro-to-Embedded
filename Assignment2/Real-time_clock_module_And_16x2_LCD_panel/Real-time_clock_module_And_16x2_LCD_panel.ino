#include <Wire.h> 
#include "RTClib.h" 
#include <LiquidCrystal_I2C.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); 
RTC_DS3231 RTC;

void setup() { 
  Serial.begin(9600); 
  // lcd.begin(16, 2); // Initialize the LCD with 16 columns and 2 rows
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Wire.begin(); 
  RTC.begin(); 
  RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
} 

// Function to display number parameter at lcd
void print2digits(int number) { 
  if (number >= 0 && number < 10) {
    lcd.print('0');
  } 
  lcd.print(number, DEC);
} 

// Function for print current time at lcd
void printDateTime(DateTime dt) {

  // display Time in lcd
  lcd.setCursor(0, 0); // Set cursor to the first row
  lcd.print("Time: "); 
  print2digits(dt.hour()); 
  lcd.print(':'); 
  print2digits(dt.minute()); 
  lcd.print(':'); 
  print2digits(dt.second()); 

  // display Date in lcd
  lcd.setCursor(0, 1); // Set cursor to the second row
  lcd.print("Date: ");
  print2digits(dt.day()); 
  lcd.print('/'); 
  print2digits(dt.month()); 
  lcd.print('/'); 
  lcd.print(dt.year(), DEC); 
}

void loop() { 
  DateTime now = RTC.now(); 
  printDateTime(now);
  delay(1000); 
}
