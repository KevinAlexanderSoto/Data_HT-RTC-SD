void INICIAR_MODULO ();
int GET_HOUR();
int GET_MINUTE();

/////////////DHT11 sensor/////////////

void INICIAR_MODULO_DHT1();

float GET_HUMIDITY_SENSOR1();

float GET_TEMPERATURE_SENSOR1();

/////////////DHT11 sensor2/////////////
void INICIAR_MODULO_DHT2();

float GET_HUMIDITY_SENSOR2();

float GET_TEMPERATURE_SENSOR2();

//////////////////////// ESCRITURA SD ///////////////////////////////////////////

void INICIAR_LECTOR_SD ();
void WRITE_DATA_ON_SD(float data[4]);
