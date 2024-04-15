#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;


void setup() {

    USE_SERIAL.begin(115200);

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("BloomBlissHub", "raspberryConnect");

}

void loop() {
    set_remote_button()

    delay(5000);
}

void set_remote_button(){
  // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;

        // configure traged server and url
        http.begin("http://raven.local", ca);

        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                // USE_SERIAL.println(payload);
            }
        } else {
            //USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }
}
