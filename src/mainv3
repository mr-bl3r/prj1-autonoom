/*
** Line Follower Basic. 5
** gemaakt door de boy Boyds
*/
#include <arduino.h>

/* Define the pins for the IR receivers */
const int irPins[5] = {A8, A9, A10, A11, A12};

/* Define values for the IR Sensor readings */

// an array to hold values from analogRead on the ir sensor (0-1023)
int irSensorAnalog[5] = {0,0,0,0,0};

// an array to hold boolean values (1/0) for the ir sensors, based on the analog read and the predefined treashold
int irSensorDigital[5] = {0,0,0,0,0}; 

// the value above which we determine an IR sensor reading indicates the sensor is over a line
int treashold = 500; 

// binary representation of the sensor reading from left to right
int irSensors = B00000; 

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
}

void Scan() {
  // Initialize counters, sums etc.
 
  count = 0;
  
  irSensors = B00000;
    
  for (int i = 0; i < 5; i++) {
    irSensorAnalog[i] = analogRead(irPins[i]);

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
       if (errorLast < 0) { error = -180;}
       else if (errorLast > 0) {error = 180;}
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

  else if (error >=180) {
    correction = 305;
  }

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

  else if (error <= -180) {
    correction = -305;
  }
  
  if (correction > 0) {
    motorRSpeed = maxSpeed - correction;
    motorLSpeed = maxSpeed;
  }
  
  else if (correction < 0) {
    motorRSpeed = maxSpeed;
    motorLSpeed = maxSpeed + correction;
  }
else if (correction == 0) {
    motorRSpeed = maxSpeed;
    motorLSpeed = maxSpeed;
  }
}

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

}


void loop() {
 

 Scan();
 UpdateError();
 UpdateCorrection();
 Drive();
}

