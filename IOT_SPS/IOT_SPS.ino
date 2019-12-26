#include <Servo.h>
#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 11 
#define DIO 12
#define TEST_DELAY 2000
TM1637Display display(CLK, DIO);

const int BarUp = 90, BarDown = 0;
bool isEntryBarOpen = false, isExitBarOpen = false;
const int irEntryPin = A5; // IR Entry
const int irExitPin = A4; // Exit Gate IR

//const int spotOne = A0, spotTwo = A1, spotThree = A2, spotFour = A3;

int entryServoPin = 8;
int exitServoPin = 9;

int entryIRSensorValue = 0;
int exitIRSensorValue = 0;
int count=0;


int out1 = 2; //led
int out2 = 3; //led
int out3 = 4; //led
int out4 = 5; //led

const int trigger=6; // ult
const int echo=7;
int buzzer = 13;
float duration,inches,cm;

Servo entryServo, exitServo;

void setup() 
{
  Serial.begin(9600);
  entryServo.attach(entryServoPin);
  exitServo.attach(exitServoPin); 
  pinMode(irEntryPin, INPUT);  //IR   
  pinMode(irExitPin, INPUT);

  exitServo.write(BarDown);
//  entryServo.write(BarDown);

// -- car parking spot IR inputs
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(A2, INPUT);
 pinMode(A3, INPUT);
 // --- 

// -- car parking sport LED outputs
 pinMode(out1, OUTPUT);
 pinMode(out2, OUTPUT);
 pinMode(out3, OUTPUT);
 pinMode(out4, OUTPUT);
 // --

   pinMode(trigger,OUTPUT);
   pinMode(echo,INPUT);
   pinMode(buzzer, OUTPUT);
}

int detectEntryIR() {
   entryIRSensorValue = analogRead(irEntryPin); // IR sensor Enrty gate
   Serial.println(entryIRSensorValue);
   return entryIRSensorValue;
}

int detectExitIR() {
  exitIRSensorValue = analogRead(irExitPin);
  Serial.println(exitIRSensorValue);
  return exitIRSensorValue;
}

void openEntryGate() {
  entryServo.write(BarUp);
//  delay(30);
  Serial.println("Servo entry opened");
//  delay(1000);
  isEntryBarOpen = true;
}

void closeEntryGate() {
  entryServo.write(BarDown);
  Serial.println("Servo entry closed");
//    delay(60);
  if (isEntryBarOpen) {
    count += 1;
    isEntryBarOpen = false;
    Serial.print("After entry Gate Close: ");
    Serial.println(count);
  }
}

void closeExitGate() {
  exitServo.write(BarDown);
  Serial.println("Servo exit closed");
  if (isExitBarOpen) {
    count -= 1;
    isExitBarOpen = false;
    Serial.print("After entry Gate Close: ");
    Serial.println(count);
  }
}

void openExitGate() {
  exitServo.write(BarUp);
  Serial.println("Servo entry opeonned");
  isExitBarOpen = true;  
}

void loop() 
{ 
  int detect0 = digitalRead(A0);
  int detect1 = digitalRead(A1);
  int detect2 = digitalRead(A2);
  int detect3 = digitalRead(A3);
  
  
  if (count < 2) {
    if (detectEntryIR() < 600) {
      openEntryGate();
    } else {
      closeEntryGate();
    }
  }

  display.setBrightness(0x0f);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };

  display.showNumberDec(count);

  if (detectExitIR() < 600) {
    if (count > 0) {
      openExitGate();  
    }
  } else {
    closeExitGate();
  }

  if(detect0 == LOW)               // IR 0
  {
    Serial.println("Obastacle on the way 1 "); 
   digitalWrite(out1,0);
  }
  else
  {
    Serial.println("All clear 1");
     digitalWrite(out1,1);  
  }
  delay(300);   


  
  
  if(detect1 == LOW)              // IR 1
  {
    Serial.println("Obastacle on the way 2 "); 
   digitalWrite(out2,0);
  }
  else
  {
    Serial.println("All clear 2");
     digitalWrite(out2,1);  
  }
  delay(300);  

  

  if(detect2 == LOW)            // IR 2
  {
    Serial.println("Obastacle on the way 3 "); 
   digitalWrite(out3,0);
  }
  else
  {
    Serial.println("All clear 3");
     digitalWrite(out3,1);  
  }
  delay(300);


 if(detect3 == LOW)            // IR 3
  {
    Serial.println("Obastacle on the way 4 "); 
   digitalWrite(out4,0);
  }
  else
  {
    Serial.println("All clear 4");
     digitalWrite(out4,1);  
  }
  delay(300);

  digitalWrite(trigger,LOW);
   delayMicroseconds(100);
   digitalWrite(trigger,HIGH);
   delayMicroseconds(100);
   digitalWrite(trigger,LOW);
   pinMode(echo,INPUT);
   duration=pulseIn(echo,HIGH);
   cm=(duration/2)/29.1;
  inches=(duration/2)/74;

  if(inches <= 0.70)
  {
   
    tone(buzzer, 1000,1000);
    }
   else
   {
     noTone(buzzer);
    } 

      Serial.print("Duration:");
       Serial.print(inches);
        Serial.print(" inches ");
         Serial.print(cm);
          Serial.println(" cm");
          delay(1000);
  
}
