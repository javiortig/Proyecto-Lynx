#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";
const char* serverURL = "http://<RaspberryPiIP>:5000/update_distance";

void setup() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
    }
}

void loop() {
    long rssi = WiFi.RSSI();
    float distance = pow(10, (referenceRSSI - rssi) / (10 * pathLossExponent));

    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverURL);
        http.addHeader("Content-Type", "application/json");
        
        String jsonPayload = String("{\"player_id\": \"Player1\", \"distance\": ") + distance + "}";
        int httpResponseCode = http.POST(jsonPayload);
        http.end();
    }

    delay(1000);  // Send data every second
}
