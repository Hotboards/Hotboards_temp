/*
  Hotboards temp Library - Farenheit degrees

 Read the temperaure in celsius and then convert to Farenheit degrees, and also display
 the value on the serial port.

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
    // read temperature in celcius degrees
    float val = sensor.read( );
    // convert to farenheit degrees
    float tempF = sensor.CelsiusToFarenheit( val );
    // print it on the serial port
    Serial.print( "Temp: " );
    Serial.print( tempF );
    Serial.println( " F" );
    // take the next value after 2 sec (just to not read too often)
    delay( 2000 );
}
