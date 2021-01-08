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

void AD5933_EB::set_start_freq(float freq)
{
    //Start freq code:= (required_req/(MCLK/4))*2^27
    char code_buf[24];
    _start_freq = freq;
    // int D = int(freq / (MCLK / 4.0)) * pow(2, 27);
    long int D = int(1950 / (16776000 / 4.0)) * pow(2, 27);
    Serial.println(D, DEC);
    String str = String(D, HEX);
    Serial.println(str);
    str.toCharArray(code_buf, 24);
    int freq_code = str2hex(code_buf);
    Serial.println(freq_code);
}

int AD5933_EB::str2hex(char *s)
{
    int x = 0;
    for (;;)
    {
        char c = *s;
        if (c >= '0' && c <= '9')
        {
            x *= 16;
            x += c - '0';
        }
        else if (c >= 'A' && c <= 'F')
        {
            x *= 16;
            x += (c - 'A') + 10;
        }
        else
            break;
        s++;
    }
    return x;
}