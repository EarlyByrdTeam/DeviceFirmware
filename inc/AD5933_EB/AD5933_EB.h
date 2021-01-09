/*
  AD5933_EB.h - Library for interfacing with AD5933 impedance analyzer from arduino compatible MCU.
  Created by Mawaba Pascal Dao, Jan 7, 2021.
  Released into the public domain.
*/

#ifndef AD5933_EB_h
#define AD5933_EB_h

#include "Arduino.h"

#define AD5933_ADDR (0x0D)

#define CTRL_REG1 (0x80)
#define CTRL_REG2 (0x81)
// Start Frequency Register
#define START_FREQ_1 (0x82)
#define START_FREQ_2 (0x83)
#define START_FREQ_3 (0x84)
// Frequency increment register
#define INC_FREQ_1 (0x85)
#define INC_FREQ_2 (0x86)
#define INC_FREQ_3 (0x87)
// Number of increments register
#define NUM_INC_1 (0x88)
#define NUM_INC_2 (0x89)
// Number of settling time cycles register
#define NUM_SCYCLES_1 (0x8A)
#define NUM_SCYCLES_2 (0x8B)
//Control sequences
#define CTRL_STANDBY_MODE (0b10110000)
// #define MCLK (16776000) //16.776 MHz internal oscillator on (AD5933)

class AD5933_EB
{
public:
  AD5933_EB();
  bool reset(void);
  bool set_freq_start(unsigned long freq);
  bool set_freq_delta(unsigned long delta);
  bool set_incr_num(int num_incr);
  bool set_measurement_delay(void);
  bool init(void);
  bool standby(void);

private:
  unsigned long _freq_start;
  unsigned long _freq_delta;
  int _num_incr;
  unsigned long _freq_max;

  bool send(byte data[], int size);
  bool freq_setting(byte reg[], long setting);
  const unsigned long mclk = 16776000;
};

#endif
