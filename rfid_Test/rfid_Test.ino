#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // RST pin la D9
#define SS_PIN          10          // SDA (SS) pin la D10

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Creează instanță MFRC522

void setup() {
  Serial.begin(9600);         // Inițializează comunicarea serială
  SPI.begin();                // Pornește SPI
  mfrc522.PCD_Init();         // Inițializează modulul RC522
  Serial.println("Apropie un card RFID...");
}

void loop() {
  // Verifică dacă este un card prezent
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Verifică dacă poate citi UID
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Afișează UID
  Serial.print("Card detectat, UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
