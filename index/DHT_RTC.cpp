#include<Arduino.h> // si el archivo es .ino , no hya que colocar esto
#include <Wire.h>    // incluye libreria para interfaz I2C
#include <RTClib.h>   // incluye libreria para el manejo del modulo RTC
#include <SD.h> // para manejo del lector SD 
#include <SPI.h>

RTC_DS1307 rtc;    // crea objeto del tipo RTC_DS1307

void INICIAR_MODULO () {
 
 if (! rtc.begin()) {       // si falla la inicializacion del modulo
 Serial.println("Modulo RTC no encontrado !");  // muestra mensaje de error
 Serial.flush();
        abort();
 }
 Serial.println("Modulo RTC inicializado!");
 if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }      
}

int GET_HOUR() {
 DateTime fecha = rtc.now();      // funcion que devuelve fecha y horario en formato
 return fecha.hour();
 
}

int GET_MINUTE() {
 DateTime fecha = rtc.now();      
 return fecha.minute();

}


////////////////////////DHT11 sensor1///////////////////////////////7

#include <DHT.h>

#define DHT1PIN 2     // Digital pin connected to the DHT sensor
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

#include <DHT.h>

#define DHT2PIN 3     // Digital pin connected to the DHT sensor

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

//////////////////////// ESCRITURA SD ///////////////////////////////////////////
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
  // Abrir archivo y escribir valor
  dataFile = SD.open("data.txt", FILE_WRITE);
    float nan= sqrt (-1); 
    
  if (dataFile ) { 
     DateTime j = rtc.now();
 
        //HUMIDITY SENSOR1:
        dataFile.print((data[0] == nan) ? 00.00 :data[0]  );
        dataFile.print("    ");
        //TEMPERATURA SENSOR1:
        dataFile.print((data[1] == nan) ? 00.00 :data[1] );
        dataFile.print("    ");
        
        ///////////data sensor 2///////////////////7
        //HUMIDITY SENSOR2:
        dataFile.print((data[2] == nan) ? 00.00 :data[2] );
        dataFile.print("    ");
        //TEMPERATURA SENSOR2:
        dataFile.print((data[3] == nan) ? 00.00 :data[3] );
        dataFile.print("    ");
        
       
   //TODO :  AGREGAR FECHA  
        dataFile.print(j.day());
        dataFile.print("/");
        dataFile.print(j.month());
        dataFile.print("/");
        dataFile.print(j.year());
        dataFile.print("    ");
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
