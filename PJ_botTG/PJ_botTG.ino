//Check Battery
int analogInPin  = A0;
int sensorValue; 
float calibration = 0.36;
float voltage;
int bat_percentage;




#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define D4 2 //LED Board
#define D0 16

//WiFi connet
const char* ssid = "Pozz Seang";
const char* password = "14062003";



void setup() {
  Serial.begin(115200);

  //Wifi connet
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //pin mode LED
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);

  //WiFi Connecting
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(D4, LOW);
    digitalWrite(D0, HIGH);
    delay(250);
    digitalWrite(D4, HIGH);
    digitalWrite(D0, LOW);
    delay(250);
  }
  digitalWrite(D4, HIGH);
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
  Serial.println("");

}
int numDelay = 8000;
void loop() {
  
  web();
  digitalWrite(D4, LOW);
  digitalWrite(D0, HIGH);
  delay(numDelay);
  web();
  digitalWrite(D4, HIGH);
  digitalWrite(D0, LOW);
  delay(numDelay);

}
void web(){
  HTTPClient http;
  http.begin("http://9991-36-37-184-224.ngrok.io/txt/battery.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  CheckBattery();
  http.POST("battery=Battery Percentage = "+String(bat_percentage)+"%");
  http.end();
}
String CheckBattery(){
  sensorValue = analogRead(analogInPin);
  voltage = (((sensorValue * 3.3) / 1024) * 2 + calibration);
  bat_percentage = mapfloat(voltage, 2.8, 4.2, 0, 100);//9=9v 4.2=4.2V
  if (bat_percentage >= 100){
      bat_percentage = 100;
  }
  if (bat_percentage <= 0){
      bat_percentage = 1;
  }
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
