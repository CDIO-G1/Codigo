#include <Wire.h>//librerias
#include <Adafruit_ADS1015.h>//librerias

 
Adafruit_ADS1115 ads1115(0x48); // construct an ads1115 at address 0x48

const int AirValue = 30448;  // Medimos valor en seco
const int WaterValue = 17513;  // Medimos valor en agua
const int LackSaultValue = 19400;// Medimos valor sin sal
const int SalinityValue = 24640;// Medimos valor  de una cucharada sal en taza

int salinity_power_pin = 5; 
 


void setup() {
  Serial.begin(9600);//velocidad a la que trabaja nuestro monitor serie
  ads1115.begin(); //Initialize ads1115
  ads1115.setGain(GAIN_ONE);// se seleciona la ganacia one que es la de 4.096V
  
  pinMode(salinity_power_pin, OUTPUT);
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
  Serial.println("-----------------------");
  Serial.println("%");

  delay(1000);// tiempo de espera entre medida y medida en ms

  int adc1;// entrada definida (1) para comunicarse con nuestra placa
  int input_pin = 5;
 
  int16_t sal;
  int salinity_input_pin = 5;

  digitalWrite( salinity_power_pin, HIGH );

  adc1 = ads1115.readADC_SingleEnded(1);// entrada selecionada la 0 comunicanose con nuestra placa
  sal = 100*LackSaultValue/(LackSaultValue-SalinityValue)-adc1*100/(LackSaultValue-SalinityValue);//formula para sacar porcentaje,(algoritmo)
 
  digitalWrite( salinity_power_pin, LOW );

  Serial.print("Salinidad: ");
  Serial.println(adc1);// entrada selecionada la 1 comunicanose con nuestra placa
  Serial.print("Porcentaje de salinidad (%):");//Esto es el porcentaje que se muestra en el monitor serie 
  Serial.print(sal);//este es el resultado de el algoritmo 
  Serial.println("%");
  Serial.println("-----------------------");
  delay(1000);
  
 }
