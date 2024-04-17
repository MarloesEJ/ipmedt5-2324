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
int Level = 1;
// int WasLevel = 0;

//sensor
const int dry = 3045; 
const int wet = 0; //the value the sensor gives when its in 100% water

int Procenten[] = {15, 25, 35, 40, 47, 55, 65, 75, 80};
//int percentageHumididy =0;

//delay sensor
unsigned long previousMillis = 0;
long sensorInterval = 10000; //60000 is a minute

//water
bool giveWater = 0;
bool giveWaterApp = 0;
long waterInterval = 5000;
unsigned long waterPreviousMillis = 0;

int checkInterval = 500;

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

  // if(interupt(checkInterval)){
    get_data();
  // }

  
  if(interupt(sensorInterval)){
    SensorCheck();
  }

  ShowLevel();

  if(!giveWaterApp){
    AutoCheck();

    if(automation){ //if automation is on, these things will be checked
      
      PlusCheck();
      MinCheck();
      if(giveWater == 1){
        GiveWater();
      }
    }
  }
  else{
    GiveWater();
  }
  
  // delay(50);
}

void ShowLevel(){
  for(int i = 0; i < 9; i++){ //first turn off all leds, otherwise a led will stay on if levels is getting lowerd
    digitalWrite(Leds[i], LOW);
  }
  if(automation == 1){
    for(int i = 0; i < Level; i++){ //turn on leds till the amount off levels.
      digitalWrite(Leds[i], HIGH);
    }
  }
}

void SensorCheck(){
  // Serial.println("check sensor");
  int sensorVal = analogRead(SensorPin);
 
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);
  give_App("http://raven.local:443/", percentageHumidity)
  
  if(percentageHumidity<Procenten[Level-1]){
    giveWater = 1;
  }
}

void GiveWater(){
  unsigned long waterCurrentMillis = millis();
  if(!waterInterupt(waterInterval)){
    digitalWrite(WaterPin, HIGH);
    Serial.println("on");
  }
  else{
    digitalWrite(WaterPin, LOW);
    Serial.println("off");
    giveWater = 0;
    giveWaterApp = 0;
    goToSite("http://raven.local:443/water_given");
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

bool interupt(long interval){
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    return true;
  }
  else{
    return false;
  }
}

bool waterInterupt(long interval){
  unsigned long currentMillis = millis();
  if(currentMillis - waterPreviousMillis >= interval){
    waterPreviousMillis = currentMillis;
    return true;
  }
  else{
    return false;
  }
}

void give_App(String site, int value){
  http.begin(site);
  //http.addHeader("giveWater", value);
  http.POST(value);
}


void get_data(){
  automation = get_from_site("http://raven.local:443/get_Automation_state");
  Level = get_from_site("http://raven.local:443/get_Level_state");
  giveWaterApp = get_from_site("http://raven.local:443/get_giveWater_state");
}

void goToSite(String site){
  // wait for WiFi connection
  if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin(site); //http://raven.local/

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {

            // file found at server
            Serial.println("went to site");
        } 
        else {
            //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
}

int get_from_site(String site){
  // wait for WiFi connection
  if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin(site); //http://raven.local/

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                return payload.toInt();
                // USE_SERIAL.println(payload);
            }
        } 
        else {
            //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
}
