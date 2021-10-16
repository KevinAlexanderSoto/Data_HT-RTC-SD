  
  #include "DHT_RTC_EXPORT.h";

  int h_activado  ;
  int h_actual ;
  float dataArray [6];
  int intervalo_Activado = 1
  
            
            
            
            ;//brecha toma de datos EN MINUTOS 
  int ledInfo=4 ;
  
  void setup() {
      Serial.begin(9600);
      INICIAR_MODULO ();// inicia el RTC con fecha de compilacion y setea otras opciones
      INICIAR_SENSOR_LUX();
      INICIAS_SENSOR_LUX2();
      INICIAR_MODULO_DHT1();
      INICIAR_MODULO_DHT2();
      INICIAR_LECTOR_SD ();
      pinMode(ledInfo, OUTPUT);
      h_activado = GET_MINUTE()+ intervalo_Activado;
  }
  void loop() {
    Toma_datos();
    Serial.println( GetLux1());
   delay(2000); 
    Serial.println( GetLux2());
   delay(2000); 
  }
  
  void Toma_datos(){
    
    if(h_activado >= 59){// para caso especial de usar minutos, con hora es 24
      h_activado = h_activado - 59;
      }
      
     h_actual = GET_MINUTE();
     
    if(h_actual >= h_activado && h_actual-h_activado < 3){
      
    dataArray [0]= GET_HUMIDITY_SENSOR1();
    dataArray [1]= GET_TEMPERATURE_SENSOR1();
    dataArray [2]= GET_HUMIDITY_SENSOR2();
    dataArray [3]= GET_TEMPERATURE_SENSOR2();
    dataArray [4]= GetLux1();
    dataArray [5]= GetLux2();
    // guardar data en la sd
    WRITE_DATA_ON_SD(dataArray);
    
  digitalWrite(ledInfo, HIGH);  //avisa cuando se escribe un programa 
  delay(3000);                       
  digitalWrite(ledInfo, LOW);
    h_activado = GET_MINUTE()+ intervalo_Activado;// para volver a comparar y hacer el ciclo 
    }
    
  }
