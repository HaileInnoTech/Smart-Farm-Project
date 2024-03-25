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

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 25200;
NTPClient timeClient(ntpUDP, "asia.pool.ntp.org", utcOffsetInSeconds);

String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600);  // Set the baud rate for Arduino communication

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  timeClient.begin();


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
  timeClient.update();
String timeStamp = "";
time_t epochTime = timeClient.getEpochTime();
struct tm *ptm = gmtime(&epochTime); 

// Format time into ISO 8601 format
char isoTime[30]; // Adjust buffer size as needed
strftime(isoTime, sizeof(isoTime), "%Y-%m-%dT%H:%M:%SZ", ptm);
timeStamp = String(isoTime);

Serial.println("ISO 8601 Timestamp: " + timeStamp);

  // if (arduinoSerial.available()) {

  // String data = arduinoSerial.readString();
  // String humidity = getValue(data, "Humidity:");
  // String temperature = getValue(data, "Temperature:");

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
  payload["collection"] = "data2";
  payload["document"]["temperature"] = temperature;
  payload["document"]["humidity"] = humidity;
  payload["document"]["timestamp"] = timeStamp;
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