#include <IRremote.h>  //Tendréis que instalar la libreria
 
const int RECV_PIN = 9;  //recibiremos la información del mando por el pin 9

//A continuación, creamos contantes con el valor de cada tecla del mando, que previamente hemos obtenido.
//El código está configurado para que nos muestre por el Monitor serie el valor de cada tecla que recibe en tiempo real.
const int mando_rojo = 20145;
const int mando_verde = -29071;
const int mando_amarillo = -14791;
const int mando_azul = -31111;

IRrecv irrecv(RECV_PIN);
decode_results results;

//Asignamos los pines con los que trabajaremos.
int alimentacion = 7;
int rojo = 4;
int verde = 5;
int azul = 6;

int valor;
//Los estados nos permiten encender un color en concreto y apagarlo con una segunda pulsación.
int estado_rojo = 0;
int estado_verde = 0;
int estado_azul = 0;
int inicializar = 0;

void setup()
{
   Serial.begin(9600);
   irrecv.enableIRIn();
   pinMode(alimentacion, OUTPUT);
   pinMode(rojo, OUTPUT);
   pinMode(verde, OUTPUT);
   pinMode(azul, OUTPUT);
}
 
void loop()
{
   if(inicializar == 0){  //Todos los LED comienzan apagados a la espera de su activación.
      digitalWrite(alimentacion, HIGH);
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, HIGH);
      inicializar = 1;
   }
   
   if (irrecv.decode(&results))
   {
      Serial.println(results.value);  //nos muestra en el Monitor serie el valor de la techa que recibe.
      valor = results.value;
      Serial.println(valor);

      switch(valor)
      {
      case mando_rojo:
         if(estado_rojo==0){
            digitalWrite(alimentacion, HIGH);
            digitalWrite(rojo, LOW);  //En la tira LED con la que he trabajado LOW=ENCENDIDO, HIGH=APAGADO
                                      //Puede variar con otras tiras LED
            estado_rojo = 1;
         }
         else{
            digitalWrite(alimentacion, HIGH);
            digitalWrite(rojo, HIGH);
            estado_rojo = 0;
         }
         break;
         
      case mando_verde:
        if(estado_verde==0){
           digitalWrite(alimentacion, HIGH);
           digitalWrite(verde, LOW);
           estado_verde = 1;
        }
        else{
            digitalWrite(alimentacion, HIGH);
            digitalWrite(verde, HIGH);
            estado_verde = 0;
        }
        break;
      case mando_azul:
         if(estado_azul==0){
            digitalWrite(alimentacion, HIGH);
            digitalWrite(azul, LOW);
            estado_azul = 1;
         }
         else{
            digitalWrite(alimentacion, HIGH);
            digitalWrite(azul, HIGH);
            estado_azul = 0;
         }
         break;
      }
      
      irrecv.resume();
   }
}
