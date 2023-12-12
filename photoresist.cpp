#include <Arduino.h>

#define foco 12
const int fotoresistencia = 25;
//#define fotoresistencia 25
int valorLDR = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(fotoresistencia, INPUT);
  pinMode(foco, OUTPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  valorLDR = analogRead(fotoresistencia);
  
  Serial.println(valorLDR);
  //Serial.print('h');
 
  if(valorLDR <= 400) //0
  {
    digitalWrite(foco, HIGH);
    //Serial.println('perro');
  }
  if(valorLDR > 500) //350
  {
    digitalWrite(foco, LOW);
    //Serial.println('perro');
  }

  delay(200);
}