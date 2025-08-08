#include <Stepper.h>

int stepsPerRevolution = 2048;
int rpm = 10; // Spped of the motor

int stepperPins[] = {8, 9, 10, 11};
Stepper myStepper(stepsPerRevolution, stepperPins[0], stepperPins[1], stepperPins[2], stepperPins[3]);

void setup()
{
  myStepper.setSpeed(rpm);
}

void loop()
{
  myStepper.step(stepsPerRevolution);
  delay(1000);
  myStepper.step(-stepsPerRevolution);
  delay(1000);
}