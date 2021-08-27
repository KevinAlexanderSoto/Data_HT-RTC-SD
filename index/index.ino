  
  #include "DHT_RTC_EXPORT.h";

  int h_activado  ;
  int h_actual ;
  float dataArray [3];
  int intervalo_Activado = 3;//brecha toma de datos EN MINUTOS 
  
  void setup() {
      Serial.begin(9600); 
      Serial.println("serial init");// inicializa comunicacion serie a 9600 bps
      //INICIAR_MODULO ();// inicia el RTC con fecha de compilacion y setea otras opciones
      INICIAR_MODULO_DHT1();
     /*  INICIAR_MODULO_DHT2(); */
      INICIAR_LECTOR_SD ();
      //h_activado = GET_MINUTE()+ intervalo_Activado;
  }
  void loop() {
    //Toma_datos();
    /* Serial.print("MINUTO:");
    Serial.println(GET_MINUTE());*/
    delay(100);
 Serial.println( "...........................");
  Serial.print("HUMIDITY SENSOR1:");
    Serial.println( GET_HUMIDITY_SENSOR1());
   
    Serial.print("TEMPERATURA_DHT11_SENSOR1:"); 
   Serial.println( GET_TEMPERATURE_SENSOR1());
   /*delay(100);
Serial.println( "...........................");
  Serial.print("HUMIDITY SENSOR2:");
    Serial.println( GET_HUMIDITY_SENSOR2());
   
    Serial.print("TEMPERATURA_DHT11_SENSOR2:");
    Serial.println( GET_TEMPERATURE_SENSOR2()); */
    dataArray [0]= GET_HUMIDITY_SENSOR1();
    dataArray [1]= GET_TEMPERATURE_SENSOR1();
    dataArray [2]= 0;
    dataArray [3]= 0;
    WRITE_DATA_ON_SD(dataArray);
    delay(5000);
  }
  
  void Toma_datos(){
    
    if(h_activado > 60){// para caso especial de usar minutos, con hora es 24
      h_activado = h_activado - 60;
      }
      
     h_actual = GET_MINUTE();
     
    if(h_actual >= h_activado){
      
    //TODO : leer temperatura , humedad
    dataArray [0]= GET_HUMIDITY_SENSOR1();
    dataArray [1]= GET_TEMPERATURE_SENSOR1();
    dataArray [2]= GET_HUMIDITY_SENSOR2();
    dataArray [3]= GET_TEMPERATURE_SENSOR2();

    //TODO : guardar data en la sd
    WRITE_DATA_ON_SD(dataArray);
        
    h_activado = GET_MINUTE()+ intervalo_Activado;// para volver a comparar y hacer el ciclo 
    }
    
  }
