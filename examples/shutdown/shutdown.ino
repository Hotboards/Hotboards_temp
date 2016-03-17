/*
  Hotboards temp Library - shutdown sensor (low power mode)

 Shutdown the sensor after read the tempeture and turn on it right after took the temperature.

 The circuit (tested on Arduino UNO):
 *  VDD   -->  5.0v
 *  SDA   -->  A4
 *  SCL   -->  A5
 *  ALERT -->  7
 *  GND   -->  GND

 Library and example created by Diego from Hotboards
 This example code is in the public domain.
 */
#include <Arduino.h>
#include <Wire.h>
#include <Hotboards_temp.h>

// instance a sensor with address number 7 (none of the jumpers on the board is short circuted)
// and also 0.5 celsius degrees resolution
Hotboards_temp sensor( Sensor_7 );

void setup( void )
{
    // init serial port
    Serial.begin( 9600 );
    // this module needs the I2C so we need to init the wire library
    Wire.begin( );
    // init sensor, (we assume the sensor is connected)
    sensor.begin( );
}

void loop( void )
{
    // turn on sensor
    sensor.shutdown( HT_SENSOR_ON );
    // before read any tempeture we need to wait, this depends on the resolution
    // 30 ms for 0.5
    // 65 ms for 0.25
    // 130 ms for 0.125
    // 250 ms for 0.0625
    delay( 50 );
    // read temperature in celcius degrees
    float val = sensor.read( );
    // print it on the serial port
    Serial.print( "Temp: " );
    Serial.print( val );
    Serial.println( " C" );
    // put sensor in low power mode
    sensor.shutdown( HT_SENSOR_OFF );
    // take the next value after 2 sec (just to not read too often)
    delay( 2000 );
}
