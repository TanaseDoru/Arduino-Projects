/*
Easy Arduino Tutorial: #9 IR Receiver

In this sketch we control an LED using a remote control and a IR Receiver.

Library used: IRremote by shirriff, z3t0, ArminJo https://www.arduinolibraries.info/libraries/i-rremote


Created by: InterlinkKnight
Last modification: 2024-07-21
*/


///////////////////////////
////////// Pins ///////////
///////////////////////////

const int IRReceiverPin = 6;  // Pin for IR receiver

// IR Receiver:
#include <IRremote.hpp>  // Include the library for IR receiver
uint64_t decCode;  // Create variable to store the code we received from the remote control



void setup()  // Start of setup - Runs once when we reset or power the board
{
  
  // Start serial communication for printing the serial monitor:
  Serial.begin(9600);  // Start serial communication with baud rate of 9600 bps


  // IR Receiver:
  IrReceiver.begin(IRReceiverPin);
  
}  // End of setup





void loop()  // Start of loop - Runs over and over again indefinitely
{

  delay(50);  // Wait this amount of milliseconds. 1000 milliseconds is 1 second
  
  
  // IR Receiver:
  if(IrReceiver.decode())  // If we receive a signal from the IR receiver
  {
    decCode = IrReceiver.decodedIRData.decodedRawData;  // Store the code we received
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);  // Print in the serial monitor the value of the remote control
    
    IrReceiver.resume();  // Receive the next value
    

  }  // End of if we receive a signal from the IR receiver

}  // End of loop
