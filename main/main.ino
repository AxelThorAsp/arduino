#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Stepper.h>

#define SKREF 2048
#define ONE_WIRE_BUS 19

// TCS230 or TCS3200 pins wiring to Arduino
#define S0 14
#define S1 15
#define S2 16
#define S3 17
#define sensorOut 18

// Stores frequency read by the photodiodes
int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

// Stores the red. green and blue colors
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

Stepper stepper (SKREF, 4, 6, 5, 7);
Stepper stepper2 (SKREF, 8, 10, 9, 11);
Stepper stepper3 (SKREF, 0, 2, 1, 3);

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);





void setup() {
  // put your setup code here, to run once:
  // Start serial communication for debugging purposes
  Serial.begin(9600);
  // Start up the library
  //Temperature 
  sensors.begin();
  
  stepper.setSpeed(16);
  stepper2.setSpeed(16);
  stepper3.setSpeed(16);
  
  //Light sensor
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
 
}

void twoStep() {
  while (true) {
      stepper.step(1);
      stepper3.step(1);
    }
  }



void printTemp() {
  sensors.requestTemperatures();
  Serial.print("Celsius temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println("");
  delay(1000);
  }

void printColor() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  // Reading the output frequency
  redFrequency = pulseIn(sensorOut, LOW);
  redColor = map(redFrequency, 72, 110, 255,0);
  
  // Printing the RED (R) value
  Serial.print("R = ");
  Serial.print(redColor);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  greenFrequency = pulseIn(sensorOut, LOW);

  greenColor = map(greenFrequency, 230, 460, 255, 0);
  
  // Printing the GREEN (G) value  
  Serial.print(" G = ");
  Serial.print(greenColor);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  // Reading the output frequency
  blueFrequency = pulseIn(sensorOut, LOW);
  
  blueColor = map(blueFrequency, 162, 200, 255, 0);
  
  // Printing the BLUE (B) value 
  Serial.print(" B = ");
  Serial.print(blueColor);
  delay(100);

  // Checks the current detected color and prints
  // a message in the serial monitor
  if(redColor > greenColor && redColor > blueColor){
      Serial.println(" - RED detected!");
  }
  if(greenColor > redColor && greenColor > blueColor){
    Serial.println(" - GREEN detected!");
  }
  if(blueColor > redColor && blueColor > greenColor){
    Serial.println(" - BLUE detected!");
  }
  
}
void loop() {
  // put your main code here, to run repeatedly
  //twoStep();
  printTemp();
  printColor();

}
