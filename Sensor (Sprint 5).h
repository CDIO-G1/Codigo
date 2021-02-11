//Esto es la librería con todos los sensores

//La primera función es la del sensor de humedad
double humedad(int canalhum, int AirValue, int WaterValue) {

  //Declaro las variables, pido una lectura del adc en el pin 0
  int16_t adc0;
  double humedad;
  adc0 = ads1115.readADC_SingleEnded(canalhum);


  //Hago el cálculo con una formula para sacar el porcentaje de la humedad
  humedad = 100 * AirValue / (AirValue - WaterValue) - adc0 * 100 / (AirValue - WaterValue);


  //Muestro por pantalla los datos que lee el adc para hacer la calibración
  //Descomentar para ver los datos de calibración
  /*Serial.println("----------------------------");
  Serial.println("Datos de calibración:");
  Serial.print("Humedad: ");
  Serial.println(adc0);*/

  if (humedad > 100) {

    humedad = 100;

  }


  if (humedad < 0) {

    humedad = 0;

  }

  return humedad;

}

//La segunda función es la del sensor de salinidad
double salinidad(int canalsal, int Nosal, int Sisal) {

  int salinity_power_pin = 5;
  pinMode(salinity_power_pin, OUTPUT);

  //Declaro las variables, pido una lectura del adc en el pin 1
  int adc1;
  double sal;

  digitalWrite( salinity_power_pin, HIGH );

  adc1 = ads1115.readADC_SingleEnded(canalsal);

  //Hago el cálculo con una formula para sacar el porcentaje de la salinidad
  sal = 100 * Nosal / (Nosal - Sisal) - adc1 * 100 / (Nosal - Sisal);

  digitalWrite( salinity_power_pin, LOW );

  //Muestro por pantalla los datos que lee el adc para hacer la calibración
  //Descomentar para ver los datos de calibración
  Serial.print("Salinidad: ");
  Serial.println(adc1);


  if (sal > 100) {

    sal = 100;

  }


  if (sal < 0) {

    sal = 0;

  }
  
  return sal;

}


//La tercera función es la del sensor de temperatura
double temperatura(int canaltemp) {

  //Declaro las variables, pido una lectura del adc en el pin 2
  int16_t adc2;
  double temp;
  adc2 = ads1115.readADC_SingleEnded(canaltemp);

  //Hago el cálculo con una formula para sacar la temperatura en grados centigrados
  temp = ((4.096 * adc2) - (((pow(2, 15) - 1) * 0.79))) / ((pow(2, 15) - 1) * 37 * pow(10, -3));


  //Muestro por pantalla los datos que lee el adc para hacer la calibración
  //Descomentar para ver los datos de calibración
  /* Serial.print("El adc del sensor de temperatura esta leyendo: ");
  Serial.println(adc2); */

  return temp;

}

double iluminacion(int canalilum) {

  int16_t adc3;
  double ilum;
  adc3 = ads1115.readADC_SingleEnded(3);

  //Descomentar para ver los datos de calibración
  /* Serial.print("El adc del sensor de iluminacion esta leyendo: ");
  Serial.println(adc3);
  Serial.println("----------------------------"); */


  if (adc3 < 50) {

    ilum = 1;

  }
  if (adc3 > 50 && adc3 < 200) {

    ilum = 2;

  }
  if (adc3 > 200 && adc3 < 350) {

    ilum = 3;

  }
  if (adc3 > 350) {

    ilum = 4;

  }

  return ilum;
}
