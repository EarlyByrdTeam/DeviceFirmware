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

bool AD5933_EB::start_freq_sweep(void)
{
    byte sweep_seq[2] = {CTRL_REG1, 0x21};
    return send(sweep_seq, 2);
}

bool AD5933_EB::check_result(void)
{
    byte status = readReg(STATUS_REG);
    if (status == 0xFF)
        return false; //Could not read register
    else
    {
        if (status & 0x02 > 0) //results available
            return true;
        else
            return false; // Results not available
    }
}

bool AD5933_EB::read_complex_data(int *real, int *imag)
{
    byte realData[2];
    byte imagData[2];

    realData[0] = readReg(REAL_DATA_REG_1);
    realData[1] = readReg(REAL_DATA_REG_2);
    imagData[0] = readReg(IMAG_DATA_REG_1);
    imagData[1] = readReg(IMAG_DATA_REG_2);

    if (realData[0] == 0xFF || realData[1] == 0xFF || imagData[0] == 0xFF || imagData[1] == 0xFF)
        return false;

    //Combine components into real and imaginary 16-bit ints
    *real = (int16_t)(((realData[0] << 8) | realData[1]) & 0xFFFF);
    *imag = (int16_t)(((imagData[0] << 8) | imagData[1]) & 0xFFFF);
    return true;
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

bool AD5933_EB::receiveByte(byte reg, byte *value)
{
    // Wire.beginTransmission(AD5933_ADDR);
    // Wire.write(reg);             // set register for read
    // Wire.endTransmission(false); // false to not release the line

    Wire.requestFrom(AD5933_ADDR, 1); // request bytes from register XY
    // byte buff[READ_LENGTH];
    // Wire.readBytes(buff, READ_LENGTH);

    // Wire.requestFrom(reg, 1); //Read one byte from status register
    if (Wire.available())
    {
        *value = Wire.read();
        return true;
    }
    else
    {
        *value = 0xFF;
        return false;
    }
}

byte AD5933_EB::readReg(byte reg)
{
    byte val = 0xFF; //How likely is it to read 0xFF as actual data?
    if (receiveByte(reg, &val))
    {
        Serial.print("Read: ");
        Serial.println(val);
        return val;
    }

    else
    {
        Serial.print("Error reading register ");
        Serial.println(reg);
        return val;
    }
}