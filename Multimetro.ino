/*
 * Fundacion Kinal
 * Centro educativo tecnico laboral Kinal
 * Electronica
 * Grado: Quinto
 * Sección: A
 * Curso: Taller de electronica digital y reparación de computadoras I
 * Nombre: Juan David Tejada Peñuela 
 * Carnet: 2022454
 * Proyecto: Multimetro
*/
#include <SoftwareSerial.h>
#define ANALOG_PIN 18
float Sensibilidad=0.185;
float Rx = 0;
int R= 10000;
float Vout = 0;
float operacion = 0;
float lectura_pin = 0;
float result = 0;
char recepcion;
SoftwareSerial BT(3,2); // RX, TX pins

void setup() {
Serial.begin(9600);
BT.begin(9600);
}

void loop() {
  if (BT.available()) {
    recepcion = BT.read();
    Serial.println(recepcion);

    if (recepcion == '1') {
  // Valores de voltaje
  float voltaje =  (float)25*analogRead(A1)/1023;
  Serial.print(voltaje);
  Serial.println(";");
  BT.print(voltaje);
  BT.println(";");
    }

    if (recepcion == '2') {
  //Valores de Resistencia
  lectura_pin = analogRead(ANALOG_PIN);
  operacion = lectura_pin * 5;
  Vout = operacion / 1023;
  result = (5/Vout) -1;
  Rx = R * result;
  Serial.print(Rx);
  Serial.println(";");
  BT.print(Rx);
  BT.println(";");
    }

    if (recepcion == '3') {
  // Valores de corriente
  float corriente = get_corriente(200);  
  Serial.print(corriente);
  Serial.println(";");
  BT.print(corriente);
  BT.println(";");
    }
  }  
  

}

float get_corriente(int n_muestras) // funcion que complementa la formula para obtener el valor de corriente
{
  float voltajeSensor;
  float CURRENT=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(A0) * (5.0 / 1023.0);////lectura del sensor
    CURRENT=CURRENT+(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  CURRENT=CURRENT/n_muestras;
  return(CURRENT);
}
