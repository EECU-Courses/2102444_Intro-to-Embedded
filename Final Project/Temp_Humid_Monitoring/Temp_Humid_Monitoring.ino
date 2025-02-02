/*
 * Uses MIFARE RFID card using RFID-RC522 reader
 * Uses MFRC522 - Library
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *
 * More pin layouts for other boards can be found here: https://github.com/miguelbalboa/rfid#pin-layout
*/

// -----------------------------------------------------------------------------------------

/*
  The following pins are usable for PinChangeInterrupt:
  Arduino Uno/Nano/Mini: All pins are usable
  Arduino Mega: 10, 11, 12, 13, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64),
               A11 (65), A12 (66), A13 (67), A14 (68), A15 (69)
  Arduino Leonardo/Micro: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI)
  HoodLoader2: All (broken out 1-7) pins are usable
  Attiny 24/44/84: All pins are usable
  Attiny 25/45/85: All pins are usable
  Attiny 13: All pins are usable
  Attiny 441/841: All pins are usable
  ATmega644P/ATmega1284P: All pins are usable
*/

#include "PinChangeInterrupt.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <DHT.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

// choose a valid PinChangeInterrupt pin of your Arduino board
#define pinAlert 13

#define BuzzerPin 2   // Define Pin of Buzzer

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set up the LCD's number of columns and rows

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

// Set up Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

// Define the Keymap of Keypad
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {39, 41, 43, 45}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {37, 35, 33, 31}; // Connect to the column pinouts of the keypad

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Base Station 1 DHT11 (Temp & Humid Sensor)
#define Base1DHTPIN 32    // Digital pin connected to the DHT sensor
#define Base1DHTTYPE DHT11   // Type of DHT sensor used (DHT11 or DHT22)
// Base Station 2 DHT11 (Temp & Humid Sensor)
#define Base2DHTPIN 22    // Digital pin connected to the DHT sensor
#define Base2DHTTYPE DHT11   // Type of DHT sensor used (DHT11 or DHT22)
// Base Station 3 DHT11 (Temp & Humid Sensor)
#define Base3DHTPIN 42    // Digital pin connected to the DHT sensor
#define Base3DHTTYPE DHT11   // Type of DHT sensor used (DHT11 or DHT22)

DHT dht1(Base1DHTPIN, Base1DHTTYPE);  // Declare dht1 as Base1 DHT11 
DHT dht2(Base1DHTPIN, Base1DHTTYPE);  // Declare dht1 as Base2 DHT11 
DHT dht3(Base1DHTPIN, Base1DHTTYPE);  // Declare dht1 as Base3 DHT11 

const int redPin = 11;   // PWM pin for red color
const int greenPin = 10; // PWM pin for green color
const int bluePin = 9;  // PWM pin for blue color

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void HumidAlert(float humid) {
  if (humid < 70.00) {
    digitalWrite(BuzzerPin, HIGH);  // turn the Buzzer on
  } else {
    digitalWrite(BuzzerPin, LOW);  // turn the Buzzer off
  }
}

// Function for display Temp&Humid in LCD
void DisplayToLCD(char channel,float temp,float humid) {

  lcd.setCursor(0, 0);  // Set cursor to the first row
  lcd.print("Channel: ");
  lcd.print(channel);

  lcd.setCursor(0, 1);  // Set cursor to the first row
  /*  'A' : Display Temperature
      'B' : Display Humidity    */
  lcd.print("Select Mode(A/B)");

  char kpd = keypad.getKey(); // Get key pressed
  while (kpd!='A' || kpd!='B') {
    kpd = keypad.getKey(); // Get key pressed
    Serial.println(kpd);
    delay(100);
    if (kpd=='A' || kpd=='B') {
      lcd.setCursor(0, 1);  // Set cursor to the first row
      lcd.print("                "); // 16 spaces to clear the row
      break;
    }
  }

  switch (kpd) {
    case 'A': 
      lcd.setCursor(0, 1);  // Set cursor to the first row
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print(" C");
      break;
    case 'B': 
      lcd.setCursor(0, 1);  // Set cursor to the first row
      lcd.print("Humid: ");
      lcd.print(humid);
      break;
    default:
      lcd.setCursor(0, 1);  // Set cursor to the first row
      lcd.print("Temp: ");
      lcd.print(temp);
      lcd.print(" C");
  }

}

void setup() {
  Serial.begin(9600);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  lcd.init(); // initialize the lcd
  lcd.backlight();
  Wire.begin();
  SPI.begin();                     // Init SPI bus
  mfrc522.PCD_Init();              // Init MFRC522 card

  pinMode(BuzzerPin, OUTPUT);     // Set Buzzer Pin Mode
  
  // Set RGB Pin to be Output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // attach the new PinChangeInterrupts and enable event functions below
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(pinAlert), Alert, RISING);
}

void loop() {

  char kpd = keypad.getKey(); // Get key pressed

  float temp;
  float humid;
  bool correctChannel = true;
  if (kpd != NO_KEY && mfrc522.PICC_IsNewCardPresent()){ // If a key is pressed And Card Detected

    lcd.clear(); // Clear the LCD
    Serial.println(kpd);

    switch (kpd) {
      case '1': 
        temp = dht1.readTemperature();
        humid = dht1.readHumidity();
        break;
      case '2': 
        temp = dht2.readTemperature();
        humid = dht2.readHumidity();
        break;
      case '3': 
        temp = dht3.readTemperature();
        humid = dht3.readHumidity();
        break;
      default:
        correctChannel = false;
    }

    if (correctChannel) {
      // Adjust LED color based on temperature
      if (temp >= 10) {
        setColor(255, 0, 0); // Red
        HumidAlert(humid);
      } else if (temp <= 20) {
        setColor(0, 0, 255); // Blue
      } else {
        setColor(0, 255, 0); // Green
      }
      DisplayToLCD(kpd, temp, humid);
      delay(500);
    } else {
      lcd.setCursor(0, 0);  // Set cursor to the first row
      lcd.print("Error");
      lcd.setCursor(0, 1);  // Set cursor to the first row
      lcd.print("Error");
      // lcd.print("");
      delay(500);
    }
  }
  
}

void Alert() {
  // Toggle the state of the buzzer
  if (digitalRead(BuzzerPin) == HIGH) {
    digitalWrite(BuzzerPin, LOW);
  } else {
    digitalWrite(BuzzerPin, HIGH);
  }
}
