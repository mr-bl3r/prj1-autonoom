#include <Arduino.h>

// Variables will change:
int ledState = HIGH;         // the current state of the output pi
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int rechtsom = 0;
int linksom = 0;

#define DS1 22
#define DS2 24
#define DS3 26
#define DS4 28
#define DS5 30
#define DS6 32

int delayR = 50;
int bl = 1;
int wh = 0;
int DRD = 10;       //Doorrijdelay

int s1, s2, s3, s4, s5, s6;
int Ls1, Ls2, Ls3, Ls4, Ls5, Ls6;

void straight() {
  Serial.println("Driving straight");
  //Driving forward
  //Motor A forward @ full speed
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed

}

void right() {
  Serial.println("Gaat naar rechts");
  //Driving right
  //Motor A forward @ full speed forward
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed backward
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed backward
}


void left() {
  Serial.println("Gaat naar links");
  //Driving left
  //Motor A forward @ full speed backward
    digitalWrite(12, HIGH); //Establishes  direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed backward

  //Motor B forward @ full speed forward
    digitalWrite(13, LOW);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);     //Spins the motor on Channel B at full speed forward
}
  


void stop() {
  digitalWrite(9, HIGH);
  digitalWrite(8, HIGH);
}
void pause() { 
  Serial.println("start pauze"); 

}

void setup() {
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pi
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin

  //Setup sensor
  pinMode(DS1, INPUT);
  pinMode(DS2, INPUT);
  pinMode(DS3, INPUT);
  pinMode(DS4, INPUT);
  pinMode(DS5, INPUT);
  pinMode(DS6, INPUT);
  
  Serial.begin(9600); //Starts the serial monitor
}

void loop(){
  // assigns signal 1-6 from digital sensor 1-6
s1 = digitalRead(DS1);
s2 = digitalRead(DS2);
s3 = digitalRead(DS3);
s4 = digitalRead(DS4);
s5 = digitalRead(DS5);
s6 = digitalRead(DS6);
//tijdelijke straight

straight();
 //rechts af
  if (s5 == bl){//rechter sensor 
      //1e stap hij moet door rijden totdat sensor 6 wit is
      s6 = digitalRead(DS6);
      while (s6 == bl){
          s6 = digitalRead(DS6);
          Serial.println("S6 is zwart rechtsom");
      }
       Serial.println("S6 is wit");
        stop();
        delay(2000);
        right();
        //vanaf hier moet hij opzoek naar de lijn en kijken of sensor 1 weer zwart word
        s1 = digitalRead(DS1);
        while(s1 == wh){
          s1 = digitalRead(DS1);
          Serial.println("S1 wit"); 
        } 
        Serial.println("S1 zwart");
        stop();
        delay(400); //deze delay weg als het draaien werkt
  }

  // linker af
 if (s4 == bl){//rechter sensor
      //1e stap hij moet door rijden totdat sensor 6 wit is
      s6 = digitalRead(DS6);
      while (s6 == bl){
          s6 = digitalRead(DS6);
          Serial.println("S6 is zwart linksom");
      }
      Serial.println("S6 is wit");
      stop();
      delay(2000);
      left();
      //vanaf hier zoek hij weer de lijn
      s1 = digitalRead(DS1);
      while(s1 == wh){
        s1 = digitalRead(DS1);
        Serial.println("S1 wit");
      }
      Serial.println("S1 zwart");
      stop();
      delay(400); //deze delay weg als het draaien werkt
  }



 //correctie links

    if(s2 == bl){
      
      analogWrite(3, 255);     //Spins the motor on Channel A at full speed 
      digitalWrite(12, HIGH);  //Establishes forward direction of Channel A
    
      analogWrite(11, 20);     //Spins the motor on Channel B at full speed forward
      digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
       
       
    }

//correctie rechts

    if(s3 == bl){
      analogWrite(3, 20);     //Spins the motor on Channel A at full speed 
      digitalWrite(12, HIGH);  //Establishes forward direction of Channel A
    
      analogWrite(11, 255);     //Spins the motor on Channel B at full speed forward
      digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
      
      }
    }




