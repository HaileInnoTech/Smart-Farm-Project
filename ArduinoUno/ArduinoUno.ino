#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT11   // DHT 11

const int relayPin = 13;


SoftwareSerial espSerial(10, 11); // RX, TX pins for ESP8266 communication
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600); // Set the baud rate for ESP8266 communication
  dht.begin();
  pinMode(relayPin, OUTPUT);

}

void loop() {
  delay(2000);
  read_Humid_Temp();
  read_Fire();
  read_Gas();
  read_Rain();
  //testRelay();
  Serial.println();
 
}

void read_Humid_Temp() {
   float humid_value = dht.readHumidity();
  float temperature_value = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(humid_value) || isnan(temperature_value)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Humidity: ");
  Serial.print(humid_value);
  Serial.println(" %");
  Serial.print("Temperature: ");
  Serial.print(temperature_value);
  Serial.println(" *C ");
  
  // Send humidity and temperature values to ESP8266
  espSerial.print("Humidity: ");
  espSerial.print(humid_value);
  espSerial.print(" %, Temperature: ");
  espSerial.print(temperature_value);
  espSerial.println(" *C");
}
void read_Fire(){
  float fire_value= analogRead(A0);
  float fire_detection =digitalRead(3);
  String fire_status;
  Serial.print("Fire Value: ");
  Serial.print(fire_value);
  Serial.println("");
  Serial.print("Fire Detection: ");
  Serial.print(fire_detection);
  Serial.println("");
  if (fire_detection == 1) {
    fire_status = "Không có lửa";
  } else {
    fire_status = "Có lửa";
  }
    Serial.print("Fire Status: ");
    Serial.print(fire_status);
    Serial.println("");

  espSerial.print("Fire Value: ");
  espSerial.println(fire_value);
  
  espSerial.print("Fire Detection: ");
  espSerial.println(fire_value);

  espSerial.print("Fire Status: ");
  espSerial.println(fire_status);

}
void read_Gas(){
  float gas_value= analogRead(A1);
  float gas_detection  = digitalRead(4);
  String gas_status;
  Serial.print("Gas Value: ");
  Serial.print(gas_value);
  Serial.println("");
  if (gas_value < 35) {
    gas_status = "Không có khói";
  } else {
    gas_status = "Có khói";
  }
    Serial.print("Gas Detection: ");
    Serial.print(gas_detection);
    Serial.println("");
    Serial.print("Gas Status: ");
    Serial.print(gas_status);
    Serial.println("");
   
  espSerial.print("Gas Value: ");
  espSerial.println(gas_value);

  espSerial.print("Gas Status: ");
  espSerial.println(gas_status);

}

void testRelay(){
    digitalWrite(relayPin, HIGH);
  
  // Wait for a second
  delay(1000);
  
  // Deactivate the relay
  digitalWrite(relayPin, LOW);
  
  // Wait for a second
  delay(1000);
}


void read_Rain(){
  {
  float rain_value = analogRead(A2);
  String rain_status;
  Serial.print("Rain value: ");
  Serial.print(rain_value);
  Serial.println("");
  if (rain_value < 400) {
    rain_status = "Có mưa";
  } else {
    rain_status = "Không có mưa";
  }
   Serial.print("Rain Status: ");
    Serial.print(rain_status);
    Serial.println("");
   
  espSerial.print("Rain Value: ");
  espSerial.println(rain_value);

  espSerial.print("Rain Status: ");
  espSerial.println(rain_status);
}
}