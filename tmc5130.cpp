#include "tmc5130.h"

TMC5130::TMC5130(int csPin)
{
  this->csPin = csPin;
}

void TMC5130::begin()
{
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, LOW);

  sendSpiDataToTMC(TMC5130_GSTAT, 0x00000000, csPin, true); //read GSTAT
  sendSpiDataToTMC(TMC5130_GSTAT, 0x00000000, csPin, true); //read GSTAT
//  sendSpiDataToTMC(TMC5130_GCONF|0x80, 0x00000000, csPin, true); //write EN_PWM_MODE
  sendSpiDataToTMC(TMC5130_GCONF|0x80, 0x00000004, csPin, true); //write EN_PWM_MODE
//  sendSpiDataToTMC(TMC5130_CHOPCONF|0x80, 0x000101D5, csPin, true); //write CHOPCONF
  sendSpiDataToTMC(TMC5130_CHOPCONF|0x80, 0x000100C3, csPin, true); //write CHOPCONF
//  sendSpiDataToTMC(TMC5130_IHOLD_IRUN|0x80, 0x00070603, csPin, true); //write IHOLD_IRUN: IHOLD=3, IRUN=6, IHOLDDELAY=7 
//  sendSpiDataToTMC(TMC5130_IHOLD_IRUN|0x80, 0x00061F0A, csPin, true); //write IHOLD_IRUN: IHOLD=10, IRUN=31, IHOLDDELAY=6 
//  sendSpiDataToTMC(TMC5130_IHOLD_IRUN|0x80, 0x0006120A, csPin, true); //write IHOLD_IRUN: IHOLD=10, IRUN=18, IHOLDDELAY=6 
  sendSpiDataToTMC(TMC5130_IHOLD_IRUN|0x80, 0x00061A05, csPin, true); //write IHOLD_IRUN: IHOLD=5, IRUN=26, IHOLDDELAY=6 
  sendSpiDataToTMC(TMC5130_TPOWERDOWN|0x80, 0x0000000A, csPin, true); //write TPOWERDOWN=10
  sendSpiDataToTMC(TMC5130_TPWMTHRS|0x80, 0x000001F4, csPin, true); //write TPWM_THRS=500
//  sendSpiDataToTMC(0xF0, 0x00000000, csPin, true); //write PWMCONF
  sendSpiDataToTMC(0xF0, 0x000401C8, csPin, true); //write PWMCONF
  sendSpiDataToTMC(TMC5130_A1|0x80, 0x000003E8, csPin, true);  // write acceleration, was 0x03e8=1000
//  sendSpiDataToTMC(TMC5130_A1|0x80, 0x00000020, csPin, true);  // acceleration, was 0x03e8=1000
  sendSpiDataToTMC(TMC5130_V1|0x80, 0x000186A0, csPin, true);  //write V1
  sendSpiDataToTMC(TMC5130_AMAX|0x80, 0x00001338, csPin, true);  //write acceleration max=5000
//  sendSpiDataToTMC(TMC5130_AMAX|0x80, 0x0000C350, csPin, true);  //write acceleration max, was 0xC350=50000
//  sendSpiDataToTMC(TMC5130_AMAX|0x80, 0x00000100, csPin, true);  // acceleration max, was 0xC350=50000
//  sendSpiDataToTMC(TMC5130_VMAX|0x80, 0x000186A0, csPin, true);  //write VMAX
  sendSpiDataToTMC(TMC5130_DMAX|0x80, 0x000002BC, csPin, true);  //write DMAX=700
  sendSpiDataToTMC(TMC5130_D1|0x80, 0x00000578, csPin, true);  //write D1
  sendSpiDataToTMC(TMC5130_VSTOP|0x80, 0x0000000A, csPin, true);  //write VSTOP
//  sendSpiDataToTMC(TMC5130_RAMPMODE|0x80, 0x00000000, csPin, true);  //write RAMPMODE=0
  sendSpiDataToTMC(TMC5130_RAMPMODE|0x80, 0x00000001, csPin, true);  //write RAMPMODE=1

  //configure stallguard and coolstep
  sendSpiDataToTMC(TMC5130_TCOOLTHRS|0x80, 0x00001000, csPin, true);  //TMC5130_TCOOLTHRS=0x1000
  sendSpiDataToTMC(TMC5130_THIGH|0x80, 0x0000007F, csPin, true);  //TMC5130_THIGH=0x007F
  sendSpiDataToTMC(TMC5130_COOLCONF|0x80, 0x00000203, csPin, true); //write COOLCONF: semin=3, semax=2, seimin=0, seup=0, sedn=0;


  //finish configuration
  sendSpiDataToTMC(TMC5130_XACTUAL|0x80, 0x00000000, csPin, true);
  sendSpiDataToTMC(TMC5130_XTARGET|0x80, 0x00000000, csPin, true);
  sendSpiDataToTMC(TMC5130_GSTAT, 0x00000000, csPin, true); //read GSTAT
  sendSpiDataToTMC(TMC5130_GSTAT, 0x00000000, csPin, true); //read GSTAT
  sendSpiDataToTMC(0x6F, 0x00000000, csPin, true); //read DRV_STATUS
}

void TMC5130::move(unsigned long steps, bool backwards)
{
  if(backwards)
  {
    sendSpiDataToTMC(TMC5130_XACTUAL, steps, csPin, true);
    sendSpiDataToTMC(TMC5130_XTARGET|0x80, 0x00000000, csPin, true);
  }
  else
  {
    sendSpiDataToTMC(TMC5130_XACTUAL, 0x00000000, csPin, true);
    sendSpiDataToTMC(TMC5130_XTARGET|0x80, steps, csPin, true);
  }
}

void TMC5130::speed(unsigned long speed, bool direction)
{
  if(direction==1) sendSpiDataToTMC(TMC5130_RAMPMODE|0x80, 0x00000002, csPin, true);  //write RAMPMODE=2
  else sendSpiDataToTMC(TMC5130_RAMPMODE|0x80, 0x00000001, csPin, true);  //write RAMPMODE=1
//  sendSpiDataToTMC(TMC5130_XACTUAL, 0x00000000, csPin, true);
  sendSpiDataToTMC(TMC5130_VMAX|0x80, speed, csPin, true);
}

void TMC5130::readtstep()
{
  sendSpiDataToTMC(TMC5130_TSTEP, 0, csPin, true);
  sendSpiDataToTMC(TMC5130_TSTEP, 0, csPin, true);
}
