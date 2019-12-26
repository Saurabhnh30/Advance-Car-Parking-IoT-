#include <Servo.h> // include Servo library 

Servo horizontal; // horizontal servo
int servoh = 90; // stand horizontal servo
//
Servo vertical; // vertical servo 
int servov = 90; // stand vertical servo

// LDR pin connections
//name = analogpin;
int ldrlt = 0; //LDR top left
int ldrrt = 1; //LDR top rigt
int ldrld = 2; //LDR down left ATTTTTTTTTTTTTTTTt
int ldrrd = 3; //LDR down rigt
int ledFisso = 13;
int led = 8;

void setup()
{
  Serial.begin(9600);
// servo connections
//name.attacht(pin);
  horizontal.attach(10); 
  vertical.attach(9);
pinMode(ledFisso, OUTPUT); 
pinMode(led, OUTPUT); 

}

void loop() 
{
  digitalWrite(ledFisso, LOW);
  digitalWrite(led, LOW);
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt

  //int dtime = analogRead(4)/20; // read potentiometers
int tol = analogRead(5)/4;
//  int tol = 20;
//  int tol = 40;

  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt

  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
    if (avt > avd){
      servov = ++servov;
      digitalWrite(led, HIGH);
      delay(1000);                  // attende un seconso (1000 millisecondi)
      digitalWrite(led, LOW);    // spegne il led
      delay(1000);  
      digitalWrite(led, HIGH);
      if (servov > 180){
        servov = 180;
       }
    }
    else if (avt < avd){
////        digitalWrite(led, HIGH);
////      delay(100);                  // attende un seconso (1000 millisecondi)
////      digitalWrite(led, LOW);    // spegne il led
////      delay(100);  
////      digitalWrite(led, HIGH);
//      servov= --servov;
      if (servov < 0){
        servov = 0;
      }
    }
  vertical.write(servov);
  //delay(15);
}

  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
          if (avl > avr){
            digitalWrite(ledFisso, HIGH);
            delay(1000);                  // attende un seconso (1000 millisecondi)
            digitalWrite(ledFisso, LOW);    // spegne il led
            delay(1000);  
            digitalWrite(ledFisso, HIGH);
                servoh = --servoh;
                
                if (servoh < 0){
                  servoh = 0;
                }
          }
          else if (avl < avr){
            digitalWrite(ledFisso, HIGH);
            delay(100);                  // attende un seconso (1000 millisecondi)
            digitalWrite(ledFisso, LOW);    // spegne il led
            delay(100);  
            digitalWrite(ledFisso, HIGH);
                  servoh = ++servoh;
                  
                  if (servoh > 169){
                    servoh = 169;
                  }
              }
          else if (avl == avr){
                  // nothing
           }
           horizontal.write(servoh);
           //delay();
  }
   delay(50);
}
