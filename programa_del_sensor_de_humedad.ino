#include <Wire.h>//librerias
#include <Adafruit_ADS1015.h>//librerias

Adafruit_ADS1115 ads1115(0x48); // construct an ads1115 at address 0x48
const int AirValue = 30448;  // Medimos valor en seco
const int WaterValue = 17513;  // Medimos valor en agua
void setup() {
  
 
  Serial.begin(9600); //velocidad a la que trabaja nuestro monitor serie
  Serial.println("Inicializando...");
  ads1115.begin(); //Initialize ads1115
  Serial.println("Ajustando la ganancia...");
  ads1115.setGain(GAIN_ONE);// se seleciona la ganacia one que es la de 4.096V
  
  Serial.println("Tomando medidas del canal AIN0");
  
  Serial.println("Rango del ADC: +/- 4.096V (1 bit=2mV)"); //valores con los que trabaja nuestra placa
}

void loop() {
  
  int16_t adc0;// entrada definida (0) para comunicarse con nuestra placa
  int16_t humedad;
  adc0 = ads1115.readADC_SingleEnded(0);// entrada selecionada la 0 comunicanose con nuestra placa
  humedad = 100*AirValue/(AirValue-WaterValue)-adc0*100/(AirValue-WaterValue);//formula para sacar porcentaje,(algoritmo)

  Serial.print("Humedad: ");
  Serial.println(adc0);// entrada selecionada la 0 comunicanose con nuestra placa
  Serial.print("Cantidad de Humedad(%): ");//Esto es el porcentaje  que se muestra en el monitor serie 
  Serial.print(humedad);//este es el resultado de el algoritmo 
  Serial.println("%");

  delay(5000);// tiempo de espera entre medida y medida en ms

}
