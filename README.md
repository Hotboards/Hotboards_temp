Hotboards_temp
================


Super cool librería de propósito general para leer y controlar el sensor de temperatura ambiental MCP9808 con interfaz I2C. La librería permite leer la temperatura actual, establecer alarmas, cambiar la resolución, apagar y encender el sensor, además cuenta con un par de funciones auxiliares para convertir grados Celsius a Fahrenheit

Descarga la librería en formato  [**zip**](https://github.com/Hotboards/Hotboards_temp/archive/master.zip), renombra el archivo ( _solo quita el **-master**_ ) e importala a tu Arduino IDE como dice [aqui](http://developer.mbed.org/cookbook/Working-with-Libraries).



API

---


**Hotboards_temp( uint8_t address, uint8_t resolution = _0p5C )**

Constructor para el sensor de temperatura. El primer parámetro es la dirección que tendrá el sensor, esta dirección se establece conforme a los valores de los jumpers A0, A1 y A2 en la tarjeta, el valo9r por default es 7. 
El segundo parámetro es la resolución por default que tendrá el sensor (se debe usar los valores: _0p5C, _0p25C, _0p125C and _0p0625C), el valor por default es _0p5C (_0.5C_)

```cpp
// Creamos un sensor con dirección 7 y resolución de 0.5 C
Hotboards_temp sensor( Sensor_7 );

// Creamos un sensor con direccion 5 y resolucion de 0.125 C
Hotboards_temp sensor2( Sensor_5, _0p125C );
```


**bool begin( void )**

Detecta si el sensor está conectado leyendo su ID interno, además establece resolución por default, limpia alarmas y enciende en caso que este en estado de shutdown

```cpp
// inicializamos el sensor y ademas detectamos si esta conectado
if( sensor.begin( ) == 1 ){
  // sensor conectado, podemos leerlo
}
```

**float read( void )**

Obtiene la temperatura actual del sensor en grados Celsius y con la resolución a la cual fue configurado

```cpp
// inicializamos sensor (asumimos que esta conectado)
sensor.begin( );
// leemos la temperatura
float temp = sensor.read( );
```

**void setAlarms( float lower, float upper )**

Establece nivel de temperaturas inferior y superior, cuando la temperatura alcance o sobrepase alguno de estos márgenes el pin ALERT del sensor cambiara a un valor bajo de manera automática indicado que la temperatura esta en punto de alarma

```cpp
// establecemos alarma inferior (0C) y superior (10.0C)
sensor.setAlarm( 0.0, 10.0 );
// en alguna parte de la funcion loop
// :
// asumimos que el pin 5 (arduino) esta conectado a el ALERT pin (sensor)
if( digitalRead(5) == 0 ){
  // temperatura por debajo o arriba de los limites
}
```

**void disableAlarms( void )**

Deshabilita las alarmas, el pin ALERT ya no cambiara su estado cuando la temperatura sobrepase los límites establecidos

```cpp
// establecemos alarmas
sensor.setAlarm( 0.0, 10.0 );
// :
// tiempo despues, las desabilitamos
sensor.disableAlarms( );
```

**void shutdown( bool state )**

Manda y/o quita del estado de bajo consumo el sensor. Una vez que el sensor salga de un estado de low power se debe esperar cierto tiempo a que se obtenga la primera lectura valida, esto depende de la resolución. 30ms para 0.5C, 60ms para 0.25C, 130ms para 0.125C y 250ms para 0.0625C.

```cpp
// ponemos el sensor en modo low power
sensor.shutdown( HT_SENSOR_OFF );
// quitamos el sensor del estado de low power
sensor.shutdown( HT_SENSOR_ON );
```

**void setResolution( uint8_t resolution )**

Cambia la resolución actual. Existen solo 4 valores de resolución: 0.0625, 0.125, 0.25 and 0.5, estos valores se establecen usando las definiciones _0p5C, _0p25C, _0p125C and _0p0625C

```cpp
// cambiamos la resolucion del sensor
sensor.setResolution( _0p0625C );
// leemos la temperatura con la nueva resolucion
float temp = sensor.read( );
```

**float CelsiusToFarenheit( float celsius )**

Convierte grados Celsius a grados Fahrenheit

```cpp
// leemos temperatura en grados celsius
float tempC = sensor.read( );
// convertimos a farenheit
float tempF = sensor.CelsiusToFarenheit( tempC );
```

**float FarenheitToCelsius( float farenheit )**

Convierte grados Fahrenheit a grados Celsius

```cpp
// convertimos 98.5 F a grados Celsius
float tempC = sensor.FarenheitToCelsius( 98.5 );
```

Ejemplos
--------

- [Establecemos alarmas superior e inferior](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/alarms/alarms.ino)
- [Convertimos temperatura a grados Farenheit](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/farenheit/farenheit.ino)
- [Simple lecura de uns sensor](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/read/read.ino)
- [Cmabiando la resolucion del sensor](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/resolution/resolution.ino)
- [Leyendo dos sensores](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/sensors/sensors.ino)
- [Sensor en modo Low power](https://github.com/Hotboards/Hotboards_temp/tree/master/examples/shutdown/shutdown.ino)
