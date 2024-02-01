#include <SoftwareSerial.h>

SoftwareSerial arduinoSerial(D3, D4); // RX (D3) and TX (D4) pins for Arduino communication

void setup() {
  Serial.begin(9600);
  arduinoSerial.begin(9600); // Set the baud rate for Arduino communication
}

void loop() {
  if (arduinoSerial.available()) {
    String data = arduinoSerial.readString();
    Serial.println("Received from Arduino: ");
    Serial.println(data);

  }
}