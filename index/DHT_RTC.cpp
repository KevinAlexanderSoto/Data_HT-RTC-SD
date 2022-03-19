#include<Arduino.h> // si el archivo es .ino , no hya que colocar esto
#include <Wire.h>    // incluye libreria para interfaz I2C
#include <RTClib.h>   // incluye libreria para el manejo del modulo RTC
#include <SD.h> // para manejo del lector SD 
#include <SPI.h>
#include <DHT.h> // para manejo del los sensore Humedad y Temperatura 
#include <BH1750.h>//para manejo del sendor de lux

RTC_DS1307 rtc;    // crea objeto del tipo RTC_DS1307 , tiene dirrecion 0X68

BH1750 medirlux1;// TIENE direccion 0x23
BH1750 medirlux2;// TIENE direccion 0x5C CONECTARLO A VCC
BH1750 medirlux3;

//puertos de datos sensores lux 
int inLux1 = 1; 
int inLux1-2 = 2;

int inLux2 = 1; 
int inLux2-2 = 2;

int inLux3 = 1; 
int inLux3-2 = 2;

int inLux4 = 1; 
int inLux4-2 = 2;

void INICIAR_MODULO () {
 
 if (! rtc.begin()) {       // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 Serial.flush();
        abort();
 }
 Serial.println("Modulo RTC inicializado!");

 if ( !rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void INICIAR_SENSOR_LUX(){
  Wire.begin(inLux1,inLux1-2);
  medirlux1.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
  
}

void INICIAS_SENSOR_LUX2(){
  Wire2.begin(inLux2,inLux2-2);
  medirlux2.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire2);
  };

  void INICIAS_SENSOR_LUX3(){
  Wire.begin(inLux3,inLux3-2);
  medirlux2.begin();
  };

  void INICIAS_SENSOR_LUX4(){
  Wire.begin(inLux4,inLux4-2);
  medirlux2.begin();
  };

int GET_HOUR() {
 DateTime fecha = rtc.now();      // funcion que devuelve fecha y horario en formato
 return fecha.hour();
 
}

int GET_MINUTE() {
 DateTime fecha = rtc.now();      
 return fecha.minute();

}


////////////////////////DHT11 sensor1///////////////////////////////7


#define DHT1PIN 2     // Digital pin connected to the DHT sensor 1
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

#define DHTTYPE DHT11
 
DHT dht(DHT1PIN, DHTTYPE);

void INICIAR_MODULO_DHT1(){
    
    dht.begin();
    Serial.println(F("DHT11 sensor1 TEST"));

}

float GET_HUMIDITY_SENSOR1(){
    return dht.readHumidity();
}

float GET_TEMPERATURE_SENSOR1(){
    return dht.readTemperature();
}
////////////////////////DHT11 sensor2//////////////////////////////7

#define DHT2PIN 3     // Digital pin connected to the DHT sensor2

#define DHTTYPE DHT11
 
DHT dht2(DHT2PIN, DHTTYPE);
void INICIAR_MODULO_DHT2(){
    
    dht2.begin();
    Serial.println(F("DHT11 sensor2 TEST"));

}

float GET_HUMIDITY_SENSOR2(){
    return dht2.readHumidity();
}

float GET_TEMPERATURE_SENSOR2(){
    return dht2.readTemperature();
}
////////////////////////DHT11 sensor3//////////////////////////////7

#define DHT3PIN 5    // Digital pin connected to the DHT sensor3

#define DHTTYPE DHT11
 
DHT dht3(DHT3PIN, DHTTYPE);
void INICIAR_MODULO_DHT3(){
    
    dht3.begin();
    Serial.println(F("DHT11 sensor3 TEST"));

}

float GET_HUMIDITY_SENSOR3(){
    return dht3.readHumidity();
}

float GET_TEMPERATURE_SENSOR3(){
    return dht3.readTemperature();
}
////////////////////////LECTURA LUX////////////////////////////////////
int GetLux1(){
  return medirlux1.readLightLevel();
  
  };

int GetLux2(){
  return medirlux2.readLightLevel();
  
  };
/////////////////////////ESCRITURA SD ///////////////////////////////////////////
File dataFile;

void INICIAR_LECTOR_SD ()
{

  Serial.print(F("Iniciando SD ..."));
  if (!SD.begin(10))
  {
    Serial.println(F("Error al iniciar SD"));
    return;
  }
  Serial.println(F("SD Iniciado correctamente"));

}

void WRITE_DATA_ON_SD(float data[4] )
{
  
    // para manejo del error (NaN) en la medicion 
  for (size_t i = 0; i < 4; i++)
  {
    if (isnan(data[i]))
    {
      data[i] = 00.00; 
    }
    
  }
  
  // Abrir archivo y escribir valor
  dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile ) { 
     DateTime j = rtc.now();
     
      ///////////data sensor 1///////////////////7
        //HUMIDITY SENSOR1:
        dataFile.print(data[0]  );
        dataFile.print("   ");
        //TEMPERATURA SENSOR1:
        dataFile.print(data[1] );
        dataFile.print("   ");
        //LUX 1
        dataFile.print(data[4] );
        dataFile.print("   ");
        
        ///////////data sensor 2///////////////////7
        //HUMIDITY SENSOR2:
        dataFile.print(data[2] );
        dataFile.print("   ");
        //TEMPERATURA SENSOR2:
        dataFile.print(data[3] );
        dataFile.print("   ");
        //LUX 2
        dataFile.print(data[5] );
        dataFile.print("   ");        
        
       
   //TODO :  AGREGAR FECHA  
        dataFile.print(j.day());
        dataFile.print("/");
        dataFile.print(j.month());
        dataFile.print("/");
        dataFile.print(j.year());
        dataFile.print("   ");
        dataFile.print(j.hour()) ;
        dataFile.print(":") ;
        dataFile.print(j.minute()) ;  
        dataFile.println(" ");       
        dataFile.close();
  
  } 
  else {
    //Serial.println("Error al abrir el archivo");

    
  }
  
        
  delay(500);
}
