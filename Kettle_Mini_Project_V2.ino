//Arduino Mini Project to create "Temperature Controlled Water Kettle"
//Mini Project by : Hrudayesh 
//yotube.com @Hrudayesh
//Relay module I have used in this Poject is Active Low,change the code according for your Project


//Including Libraries for I2C LCD Display ,Temperature Sensor and other libraries required for communucation Protocol
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <OneWire.h>


//Declaring constants for pins we are using in the project
#define relayPin 8
#define selectButtonPin 7
#define potPin A0
#define tempSensorPin 5
#define buzzerPin 9


LiquidCrystal_I2C lcd(0x27,16,2);

OneWire oneWire(tempSensorPin);

DallasTemperature sensors(&oneWire);

int celsius = 0;
int select = 0;
int tempRange = 0;
int range;
int tempSelect;
int selectPin = 2;

void setup()
{
  lcd.init();
  lcd.setCursor(0,0);
  lcd.backlight();
  sensors.begin();

  pinMode(relayPin,OUTPUT);
  pinMode(selectButtonPin,INPUT);
  pinMode(potPin,INPUT);
  pinMode(tempSensorPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(selectPin,INPUT);


  lcd.setCursor(0,0);
  lcd.print("Select Temp Val");
  lcd.setCursor(15,1);
  lcd.print("C");

  Serial.begin(9600);
  digitalWrite(relayPin,HIGH);

}

void loop()
{

 
  while(select != 1)
  {
    lcd.setCursor(0,0);
    lcd.print("Select Temp Val");
    lcd.setCursor(15,1);
    lcd.print("C");

    select = digitalRead(selectButtonPin);
    range = analogRead(A0);
    tempRange = map(range,0,1024,20,101);

    if(tempRange != 100)
    { 
      lcd.setCursor(12,1);
      lcd.print("0");
      lcd.setCursor(13,1);
      lcd.print(tempRange);
      //delay(1000);

    }

    if(tempRange == 100)
    {
      lcd.setCursor(12,1);
      lcd.print(tempRange);
      //delay(1000);
  
    }
  }

  if(select == 1)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Heating Water");
    lcd.setCursor(0,1);
    lcd.print("Temp");
    lcd.setCursor(15,1);
    lcd.print("C");

    tempSelect = tempRange;
    
  }

  //sensors.requestTemperatures();
  //celsius = sensors.getTempCByIndex(0);

    

    while(celsius < tempSelect)
    {
      digitalWrite(relayPin,LOW);
      sensors.requestTemperatures();
      celsius = sensors.getTempCByIndex(0);

      if(celsius == -127)
      {
        lcd.clear();
      }

      else
      {
        lcd.setCursor(0, 0);
        lcd.print("Heating Water");
        lcd.setCursor(0,1);
        lcd.print("Temp");
        lcd.setCursor(15,1);
        lcd.print("C");
      
        lcd.setCursor(13,1);
        lcd.print(celsius);
        Serial.println(celsius);
      }

    }
    Serial.println(celsius);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Water Heated");
    lcd.setCursor(0,1);
    lcd.print("Kettle is OFF");

    digitalWrite(relayPin,HIGH);

    tone(buzzerPin,1000);
    delay(1000);
    noTone(buzzerPin);
    
    lcd.clear();
    select = 0;


  
}
