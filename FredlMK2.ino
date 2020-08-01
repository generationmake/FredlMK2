#include "tmc5130.h"

// for Arduino MKR WiFi 1010 (on adapter)
TMC5130 tmc1(5); // stepper 1
TMC5130 tmc2(4); // stepper 2

// for Adafruit nRF52832 Bluefruit Feather
//TMC5130 tmc1(27); // stepper 1
//TMC5130 tmc2(30); // stepper 2

#define EMERGENCYSTOP A4

#include "VidorGraphics.h"
#include "VidorCamera.h"

VidorCamera vcam;

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

  
  if (!FPGA.begin()) {
    Serial.println("Initialization failed!");
    while (1) {}
  }
  /**
    begin() enable the I2C communication and initialize the display for the camera
  */
  if (!vcam.begin()) {
    Serial.println("Camera begin failed");
    while (1) {}
  }
  /**
      qrrec.begin(); enable the QR code recognition
  */
  vcam.qrrec.begin();
  delay(4000);
  Serial.println("Power ON");
  
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
int check_qrcode(void)
{
  int validcounter=0;
  static int qrrecognized=0;

    /**
     qrrec.readQRCode(); get, if available, the coordinates of the QR code in the screen
  */
  vcam.qrrec.readQRCode();
  for (int i = 0; i < QR_PT_DET_NUM; i++) {
    if (vcam.qrrec.qr.pt[i].valid) {
      validcounter++;
    }
  }

  Serial.println(validcounter);
  if(validcounter>2) qrrecognized++;
  else qrrecognized=0;
  if(qrrecognized>2) return 1;
  else return 0;
}
void drive(void)
{  
  if(!emergencybutton())
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
    digitalWrite(LED_BUILTIN, LOW);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
  }
}

void stop(void)
{  
  tmc1.speed(00000,1); // should be one turn with 1.8 degrees and 256 micro steps
  tmc2.speed(00000,1); // should be one turn with 1.8 degrees and 256 micro steps
  digitalWrite(LED_BUILTIN, LOW);
  tmc1.readtstep(); // read tstep
  tmc2.readtstep(); // read tstep
}

void loop() {
  static int state=0;
  static int count=0;

  Serial.print("input voltage: ");    
  Serial.println(inputvoltage());    
  if(emergencybutton())
  {
    Serial.println("emergency button active");    
  }
  Serial.print("state: ");    
  Serial.println(state);    

  if(state==0)  // wait for QR code
  {
    if(check_qrcode())
    {
      Serial.println("QR code recognized!!!");
      state=1;  // go to next state
      count=0;  // reset counter
    }
  }
  else if(state==1)  // drive
  {
    drive();
    if(count>20)
    {
      state=2;  // go to next state
      count=0;  // reset counter
    }
  }
  else if(state==2)  // wait for barrel
  {
    stop();
  }
  delay(100);
  count++;    

}
