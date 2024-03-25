#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <SoftwareSerial.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>

const char* rootCACertificate =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIF6TCCA9GgAwIBAgIQBeTcO5Q4qzuFl8umoZhQ4zANBgkqhkiG9w0BAQwFADCB\n"
  "iDELMAkGA1UEBhMCVVMxEzARBgNVBAgTCk5ldyBKZXJzZXkxFDASBgNVBAcTC0pl\n"
  "cnNleSBDaXR5MR4wHAYDVQQKExVUaGUgVVNFUlRSVVNUIE5ldHdvcmsxLjAsBgNV\n"
  "BAMTJVVTRVJUcnVzdCBSU0EgQ2VydGlmaWNhdGlvbiBBdXRob3JpdHkwHhcNMTQw\n"
  "OTEyMDAwMDAwWhcNMjQwOTExMjM1OTU5WjBfMQswCQYDVQQGEwJGUjEOMAwGA1UE\n"
  "CBMFUGFyaXMxDjAMBgNVBAcTBVBhcmlzMQ4wDAYDVQQKEwVHYW5kaTEgMB4GA1UE\n"
  "AxMXR2FuZGkgU3RhbmRhcmQgU1NMIENBIDIwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n"
  "DwAwggEKAoIBAQCUBC2meZV0/9UAPPWu2JSxKXzAjwsLibmCg5duNyj1ohrP0pIL\n"
  "m6jTh5RzhBCf3DXLwi2SrCG5yzv8QMHBgyHwv/j2nPqcghDA0I5O5Q1MsJFckLSk\n"
  "QFEW2uSEEi0FXKEfFxkkUap66uEHG4aNAXLy59SDIzme4OFMH2sio7QQZrDtgpbX\n"
  "bmq08j+1QvzdirWrui0dOnWbMdw+naxb00ENbLAb9Tr1eeohovj0M1JLJC0epJmx\n"
  "bUi8uBL+cnB89/sCdfSN3tbawKAyGlLfOGsuRTg/PwSWAP2h9KK71RfWJ3wbWFmV\n"
  "XooS/ZyrgT5SKEhRhWvzkbKGPym1bgNi7tYFAgMBAAGjggF1MIIBcTAfBgNVHSME\n"
  "GDAWgBRTeb9aqitKz1SA4dibwJ3ysgNmyzAdBgNVHQ4EFgQUs5Cn2MmvTs1hPJ98\n"
  "rV1/Qf1pMOowDgYDVR0PAQH/BAQDAgGGMBIGA1UdEwEB/wQIMAYBAf8CAQAwHQYD\n"
  "VR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMCMCIGA1UdIAQbMBkwDQYLKwYBBAGy\n"
  "MQECAhowCAYGZ4EMAQIBMFAGA1UdHwRJMEcwRaBDoEGGP2h0dHA6Ly9jcmwudXNl\n"
  "cnRydXN0LmNvbS9VU0VSVHJ1c3RSU0FDZXJ0aWZpY2F0aW9uQXV0aG9yaXR5LmNy\n"
  "bDB2BggrBgEFBQcBAQRqMGgwPwYIKwYBBQUHMAKGM2h0dHA6Ly9jcnQudXNlcnRy\n"
  "dXN0LmNvbS9VU0VSVHJ1c3RSU0FBZGRUcnVzdENBLmNydDAlBggrBgEFBQcwAYYZ\n"
  "aHR0cDovL29jc3AudXNlcnRydXN0LmNvbTANBgkqhkiG9w0BAQwFAAOCAgEAWGf9\n"
  "crJq13xhlhl+2UNG0SZ9yFP6ZrBrLafTqlb3OojQO3LJUP33WbKqaPWMcwO7lWUX\n"
  "zi8c3ZgTopHJ7qFAbjyY1lzzsiI8Le4bpOHeICQW8owRc5E69vrOJAKHypPstLbI\n"
  "FhfFcvwnQPYT/pOmnVHvPCvYd1ebjGU6NSU2t7WKY28HJ5OxYI2A25bUeo8tqxyI\n"
  "yW5+1mUfr13KFj8oRtygNeX56eXVlogMT8a3d2dIhCe2H7Bo26y/d7CQuKLJHDJd\n"
  "ArolQ4FCR7vY4Y8MDEZf7kYzawMUgtN+zY+vkNaOJH1AQrRqahfGlZfh8jjNp+20\n"
  "J0CT33KpuMZmYzc4ZCIwojvxuch7yPspOqsactIGEk72gtQjbz7Dk+XYtsDe3CMW\n"
  "1hMwt6CaDixVBgBwAc/qOR2A24j3pSC4W/0xJmmPLQphgzpHphNULB7j7UTKvGof\n"
  "KA5R2d4On3XNDgOVyvnFqSot/kGkoUeuDcL5OWYzSlvhhChZbH2UF3bkRYKtcCD9\n"
  "0m9jqNf6oDP6N8v3smWe2lBvP+Sn845dWDKXcCMu5/3EFZucJ48y7RetWIExKREa\n"
  "m9T8bJUox04FB6b9HbwZ4ui3uRGKLXASUoWNjDNKD/yZkuBjcNqllEdjB+dYxzFf\n"
  "BT02Vf6Dsuimrdfp5gJ0iHRc2jTbkNJtUQoj1iM=\n"
  "-----END CERTIFICATE-----\n";



