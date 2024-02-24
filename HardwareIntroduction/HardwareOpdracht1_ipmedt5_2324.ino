#define PIN_CLK 32
#define PIN_DT 34
#define PIN_SW 35 //button on the encoder


int state;
int lastState;
float ledFrequentie = 0;


void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_CLK, INPUT);
  pinMode(PIN_DT, INPUT);
  pinMode(PIN_SW, INPUT);

  Serial.begin(9600);

  lastState = digitalRead(PIN_CLK);
}

void loop() {
  // put your main code here, to run repeatedly:
  state = digitalRead(PIN_CLK);
  if(lastState != state){
    Serial.println("If1");
    if(digitalRead(PIN_DT)!= state){
      Serial.println("If2");
      if(ledFrequentie != 100){
        Serial.println("If3");
        ledFrequentie += 0.25;
        Serial.print("led is: ");
        Serial.println(ledFrequentie);
      }
    }
    else {
      if (ledFrequentie != 0){
      Serial.println("elseif");
      ledFrequentie -= 0.25;
      Serial.print("led is: ");
      Serial.println(ledFrequentie); 
      }
    }
  }
  lastState = state;
}
