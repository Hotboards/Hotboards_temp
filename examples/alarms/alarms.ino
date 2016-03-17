/*
  Hotboards temp Library - setting alarms

 Set upper and lower alarms and trhoug pin 7 monitor the ALERT signal, turn on a led when the
 temperature is below or above the alarm values.

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
    // pin 7 will be sense the ALERT signal
    pinMode( 7, INPUT );
    // on pin 13 is the led that will be turn on when the alarm is set
    pinMode( 13, OUTPUT );
    // set lower alarm to 0.0 C and upper alarm to 26.0 C. We assume the eviromental temp is around
    // 23-24 degrees
    sensor.setAlarms( 0.0, 26.0 );
}

void loop( void )
{
    // sense the ALERT signal and turn on/off the led on your Arduino board
    if( digitalRead( 7 ) == 0 ) digitalWrite( 13, HIGH ); // temp outside the limits, alarm!!
    else digitalWrite( 13, LOW );
    // read temperature in celcius degrees
    float val = sensor.read( );
    // print it on the serial port
    Serial.print( "Temp: " );
    Serial.print( val );
    Serial.println( " C" );
    // take the next value after 2 sec (just to not read too often)
    delay( 2000 );
}
