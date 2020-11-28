
#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1115(0x48); // construct an ads1115 at address 0x48

const int tempmin = -21.35;// el valor mas bajo que pede leer nuestro sensor es de -21.35º
const int tempmax = 89.35;//// el valor mas alto que pede leer nuestro sensor es de 89.35º

  void setup() {
  Serial.begin(9600);//velocidad a la que trabaja nuestro monitor serie

  ads1115.begin();
  ads1115.setGain(GAIN_ONE);
}

void loop() {
  
  int16_t adc2;// entrada definida (2) para comunicarse con nuestra placa
  float temperatura;
  adc2 = ads1115.readADC_SingleEnded(2);
  temperatura = ((4.096*adc2)-(((pow(2,15)-1)*0.79)))/((pow(2,15)-1)*37*pow(10,-3));// este es el algorito para calcular la temperatura


  Serial.print("AIN2: ");
  Serial.println(adc2);
  Serial.print("Temperatura: ");//
  Serial.print(temperatura);//este es el valor que lee nuestro sensor
  Serial.println("º");

  delay(3000);

}
