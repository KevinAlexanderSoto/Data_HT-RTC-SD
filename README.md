Introducción 
=============
programa para arduino , lee temperatura y humedad en tiempo real , los datos los guarda en una SD. para el proyecto se necesitan 3 DHT11, 1 RTC , 1 modulo SD , 1 ArduinoMega, 4 sensores GY30 DE LUX



pinado
-------
par la SD (Por revisar)

* VCC of module to 5V of Arduino.
* GND of module to GND of Arduino.
* CS to digital pin 10 of Uno.
* MOSI to digital pin 11 of Uno.
* MISO to digital pin 12.
* SCK to digital pin 13.

sensor TH 1 
 * data a pin 53
 * vcc 5v 

 sensor TH 2

 * data a pin 51
 * vcc 5v
 
 sensor TH 3

 * data a pin 48
 * vcc 5v
---------------------------------------------------------------------
sensor lux 1
* 46
* 47
* vcc 5v

sensor lux 2
* 44
* 45
* vcc 5v

sensor lux 3
* 42
* 43
* vcc 5v

sensor lux 4
* 40
* 41
* vcc 5v

 Led de aviso 

 * pin 4 

Anexo 
--------

* sensor de humdad y temperatura tiene tres pines, vcc,GND, y datos
* sensor de lux tiene 4 pines: GND y VCC , SDA y scl para comunicación(data), ADO para ponerle direccion al sensor, el sensor funciona por comunicacion serial(creo),estos utilizan comunicación I2C,se va a hacer un puente con otro Arduino que va a cambiar la dirrecion IC2 de 2 sensores y lo va a mandar al ardino principal, los otros dos se conectan directamente al Arduino principal. Esto debido a que los sensores de lux solo tienen 2 dirreciones  