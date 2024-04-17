#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

//defines
#define SensorPin 35
#define WaterPin 22

//touche buttons
#define PlusButtonPin 4
#define MinButtonPin 15
#define AutButtonPin 13

int buttonThreshold = 20; //under this threshold a button is pressed

//true is pressed. with this we make sure it only does one step and you cant keep a button pressed.
bool PlusLastState = false;
bool MinLastState = false;
bool AutLastState = false;

bool automation = 0;

//ledbar
int Leds [] = {12, 14, 27, 26, 25, 33, 32, 23, 3}; //the bar has 10 leds, but the fist shows if the automation is on, the second is the minimum level. The first two will always be on together
int currentLevel = 1;
// int WasLevel = 0;

//sensor
const int dry = 5000; 
const int wet = 10; //the value the sensor gives when its in 100% water

int Procenten[] = {15, 25, 35, 40, 47, 55, 65, 75, 80};
//int percentageHumididy =0;

//delay sensor
unsigned long previousMillis = 0;
long sensorInterval = 10000; //60000 is a minute

//water
bool isWaterNeeded = false;
bool isWaterNeededApp = false;
long waterInterval = 5000;
unsigned long waterPreviousMillis = 0;


void setup() {

  USE_SERIAL.begin(115200);

  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP("BloomBlissHub", "raspberryConnect");

  for(int i = 0; i < 9; i++){
    pinMode(Leds[i], OUTPUT);
  }
  pinMode(SensorPin, INPUT);
  pinMode(WaterPin, OUTPUT);
  digitalWrite(WaterPin, LOW);

}

void loop() {

  get_data();
  

  if(isWaterNeededApp){
    GiveWater();
  }

  if (millis() - previousMillis >= sensorInterval) {
    SensorCheck();
    previousMillis = millis();
  }

  ShowLevel();
  
  AutoCheck();
  if(automation){
    PlusCheck();
    MinCheck();
    if(isWaterNeeded){
      GiveWater();
    }
  }
  else{
    isWaterNeeded = 0;
  }

}

void ShowLevel(){
  for(int i = 0; i < 9; i++){ //first turn off all leds, otherwise a led will stay on if levels is getting lowerd
    digitalWrite(Leds[i], LOW);
  }
  if(automation){
    for(int i = 0; i < currentLevel; i++){ //turn on leds till the amount off levels.
      digitalWrite(Leds[i], HIGH);
    }
  }
}

void SensorCheck(){
  // Serial.println("check sensor");
  int sensorVal = analogRead(SensorPin);
 
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);
  goToSite("http://raven.local:443/moisture_state/"+String(percentageHumidity));
  
  if(percentageHumidity<Procenten[currentLevel-1]){
    isWaterNeeded = true;
  }
}

void GiveWater() {
  if(millis() - waterPreviousMillis >= waterInterval) {
    digitalWrite(WaterPin, LOW);
    isWaterNeeded = false;
    isWaterNeededApp = false;
    goToSite("http://raven.local:443/water_given");
    waterPreviousMillis = millis();
  } else {
    digitalWrite(WaterPin, HIGH);
  }
}

void PlusCheck(){
  int PlusState = touchRead(PlusButtonPin);
  if(PlusState<buttonThreshold){ //compares the current state with the threshold when the button is pressed
    if(PlusLastState == false){ //if the button was not pressed in the last run will the program do the next code
      goToSite("http://raven.local:443/plus_pressed");
      PlusLastState = true; 
    }
  }
  else{
    PlusLastState = false; //the button is released.
  }
}

void MinCheck(){
  int MinState = touchRead(MinButtonPin);
  if(MinState<buttonThreshold){
    if(MinLastState == false){
      goToSite("http://raven.local:443/min_pressed");
      MinLastState = true;
    }
  }
  else{
    MinLastState = false;
  }
}

void AutoCheck(){
  int AutState = touchRead(AutButtonPin);
  if(AutState<buttonThreshold){
    if(AutLastState == false){
      goToSite("http://raven.local:443/auto_pressed");
      AutLastState = true;
    }
  }
  else{
    AutLastState = false;
  }
}


void get_data(){
  automation = get_from_site("http://raven.local:443/get_Automation_state");
  currentLevel = get_from_site("http://raven.local:443/get_Level_state");
  isWaterNeededApp = get_from_site("http://raven.local:443/get_giveWater_state");
}

void goToSite(String site) {
  if (wifiMulti.run() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(site);

    int httpCode = http.GET();
    if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
      Serial.println("Request success");
    } else {
      Serial.println("Request failed");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}

int get_from_site(String site) {
  if (wifiMulti.run() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(site);

    int httpCode = http.GET();
    if (httpCode > 0 && httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      return payload.toInt();
    } else {
      Serial.println("Request failed");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
