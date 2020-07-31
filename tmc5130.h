#ifndef TMC5130_H
#define TMC5130_H

#define TMC5130_GCONF      0x00
#define TMC5130_GSTAT      0x01
#define TMC5130_IFCNT      0x02
#define TMC5130_SLAVECONF  0x03
#define TMC5130_IO         0x04
#define TMC5130_X_COMPARE  0x05

#define TMC5130_IHOLD_IRUN 0x10
#define TMC5130_TPOWERDOWN 0x11
#define TMC5130_TSTEP      0x12
#define TMC5130_TPWMTHRS   0x13
#define TMC5130_TCOOLTHRS  0x14
#define TMC5130_THIGH      0x15

#define TMC5130_RAMPMODE   0x20
#define TMC5130_XACTUAL    0x21
#define TMC5130_VACTUAL    0x22
#define TMC5130_VSTART     0x23
#define TMC5130_A1         0x24
#define TMC5130_V1         0x25
#define TMC5130_AMAX       0x26
#define TMC5130_VMAX       0x27
#define TMC5130_DMAX       0x28
#define TMC5130_D1         0x2A
#define TMC5130_VSTOP      0x2B
#define TMC5130_TZEROWAIT  0x2C
#define TMC5130_XTARGET    0x2D

#define TMC5130_CHOPCONF   0x6C
#define TMC5130_COOLCONF   0x6D

#include "spiHelper.h"

class TMC5130
{
public:
  TMC5130(int csPin);

  void begin();

  void move(unsigned long steps, bool backwards);
  void speed(unsigned long speed, bool direction);
  void readtstep(void);
  
private:
  int csPin;
  
};

#endif
