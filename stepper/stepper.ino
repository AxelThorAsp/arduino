#include <Stepper.h>
#define SKREF 2048
Stepper stepper (SKREF, 4, 6, 5, 7);
Stepper stepper2 (SKREF, 8, 10, 9, 11);
Stepper stepper3 (SKREF, 0, 2, 1, 3);

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(16);
  stepper2.setSpeed(16);
  stepper3.setSpeed(16);
  exit(1);
}

void loop() {
  // put your main code here, to run repeatedly:
  // setja hraðann 1 rpm
  delay(1000);
  stepper2.step(SKREF); // fara 2048 skref -- einn hring á einni mínútu
  delay(1000); // hinkra í sekúndu (í ms)
  stepper2.step(SKREF);

  stepper.step(SKREF);
  delay(1000);

  stepper3.step(SKREF);
  
  
  //stepper2.step(SKREF);
  //delay(1000);
  //stepper2.step(-SKREF);

  //delay(1000);
  //stepper3.step(SKREF);
  //stepper3.step(SKREF);
}
