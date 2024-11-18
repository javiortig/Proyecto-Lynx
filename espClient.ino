#include <WiFi.h>
#include <esp_wifi.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

const char* serverURL = "http://<RaspberryPiIP>:5000/update_distance";
const uint8_t bssid[6] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};  // Raspberry Pi MAC address

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to Wi-Fi...");
  }
  
  Serial.println("Connected to Wi-Fi");
}

void loop() {
  wifi_ap_record_t ap_info;
  esp_err_t result = esp_wifi_sta_get_ap_info(&ap_info);

  if (result == ESP_OK) {
    wifi_ftm_initiator_cfg_t cfg = {};
    cfg.resp_mac = bssid;  // Target AP MAC address
    cfg.channel = 1;       // Wi-Fi channel
    cfg.lci = false;       // Location Configuration Information
    cfg.lcr = false;       // Location Civic Report
    cfg.iterations = 8;    // Number of RTT measurements

    int16_t rtt = 0;  // Placeholder for RTT value
    // (Use ESP-IDF to configure RTT and fetch results here)
    // Calculate distance (in meters)
    float distance = rtt * 0.000299792458 / 2;  // RTT * speed of light / 2

    // Send the distance to the server
    sendDistanceToServer(distance);
  }

  delay(1000);  // Repeat every second
}

void sendDistanceToServer(float distance) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    
    String payload = "{\"player_id\": \"Player1\", \"distance\": " + String(distance) + "}";
    int httpResponseCode = http.POST(payload);
    http.end();

    if (httpResponseCode > 0) {
      Serial.printf("HTTP Response Code: %d\n", httpResponseCode);
    } else {
      Serial.println("Error in HTTP request");
    }
  }
}
