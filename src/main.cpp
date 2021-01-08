/*
** Line Follower Basic v. 5
** gemaakt door de boy Boyds
*/
#include <arduino.h>

/* Define motor controll inputs */
const int motorRPin1 = 2; // signal pin 1 for the right motor, connect to IN1               
const int motorRPin2 = 3;  // signal pin 2 for the right motor, connect to IN2
const int motorREnable = 5; // enable pin for the right motor (needs to be PWM enabled)

const int motorLPin1 = 4; // signal pin 1 for the left motor, connect to IN3 (was 5 - need to change)             
const int motorLPin2 = 7; // signal pin 2 for the left motor, connect to IN4
const int motorLEnable = 6; // enable pin for the left motor (needs to be PWM enabled)

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
  /* Set up motor controll pins as output */
  pinMode(motorLPin1,OUTPUT);        
  pinMode(motorLPin2,OUTPUT);
  pinMode(motorLEnable,OUTPUT);
  
  pinMode(motorRPin1,OUTPUT);        
  pinMode(motorRPin2,OUTPUT);
  pinMode(motorREnable,OUTPUT);
   
  /* Set-up IR sensor pins as input */
  for (int i = 0; i < 5; i++) {
    pinMode(irPins[i], INPUT);
  }
  
  /* Change the PWM frequency of digital pins 5 and 6 (timer0) to Phase-correct PWM of 31.250 kHz
  from the default of ~500Hz. Using code from Adjusting PWM Frequencies
  http://playground.arduino.cc/Main/TimerPWMCheatsheet
  
  This requires a separate change in the wiring.c function in the Arduino program files 
  hardware\arduino\cores\arduino\wiring.c from:
  #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(64 * 256))
  
  to:
  #define MICROSECONDS_PER_TIMER0_OVERFLOW (clockCyclesToMicroseconds(1 * 510))
  
  Without the change to wiring.c time functions (millis, delay, as well as libraries using them
  will not work corectly.
  */
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(WGM01) | _BV(WGM00); 
  TCCR0B = _BV(CS00); 
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
    Serial.print(irSensorAnalog[i]);
    Serial.print("|");
    count = count + irSensorDigital[i];
    int b = 5-i;
    irSensors = irSensors + (irSensorDigital[i]<<b);
    }    
}


void UpdateError() {
  
  errorLast = error;  
  
  switch (irSensors) {
     
    case B00000:
       if (errorLast < 0) { error = -180;}
       else if (errorLast > 0) {error = 180;}
       break;
     
     case B10000: // leftmost sensor on the line
       error = -120;
       break;
      
     case B01000:
       error = -60;
       break;

     case B00100:
       error = 0; 
       break;

     case B00010:  
       error = 60;
       break;
       
     case B00001: // right most sensor //v2
       error = 120;
       break;           

    // case B000001: // rigtmost sensor on the line
     //  error = 150;
    //   break;
       
/* 2 Sensors on the line */         
     
     case B11000:
       error = -120;
       break;
      
     case B01100:           // licht links
       error = -60;
       break;

     case B00110:           // licht rechts
       error = 60;
       break;

     case B00011: 
       error = 120;
       break;           
     
     case B10100:           //scherp links
        error = -150;
        break; 
 
     case B00101:           // scherp rechts
       error = 150;
       break;
/* 3 Sensors on the line */    
       // Als de auto op 2, 1 en 3 staat probeer case B01110
       
     case B11100:
     //case B01110:
       error = -150;
       break;
      
     //case B00111:
     case B00111:
       error = 150;
       break;

 /* 4 Sensors on the line       
     case B111100:
       error = -150;
       break;
       
     case B111010:
       error = -150;
       break;
      
     case B001111:
       error = 150;
       break;
       
     case B010111:
       error = 150;
       break;
            */
/* 5 Sensors on the line */      

     case B11111:
       interupt = 1; // increment interupts when pause stop line is found
       error = 0;
       break;
   
     default:
     error = errorLast;
  }
}

void UpdateCorrection() {

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
    correction = 255;
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
    correction = -255;
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
  
  else if (motorRSpeed == 0) { // right motor fast stop
     digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
    digitalWrite(12, LOW); //Establishes reverse direction of Channel A
    analogWrite(3, 0);
  }
  
  if (motorLSpeed >= 0) { // left motor forward (using PWM)
     digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    digitalWrite(13, HIGH); //Establishes fwd direction of Channel A
    analogWrite(11, motorRSpeed);
  } 
  
  else if (motorLSpeed < 0) { // left motor reverse (using PWM)
     digitalWrite(8, LOW);   //Disengage the Brake for Channel A
    digitalWrite(13, LOW); //Establishes reverse direction of Channel A
    analogWrite(11, motorRSpeed);
  } 

}


void loop() {
 

 Scan();
 UpdateError();
 UpdateCorrection();
 Drive();
}

