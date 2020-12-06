/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "e-OVJ2oCTj-Eig7_3QiXiJ-NexiwWqRm";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Bbox-34E9EF0E";
char pass[] = "ED1993992F2EAAAA93C4CD62A6649D";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
int ledPin1 = 0;
   int ledPin2 = 0;
   float q = 2.5;
   float u = 15.0;
   float q2= 2;
   float u2 = 15.0;
   unsigned long previousMillis=0 ;
   unsigned long interval = 300;
   float ledtime1 = 1.0;
   int swich = 0;
   int ledtime2;
   float intervalmultip = 1;
void setup()
{
 
  
  pinMode(15, OUTPUT);
   pinMode(16, OUTPUT);
  // Debug console
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
   timeClient.begin();
   
}

void loop()
{
  //Serial.println(pome);
  Blynk.run();
  if(swich > 0){
    //Serial.print("phone");
  analogWrite(15,ledPin1);
  analogWrite(16,ledPin2);}
  else if(swich ==0){
    analogWrite(16,ledtime1);
    analogWrite(15,ledtime2);
    //Serial.println("timer");
  }
  if( millis() - previousMillis >= (interval)) {
    timeClient.update();
    float secondes = (timeClient.getSeconds());
    float minutesomme = 60*timeClient.getHours()+ timeClient.getMinutes()+ secondes/60;
    //int dercalc =  millis() - previousMillis
    int previousledtime = ledtime1;   
    previousMillis = millis();
     
 // Serial.println(secondes);
 // Serial.println(minutesomme);
  
  ledtime1 = 1300*exp(-1.0/2.0*pow((minutesomme/60-u)/q,2)); //pome est declaré comme float pome = 1; avant le  void setup
  intervalmultip = constrain((ledtime1-previousledtime),0.1,100);
 //interval = interval/intervalmultip;
 //Serial.println(interval);
  if(ledtime1 < 10){
    ledtime1 = 0;
  }
  
  //Serial.println(ledtime1);
  ledtime2 = 1024*exp(-1.0/2.0*pow((minutesomme/60-u2)/q2,2));
   if(ledtime2 < 10){
    ledtime2 = 0;
  }
  //Serial.println(ledtime2);
    }
 
}

BLYNK_WRITE(V1)
{
   ledPin1 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}

BLYNK_WRITE(V2)
{
   ledPin2 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}

BLYNK_WRITE(V3)
{
  swich = param.asInt();
  //Serial.println(swich);
}

BLYNK_WRITE(V6)
{
  u = param.asInt();
  u2 = u;
  //Serial.println(swich);
}

BLYNK_READ(V4) //Blynk app has something on V5
{
  
  Blynk.virtualWrite(V4, ledtime1); //sending to Blynk
}

BLYNK_READ(V5) //Blynk app has something on V5
{
  
  Blynk.virtualWrite(V5, (interval)); //sending to Blynk
}
