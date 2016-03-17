/*
  Hotboards temp Library - read temp from two sensors

 Read the temperature in celsius degrees from two sensor, the second one should have short circuited
 A0 (on the sensor board) in order to have a different address value (Sensor_6)

 The circuit (tested on Arduino UNO):
 *  VDD   -->  5.0v
 *  SDA   -->  A4 (for both sensors)
 *  SCL   -->  A5 (for both sensors)
 *  GND   -->  GND

 Library and example created by Diego from Hotboards
 This example code is in the public domain.
 */
#include <Arduino.h>
#include <Wire.h>
#include <Hotboards_temp.h>

// instance a sensor with address number 7 (none of the jumpers on the board is short circuted)
// and also 0.5 celsius degrees resolution
Hotboards_temp sensor1( Sensor_7 );
// instance a second sensor but with address 6, this means A0 is short circuited
Hotboards_temp sensor2( Sensor_6 );

void setup( void )
{
    // init serial port
    Serial.begin( 9600 );
    // this module needs the I2C so we need to init the wire library
    Wire.begin( );
    // init sensors, (we assume the sensor are connected)
    sensor1.begin( );
    sensor2.begin( );
}

void loop( void )
{
    // read temperature in celcius degrees from the first sensor
    float temp1 = sensor1.read( );
    // print it on the serial port
    Serial.print( "Sensor 1 : " );
    Serial.print( temp1 );
    Serial.print( " C, " );

    // read temperature in celcius degrees, from the second sensor
    float temp2 = sensor2.read( );
    // print it on the serial port
    Serial.print( "Sensor 2 : " );
    Serial.print( temp2 );
    Serial.println( " C" );

    // take the next values after 2 sec (just to not read too often)
    delay( 2000 );
}
