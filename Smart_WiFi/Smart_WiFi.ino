#include <WiFiManager.h> //It activates captive portal and dynamic Wifi selection
#include <ESP8266WiFi.h> //required for ESP wifi functionality
#include <WiFiClient.h> //required for TCP connection to connect to remote server. Used fo checking internet access
#include <ESP8266WebServer.h> // for hosting webserver on the ESP

// Constants
WiFiManager wm;
ESP8266WebServer server(80);
bool wasConnected = false;
bool internetConnected = true;
bool inAPMode = false; // Tracks whether the ESP is in AP mode
unsigned long previousMillis = 0;
unsigned long localWebStart = 0;
unsigned long currentMillis ;
const long interval = 10000; // Recheck WiFi connection every 10 seconds
const long interval1 = 10000;

#ifndef APSSID
#define APSSID "HydroAP"
#define APPSK "1234567890"
#endif

const char* ssid = APSSID;
const char* password = APPSK;

float currentTemperature = 25.0;
const char* test_host = "8.8.8.8";
const int test_port = 53;
//------------------------------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  Serial.println("Welcome to SmartWifi! Preparing to scan for hotspot, Turn on your device hotspot.");
  delay(10000);
  // Start in STA mode and attempt to connect
  WiFi.mode(WIFI_STA);
  bool res = wm.autoConnect("Hydroguard", "12345678");

  if (!res) {
    Serial.println("Failed to connect. Captive portal opened.");
    wasConnected = false;
  } else {
    Serial.print("Connected to Wi-Fi: ");
    Serial.println(WiFi.SSID());
    wasConnected = true;
  }
}

void loop() {
  currentMillis = millis();

  if (!inAPMode) { // Handle STA mode logic
    if (WiFi.status() != WL_CONNECTED) {
      if (wasConnected) {
        Serial.println("Wi-Fi disconnected.");
        Serial.println("Captive portal will reopen in 10 seconds");
        wasConnected = false;
        previousMillis = currentMillis;
      }

      if (currentMillis - previousMillis >= interval) {
        Serial.println("Reopening captive portal...");
        wm.autoConnect("Hydroguard", "12345678");
        previousMillis = currentMillis;
      }
    } else {
      if (!wasConnected) {
        Serial.print("Reconnected to Wi-Fi: ");
        Serial.println(WiFi.SSID());
        wasConnected = true;

        if (checkInternetAccess()) {
          Serial.println("Internet access is available!");
          uploadToFirebase();
        } else {
          Serial.println("No internet access. Switching to local server in 10 seconds.");
          internetConnected = false;
          localWebStart = currentMillis;
        }
      }

      if (checkInternetAccess()) {
        uploadToFirebase();
        internetConnected = true;
      }
    }

    if (!internetConnected && (currentMillis - localWebStart >= interval1)) {
      Serial.println("Switching to AP mode now...");
      startLocalWebServer();
    }
  } else { // Handle AP mode logic
    server.handleClient();
  }
}

bool checkInternetAccess() {
  WiFiClient client;
  if (client.connect(test_host, test_port)) {
    client.stop();
    return true;
  } else {
    return false;
  }
}

void startLocalWebServer() {
  inAPMode = true; // Mark as in AP mode
  WiFi.mode(WIFI_AP); // Switch to AP-only mode
  WiFi.softAP(ssid, password);

  server.on("/", []() {
    String html = R"rawliteral(
            <!DOCTYPE html>
            <html>
            <head>
                <title>ESP Web Server</title>
            </head>
            <body>
                <h1>ESP Web Server</h1>
                <p>Current Temperature: )rawliteral";
    html += String(currentTemperature, 2) + " °C</p>";
    html += R"rawliteral(
                <button onclick="fetch('/restore-sta').then(response => response.text().then(alert))">
                    Restore STA Mode
                </button>
            </body>
            </html>
        )rawliteral";
    server.send(200, "text/html", html);
  });

  server.on("/restore-sta", []() {
    server.send(200, "text/plain", "Switching back to STA mode...");
    restoreSTA();
  });

  server.begin();
  Serial.println("Local web server started. Access at http://192.168.4.1/");
}

void restoreSTA() {
  inAPMode = false;
  Serial.println("Button was clicked! Running function...");
  server.stop();
  WiFi.softAPdisconnect(true);
  server.send(200, "text/plain", "Local web server stopped and AP mode turned off!");

  Serial.println("Restarting Wi-Fi configuration...");
  bool res = wm.autoConnect("Hydroguard", "12345678");
  if (!res) {
    Serial.println("Failed to connect. Captive portal opened.");
  } else {
    Serial.print("Connected to Wi-Fi: ");
    Serial.println(WiFi.SSID());
  }
  if (checkInternetAccess()) {
    Serial.println("Internet access restored.");

  } else {
    Serial.println("No internet access. Switching to local server in 10 seconds.");
    localWebStart = currentMillis;
  }

}

//void restoreSTA() {
//    inAPMode = false;
//ESP.restart();
//}


void uploadToFirebase() {
  Serial.println("Uploading data to Firebase...");
  // Add Firebase upload code here
}
