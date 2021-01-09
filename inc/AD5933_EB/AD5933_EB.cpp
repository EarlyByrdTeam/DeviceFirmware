#include "Arduino.h"
#include "AD5933_EB.h"
#include "Wire.h"
#include "math.h"

AD5933_EB::AD5933_EB()
{
    Serial.println("AD5933 Library for EB device");
}

bool AD5933_EB::reset(void)
{
    byte rst_seq[2] = {CTRL_REG2, 0x10}; //reset sequence
    return send(rst_seq, 2);
}

bool AD5933_EB::set_freq_start(unsigned long freq)
{
    byte reg[3] = {START_FREQ_1, START_FREQ_2, START_FREQ_3};
    _freq_start = freq;
    return freq_setting(reg, freq);
}

bool AD5933_EB::set_freq_delta(unsigned long delta)
{
    byte reg[3] = {INC_FREQ_1, INC_FREQ_2, INC_FREQ_3};
    _freq_delta = delta;
    return freq_setting(reg, delta);
}

bool AD5933_EB::set_incr_num(int num_incr)
{
    byte code[2];
    byte reg[2] = {NUM_INC_1, NUM_INC_2};
    byte packet[2];

    _num_incr = num_incr;
    code[0] = (num_incr & 0xFF);
    code[1] = ((num_incr >> 8) & 0xFF);

    Serial.print(code[0], HEX);
    Serial.println(code[1], HEX);

    for (int i = 0; i < 2; i++)
    {
        packet[0] = reg[i];
        packet[1] = code[i];
        if (!send(packet, 2))
            return false;
    }
    return true;
}

bool AD5933_EB::set_measurement_delay(void)
{
    byte reg[2] = {NUM_SCYCLES_1, NUM_SCYCLES_2};
    byte code[2];
    byte packet[2];
    float settling_time = 0.001; //1ms
    unsigned long f_max;
    unsigned long D;

    f_max = _freq_start + (_freq_delta * _num_incr);

    _freq_max = f_max;
    D = round(settling_time * f_max);
    code[0] = (D & 0xFF);
    code[1] = ((D >> 8) & 0xFF);
    Serial.println(D, DEC);
    Serial.print(code[0], HEX);
    Serial.println(code[1], HEX);

    for (int i = 0; i < 2; i++)
    {
        packet[0] = reg[i];
        packet[1] = code[i];
        if (!send(packet, 2))
            return false;
    }
    return true;
}

bool AD5933_EB::freq_setting(byte reg[], long setting)
{
    byte code[3];
    byte packet[2];
    //Start freq code:= (required_req/(MCLK/4))*2^27
    //Freq incr code:= (required_delta/(MCLK/4))*2^27
    long D = round(setting / (mclk / 4.0) * pow(2, 27));
    //split into 3 bytes
    code[0] = (D >> 16) & 0xFF;
    code[1] = (D >> 8) & 0xFF;
    code[2] = D & 0xFF;

    Serial.print(code[0], HEX);
    Serial.print(code[1], HEX);
    Serial.println(code[2], HEX);

    for (int i = 0; i < 3; i++)
    {
        packet[0] = reg[i];
        packet[1] = code[i];
        if (!send(packet, 2))
            return false;
    }
    return true;
}

bool AD5933_EB::init(void)
{
    byte init_seq[2] = {CTRL_REG1, 0x11};
    bool res = send(init_seq, 2);
    delay(500);
    return res;
}

bool AD5933_EB::standby(void)
{
    byte standby_seq[2] = {CTRL_REG1, CTRL_STANDBY_MODE};
    return send(standby_seq, 2);
}

bool AD5933_EB::send(byte data[], int size)
{
    Wire.beginTransmission(AD5933_ADDR);
    Wire.write(data, size);
    if (Wire.endTransmission() != 0x00)
        return false;
    else
        return true;
}