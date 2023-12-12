//DECLARACIONES
#include <Arduino.h>
#include "BluetoothSerial.h"

//DEFINICIONES
//revisar si la tarjeta tiene Bluetooth habilitado
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta habilitado
#endif

//revisar si la tarjeta puede hacer comunicación serial por Blutooth
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Comunicacion Serial Bluetooth no habilitada
#endif

int recibido;// variable para guardar el caracter recibido como entero
char recibidoChar;// el valor recibido como CHAR se guarda aqui
const char encender ='1'; //definir el caracter para encender el LED
const char apagar ='0'; //definir el caracter para apagar el LED
const char encender_2='2';
const char encender_3='3';
#define LED 23 //definir el pin donde está conectado el LED
#define LED_1 22
int bandera=0;
// crear objeto SerialBT que representa la conexion BT
BluetoothSerial SerialBT;

//CONFIGURACIONES
void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32 Equipo 3"); // nombre del dispositivo BT
  Serial.println("Dispositivo iniciado, ahora puede conectarlo por BT");
  Serial.println("Para encender el LED, envie: 1");
  Serial.println("Para encender el LED, envie: 2");
  Serial.println("Para encender ambos LEDS, envie 3");
  Serial.println("Para apagar cualquier LED, envie: 0");
  pinMode(LED, OUTPUT);
  pinMode(LED_1,OUTPUT);
}

//BUCLE PRINCIPAL
void loop() {
  //almacenar el caracter leído de la terminal
  recibidoChar =(char)SerialBT.read(); 

  if (Serial.available()) { // si la comunicación serial está habilitada
    // leer la información que llega por el puerto serial y escribirla en el puerto serial BT
    SerialBT.write(Serial.read()); 
  }
  if (SerialBT.available()) { // si la comunicación BT serial está habilitada
    SerialBT.print("Recibido:");// mandar mensaje por BT
    SerialBT.println(recibidoChar);// escribir el caracter que se recibio     
    Serial.print ("Recibido:");// mandar mensaje por serial
    Serial.println(recibidoChar);// escribir el caracter que se recibio     

    if(recibidoChar == encender) { // si se detecta el caracter para encender el LED...
      SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      bandera=1; }
    else if(recibidoChar == apagar){ // si se detecta el caracter para apagar el LED...
      SerialBT.println("LED APAGADO:");// mandar mensaje por BT
      Serial.println("LED APAGADO:");// mandar mensaje por serial
      bandera=0;
      }
      else if(recibidoChar == encender_2){
        SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      bandera=2; 
      }
      else if(recibidoChar == encender_3){
        SerialBT.println("LED ENCENDIDO:");// mandar mensaje por BT
      Serial.println("LED ENCENDIDO:");// mandar mensaje por serial
      bandera=3; 
      }
      else { // si no es ninguno de los caracteres definidos
      SerialBT.println("CARACTER NO VALIDO");// mandar mensaje por BT
      Serial.println("CARACTER NO VALIDO");// mandar mensaje por serial
    }
    
  }
  switch(bandera){
    case 1:
      digitalWrite(LED, HIGH);
      delay(250);
      digitalWrite(LED, LOW);
      delay(250);

    break;
    case 2:
      digitalWrite(LED_1, HIGH);
      delay(250);
      digitalWrite(LED_1, LOW);
      delay(250);
    break;
    
    case 3:
      digitalWrite(LED, HIGH);
      digitalWrite(LED_1, HIGH);
      delay(750);
      digitalWrite(LED, LOW);
      digitalWrite(LED_1, LOW);
      delay(750);

    break;
    
    default:
      digitalWrite(LED, LOW);
      digitalWrite(LED_1, LOW); 
  }
  delay(20);
}