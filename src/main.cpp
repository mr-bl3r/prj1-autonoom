#include <Arduino.h>

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

#define DS1 22
#define DS2 24
#define DS3 26
#define DS4 28
#define DS5 30
#define DS6 32

int delayR = 50;
int bl = 1;
int wh = 0;


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
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed backward
    digitalWrite(13, LOW);  //Establishes backward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed backward
    
}

void left() {
  Serial.println("Gaat naar links");
  //Driving left
  //Motor A forward @ full speed backward
    digitalWrite(12, LOW); //Establishes backward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed backward

  //Motor B forward @ full speed forward
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 255);    //Spins the motor on Channel B at full speed forward
    

}

void pause() {
  Serial.println("start pauze"); 

}



void setup() {
  

  
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
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
  
  int digitalstate[] = {DS1, DS2, DS3, DS4, DS5, DS6};
  // read the state of the switch into a local variable:
  int reading = digitalRead(digitalstate[0, 1, 2, 3, 4, 5]);
 
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }

  // assigns signal 1-6 from digital sensor 1-6
  int s1 = digitalRead(DS1);
  int s2 = digitalRead(DS2);
  int s3 = digitalRead(DS3);
  int s4 = digitalRead(DS4);
  int s5 = digitalRead(DS5);
  int s6 = digitalRead(DS6);
  

  
  //Straight line driving
  if ((s1 == bl) && (s2 == wh) && (s3 == wh) && (s4 == wh) && (s5 == wh)){
        digitalWrite(9, HIGH);  //Engage the Brake for Channel A
        digitalWrite(8, HIGH);  //Engage the Brake for Channel B
        straight();
        delay(delayR);
       loop();
  }

  //Rechts slap
  if ((s1 == bl) && (s6 == bl) && (s2 == wh) && (s3 == wh) && (s4 == wh)){
    if (s5 == bl){
      if (s6 == wh){
        digitalWrite(9, HIGH);  //Engage the Brake for Channel A
        digitalWrite(8, HIGH);  //Engage the Brake for Channel B 
        right();
        delay(delayR);
        loop();
    }
   }
  }

  //Rechts scherp
  if ((s1 == bl) && (s5 == bl) && (s2 == wh) && (s4 == wh)){
    if (s3 == bl){
      if (s6 == wh){
        digitalWrite(9, HIGH);  //Engage the Brake for Channel A
        digitalWrite(8, HIGH);  //Engage the Brake for Channel B
        right();
        loop();
      }
    }
  }


  //Rechts haaks
  if((s1 == bl) && (s3 == bl) && (s5 == bl) && (s6 == bl)){
    if(s6 == wh){
       digitalWrite(9, HIGH);  //Engage the Brake for Channel A
       digitalWrite(8, HIGH);  //Engage the Brake for Channel B
       right();                //The car go right
       delay(delayR);
       loop();                 //Runs the void loop again
    }
  }

  



 


  //vanaf hier ff negeren
  //--------------------------------------------------------------------------------------------------------------
  
  //Driving forward
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed
  digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);    //Spins the motor on Channel B at half speed
  Serial.println("I'm driving forward at full speed!");
  delay(1000);

  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B


  delay(1000);
  
  //Driving in reverse
  //Motor A reverse @ full speed
  digitalWrite(12, LOW);  //Establishes backward direction of Channel A(low is direction)
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);    //Spins the motor on Channel A at full speed(255)
  
  //Motor B reverse @ full speed
  digitalWrite(13, LOW); //Establishes reverse direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at full speed
  Serial.println("I'm driving backwards at full speed!");
  
  delay(1000);
  
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B
  
  
  delay(1000);
  
  //Turning left or right idk
  //Motor A forward @ half speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B reverse @ half speed
  digitalWrite(13, LOW); //Establishes reverse direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at half speed
  Serial.println("I'm turning at half speed! Left or right i don't know yet ;.(");
  delay(1000);

  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B

  delay(1000);

  //Turning left or right idk
  //Motor A forward @ half speed
  digitalWrite(12, LOW); //Establishes reverse direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B reverse @ half speed
  digitalWrite(13, HIGH); //Establishes reverse direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, 255);   //Spins the motor on Channel B at half speed
  Serial.println("I'm turning at half speed! Left or right i don't know yet ;.(");
  delay(1000);

  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B

  delay(1000);

}