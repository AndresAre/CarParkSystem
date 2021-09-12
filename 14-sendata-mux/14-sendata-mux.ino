/*Reads values between 0-1023 for each LDR.
 * In calibration mode, it gets that max value
 * In non-calibration mode, it normalizes the value to 0.0 - 1.0
 * and sends data to server
*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "iot-lab";
const char* password = "pervasive";
String ServerIP = "192.168.1.38"; //Paul Asus  MAC: 40:E2:30:CC:1E:8D
//String ServerIP = "192.168.1.88"; //Darren PC MAC: CC:B0:DA:CA:EA:D1


#define P1 D1
#define P2 D2
#define P3 D3
#define P4 D4
#define P5 D5
#define P6 D6
#define P7 D7
#define P8 D8



int P1MAX = 10000, P2MAX  = 10000, P3MAX  = 10000, P4MAX  = 10000, P5MAX = 10000, P6MAX  = 10000, P7MAX  = 10000, P8MAX  = 10000;
float P1NORM = 0, P2NORM = 0, P3NORM = 0, P4NORM = 0, P5NORM = 0, P6NORM = 0, P7NORM = 0, P8NORM = 0;

int sensorValue = 0;

//--- Set by getCommand() ---
int CALSTATE = 0;
int cmd = 0;

void setup() {
  Serial.begin(9600);
  //MAC: B4:E6:2D:34:A4:A2
  //IP: 192.168.1.35
 
  Serial.println("MAC: " + WiFi.macAddress());
  pinMode(P1, OUTPUT);
  pinMode(P2, OUTPUT);
  pinMode(P3, OUTPUT);
  pinMode(P4, OUTPUT);
  pinMode(P5, OUTPUT);
  pinMode(P6, OUTPUT);
  pinMode(P7, OUTPUT);
  pinMode(P8, OUTPUT);
}


void setAllLow(){
  digitalWrite(P1, LOW);  
  digitalWrite(P2, LOW);  
  digitalWrite(P3, LOW);  
  digitalWrite(P4, LOW);  
  digitalWrite(P5, LOW);  
  digitalWrite(P6, LOW);  
  digitalWrite(P7, LOW);  
  digitalWrite(P8, LOW);  
}

void readPin(int pin){
  setAllLow();
  if(pin == 1) digitalWrite(P1, HIGH); 
  if(pin == 2) digitalWrite(P2, HIGH); 
  if(pin == 3) digitalWrite(P3, HIGH); 
  if(pin == 4) digitalWrite(P4, HIGH); 
  if(pin == 5) digitalWrite(P5, HIGH); 
  if(pin == 6) digitalWrite(P6, HIGH); 
  if(pin == 7) digitalWrite(P7, HIGH); 
  if(pin == 8) digitalWrite(P8, HIGH);
  delay(50);
  sensorValue = analogRead(A0);
  if(CALSTATE == 1) {
     if(pin == 1) P1MAX = sensorValue;
     if(pin == 2) P2MAX = sensorValue;
     if(pin == 3) P3MAX = sensorValue;
     if(pin == 4) P4MAX = sensorValue;
     if(pin == 5) P5MAX = sensorValue;
     if(pin == 6) P6MAX = sensorValue;
     if(pin == 7) P7MAX = sensorValue;
     if(pin == 8) P8MAX = sensorValue;
  }
  
  if(pin == 1) {
    P1NORM = (float)sensorValue/P1MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P1MAX, P1NORM);
  }
  if(pin == 2) {
    P2NORM = (float)sensorValue/P2MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P2MAX, P2NORM);
  }
  if(pin == 3) {
    P3NORM = (float)sensorValue/P3MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P3MAX, P3NORM);
  }
  if(pin == 4) {
    P4NORM = (float)sensorValue/P4MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P4MAX, P4NORM);
  }
  if(pin == 5) {
    P5NORM = (float)sensorValue/P5MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P5MAX, P5NORM);
  }
  if(pin == 6) {
    P6NORM = (float)sensorValue/P6MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P6MAX, P6NORM);
  }
  if(pin == 7) {
    P7NORM = (float)sensorValue/P7MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P7MAX, P7NORM);
  }
  if(pin == 8) {
    P8NORM = (float)sensorValue/P8MAX;
    Serial.printf("P%d: %d/%d %.2f\n", pin, sensorValue, P8MAX, P8NORM);
  }
}

void loop() {
  //getCommandFromSerialMonitor();
  getCommandFromServer();
  for(int i=1; i<=8; i++) readPin(i);
  Serial.println("----------------------");

  sendToServer();
}

void sendToServer(){
  if(WiFi.status() != WL_CONNECTED ){
    Serial.println("Wifi not connected...");
    WiFi.begin(ssid, password); 
  } 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  Serial.print("Connected to: "); Serial.println(WiFi.SSID());
  Serial.print("Your IP: "); Serial.println(WiFi.localIP());
  HTTPClient http;

  String datatosend = "/parking/setdata.php?" 
  + String("a=") + String(P1NORM) + String("&")
  + String("b=") + String(P2NORM) + String("&") 
  + String("c=") + String(P3NORM) + String("&") 
  + String("d=") + String(P4NORM) + String("&") 
  + String("e=") + String(P5NORM) + String("&") 
  + String("f=") + String(P6NORM) + String("&")
  + String("g=") + String(P7NORM) + String("&") 
  + String("h=") + String(P8NORM);
 
  Serial.print("Sensor values: "); Serial.println(datatosend);

  http.begin(ServerIP, 80, datatosend);

  int httpCode = http.GET();
  
  if(httpCode > 0){
    Serial.printf("GET code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK){
      String response = http.getString();
      Serial.println(response);
    }
  } else {
    Serial.printf("GET failed: error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

void getCommandFromSerialMonitor(){
  String inStr = Serial.readStringUntil('\n');
   if(inStr.equals("caloff")){
        Serial.println("CAL OFF");
        CALSTATE = 0;
   }else if(inStr.equals("calon")){
       Serial.println("CAL ON");
       CALSTATE = 1;
   } 
}

void getCommandFromServer(){
   if(WiFi.status() != WL_CONNECTED ){
    Serial.println("Wifi not connected...");
    WiFi.begin(ssid, password); 
  } 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 

  Serial.print("Connected to: "); Serial.println(WiFi.SSID());
  Serial.print("Your IP: "); Serial.println(WiFi.localIP());
  HTTPClient http;
  
  String datatosend = "/parking/getcmd.php"; 
 
  Serial.print("Get cmd: "); Serial.println(datatosend);

  http.begin(ServerIP, 80, datatosend);

  int httpCode = http.GET();
  
  if(httpCode > 0){
    Serial.printf("GET code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK){
      String response = http.getString();
      CALSTATE = response.toInt();
      Serial.println(response);
       if(CALSTATE==0){
          Serial.println("CAL OFF");
        }else if(CALSTATE==1){
          Serial.println("CAL ON");
       } 
    }
  } else {
    Serial.printf("GET failed: error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}
