#include "Arduino.h"
#include "AD5933_EB.h"
#include "Wire.h"

AD5933_EB::AD5933_EB()
{
    Serial.println("AD5933 Library for EB device");
}

bool AD5933_EB::reset(void)
{
    Wire.beginTransmission(AD5933_ADDR);
    byte rst_seq[2] = {0x81, 0x10}; //reset sequence
    Wire.write(rst_seq, 2);         //reset the AD5933
    if (Wire.endTransmission() != 0x00)
        return false;
    else
        return true;
}