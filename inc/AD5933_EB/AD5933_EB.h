/*
  AD5933_EB.h - Library for interfacing with AD5933 impedance analyzer from arduino compatible MCU.
  Created by Mawaba Pascal Dao, Jan 7, 2021.
  Released into the public domain.
*/

#ifndef AD5933_EB_h
#define AD5933_EB_h

#include "Arduino.h"

#define AD5933_ADDR (0x0D)
#define MCLK (16776000) //16.776 MHz internal oscillator on (AD5933)

class AD5933_EB
{
public:
  AD5933_EB();
  bool reset(void);
  void set_start_freq(float freq);

private:
  float _start_freq;
  int str2hex(char *s);
};

#endif
