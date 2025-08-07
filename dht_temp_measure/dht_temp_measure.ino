#include <DHT.h>

#define DHTPIN A0       // DHT11 data pin
#define DHTTYPE DHT11   // DHT11 sensor
DHT dht(DHTPIN, DHTTYPE);



// 7-segment display pins (Common Anode)
int pinA = 11; // Segment a
int pinB = 7;  // Segment b
int pinC = 4;  // Segment c
int pinD = 2;  // Segment d
int pinE = 13;  // Segment e
int pinF = 10; // Segment f
int pinG = 5;  // Segment g
int pinDP = 3; // Decimal point
int D1 = 12;   // Digit 1
int D2 = 9;    // Digit 2
int D3 = 8;    // Digit 3
int D4 = 6;    // Digit 4

const int digitPins[4] = {D1, D2, D3, D4};

// Segment patterns for digits 0-9 (Common Anode: LOW = on)
const byte digitPatterns[10] = {
  B00111111, // 0
  B00000110, // 1
  B01011011, // 2
  B01001111, // 3
  B01100110, // 4
  B01101101, // 5
  B01111101, // 6
  B00000111, // 7
  B01111111, // 8
  B01101111  // 9
};

void setup() {
  // Set all segment and digit pins as outputs
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinDP, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  // Turn off all digits initially
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH);
  // Initialize DHT sensor
  Serial.begin(9600);
  dht.begin();
}

void loop() {

  // Read temperature from DHT11
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature!");
    return;
  }

  // Convert temperature to integer (e.g., 25.67 -> 2567)
  int tempInt = (int)(temperature * 100);
  int digits[4] = {0, 0, 0, 0};
  digits[3] = tempInt % 10;         // Second decimal place
  digits[2] = (tempInt / 10) % 10;  // First decimal place
  digits[1] = (tempInt / 100) % 10; // Units
  digits[0] = (tempInt / 1000) % 10; // Tens

  // Multiplexing to display digits
  for (int i = 0; i < 4; i++) {
    // Turn off all digits
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH);
    // Set segments for current digit
    digitalWrite(pinA, bitRead(digitPatterns[digits[i]], 0));
    digitalWrite(pinB, bitRead(digitPatterns[digits[i]], 1));
    digitalWrite(pinC, bitRead(digitPatterns[digits[i]], 2));
    digitalWrite(pinD, bitRead(digitPatterns[digits[i]], 3));
    digitalWrite(pinE, bitRead(digitPatterns[digits[i]], 4));
    digitalWrite(pinF, bitRead(digitPatterns[digits[i]], 5));
    digitalWrite(pinG, bitRead(digitPatterns[digits[i]], 6));
    // Set decimal point (on for 3rd digit)
    digitalWrite(pinDP, (i == 1) ? HIGH : LOW); // HIGH = on for Common Anode
    // Activate current digit
    digitalWrite(digitPins[i], LOW); // HIGH = on for Common Anode
    delay(5); // Display for 5ms
  }
}
