#define ledPin 5

int ledState = LOW;

unsigned long previousMillis =0;

float frequentie = 5;

long interval = (1/frequentie)*1000;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if(ledState ==LOW){
      ledState = HIGH;
    }
    else{
      ledState = LOW;
    }
    digitalWrite(ledPin, ledState);
  }
}
