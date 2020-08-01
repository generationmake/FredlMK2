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

//#define MAXDIM 10

//static uint16_t x[QR_PT_DET_NUM], y[QR_PT_DET_NUM];

//struct qrPtn {
//  uint16_t x[QR_PT_DET_NUM];
//  uint16_t y[QR_PT_DET_NUM];
//};

//static qrPtn qrBufferPtn[MAXDIM];

//uint16_t count = 0, last;

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

void loop() {
//  Serial.print("input voltage: ");    
//  Serial.println(inputvoltage());    
  int validcounter=0;
  static int qrrecognized=0;

    /**
     qrrec.readQRCode(); get, if available, the coordinates of the QR code in the screen
  */
  vcam.qrrec.readQRCode();
//  Serial.print("QR_PT_DET_NUM: ");    
//  Serial.println(QR_PT_DET_NUM);    
  for (int i = 0; i < QR_PT_DET_NUM; i++) {
    if (vcam.qrrec.qr.pt[i].valid) {
      validcounter++;
//  Serial.println("valid");    
//      x[i] = (vcam.qrrec.qr.pt[i].xs + vcam.qrrec.qr.pt[i].xe) / 2;
//      y[i] = (vcam.qrrec.qr.pt[i].ys + vcam.qrrec.qr.pt[i].ye) / 2;
//      vcam.vgfx.Cross(x[i], y[i], 65535);

    }
  }

//  last = count % MAXDIM;
//  for (int i = 0; i < QR_PT_DET_NUM; i++) {
//    vcam.vgfx.Cross(qrBufferPtn[last].x[i], qrBufferPtn[last].y[i], 0, 0);
//    qrBufferPtn[last].x[i] = x[i];
//    qrBufferPtn[last].y[i] = y[i];
//  }
//  count++;
  Serial.println(validcounter);
  if(validcounter>2) qrrecognized++;
  else qrrecognized=0;
  if(qrrecognized>2) Serial.println("QR code recognized!!!");
  delay(30);    

/*  if(emergencybutton())
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
    tmc1.speed(10000,0); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(10000,1); // should be one turn with 1.8 degrees and 256 micro steps
    digitalWrite(LED_BUILTIN, HIGH);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    delay(2000);
    tmc1.readtstep(); // read tstep
    tmc2.readtstep(); // read tstep
    tmc1.speed(30000,0); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(30000,1); // should be one turn with 1.8 degrees and 256 micro steps
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
  delay(4000);*/

}
