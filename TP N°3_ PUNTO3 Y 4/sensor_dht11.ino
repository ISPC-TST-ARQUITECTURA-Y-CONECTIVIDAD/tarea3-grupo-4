#include "UbidotsEsp32Mqtt.h"
#include "DHT.h"
/*Definimos que el Pin de Datos del sensor estará conectado al pin 23 del ESP32*/
#define DHTPIN 23           
/*Definimos que el tipo de sensor que estamos utilizando es un DHT11*/
#define DHTTYPE DHT11     // DHT 11
/*Se actualizan algunos parámetros del DHT11 con los puntos definidos anteriormente*/ 
DHT dht(DHTPIN, DHTTYPE);


/*Definimos primero el Token que nos brinda la plataforma Ubidots para hacer la conexión*/
const char *UBIDOTS_TOKEN = "BBFF-26VqLz8bpBwO94vbqHuxOmGSjNiscmHNYTSk9QOLAWwv38uLakDjUly";
/*Definimos SSID y PASSWORD de nuestra red WiFi*/
const char *WIFI_SSID = "Carrizo-Claro";      
const char *WIFI_PASS = "29897426";     
/*Definimos el nombre de nuestro dispositivo, el cual aparecerá en la plataforma Ubidots*/
const char *DEVICE_LABEL = "esp32-edc";
/*Definimos las variables que se medirán y que serán publicadas en la plataforma Ubidots*/
const char *VARIABLE_LABEL_1 = "Termometro"; 
const char *VARIABLE_LABEL_2 = "Humedad";

 
/*Definimos la frecuencia de publicación de 5 segundos*/
const int PUBLISH_FREQUENCY = 5000; 
/*Definimos unas variables extra, que incluye la librería*/
unsigned long timer;
uint8_t analogPin = 34; 
/*Definimos que las variables de la librería UBIDOTS trabajarán con el Token*/
Ubidots ubidots(UBIDOTS_TOKEN);


/*La librería nos da una función de Subscripción para mensajes de regreso desde la plataforma Ubidots hacia nuestro circuito*/
void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


/*Definimos la función Setup() para iniciar nuestro circuito*/
void setup()
{
  /*Iniciamos el terminal Serial a 115200*/
  Serial.begin(115200);     
  /*Imprimimos el siguiente texto para asegurar el encendido del circuito*/
  Serial.println("Medición inciada");
  Serial.println("DHT11 Encendido");
  /*Iniciamos nuestro sensor DHT11*/
  dht.begin();
  /*Incluimos un retardo de 1 segundo*/
  delay(1000);

  /*Ahora, se incluye las funciones de conexión de la Plataforma, como la conexión a internet con las credenciales de WiFi*/
  // ubidots.setDebug(true);  //Descomentar esto para que los mensajes de depuración estén disponibles
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  /*Se inicia la función de subscripción para los mensajes de retorno, que se definió líneas arriba*/
  ubidots.setCallback(callback);
  /*Se incluye las funciones de Setup y Reconnect, predefinidas de la librería*/
  ubidots.setup();
  ubidots.reconnect();
  timer = millis();
}

/*Iniciamos el bucle de la función Loop()*/
void loop()
{
  /*Definimos que, si no se conecta a la plataforma Ubidots, se pasa la función Reconnect() para volver a establecer la conexión*/
  if (!ubidots.connected())
  {
    ubidots.reconnect();
  }
  /*En esta condicional, iniciamos la medición de Temperatura y Humedad del sensor, y la información será enviada a la Plataforma*/
  if (abs(millis() - timer) > PUBLISH_FREQUENCY) 
  {
    /*Hacemos la medición de Temperatura y Humedad del sensor, y lo definimos en variables Float */
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    /*Definimos que el valor de Temperatura será enviado por la variable 1, a la plataforma Ubidots*/
    ubidots.add(VARIABLE_LABEL_1, t);
    /*Definimos que el valor de Humedad será enviado por la variable 2, a la plataforma Ubidots*/
    ubidots.add(VARIABLE_LABEL_2, h);
    /*Hacemos la publicación de los datos en el dispositivo definido*/
    ubidots.publish(DEVICE_LABEL);
    /*Para mostrar los datos, los imprimimos en el terminal Serial*/
    Serial.println("Enviando los datos a Ubidots: ");
    Serial.println("Temperatura: " + String(t));
    Serial.println("Humedad: " + String(h));
    Serial.println("-----------------------------------------");
    timer = millis();
  }
  /*Agregamos un delay de 10 segundos para el envío, y que luego de este tiempo, se proceda a reiniciar el bucle*/
  delay(10000); 
  ubidots.loop();
}
