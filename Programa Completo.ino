#include <Wire.h>
#include <Adafruit_ADS1015.h>

#include <ESP8266WiFi.h> //librería para mandar los datos por wifi

//Descomentar para ver mensajes de debug y del http
//#define PRINT_DEBUG_MESSAGES
//#define PRINT_HTTP_RESPONSE

#define REST_SERVER_THINGSPEAK

Adafruit_ADS1115 ads1115(0x48);

#include "sensor.h" //Incluimos nuestra librería de sensores

//Declarar el nombre y contraseña de la wifi
const char WiFiSSID[] = "MYA-L41";
const char WiFiPSK[] = "ireneirene";

const int LED_PIN = 5; // Thing's onboard, green LED

const char Server_Host[] = "api.thingspeak.com";
const int Server_HttpPort = 80;

const char Rest_Host[] = "api.thingspeak.com";
String MyWriteAPIKey = "N0DKXELDHAT2752T"; //Poner el API Key del canal de ThingSpeak
WiFiClient client;

#define NUM_FIELDS_TO_SEND 4 //Número de datos que vamos a enviar

//Declaro todas las constantes para los cálculos
int AirValue = 30000 ;
int WaterValue = 16000;
int Nosal = 1500;
int Sisal = 26160;

//Función para hacer la conexión por wifi
void connectWiFi() {

  byte ledStatus = LOW;

  //Solo lo muestra si está descomentado el mensaje de la linea 7
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
#endif

  WiFi.begin(WiFiSSID, WiFiPSK);

  while (WiFi.status() != WL_CONNECTED) {

    // Blink the LED
    digitalWrite(LED_PIN, ledStatus); // Write LED high/low
    ledStatus = (ledStatus == HIGH) ? LOW : HIGH;
#ifdef PRINT_DEBUG_MESSAGES
    Serial.println(".");
#endif
    delay(500);

  }

#ifdef PRINT_DEBUG_MESSAGES
  Serial.println( "WiFi Connected" );
  Serial.println(WiFi.localIP()); // Print the IP address
#endif

}

//Esta función es necesaria para mandar los datos al ThingSèak
void HTTPGet(String fieldData[], int numFields) {

  // Esta funcion construye el string de datos a enviar a ThingSpeak mediante el metodo HTTP GET
  // La funcion envia "numFields" datos, del array fieldData.
  // Asegurate de ajustar "numFields" al número adecuado de datos que necesitas enviar y activa los campos en tu canal web

  if (client.connect( Server_Host , Server_HttpPort )) {
#ifdef REST_SERVER_THINGSPEAK
    String PostData = "GET https://api.thingspeak.com/update?api_key=";
    PostData = PostData + MyWriteAPIKey ;
#else
    String PostData = "GET http://dweet.io/dweet/for/";
    PostData = PostData + MyWriteAPIKey + "?" ;
#endif

    for ( int field = 1; field < (numFields + 1); field++ ) {

      PostData += "&field" + String( field ) + "=" + fieldData[ field ];

    }


#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( "Connecting to Server for update..." );
#endif

    client.print(PostData);
    client.println(" HTTP/1.1");
    client.println("Host: " + String(Rest_Host));
    client.println("Connection: close");
    client.println();

#ifdef PRINT_DEBUG_MESSAGES
    Serial.println( PostData );
    Serial.println();

    //Para ver la respuesta del servidor
#ifdef PRINT_HTTP_RESPONSE
    delay(500);
    Serial.println();

    while (client.available()) {

      String line = client.readStringUntil('\r');
      Serial.print(line);

    }
    Serial.println();
    Serial.println();

#endif
#endif
  }
}

void setup() {

  //Inicializamos el arduino

  Serial.begin(9600);

  connectWiFi();

  ads1115.begin(); //Inicia el sensor
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

  Serial.println("----------------------------");
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

  //Con este switch dependiendo del valor del sensor de luz pondrá un mensaje u otro
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

  connectWiFi();
  //HTTPGet();
  String data[ NUM_FIELDS_TO_SEND + 1];  // Podemos enviar hasta 8 datos


  data[ 1 ] = String( h ); //Escribimos el dato 1.
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Humedad = " );
  Serial.println( data[ 1 ] );
#endif

  data[ 2 ] = String( s ); //Escribimos el dato 2.
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Salinidad = " );
  Serial.println( data[ 2 ] );
#endif

  data[ 3 ] = String( t ); //Escribimos el dato 3.
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Temperatura = " );
  Serial.println( data[ 3 ] );
#endif

  data[ 4 ] = String( i ); //Escribimos el dato 4.
#ifdef PRINT_DEBUG_MESSAGES
  Serial.print( "Luminosidad = " );
  Serial.println( data[ 4 ] );
#endif


  //Selecciona si quieres enviar con GET o con POST
  //HTTPPost( data, NUM_FIELDS_TO_SEND );
  HTTPGet( data, NUM_FIELDS_TO_SEND );

  //Y pongo un deepsleep de 10 segundos

  ESP.deepSleep(10 * 1000000);

}
