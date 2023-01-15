#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

#include <Servo.h>

// C++ code
//
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9,8,7,6};
byte colPins[COLS] = {5,4,3,2};
String toShow = "";
String correctPassword = "1456";
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myservo;
int pos = 0;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(10, OUTPUT);
  myservo.attach(11);
}

void loop()
{
  char customKey = customKeypad.getKey();

  if (customKey) {
    digitalWrite(10, HIGH);
    delay(15);
    digitalWrite(10, LOW);
    // check if it's the D key
    
    if (customKey == 'D') {
      if (toShow.length() > 0) {
        toShow.remove(toShow.length()-1);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(toShow);
      }
      return;
    }

    if (customKey == 'C') {
      digitalWrite(10, HIGH);
      delay(15);
      digitalWrite(10, LOW);
      delay(15);
      digitalWrite(10, HIGH);
      delay(15);
      digitalWrite(10, LOW);
      toShow = "";
      lcd.clear();
      return;
    }
    
    // check if it's the A key
    
    if (customKey == 'A') {
      if (toShow == correctPassword) {
        lcd.clear();
        lcd.setCursor(0,0);
    	  lcd.print("Correct Password");
        digitalWrite(10, HIGH);
        delay(250);
        digitalWrite(10, LOW);
        for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
          // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(15);                       // waits 15 ms for the servo to reach the position
        }
        delay(250);
        digitalWrite(10, HIGH);
        delay(250);
        digitalWrite(10, LOW);

       for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
        myservo.write(pos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15 ms for the servo to reach the position
      }

      } else {
        lcd.clear();
        lcd.setCursor(0,0);
    	  lcd.print("Incorrect Password");
        digitalWrite(10, HIGH);
        delay(2000);
        digitalWrite(10, LOW);
      }
      return;
    }
    

    lcd.clear();
    lcd.setCursor(0,0);
    toShow += customKey;
    lcd.print(toShow);
    Serial.println(customKey); 
  }
}