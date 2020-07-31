#include "tmc5130.h"

// for Arduino MKR WiFi 1010 (on adapter)
TMC5130 tmc1(5); // stepper 1
TMC5130 tmc2(4); // stepper 2

// for Adafruit nRF52832 Bluefruit Feather
//TMC5130 tmc1(27); // stepper 1
//TMC5130 tmc2(30); // stepper 2

#define EMERGENCYSTOP A4

//returns the input voltage
float inputvoltage(void)
{
  return (float)analogRead(A0)/1024.0*3.3*16;
}

//returns false if emergency button is not activated
bool emergencybutton(void)
{
  return digitalRead(EMERGENCYSTOP);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(EMERGENCYSTOP,  INPUT_PULLDOWN);   // set EMERGENCYSTOP pin to input with pull down
  delay(4000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("setup SPI for TMC");
  setupSpiForTMC();
  Serial.println("done");
  Serial.println("setup TMC");
  tmc1.begin();
  tmc2.begin();
  Serial.println("done");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

void loop() {
  Serial.print("input voltage: ");    
  Serial.println(inputvoltage());    

  if(emergencybutton())
  {
    Serial.println("emergency button active");    
  }
  else
  {
//    tmc1.move(51200, false); // should be one turn with 1.8 degrees and 256 micro steps
//    tmc2.move(51200, false); // should be one turn with 1.8 degrees and 256 micro steps
//    digitalWrite(LED_BUILTIN, HIGH);
//    delay(4000);
//    tmc1.move(0, false); // should be one turn back with 1.8 degrees and 256 micro steps
//    tmc2.move(0, false); // should be one turn back with 1.8 degrees and 256 micro steps
//    digitalWrite(LED_BUILTIN, LOW);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    tmc1.speed(30000,0); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(30000,1); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, HIGH);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    delay(2000);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    tmc1.speed(100000,0); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(100000,1); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, LOW);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    delay(2000);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    tmc1.speed(10000,1); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(10000,1); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, HIGH);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    delay(2000);
    tmc1.speed(00000,1); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(00000,1); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, LOW);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
  }
  delay(4000);

}
