#include <Wire.h>

///////////////////////////////////
/////// Device scanner for I2c ////
///////////////////////////////////
// void setup()
// {
//   Wire.begin();
//   Serial.begin(9600);
//   Serial.println("\nI2C Scanner");
// }

// void loop()
// {
//   byte error, address;
//   int devices;
//   Serial.println("Scanning...");
//   devices = 0;
//   for(address = 1; address < 127; address++)
//   {
//     Wire.beginTransmission(address);
//     error = Wire.endTransmission();
//     if(error == 0)
//     {
//       Serial.print("I2C device found at address 0x");
//       if(address < 16)
//         Serial.print("0");
//       Serial.print(address, HEX);
//       Serial.println("  !");
//       devices++;
//     }
//   }
// }

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Change address if needed
const int irLedPin = 3; // Pin connected to IR LED (use PWM-capable pin)

void setup() {
  pinMode(irLedPin, OUTPUT);
}

void loop() {
  // Blink visible to phone camera: on 1 second, off 1 second
  digitalWrite(irLedPin, HIGH);
  delay(1000);
  digitalWrite(irLedPin, LOW);
  delay(1000);
}
