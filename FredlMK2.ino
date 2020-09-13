#include "tmc5130.h"
#include "SonarExtenderI2C.h"
#include <DogGraphicDisplay.h>
#include "ubuntumono_b_32.h"
#include "ubuntumono_b_16.h"
#include "ubuntumono_b_8.h"

// for Arduino MKR WiFi 1010 (on adapter)
TMC5130 tmc1(5); // stepper 1
TMC5130 tmc2(4); // stepper 2

// for Adafruit nRF52832 Bluefruit Feather
//TMC5130 tmc1(27); // stepper 1
//TMC5130 tmc2(30); // stepper 2

#define EMERGENCYSTOP A4
#define BARRELSWITCH A1

#include "VidorGraphics.h"
#include "VidorCamera.h"

VidorCamera vcam;

SonarExtenderI2C sonar;

#define LOGO_LEN  386

#if defined(ARDUINO_ARCH_AVR)
  // AVR-specific code
const byte logo[LOGO_LEN] __attribute__((section(".progmem.data")))=
#else
  // generic, non-platform specific code
const byte logo[LOGO_LEN] =
#endif
{
   128, 24,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00,
0x00, 0x40, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0,
0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xCC, 0xFE, 0xF1, 0xF3, 0xDF, 0x9F, 0x83, 0x00, 0x00, 0x7C,
0x7E, 0xDB, 0x91, 0x9B, 0xDE, 0x5C, 0x00, 0x00, 0xFF, 0xFF,
0x0E, 0x02, 0x03, 0x07, 0xFE, 0xFC, 0x00, 0x00, 0x7E, 0x7E,
0xD3, 0x91, 0x9B, 0xDE, 0x5C, 0x00, 0x00, 0xFF, 0xFF, 0x0C,
0x02, 0x03, 0x00, 0x70, 0xF2, 0xD3, 0x91, 0x53, 0x7F, 0xFE,
0x00, 0x00, 0x02, 0x7F, 0xFF, 0xC3, 0xC1, 0x40, 0x00, 0xFF,
0xFF, 0xFF, 0x00, 0x00, 0x7C, 0x7E, 0xC3, 0x83, 0xC3, 0x7E,
0x3C, 0x10, 0x00, 0xFF, 0xFF, 0x0E, 0x02, 0x03, 0x0F, 0xFE,
0xFC, 0x00, 0x00, 0x00, 0xFF, 0x06, 0x00, 0x03, 0xFF, 0xFE,
0x00, 0x00, 0x03, 0xFF, 0xFE, 0x00, 0x00, 0x60, 0x70, 0xD2,
0x11, 0x53, 0x7E, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x18,
0x1C, 0x7E, 0xF3, 0xC1, 0x00, 0x00, 0x18, 0x7E, 0x5E, 0x93,
0x91, 0x9E, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x04,
0x04, 0x04, 0x04, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00
};

// define some values used by the panel and buttons
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
//  int adc_key_in = analogRead(0);      // read the value from the sensor 
  int adc_key_in = analogRead(2);      // read the value from the sensor 
  // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
  // my buttons when read are centered at these values (MKR1010): 0, 11, 162, 354, 531, 763
  // we add approx 50 to those values and check to see if we are close
  if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
  if (adc_key_in < 50)   return btnRIGHT;  
  if (adc_key_in < 250)  return btnUP; 
  if (adc_key_in < 450)  return btnDOWN; 
  if (adc_key_in < 650)  return btnLEFT; 
  if (adc_key_in < 850)  return btnSELECT;  

  return btnNONE;  // when all others fail, return this...
}

DogGraphicDisplay DOG;

//int backlight_led = 10;
int backlight_led = A6;
void init_backlight(boolean mono);
void mono_backlight(byte brightness);

