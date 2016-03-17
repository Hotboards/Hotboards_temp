/*
  Hotboards_temp.h - Driver to read and control a serial (i2c) temperature sensor, The Microchip
  MCP9808 is the digital sensor to control, can be read it, set its resolution, shutdown and also
  set alarms.
  Hotboards eeprom board (http://hotboards.org)
  Created by Diego Perez, March 19, 2016.
  Released into the public domain.
*/
#ifndef Hotboards_Temp_h
#define Hotboards_Temp_h

#include <Arduino.h>

#define HT_SENSOR_OFF   0
#define HT_SENSOR_ON    1

typedef enum
{
    Sensor_0 = 0,
    Sensor_1,
    Sensor_2,
    Sensor_3,
    Sensor_4,
    Sensor_5,
    Sensor_6,
    Sensor_7
} _eSensors;

typedef enum
{
    _0p5C = 0,
    _0p25C,
    _0p125C,
    _0p0625C
} _eResolution;

/** Hotboards_temp class.
 *  Used to read and config Microchip MCP9808 i2c temp sensor
 *
 * Example:
 * @code
 * #include <Hotboards_temp.h>
 *
 * Hotboards_temp sensor( Sensor_7 );
 *
 * int setup( void )
 * {
 *   Wire.begin( );
 *   sensor.begin( );
 *   float val = sensor.read( );
 *   print( val );
 * }
 * @endcode
 */
class Hotboards_temp
{
    public :
        /** Create Hotboards_temp instance
          * @param address sensor address (A0,A1 and A2 values)
          * @param resolution default temperature resoluion (use values from _eResolution enumeration)
          *
          * Example:
          * @code
          *   // instance temp sensor with address 7 and 0.5 resolution (default)
          *   Hotboards_temp sensor( Sensor_7 );
          * @endcode
          */
        Hotboards_temp( uint8_t address, uint8_t resolution = _0p5C );

        /** Detect if the sensor is conected and also set default resolution
          * @return '1' if a sensor is connected
          *
          * Example:
          * @code
          *   // init sensor and also check if is conected
          *   if( sensor.begin( ) == 1 ){
          *     // sensor is detected, do something
          *   }
          * @endcode
          */
        bool begin( void );

        /** Get temperature from sensor in Celsius degrees
          * @return The current temperature
          *
          * Example:
          * @code
          *   // init temp sensor (assume sensor is connected)
          *   sensor.begin( );
          *   // read the current temperaure
          *   float temp = sensor.read( );
          * @endcode
          */
        float read( void );

        /** Set Tlower and Tupper values and also active ALERT output pin
          * @param lower lower temperaure value to set ALERT pin
          * @param upper upper temperaure value to set ALERT pin
          *
          * Example:
          * @code
          *   // set lower nd upper alarm (on setup function)
          *   sensor.setAlarm( 0.0, 10.0 );
          *   // somewhere else on loop function
          *   // assume we conected pin 5 (arduino) to ALERT pin (sensor)
          *   if( readDigital(5) == 0 ){
          *     // temp value under lower valur or upper value
          *   }
          * @endcode
          */
        void setAlarms( float lower, float upper );

        /** Disable alarma activation, the function does not clear the previus
          * alarm values, just disable the ALERT signal
          *
          * Example:
          * @code
          *   // set lower nd upper alarm (on setup function)
          *   sensor.setAlarm( 0.0, 10.0 );
          *   // disable alarm, ALERt signal is disable
          *   sensor.disableAlarms( );
          * @endcode
          */
        void disableAlarms( void );

        /** Turn Off/On sensor (low power), after turn it on again, is necesary wait
          * from 30ms to 250ms (depends on resoluion) to read a valid temperature
          * @param state shutdown (HT_SENSOR_OFF) or turn on (HT_SENSOR_ON)
          *
          * Example:
          * @code
          *   // lets assume sensor is initialized, so shutdown
          *   sensor.shutdown( HT_SENSOR_OFF );
          *   // the we can turn it on
          *   sensor.shutdown( HT_SENSOR_ON );
          * @endcode
          */
        void shutdown( bool state );

        /** set a new resolution, possible values are 0.0625, 0.125, 0.25 and 0.5
          * @param resolution use values from _eResolution enumeration (_0p5C, _0p25C, _0p125C and _0p0625C)
          *
          * Example:
          * @code
          *   // lets assume sensor is initialized
          *   sensor.setResolution( _0p0625C );
          *   // read temperature with the new resolution
          *   float temp = sensor.read( );
          * @endcode
          */
        void setResolution( uint8_t resolution );

        /** Function to convert Celsius to Farenheit degrees
          * @param celsius temperature in celsius degrees
          *
          * Example:
          * @code
          *   // read temperature in celsius degrees
          *   float tempC = sensor.read( );
          *   // convert to farenheit
          *   float tempF = sensor.CelsiusToFarenheit( tempC );
          * @endcode
          */
        float CelsiusToFarenheit( float celsius );

        /** Function to convert Farenheit to Celsius degrees
          * @param farenheit temperature in farenheit degrees
          *
          * Example:
          * @code
          *   // convert to celsius a previus farenheit temperature
          *   float tempC = sensor.FarenheitToCelsius( 98.5 );
          * @endcode
          */
        float FarenheitToCelsius( float farenheit );

    private :
        int readReg( uint8_t reg );
        void writeReg( uint8_t reg, int val );
        void writeAlarm( uint16_t reg, float temp );
        uint8_t _address;
        uint8_t _resolution;
};

#endif
