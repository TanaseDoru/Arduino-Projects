///////////////////////////
////////// Pins ///////////
///////////////////////////

const int IRReceiverPin = 6;  // Pin for IR receiver
const int redPin = 2;
const int greenPin = 3;
const int bluePin = 4;
const int buzzerPin = 7;

///////////////////////////
////////// Vars ///////////
///////////////////////////


int guessStage = 0;
uint64_t password[] = 
{
  0xF30CFF00,
  0xE718FF00,
  0xA15EFF00,
  0xF708FF00
};
int passLen = sizeof(password) / sizeof(password[0]);

unsigned long irValue = 0;


// IR Receiver:
#include <IRremote.hpp>  // Include the library for IR receiver
uint64_t decCode;  // Create variable to store the code we received from the remote control
IRRawDataType recvData;

enum CurrentState {
  Wrong,
  Pending,
  Correct,
};

void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin,  greenValue);
  analogWrite(bluePin, blueValue);
}

void setCurrentState(CurrentState state) {
  switch (state) {
    case Wrong:
      setColor(255, 0, 0);
      break;
    case Pending:
      setColor(255, 255, 0);
      break;
    case Correct:
      setColor(0, 255, 0);
      break;
  }
}

void activateBuzzer(int miliseconds)
{
  digitalWrite(buzzerPin, HIGH);
  delay(miliseconds);
  digitalWrite(buzzerPin, LOW);

}

void correctBuzzerActivation(int milisecondsBuzzer, int milisecondsInterval)
{
  activateBuzzer(milisecondsBuzzer);
  delay(milisecondsInterval);
  activateBuzzer(milisecondsBuzzer * 2);
}


void setup()  // Start of setup - Runs once when we reset or power the board
{
  
  // Start serial communication for printing the serial monitor:
  Serial.begin(9600);  // Start serial communication with baud rate of 9600 bps


  // IR Receiver:
  IrReceiver.begin(IRReceiverPin);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);
}  // End of setup


void loop()  // Start of loop - Runs over and over again indefinitely
{

  delay(50);  // Wait this amount of milliseconds. 1000 milliseconds is 1 second
  
  
  // IR Receiver:
  if (IrReceiver.decode()) {
    irValue = (unsigned long)IrReceiver.decodedIRData.decodedRawData;

    Serial.println(irValue, HEX);  // Print it in HEX form
    // Serial.println(password[guessStage], HEX);

    if (irValue == password[guessStage]) {
      guessStage++;
      if(guessStage == passLen)
      {
        guessStage = 0;
        setCurrentState(CurrentState::Correct);
        correctBuzzerActivation(100, 100);
      }
      else
      {
        activateBuzzer(100);

      }
    }
    else if (irValue != 0)
    {
      guessStage = 0;
      setCurrentState(CurrentState::Wrong);
      activateBuzzer(100);
    }

    IrReceiver.resume();  // Ready for the next value
}


}  // End of loop
