
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
int trigPin = D6;    //Trig - green Jumper
int echoPin = D5;    //Echo - yellow Jumper
long duration, cm;
int data;
char auth[]="auth code given by blynk";
char ssid[]="your hotspot name ";
char pass[]="your hotspot password";
int relaypin=D7;
int sensorPin = A0; 
int sensorValue = 0;
int modepin=D4;
int modepinin=D3;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(relaypin,OUTPUT);
  pinMode(sensorPin,INPUT);
   pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
pinMode(modepin,INPUT);
pinMode(modepinin,INPUT);

 }
  
BLYNK_WRITE(V1)
{

  data = param.asInt();
  Serial.println(data);
 if(data==1)
 {
  digitalWrite(relaypin,HIGH);
  
  }
  if(data==0)
  {
    digitalWrite(relaypin,LOW);

    }

}
 

void loop()
{

  if(digitalRead(modepin)==HIGH)
{
 
if(digitalRead(modepinin)==HIGH)
{
  
   digitalWrite(trigPin, LOW);
      delayMicroseconds(5);            //ultrasonic
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
       
          duration = pulseIn(echoPin, HIGH);
    
    
     cm = (duration/2) / 29.1;    //print
     Serial.print(cm);
     Serial.print("cm");
     Serial.println();
     
    if(cm<50)
      {
  
            digitalWrite(relaypin,HIGH);   
            delay(10000);
          
       }
    else
      {
       digitalWrite(relaypin,LOW);
  
      }
}
if(digitalRead(modepinin)==LOW)
{    
  Blynk.run();
 
   digitalWrite(trigPin, LOW);
      delayMicroseconds(5);            //ultrasonic
          digitalWrite(trigPin, HIGH);
          delayMicroseconds(10);
          digitalWrite(trigPin, LOW);
       
          duration = pulseIn(echoPin, HIGH);
    
     cm = (duration/2) / 29.1;    //print
     Serial.print(cm);
     Serial.print("cm");
     Serial.println();
    if(cm<50) 
    { 
     Blynk.notify("someone is in the room");  
    }
}

}
  if(digitalRead(modepin)==LOW)
  {
 
Blynk.run();
 sensorValue = analogRead(sensorPin);
Serial.print("Analog Output = ");
Serial.println(sensorValue);
delay(500);
if(sensorValue<500)
{
  Blynk.notify("alarm gas leakage");
 
  }


  
  }  
}
