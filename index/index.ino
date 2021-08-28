  
  #include "DHT_RTC_EXPORT.h";

  int h_activado  ;
  int h_actual ;
  float dataArray [4];
  int intervalo_Activado = 3;//brecha toma de datos EN MINUTOS 
  int ledInfo=4 ;
  
  void setup() {
      
      INICIAR_MODULO ();// inicia el RTC con fecha de compilacion y setea otras opciones
      INICIAR_MODULO_DHT1();
      INICIAR_MODULO_DHT2();
      INICIAR_LECTOR_SD ();
      pinMode(ledInfo, OUTPUT);
      h_activado = GET_MINUTE()+ intervalo_Activado;
  }
  void loop() {
    Toma_datos();
   
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
  digitalWrite(ledInfo, HIGH);  //avisa cuando se escribe un programa 
  delay(1000);                       
  digitalWrite(ledInfo, LOW);
    h_activado = GET_MINUTE()+ intervalo_Activado;// para volver a comparar y hacer el ciclo 
    }
    
  }
