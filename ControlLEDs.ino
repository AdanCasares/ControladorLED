#include <IRremote.h>
 
const int RECV_PIN = 9;
const int mando_rojo = 20145;
const int mando_verde = -29071;
const int mando_amarillo = -14791;
const int mando_azul = -31111;
 
IRrecv irrecv(RECV_PIN);
decode_results results;

int alimentacion = 7;
int rojo = 4;
int verde = 5;
int azul = 6;

int valor;
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
   if(inicializar == 0){
      digitalWrite(alimentacion, HIGH);
      digitalWrite(rojo, HIGH);
      digitalWrite(verde, HIGH);
      digitalWrite(azul, HIGH);
      inicializar = 1;
   }
   
   if (irrecv.decode(&results))
   {
      Serial.println(results.value);
      valor = results.value;
      Serial.println(valor);

      switch(valor)
      {
      case mando_rojo:
         if(estado_rojo==0){
            digitalWrite(alimentacion, HIGH);
            digitalWrite(rojo, LOW);
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
