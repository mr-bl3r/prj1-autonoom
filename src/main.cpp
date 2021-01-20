<<<<<<< HEAD
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

=======
/*
** Line Follower Basic. 5
** gemaakt door de boy Boyds
*/
#include <arduino.h>

/* Define the pins for the IR receivers */
const int irPins[5] = {A8, A9, A10, A11, A12};
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf


int delayR = 50;
int bl = 1;
int wh = 0;

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

<<<<<<< HEAD
=======
// sensors detecting the line
int count = 0; 

// a score to determine deviation from the line [-180 ; +180]. Negative means the robot is left of the line.
int error = 0;

//  store the last value of error
int errorLast = 0;  

// a coorection value, based on the error that is used to change motor speed with PWM
int correction = 0; 

// keep track of the interupts
int interupt = 0; 

/* Set up maximum speed and speed for turning (to be used with PWM) */

// PWM to control motor speed [0 - 255]
int maxSpeed = 255; 

/* variables to keep track of current speed of motors */
int motorLSpeed = 0;
int motorRSpeed = 0;

void setup() {
    Serial.begin(9600);
   
  /* Set-up IR sensor pins as input */
  for (int i = 0; i < 5; i++) {
    pinMode(irPins[i], INPUT);
  }
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf
}

void right() {
  Serial.println("Gaat naar rechts");
  //Driving right
  //Motor A forward @ full speed forward
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, 200);   //Spins the motor on Channel A at full speed

<<<<<<< HEAD
  //Motor B forward @ full speed backward
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    analogWrite(11, 200);    //Spins the motor on Channel B at full speed backward
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
          Serial.println("S6");
      }
        delay(60);
        stop();
        delay(2000);
        right();
        //vanaf hier moet hij opzoek naar de lijn en kijken of sensor 1 weer zwart word
        s1 = digitalRead(DS1);
        while(s1 == wh){
          s1 = digitalRead(DS1);
          Serial.println("S1 wit"); 
        } 
          stop();
          delay(100000); 
  }
=======
    if (irSensorAnalog[i] >= treashold) {
        irSensorDigital[i] = 1;
    }
    else {irSensorDigital[i] = 0;}
    count = count + irSensorDigital[i];
    int b = 4-i;
    irSensors = irSensors + (irSensorDigital[i]<<b);
    }    
}


void UpdateError() {
  
  errorLast = error;  
    
  switch (irSensors) {
     //Serial.println(irSensors);
    case B00000:
       if (errorLast < 0) { error = -180;}// hier kunnen we gebruik van maken bij het maken van een bocht rond zn as
       else if (errorLast > 0) {error = 180;}// we moeten dan wel iets doen met de rest van de code omdat die nu nog door loopt
       break;
     
     case B10000: // leftmost sensor on the line
       error = -150;
       Serial.println("hikke tikke");
       break;
      
     case B01000:
       error = -90;
       break;

     case B00100:
       error = 0; 
       break;

     case B00010:  
       error = 90;
       break;
       
     case B00001: // right most sensor //v2
       error = 150;
       Serial.println("hikke naar rechts");
       break;           

/* 2 Sensors on the line */         
     
     case B11000:
       error = -150;
       break;
      
     case B01100:           // licht links
       error = -90;
       break;

     case B00110:           // licht rechts
       error = 90;
       break;

     case B00011: 
       error = 150;
       break;           
     
     case B10100:           //scherp links 
        error = 0;
        break; 
 
     case B00101:           // scherp rechts
       error = 0;
       break;
/* 3 Sensors on the line */    
       // Als de auto op 2, 1 en 3 staat probeer case B01110
       
     case B11100:
       error = -150;
       Serial.println("i should be going left"); // added this
       break;
      
     
     case B00111:
       error = 150;
       Serial.println("i should be going right"); // added this
       break;

 /* 4 Sensors on the line */      
     case B11110:           //links af maar met 1 foute lezing error
       error = -150;        //mogelijk pauze symbool?
       break;
          
     case B01111:           //rechts af maar met 1 foute lezing error
       error = 150;         //mogelijk pauze symbool?
       break;
                 
/* 5 Sensors on the line */      

     case B11111:
       interupt = 1; // increment interupts when pause stop line is found
       error = 0;     //pauze en ook stop
       break;
   
     default:
     error = errorLast;
  }
}

void UpdateCorrection() {
    //Serial.println(correction);
  if (error >= 0 && error < 30) {
    correction = 0;
  }
  
  else if (error >=30 && error < 60) {
    correction = 15;
  }
  
  else if (error >=60 && error < 90) {
    correction = 40;
  }
  
  else if (error >=90 && error < 120) {
    correction = 55;
  }  
  
  else if (error >=120 && error < 150) {
    correction = 75;
  } 
  
  else if (error >=150 && error < 180) {
    correction = 305;
    
  }   
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf


<<<<<<< HEAD
=======
  if (error <= 0 && error > -30) {
    correction = 0;
  }
  
  else if (error <= -30 && error > -60) {
    correction = -15;
  }
  
  else if (error <= -60 && error > -90) {
    correction = -40;
  }
  
  else if (error <= -90 && error > -120) {
    correction = -55;
  }  
  
  else if (error <= -120 && error > -150) {
    correction = -75;
  } 
  
  else if (error <= -150 && error > -180) {
    correction = -305;
    
  }   
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf


<<<<<<< HEAD
=======
void Drive() {
  if (motorRSpeed > 255) {motorRSpeed = 255;}
  else if (motorRSpeed < -255) {motorRSpeed = -255;}
  
  if (motorLSpeed > 255) {motorLSpeed = 255;}
  else if (motorLSpeed < -255) {motorLSpeed = -255;}
  
  if (motorRSpeed > 0) { // right motor forward (using PWM)
     digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(12, HIGH); //Establishes fwd direction of Channel A
    analogWrite(3, motorRSpeed);
  } 
  
  else if (motorRSpeed < 0) {// right motor reverse (using PWM)
     digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, motorRSpeed);
  } 
  
  else if (motorRSpeed == 0 || motorLSpeed == 0) { // right motor fast stop
     digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, 0);
  }
  
  if (motorLSpeed >= 0) { // left motor forward (using PWM)
     digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    digitalWrite(13, HIGH); //Establishes fwd direction of Channel A
    analogWrite(11, motorLSpeed);
  } 
  
  else if (motorLSpeed < 0) { // left motor reverse (using PWM)
     digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    digitalWrite(13, LOW); //Establishes reverse direction of Channel A
    analogWrite(11, motorLSpeed);
  } 
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf



  
  // linker sensor
 if (s4 == bl){//rechter sensor
      //1e stap hij moet door rijden totdat sensor 6 wit is
      s6 = digitalRead(DS6);
      while (s6 == bl){
          s6 = digitalRead(DS6);
      }
        stop();
        delay(100);
        right();

<<<<<<< HEAD
       
  }

}
=======
 Scan();
 UpdateError();
 UpdateCorrection();
 Drive();
}
>>>>>>> 651ff7a79f435a871db360ebe2971a50cce22bdf
