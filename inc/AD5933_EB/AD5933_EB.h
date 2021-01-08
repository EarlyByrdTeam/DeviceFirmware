/*
  AD5933_EB.h - Library for interfacing with AD5933 impedance analyzer from arduino compatible MCU.
  Created by Mawaba Pascal Dao, Jan 7, 2021.
  Released into the public domain.
*/

#ifndef AD5933_EB_h
#define AD5933_EB_h

#include "Arduino.h"

#define AD5933_ADDR (0x0D)

class AD5933_EB
{
public:
  AD5933_EB();
  bool reset(void);
};

#endif
