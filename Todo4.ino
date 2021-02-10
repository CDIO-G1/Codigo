#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48);

//Incluimos nuestra librería de sensores
#include "sensor.h"


//Declaro todas las constantes para los cálculos
int AirValue = 30000 ;
int WaterValue = 16000;
int Nosal = 10;
int Sisal = 26160;
char calibracion;

void setup() {

  //Inicializamos el arduino

  Serial.begin(9600);

  ads1115.begin();
  ads1115.setGain(GAIN_ONE);

}

void loop()
{

  //Llamo a las funciones de la librería y les paso los pines y las constantes pertinentes para los cálculos

  int h = humedad(0, AirValue, WaterValue);
  int s = salinidad(1, Nosal, Sisal);
  int t = temperatura(2);
  int i = iluminacion(3);


  //Los mensajes que muestra el monitor serie

  Serial.print("Porcentaje de humedad (%): ");
  Serial.print(h);
  Serial.println("%");
  Serial.println("----------------------------");

  Serial.print("Porcentaje de salinidad (%):");
  Serial.print(s);
  Serial.println("%");
  Serial.println("----------------------------");

  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("º");
  Serial.println("----------------------------");

  Serial.print("Luminosidad: ");

  switch (i) {

    case 1:

      Serial.println("Completa oscuridad ");
      Serial.println("----------------------------");
      break;

    case 2:

      Serial.println("Interior de una sala ");
      Serial.println("----------------------------");

      break;

    case 3:

      Serial.println("Nublado ");
      Serial.println("----------------------------");

      break;

    case 4:

      Serial.println("Al sol ");
      Serial.println("----------------------------");

      break;

  }

  Serial.println("----------------------------");
  Serial.println("----------------------------");
  Serial.println("----------------------------");



  //Y pongo un deepsleep de 10 segundos

  ESP.deepSleep(10 * 1000000);

}
