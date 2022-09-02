#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
 #include <ESP8266HTTPClient.h>
 
// Set these to run example.
#define FIREBASE_HOST "realtdb-esp-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "OC7qbST7asO3BiZTGw59cXzRVnYv9OXTfCC81rfl" 
#define WIFI_SSID "IZZI NUNEZ"                                          
#define WIFI_PASSWORD "23594793" 
//
//#define echoPin 5 // attach pin D2 Arduino to pin Echo of HC-SR04
//#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04
//

#define NOTE_D6  1175
#define NOTE_A5  880
int  speaker = 0; 
float myString;
int sensor = 4;
//int vr = A0; // variable resistor connected 

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int sdata = 0; // The variable resistor value will be stored in sdata.
 int led = 14;  
 int senalRecibida = 16; 
void setup()
{
  // Debug console
  Serial.begin(9600);
   pinMode(led, OUTPUT);  
   pinMode(speaker, OUTPUT);  
   pinMode(senalRecibida, OUTPUT); 
   pinMode(sensor, INPUT_PULLUP);
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
//  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  // connect to wifi.
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
 
   Firebase.set("led/1/Value","off");
   Firebase.set("ledSig/2/value",false);
//   Firebase.setString("Variable/Value","dfgdfg");
}
 
void loop()
{
//
// // Clears the trigPin condition
//  digitalWrite(trigPin, LOW);
//  delay(50);
//  digitalWrite(trigPin, HIGH);
//  delay(100);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  // Calculating the distance
//  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

int sensorVal = digitalRead(sensor);
  sendDataToDB(sensorVal);

//  Firebase.getFloat("led/1/Value") == 1 Para obtener un valor numerico de la base de datos 
  if(Firebase.getString("led/1/Value") == "off"){
    digitalWrite(senalRecibida, LOW);
    }
      else if (Firebase.getString("led/1/Value") == "on") { 
    digitalWrite(senalRecibida, HIGH);                                                     
  }
}

void sendDataToDB(float data){

 if (data == HIGH) { 
    digitalWrite(led,LOW);
    Firebase.set("ledSig/2/value",false);
  } else {
    digitalWrite(led,HIGH);
    Firebase.set("ledSig/2/value",true);
    toneAlert();
    delay(500);
    toneAlert();
  }
  
//  if(data <= 30){
//    digitalWrite(led,HIGH);
//    Firebase.set("ledSig/2/value",true);
//    toneAlert();
//    delay(500);
//    toneAlert();
//  }else{
//    digitalWrite(led,LOW);
//    Firebase.set("ledSig/2/value",false);
//
//  }
}

void toneAlert(){
  tone(speaker,NOTE_D6,200);   // PARTE 1
 delay(200);
 tone(speaker,NOTE_A5,200);
 delay(500);
}
