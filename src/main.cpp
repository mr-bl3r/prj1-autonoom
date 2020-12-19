#include <Arduino.h>

// Variables will change:
int ledState = HIGH;         // the current state of the output pi
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int rechtsom = 0;
int linksom = 0;
int rechtscor = 0;
int linkscor = 0;
int linkscorscherp = 0; 
int rechtscorscherp = 0;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 0;    // the debounce time; increase if the output flickers

#define DS1 22
#define DS2 24
#define DS3 26
#define DS4 28
#define DS5 30
#define DS6 32



int delayR = 50;
int bl = 1;
int wh = 0;

int s1, s2, s3, s4, s5, s6;
int ls1, ls2, ls3, ls4, ls5, ls6;

void straight() {
  Serial.println("Driving straight");
  //Driving forward
  //Motor A (rechterkant )forward @ full speed
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 255);   //Spins the motor on Channel A at full speed

  //Motor B (linkerkant) forward @ full speed
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
    analogWrite(11, 127);    //Spins the motor on Channel B at full speed backward
    
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

 void CheckLineCoordination(){
    if ((s1 != bl) && (s2 == bl))
    {
    digitalWrite(12, HIGH); //Establishes  direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    analogWrite(3, 200);   //Spins the motor on Channel A at full speed backward
    }
    else if ((s1 != bl) && (s3 == bl)){
      digitalWrite(13, LOW);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    analogWrite(11, 200);     //Spins the motor on Channel B at full speed forward

    }
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

  //debounce();
  // assigns signal 1-6 from digital sensor 1-6
  int s1 = digitalRead(DS1);
  int s2 = digitalRead(DS2);
  int s3 = digitalRead(DS3);
  int s4 = digitalRead(DS4);
  int s5 = digitalRead(DS5);
  int s6 = digitalRead(DS6);

  Serial.print("eerste");
  Serial.print(s4);
  Serial.print("  ");
  Serial.print(s2);
  Serial.print("  ");
  Serial.print(s1);
  Serial.print("  ");
  Serial.print(s3);
  Serial.print("  ");
  Serial.print(s5);
  Serial.println(" ");
  Serial.println(s6);
  
  delay(10);

  int ls1 = digitalRead(DS1);
  int ls2 = digitalRead(DS2);
  int ls3 = digitalRead(DS3);
  int ls4 = digitalRead(DS4);
  int ls5 = digitalRead(DS5);
  int ls6 = digitalRead(DS6);

  Serial.print("tweede");
  Serial.print(ls4);
  Serial.print(" ");
  Serial.print(ls2);
  Serial.print(" ");
  Serial.print(ls1);
  Serial.print(" ");
  Serial.print(ls3);
  Serial.print(" ");
  Serial.print(ls5);
  Serial.println(" ");
  Serial.println(ls6);



  int tot1 = s1 + ls1;

  if(tot1 >= 1){
    tot1 = 1; 
  }
  int tot2 = s2 + ls2;

  if(tot2 >= 1){
    tot2 = 1; 
  }
  int tot3 = s3 + ls3;

  if(tot3 >= 1){
    tot3 = 1; 
  }
  int tot4 = s4 + ls4; 

  if(tot4 >= 1){
    tot4 = 1; 
  }
  int tot5 = s5 + ls5;

  if(tot5 >= 1){
    tot5 = 1; 
  }
  int tot6 = s6 + ls6; 

  if(tot6 >= 1){
    tot6 = 1; 
  }

  Serial.print("tot");
  Serial.print(tot4);
  Serial.print("  ");
  Serial.print(tot2);
  Serial.print("  ");
  Serial.print(tot1);
  Serial.print("  ");
  Serial.print(tot3);
  Serial.print("  ");
  Serial.print(tot5);
  Serial.println(" ");
  Serial.println(tot6);


 
  
  //Serial.println(s6);
/*
  if((s1 == bl) || (s6 == bl)){
    CheckLineCoordination();
  }
*/
 //Straight line driving
  if ((tot1 == bl) && (tot2 == wh) && (tot3 == wh) && (tot4 == wh) && (tot5 == wh) && (tot6 == bl)){
    straight();
    delay(delayR);
       return;
      }



  

  /*
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
 */

 /* //Rechts haaks
   if((s1 == bl) && (s3 == bl) && (s5 == bl)){
      Serial.println("De auto ziet de sensor 1, 3 en 5");
      Serial.println(s6);
        if((s6 == wh)){ 
          Serial.println(s6);
          Serial.println("gaat hij naar rechts!!");
          digitalWrite(9, HIGH);  //Engage the Brake for Channel A
          digitalWrite(8, HIGH);  //Engage the Brake for Channel B
          right();                //The car go right
         delay(delayR);
         loop();                    //Runs the void loop again
        }
    
  }
   */
//Rechts haaks
if((tot1 == bl) && (tot3 == bl) && (tot5 == bl) && (tot2 == wh) && (tot4 == wh)){
      rechtsom = 123;
  Serial.println("s1 s3 s5 zien zwart");
  Serial.println(s6);

  }
  if ((rechtsom == 123) && (tot6 == wh)){
         Serial.println("moet nu draaien rechts");
         //Serial.println(s6);
         //digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
         //digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
         right();
          rechtsom = 0;              //The car go right
         if(tot1 == bl){
           Serial.println("na de bocht recht door");
           return;
        
         }
         
}


//correctie naar de lijn naar rechts
 if((tot3 == bl) && (tot2 == wh) && (tot4 == wh) && (tot5 == wh) && (tot6 == bl)){
    Serial.println("gaat naar rechts?");
    rechtscor = 36;
    delay(20);
  }
  
  if((tot3 == bl) && (rechtscor == 36) && (tot2 == wh) && (tot4 == wh)){
     Serial.println("rechtse correctie");
     analogWrite(11, 255);   //Spins the motor on Channel B at full speed
     analogWrite(3, 80);    //Spins the motor on Channel A at full speed
    if((tot1 == bl) && (tot2 == wh) && (tot3 == wh) && (tot5 == wh) && (tot4 == wh)){
     Serial.println("Heeft nu gecorrigeerd van rechts");
    return;
    }
  }
    
    
    //slappe correctie naar links
    if((tot3 == wh) && (tot2 == bl) && (tot4 == wh) && (tot5 == wh) && (tot6 == bl)){
      Serial.println("gaat naar links?");
      linkscor = 37;
      delay(20);
    }
    if((tot2 == bl) && (linkscor == 37) && (tot3 == wh) && (tot5 == wh)){
      Serial.println("linkse correctie");
      analogWrite(11, 80);   //Spins the motor on Channel B at full speed
      analogWrite(3, 255);    //Spins the motor on Channel A at full speed
      
    if((tot1 == bl) && (tot2 == wh) && (tot3 == wh) && (tot5 == wh) && (tot4 == wh)){
      Serial.println("Heeft nu gecorrigeerd van links");
      return;
     }
    }
    /*
    }
  //scherpe correctie naar links
   if((tot3 == wh) && (tot2 == wh) && (tot4 == bl) && (tot5 == wh) && (tot6 == bl)){
      Serial.println("gaat naar scherp links?");
      linkscorscherp = 38;
      delay(20);
    }

    if((tot3 == bl) && (linkscorscherp == 38) && (tot2 == wh) && (tot4 == wh)){
       Serial.println("links scherp correctie");
       analogWrite(11, 60);   //Spins the motor on Channel B at full speed
       analogWrite(3, 255);    //Spins the motor on Channel A at full speed
      if((tot1 == bl) && (tot2 == wh) && (tot3 == wh) && (tot5 == wh) && (tot4 == wh)){
       Serial.println("Heeft nu gecorrigeerd van links");
      return;
      }
    }
  //scherpe correctie naar rechts
    if((tot3 == wh) && (tot2 == wh) && (tot4 == wh) && (tot5 == bl) && (tot6 == bl)){
      Serial.println("gaat naar scherp links?");
      rechtscorscherp = 39;
      delay(20);
    }

    if((tot3 == bl) && (rechtscorscherp == 39) && (tot2 == wh) && (tot4 == wh)){
       Serial.println("links scherp correctie");
       analogWrite(11, 255);   //Spins the motor on Channel B at full speed
       analogWrite(3, 60);    //Spins the motor on Channel A at full speed
      if((tot1 == bl) && (tot2 == wh) && (tot3 == wh) && (tot5 == wh) && (tot4 == wh)){
       Serial.println("Heeft nu gecorrigeerd van links");
      return;
      }
    }
    */

    
   
    
   
//links haaks
if((tot1 == bl) && (tot3 == wh) && (tot5 == wh) && (tot2 == bl) && (tot4 == bl)){
      linksom = 123;
  Serial.println("s1 s3 s5 zien zwart");
  Serial.println(s6);

  }
  if ((linksom == 123) && (tot6 == wh)){
         Serial.println("moet nu draaien links");
         //Serial.println(s6);
         //digitalWrite(8, HIGH);   //Disengage the Brake for Channel B
         //digitalWrite(9, HIGH);   //Disengage the Brake for Channel A
         left();
         linksom = 0;                //The car go right
         if((tot1 == bl)){
           return;
         }
         
}


  
/*

 


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
*/
}
 