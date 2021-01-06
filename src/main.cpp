#include <Arduino.h>

#define DS1 22
#define DS2 24
#define DS3 26
#define DS4 28
#define DS5 30
#define DS6 32

//Motor A is de rechterkant vanaf boven achter gezien
//Motor B is de linkerkant vanaf boven achter gezien

int delayR = 50;
int bl = 1;
int wh = 0;

int s1, s2, s3, s4, s5, s6;
int ls1, ls2, ls3, ls4, ls5, ls6;
int tot1, tot2, tot3, tot4, tot5, tot6;
int rechtsom = 0;


void rechtdoor() {
  Serial.println("rechtdoor");
  //Driving forward
  //Motor A (rechterkant )forward @ full speed
    digitalWrite(12, HIGH); //Laat de motor vooruit rijden
    digitalWrite(9, LOW);   //Zet de rem uit van motor A
    analogWrite(3, 255);   //Laat moter A op volle snelheid rijden

  //Motor B (linkerkant) forward @ full speed
    digitalWrite(13, HIGH);  //Laat de motor vooruit rijden
    digitalWrite(8, LOW);   //Zet de rem uit van moter B
    analogWrite(11, 255);    //Laat moter B op volle snelheid rijden
}

void links() {
  Serial.println("Gaat naar links");
  //Driving left
  //Motor A forward @ full speed backward
    digitalWrite(12, HIGH); //Zorgt ervoor dat de motor A vooruit gaat
    digitalWrite(9, LOW);   //Zet van motor A de rem uit
    analogWrite(3, 255);    // geeft de motor een snelheid van 131 (waar 255 maximaal is)
  //Motor B forward @ full speed forward
    digitalWrite(13, LOW);  //Zorgt ervoor dat de motor B achteruit gaat
    digitalWrite(8, LOW);   //Zet de rem van motor B
    analogWrite(11, 255);    //geeft de motor een snelheid van 65 (waar 255 maximaal is)
} 

void rechts() {
  Serial.println("Gaat naar rechts");
  //Driving right
  //Motor A forward @ full speed forward
    digitalWrite(9, LOW);   //Zet de rem uit voor motor A
    digitalWrite(12, LOW); //Zet motor a in de omgekeerde stand
    analogWrite(3, 255);     // geeft de motor een snelheid van 65 (waar 255 maximaal is)

  //Motor B forward @ full speed backward
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    analogWrite(11, 255);   // geeft de motor een snelheid van 131 (waar 255 maximaal is)
}

void checkSensoren(){
      s1 = digitalRead(DS1);
      s2 = digitalRead(DS2);
      s3 = digitalRead(DS3);
      s4 = digitalRead(DS4);
      s5 = digitalRead(DS5);
      s6 = digitalRead(DS6);
}

void LastcheckSensoren(){
      ls1 = digitalRead(DS1);
      ls2 = digitalRead(DS2);
      ls3 = digitalRead(DS3);
      ls4 = digitalRead(DS4);
      ls5 = digitalRead(DS5);
      ls6 = digitalRead(DS6);
}

void totchecksensoren(){
      //reset de waardes voor dat er nieuwe waardes worden gegeven
      tot1 = 0;
      tot2 = 0;
      tot3 = 0;
      tot4 = 0;
      tot5 = 0;
      tot6 = 0;
      
      
      
      s1 = digitalRead(DS1);
      s2 = digitalRead(DS2);
      s3 = digitalRead(DS3);
      s4 = digitalRead(DS4);
      s5 = digitalRead(DS5);
      s6 = digitalRead(DS6);

      delay(10);

      ls1 = digitalRead(DS1);
      ls2 = digitalRead(DS2);
      ls3 = digitalRead(DS3);
      ls4 = digitalRead(DS4);
      ls5 = digitalRead(DS5);
      ls6 = digitalRead(DS6);
      
     tot1 = s1 + ls1;
     tot2 = s2 + ls2;
     tot3 = s3 + ls3;
     tot4 = s4 + ls4;
     tot5 = s5 + ls5;
     tot6 = s6 + ls6;

     if(tot1 >= 1){
      tot1 = 1; 
     }
     
     if(tot2 >= 1){
      tot2 = 1; 
     }
     

     if(tot3 >= 1){
      tot3 = 1; 
     }
    
    if(tot4 >= 1){
      tot4 = 1; 
    }
    
    if(tot5 >= 1){
      tot5 = 1; 
    }
    

    if(tot6 >= 1){
      tot6 = 1; 
    }

    Serial.print(tot1);
    Serial.print(tot2);
    Serial.print(tot3);
    Serial.print(tot4);
    Serial.print(tot5);
    Serial.print(tot6);
    Serial.println("  ");


}

void setup(){
    Serial.begin(9600);

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
}

void loop(){
  totchecksensoren();

  // assigns signal 1-6 from digital sensor 1-6
  int s1 = digitalRead(DS1);
  int s2 = digitalRead(DS2);
  int s3 = digitalRead(DS3);
  int s4 = digitalRead(DS4);
  int s5 = digitalRead(DS5);
  int s6 = digitalRead(DS6);


  //Print de sensor output vanaf achter boven
  Serial.print(tot4);
  Serial.print("  ");
  Serial.print(tot2);
  Serial.print("  ");
  Serial.print(tot1);
  Serial.print("  ");
  Serial.print(tot3);
  Serial.print("  ");
  Serial.print(tot5);
  Serial.println("      ");
  Serial.print(tot6);
  Serial.println(" ");

 if ((s1 == bl) && (s6 == bl) && (s5 == wh) && (s4 == wh) && (rechtsom == 0)){
       rechtdoor();
       checkSensoren();
       if(tot5 == bl){
         rechtsom = 123;
         return;
       }

    }
  
    

//Rechts haaks
if(tot5 == bl){
    rechtsom = 123;
    Serial.println("s1 s3 s5 zien zwart en je ma is zwart");
    

}
totchecksensoren();
  if ((rechtsom == 123) && (tot6 == wh)){
         Serial.println("moet nu draaien rechts");
         rechts();
         
            if(s1 == bl){
            Serial.println("na de bocht recht door");
            rechtdoor();
            delay(5);
            rechtsom = 0;             //The car go right
         } 
       }


/*
//loodrecht rechts
if((s5 == bl) && (s2 == wh) && (s4 == wh) && (s3 == bl)){     //checkt rechte bocht rechts
    Serial.println("s1 s3 s5 zien zwart");
    while(s6 = bl){       //zolang sen 6 nog zwart is dan blijf hij rechtdoor gaan en sensoren uitlezen
      checkSensoren();
      rechtdoor();
    }
    rechts();           //als 6 wit word maakt hij de bocht
    while(s1 = wh){
      checkSensoren();
    }
    rechtdoor();      //einde van de code hij gaat weer rechtdoor
  }
*/


}