#define WIFI_SSID "paPOCOF3"
#define WIFI_PASSWORD "12345678"



// #define API_KEY "AIzaSyAOmVngCIDg_WpMykay6NeKttHJPDu0pHc"
// #define DATABASE_URL "smart-farming-system-f9435-default-rtdb.asia-southeast1.firebasedatabase.app/"
// #define USER_EMAIL "hai28022002@gmail.com"
// #define USER_PASSWORD "Hoanghai___2002"

// FirebaseData fbdo;
// FirebaseAuth auth;
// FirebaseConfig config;
// unsigned long sendDataPrevMillis = 0;
// unsigned long count = 0;

SoftwareSerial arduinoSerial(D3, D4);  // RX (D3) and TX (D4) pins for Arduino communication

// WiFiUDP ntpUDP;
// const long utcOffsetInSeconds = 25200;
// NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);
// char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600);  // Set the baud rate for Arduino communication

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  // timeClient.begin();


  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  // Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  //   config.api_key = API_KEY;
  //   auth.user.email = USER_EMAIL;
  //   auth.user.password = USER_PASSWORD;
  //   config.database_url = DATABASE_URL;
  //   config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
  //   fbdo.setBSSLBufferSize(4096, 1024);
  //   // Connect to RTDB
  //   Firebase.begin(&config, &auth);
  //   Firebase.reconnectNetwork(true);
}

void loop() {
  // timeClient.update();
  // String currentTime = "";
  // currentTime += daysOfTheWeek[timeClient.getDay()];
  // currentTime += ", ";
  // currentTime += timeClient.getHours();
  // currentTime += ":";
  // currentTime += timeClient.getMinutes();
  // currentTime += ":";
  // currentTime += timeClient.getSeconds();
  // currentTime += " ";
  // currentTime += timeClient.get();
  // if (arduinoSerial.available()) {

  // String data = arduinoSerial.readString();
  // String humidity = getValue(data, "Humidity:");
  // String temperature = getValue(data, "Temperature:");

  // Prints "29.70" to the serial monitor
  // Serial.println(currentTime);     // Prints "29.70" to the serial monitor

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.setTimeout(15000);
  int temperature = random(10, 51);
  int humidity = random(10, 51);

  const String api_key = "g0k9qOqio6UY08K4PPI0FTJ0ATpMNnbu8T8Ta1ulNPypDLsOhTUgUg7sSGOJOsrw";
  const char* serverName = "https://ap-southeast-1.aws.data.mongodb-api.com/app/data-eaisp/endpoint/data/v1/action/insertOne";

  Serial.println(humidity);  // Prints "52" to the serial monitor
  Serial.println(temperature);

  http.begin(client, serverName) ; // HTTPS

    http.addHeader("Content-Type", "application/json");
  http.addHeader("api-key", api_key);
  JsonDocument payload;
  payload["dataSource"] = "mongoDB";
  payload["database"] = "IOT";
  payload["collection"] = "data";
  payload["document"]["temperature"] = temperature;
  payload["document"]["humidity"] = humidity;
  String JSONText;
  serializeJson(payload, JSONText);
  Serial.println(api_key);

  Serial.println(JSONText);

  // int httpCode = http.sendRequest("POST", JSONText);
  int httpResponseCode = http.POST(JSONText);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error in POST request: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  delay(15000);
}






// }

// String fireValue = getValue(data, "Fire Value:");
// String fireDetection = getValue(data, "Fire Detection:");
// String fireStatus = getValue(data, "Fire Status:");

// if (Firebase.ready() && (millis() - sendDataPrevMillis > 30000 || sendDataPrevMillis == 0))
//  {
//       sendDataPrevMillis = millis();
//       float temperature = random(101); // Generates a random number between 0 and 100
//       float humidity = random(101); // Generates a random number between 0 and 100

// storeDHTData(temperature, humidity, currentTime);
//  }
// Serial.println(fireValue);       // Prints "1023.00" to the serial monitor
// Serial.println(fireDetection);   // Prints "1.00" to the serial monitor
//   // Serial.println(fireStatus);      // Prints "Không có lửa" to the serial monitor
// }
// }

// String getValue(String data, String key) {
//   int startIndex = data.indexOf(key) + key.length() + 1;
//   int endIndex = data.indexOf("\n", startIndex);
//   String value = data.substring(startIndex, endIndex);

//   value.trim(); // Remove leading and trailing spaces
//   value.replace("%", ""); // Remove the "%" character
//   value.replace("*C", ""); // Remove the "*C" characters
//   return value;
// };
// void storeDHTData(float temperature, float humidity, String currentTime) {
//   Firebase.RTDB.pushFloat(&fbdo,"/Temp-Humid/temperature", temperature);
//   Firebase.RTDB.pushFloat(&fbdo,"/Temp-Humid/humidity", humidity);
//   Firebase.RTDB.pushString(&fbdo,"/Temp-Humid/timestamp", currentTime);

// }