//defines
<<<<<<< HEAD
//#define SensorPin 22
#define WaterPin 1
=======
#define SensorPin 35
#define WaterPin 22
>>>>>>> 8f069ba7b1f3071a01628e2235bfa466f2f3c498

//touche buttons
#define PlusButtonPin 4
#define MinButtonPin 15
#define AutButtonPin 13

int buttonThreshold = 20; //under this threshold a button is pressed

//true is pressed. with this we make sure it only does one step and you cant keep a button pressed.
bool PlusLastState = false;
bool MinLastState = false;
bool AutLastState = false;

//ledbar
int Leds [] = {12, 14, 27, 26, 25, 33, 32, 23, 3}; //the bar has 10 leds, but the fist shows if the automation is on, the second is the minimum level. The first two will always be on together
int Level = 1;
int WasLevel = 0;

//sensor
<<<<<<< HEAD
const int highest = 200; //the value the sensor gives when its in 100% water
int oneLevel = highest/9; //1/9 of the highest is equel to one level
=======
const int dry = 3045; 
const int wet = 239; //the value the sensor gives when its in 100% water

int Procenten[] = {15, 25, 35, 40, 47, 55, 65, 75, 80};
//int percentageHumididy =0;

//delay sensor
unsigned long previousMillis = 0;
long sensorInterval = 60000; //60000 is a minute

//water
bool giveWater = false;
long waterInterval = 10000;
>>>>>>> 8f069ba7b1f3071a01628e2235bfa466f2f3c498

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 9; i++){
    pinMode(Leds[i], OUTPUT);
  }
<<<<<<< HEAD
  //pinMode(SensorPin, INPUT);
  pinMode(WaterPin, OUTPUT);
  digitalWrite(WaterPin, HIGH); //if the pomp is put on high it is off.
=======
  pinMode(SensorPin, INPUT);
  pinMode(WaterPin, OUTPUT);
  digitalWrite(WaterPin, LOW); //if the pomp is put on high it is off.
>>>>>>> 8f069ba7b1f3071a01628e2235bfa466f2f3c498
  Serial.begin(9600);
}

void loop() {
  PlusCheck();
  MinCheck();
  AutCheck();
<<<<<<< HEAD
  //SensorCheck();
  ShowLevel();
  GiveWater();
  
=======
  ShowLevel();
  if(interupt(sensorInterval)){
    SensorCheck();
  }
  if(giveWater){
    GiveWater();
  }
  // Serial.println(interupt(sensorPreviousMillis, sensorInterval));
>>>>>>> 8f069ba7b1f3071a01628e2235bfa466f2f3c498
}

void ShowLevel(){
  for(int i = 0; i < 9; i++){ //first turn off all leds, otherwise a led will stay on if levels is getting lowerd
    digitalWrite(Leds[i], LOW);
  }
  for(int i = 0; i < Level; i++){ //turn on leds till the amount off levels.
    digitalWrite(Leds[i], HIGH);
  }
}

void SensorCheck(){
<<<<<<< HEAD
  
}

void GiveWater(){
  if(Level>6){
    digitalWrite(WaterPin, LOW);
  }
  else if(Level == 0){
    digitalWrite(WaterPin, HIGH);
  }
  else{
    digitalWrite(WaterPin, HIGH);
    
  Serial.println("check sensor");
  int sensorVal = analogRead(SensorPin);
 
  int percentageHumidity = map(sensorVal, wet, dry, 100, 0); 
  
  if(percentageHumidity<Procenten[Level-1]){
    giveWater = true;
  }
}

void GiveWater(){
  unsigned long waterCurrentMillis = millis();
  if(Level == 0){
    digitalWrite(WaterPin, LOW);
    giveWater = false;
  }
  else if(!interupt(waterInterval)){
    digitalWrite(WaterPin, HIGH);
  }
  else{
    digitalWrite(WaterPin, LOW);
    giveWater = false;
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

void PlusCheck(){
  int PlusState = touchRead(PlusButtonPin);
  if(PlusState<buttonThreshold){ //compares the current state with the threshold when the button is pressed
    if(PlusLastState == false){ //if the button was not pressed in the last run will the program do the next code
      if(Level < 9){ //the levels dont do higher then 9
        Level += 1;
        PlusLastState = true; //the button was pressed, if you keep holding it. it wil not trigger the if(PlusLastState == false)
      }  
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
      if(Level > 1){ //the level can not go lower then level 1
        Level -= 1;
        MinLastState = true;
      }
    }
  }
  else{
    MinLastState = false;
  }
}

void AutCheck(){
  int AutState = touchRead(AutButtonPin);
  if(AutState<buttonThreshold){
    if(AutLastState == false){
      if(Level == 0){ //the automation needs to be turned on
        Level = WasLevel; //level gets value of what it was before, see the else
      }
      else{
        WasLevel = Level; //remember what the value was before turning the automation off.
        Level = 0; //turn automation off.
      }
      AutLastState = true;
    }
  }
  else{
    AutLastState = false;
  }
}