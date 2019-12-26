#include<Wire.h>
#include <MQ2.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int LED = 6;
int flame_sensor = 4; 
int flame_detected;

int Analog_Input = A0;
int sensorValue = A1;

int buzzer = 5;
int role=7;   //relay
int sensorThres = 850;
int lpg, co, smoke;
MQ2 mq2(Analog_Input);
void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(buzzer, OUTPUT);
  pinMode(Analog_Input, INPUT);
  pinMode(sensorValue, INPUT);
  pinMode(role,OUTPUT); 
  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);
  
  lcd.backlight();
  lcd.init();
   mq2.begin();
}
void loop()
{
  float* values= mq2.read(true); //set it false if you don't want to print the values in the Serial
//  lpg = values[0];
  lpg = mq2.readLPG();
//  co = values[1];
  co = mq2.readCO();
//  smoke = values[2];
  smoke = mq2.readSmoke();
  lcd.setCursor(0,0);
  lcd.print("LPG:");
  lcd.print(lpg);
  lcd.print(" CO:");
  lcd.print(co);
  lcd.setCursor(0,1);
  lcd.print("SMOKE:");
  lcd.print(smoke);
  lcd.print(" AQ:");
  lcd.print(sensorValue);
  delay(1000);


  int top = analogRead(Analog_Input);
  Serial.println(top);
  Serial.print("AirQua=");
  Serial.print(sensorValue, DEC);
  Serial.print('\n');
  if (top > sensorThres)
  {
    tone(buzzer, 1000,1000);
    digitalWrite(role,LOW);
  }
  else
  {
    noTone(buzzer);
    digitalWrite(role,HIGH);
  }
  delay(100);

  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 0)
  {
    Serial.println("Flame detected...! take action immediately.");
//    digitalWrite(buzzer, HIGH);
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
//    digitalWrite(buzzer, LOW);
    digitalWrite(LED, LOW);
  }
}
