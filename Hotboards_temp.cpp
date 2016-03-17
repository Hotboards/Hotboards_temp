/*
  Hotboards_temp.cpp - Driver to read and control a serial (i2c) temperature sensor, The Microchip
  MCP9808 is the digital sensor to control, can be read it, set its resolution, shutdown and also
  set alarms.
  Hotboards eeprom board (http://hotboards.org)
  Created by Diego Perez, March 19, 2016.
  Released into the public domain.
*/
#include "Hotboards_temp.h"
#include <Wire.h>

#define SENSOR_ADDR       (uint8_t)(0x3E>>1)
#define REG_CONFIG        (uint8_t)0x01
#define REG_ALERT_UPPER   (uint8_t)0x02
#define REG_ALERT_LOWER   (uint8_t)0x03
#define REG_CRITICAL_TEMP (uint8_t)0x04
#define REG_TEMPERATURE   (uint8_t)0x05
#define REG_MANU_ID       (uint8_t)0x06
#define REG_DEVICE_ID     (uint8_t)0x07
#define REG_RESOLUTION    (uint8_t)0x08

Hotboards_temp::Hotboards_temp( uint8_t address, uint8_t resolution )
{
    _address = address | 0x18;
    _resolution = resolution;
}

bool Hotboards_temp::begin( void )
{
    bool flag = 0; // lets assume device is not here
    uint16_t val = readReg( REG_MANU_ID );
    if( val == 0x0054 )
    {
        // device is presence, default set resolution
        writeReg( REG_RESOLUTION, _resolution );
        // clear configuration register (alarms included)
        writeReg( REG_CONFIG, 0x00 );
        flag = 1;
    }
    return flag;
}

float Hotboards_temp::read( void )
{
    uint16_t val;
    float temp;

    // read the Ta register
    val = readReg( REG_TEMPERATURE );

    // small algorithm to calculate tmeperature in Celcius
    // borrowed from https://github.com/adafruit/Adafruit_MCP9808_Library/blob/master/Adafruit_MCP9808.cpp
    temp = val & 0x0FFF;
    temp /=  16.0;
    // check if a negative temperature
    if( val & 0x1000 ) temp -= 256;

    return temp;
}

void Hotboards_temp::setAlarms( float lower, float upper )
{
    // set alarm values
    writeAlarm( REG_ALERT_UPPER, upper );
    writeAlarm( REG_CRITICAL_TEMP, upper );
    writeAlarm( REG_ALERT_LOWER, lower );

    uint16_t val = readReg( REG_CONFIG );
    // set alarm only in comparator mode with LAERT pin set to LOW
    writeReg( REG_CONFIG, val | 0x0008 );
}

void Hotboards_temp::disableAlarms( void )
{
    uint16_t val = readReg( REG_CONFIG );
    // just clear the Alert Output Control bit
    writeReg( REG_CONFIG, val ^ 0x0008 );
}

void Hotboards_temp::shutdown( bool state )
{
    uint16_t val = readReg( REG_CONFIG );

    if( state == HT_SENSOR_OFF )
    {// shutdown, curretn under 1uA, and disable convertions
       writeReg( REG_CONFIG, val | 0x0100 );
    }
    else
    {// power on
       writeReg( REG_CONFIG, val ^ 0x0100 );
    }
}

void Hotboards_temp::setResolution( uint8_t resolution )
{
    resolution &= 0x03;
    writeReg( REG_RESOLUTION, resolution << 8 );
}

float Hotboards_temp::CelsiusToFarenheit( float celsius )
{
    return celsius * 9.0 / 5.0 + 32;
}

float Hotboards_temp::FarenheitToCelsius( float farenheit )
{
    return ( farenheit - 32 ) * 5.0 / 9.0;
}

int Hotboards_temp::readReg( uint8_t reg )
{
    int val;

    Wire.beginTransmission( _address );
    Wire.write( reg );
    Wire.endTransmission( );

    Wire.requestFrom( _address, (uint8_t)2 );
    val  = Wire.read( ) << 8;
    val |= Wire.read( );

    return val;
}

void Hotboards_temp::writeReg( uint8_t reg, int val )
{
    Wire.beginTransmission( _address );
    Wire.write( reg );
    Wire.write( val >> 8 );
    Wire.write( val & 0x00FF );
    Wire.endTransmission( );
}

void Hotboards_temp::writeAlarm( uint16_t reg, float temp )
{
    uint16_t val = 0x0000;
    // check if negative temp
    if( temp < 0 )
    {
        temp += 256.0;
        // set sign bit
        val = 0x1000;
    }
    // convert to binary
    val |= (uint16_t)( temp *= 16.0 );
    writeReg( reg, val );
}