//create a sample sceen content
void sample_screen(void)
{
  DOG.clear();  //clear whole display
  DOG.string(0,0,UBUNTUMONO_B_8,"www.generationmake.de",ALIGN_CENTER);
//  DOG.string(0,1,UBUNTUMONO_B_16,"EA DOGS102-6",ALIGN_CENTER,STYLE_FULL_INVERSE);
  DOG.string(0,1,UBUNTUMONO_B_16,"EA DOGM128-6",ALIGN_CENTER,STYLE_FULL_INVERSE);
}



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

//returns false if barrel is present
bool barrelstate(void)
{
  return digitalRead(BARRELSWITCH);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(EMERGENCYSTOP,  INPUT_PULLDOWN);   // set EMERGENCYSTOP pin to input with pull down
  pinMode(BARRELSWITCH,  INPUT_PULLUP);   // set BARRELSWITCH pin to input with pull down
  delay(1000);
  DOG.initialize(6,0,0,0,1,DOGM128);   //SS = 6, 0,0= use Hardware SPI, 0 = A0, 1 = RESET, EA DOGM128-6 (=128x64 dots)
  DOG.clear();  //clear whole display
  DOG.picture(0,0,logo,STYLE_INVERSE);

  sonar.begin();
  sonar.startAutoread();
  
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
  delay(1000);
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
  mono_backlight(255);    //BL to full brightness
  DOG.view(VIEW_BOTTOM);  //default viewing direction
  sample_screen();        //show content
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
  if(qrrecognized>1) return 1;
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
    tmc1.speed(52000,0); // should be one turn with 1.8 degrees and 256 micro steps
    tmc2.speed(50000,1); // should be one turn with 1.8 degrees and 256 micro steps
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
  int distance=0;
  static int olddistance=0;

  Serial.print("input voltage: ");    
  Serial.println(inputvoltage());    
  sonar.read(0);
  Serial.print("sonar distance: ");    
  distance=sonar.getMeasurementCm(0);
  Serial.println(distance);

  if(emergencybutton())
  {
    Serial.println("emergency button active");    
  }
  if(!barrelstate())
  {
    Serial.println("barrel present");    
  }
  Serial.print("state: ");    
  Serial.println(state);    

  if(state==0)  // wait for QR code
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle led 
    if(check_qrcode()||(count>30))
    {
      Serial.println("QR code recognized!!!");
      state=1;  // go to next state
      count=0;  // reset counter
    }
  }
  else if(state==1)  // drive
  {
    digitalWrite(LED_BUILTIN, LOW); // turn led on
    if(distance>25)
    {
      drive();
      if(count>20)  
      {
        state=2;  // go to next state
        count=0;  // reset counter
      }      
    }
    else stop();
  }
  else if(state==2)  // wait for barrel
  {
    stop();
    digitalWrite(LED_BUILTIN, HIGH); // turn led off
    if(!barrelstate())  // barrel loaded
    {
      state=3;  // go to next state
      count=0;  // reset counter
    }
  }
  else if(state==3)  // wait after barrel load
  {
    stop();
    digitalWrite(LED_BUILTIN, LOW); // turn led on
    if(count>20)
    {
      state=4;  // go to next state
      count=0;  // reset counter
    }    
  }
  else if(state==4)  // drive forever
  {
    if((distance<25)&&(olddistance<35)) stop();
    else drive();
  }
  delay(70);
  count++;    
  olddistance=distance;

}


//The following functions controll the backlight with a PWM. Not needed for the display content
void init_backlight(boolean mono)
{
  if(mono) //EA LED55X31-G, EA LED55X31-W, EA LED55X31-B, EA LED55X31-A, EA LED55X31-R
  {
    pinMode(backlight_led,  OUTPUT);
    mono_backlight(255);
  }
}
//Use this funtion for monochrome backlight
void mono_backlight(byte brightness)
{
#if defined(ARDUINO_ARCH_AVR)
  // AVR-specific code
  analogWrite(backlight_led, brightness);  
#elif defined(ARDUINO_ARCH_SAMD)
  // SAMD-specific code
  if(brightness>0) digitalWrite(backlight_led,  HIGH);
  else digitalWrite(backlight_led,  LOW);
#endif
}
