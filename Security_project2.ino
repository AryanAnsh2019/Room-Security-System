#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "IFTTTWebhook.h"
#define WIFI_SSID "Tayal"
#define  WIFI_PASSWORD "9810294722"
#define IFTTT_API_KEY "dXcKO63ZXO7vFJbcjr5Rwq"
#define IFTTT_EVENT_NAME "motiondetected"
LiquidCrystal_I2C lcd(0x27, 16, 2);
const byte ROWS = 4;
const byte COLS = 4;
int inputpin = 32, pinstate = 0;
boolean check;
int i = 0, ind;
char code[4] = {}, password[4] = {'1', '7', '5', '3'};
char keys[ROWS][COLS] = {
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'},
};
byte rowPins[ROWS] = {4, 5, 18, 19};
byte colPins[COLS] = {13, 12, 27, 26};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  pinMode(15, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(inputpin, INPUT);
  //  WiFi.mode(WIFI_STA);
  //  if (WiFi.status() != WL_CONNECTED)
  //  {
  //    Serial.print("Attempting to connect to SSID: ");
  //    Serial.println(WIFI_SSID);
  //    while (WiFi.status() != WL_CONNECTED)
  //    {
  //      WiFi.begin("Tayal", "9810294722");
  //      Serial.print(".");
  //      delay(5000);
  //    }
  //    Serial.println("\nConnected.");
  //  }
}
char enteredpassword[4] = {};
int currentindex = 0;
int keyPadState()
{
  char key = keypad.getKey();
  boolean check = false;
  int keyPadState = 0; //0 In progress, 1=Validate, 2=invalidated, 3 firstkeyentered
  if (key)
  {
    lcd.print(key);
    digitalWrite(15, HIGH);
    delay(50);
    digitalWrite(15, LOW);
    delay(50);
    enteredpassword[currentindex] = key;
    currentindex++;
      lcd.setCursor(currentindex-1, 1);
      lcd.print(key);
      delay(200);
      lcd.setCursor(currentindex-1, 1);
      lcd.print("*");
      //lcd.print();
    if (currentindex > 3)
    {
      check = true;
      for (currentindex = 0; currentindex < 4; currentindex++)
      {
        if (password[currentindex] != enteredpassword[currentindex])
        {
          check = false;
          currentindex = 0;
          break;
        }
      }
      if (check == false)
      {
        keyPadState = 2;
        return keyPadState;
      }
      else
      {
        keyPadState = 1;
        return keyPadState;
      }
    }
  }
}
void loop()
{
  pinstate = digitalRead(inputpin);
  int isCodeCorrect;
  isCodeCorrect = keyPadState();
  if (pinstate == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Enter password : ");
    isCodeCorrect = keyPadState();
  }
  if (isCodeCorrect == 0)
  {
  }
  if (isCodeCorrect == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acess Granted");
    while (isCodeCorrect == 1)
    {
      digitalWrite(25, HIGH);
      delay(50);
      digitalWrite(25, LOW);
      delay(50);
    }
    Serial.println("Acess granted");
  }
  if (isCodeCorrect == 2)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong Password!");
    while (isCodeCorrect == 2)
    {
      digitalWrite(15, HIGH);
      digitalWrite(23, HIGH);
      delay(50);
      digitalWrite(15, LOW);
      digitalWrite(23, LOW);
      delay(50);
      Serial.println("Acess denied");
    }
  }
  if (isCodeCorrect == 3)
  {

  }
}
