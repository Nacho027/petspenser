#include <Servo.h>

// Limites
#define SERVO_ABIERTO  		90
#define SERVO_CERRADO 		0

#define PESO_MAXIMO			100
#define PESO_MINIMO 		0

#define CANTIDAD_SENSORES	5

// Estados Embebido
#define ESTADO_EMBER_INIT			1
#define ESTADO_IDLE 				100
#define ESTADO_OCUPADO 				101
#define ESTADO_BLOQUEADO 			102

// Estados sensor ditancia
#define ESTADO_DISTANCIA_PRESENTE	103
#define ESTADO_DISTANCIA_AUSENTE	104


// Estados flex
#define ESTADO_PESO_INSUFICIENTE	105
#define ESTADO_PESO_SUFICIENTE		106

// Estados pulsador
#define ESTADO_PULSADOR_ACTIVO		107
#define ESTADO_PULSADOR_INACTIVO	108

// Estados servo
#define ESTADO_SERVO_ABIERTO		109
#define ESTADO_SERVO_CERRADO		110

#define ESTADO_SENSOR_IDLE			200

// Pines
#define PULSADOR_PIN	2
#define LED_PIN			3
#define SERVO_PIN 		7
#define FLEX_PIN 		A0
#define DISTANCIA_PIN	A1

// Eventos
#define EVENTO_PULSADOR_ACTIVADO	1000
#define EVENTO_PULSADOR_DESAVTIVADO	2000

#define EVENTO_		3000
#define EVENTO_CERRANDO_TAPA		4000

// Sensor
typedef struct stSensor
{
  int  pin;
  int  estado;
  
  long valor_actual;
  long valor_previo;
} stSensor;

stSensor stDistancia;
stSensor stFlex;
stSensor stPulsador;
stSensor stServo;
stSensor led;

typedef struct stEvento
{
  int tipo;
  int parametro;
} stEvento;

stEvento evento;

Servo servo;

int estado;
int SERVO_POSITION = 90;
int FLEX_VALUE = 0;

// Umbrales

int umbralPesoMax = 10;

void do_init()
{
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  estado = ESTADO_EMBED_INIT;
}


void setup()
{
	do_init();
}

void loop()
{
//   leer_sensores();
//   verificar_estados();
  maquina_estado();
  
  //FLEX_VALUE = analogRead(FLEX_PIN);
  //Serial.println(FLEX_VALUE);
  //SERVO_POSITION = map(FLEX_VALUE, 770, 950, 0, 180);
  //SERVO_POSITION = constrain(SERVO_POSITION, 0, 180);
  //servo.write(SERVO_POSITION);
}

void leer_sensores()
{
//   if(leer_sensor_distancia();
  if(evento_sensor_peso() || evento_sensor_distancia());
}

void verificar_estados()
{
  
  // TODO
  return;
}

void maquina_estado()
{
    leer_sensores();
    switch(estado)
    {
        case ESTADO_IDLE:
        {
        switch(evento.tipo)
        {
            case EVENTO_PULSADOR_ACTIVADO:
            {
                estado.tipo = ESTADO_OCUPADO;
            }
            case EVENTO_ABRIENDO_TAPA:
            {
            
            }
        }
        }
        case ESTADO_OCUPADO:
        {

        }
        case ESTADO_BLOQUEADO:
        {

        }
    }
}

void leer_sensor_distancia()
{
  long tiempo_pulso;
  long distancia;
  
  pinMode(stDistancia.pin, OUTPUT);
  digitalWrite(stDistancia.pin, LOW);
  
  delayMicroseconds(2);
  digitalWrite(stDistancia.pin, HIGH);
  
  delayMicroseconds(5);
  digitalWrite(stDistancia.pin, LOW);

  pinMode(stDistancia.pin, INPUT);
  tiempo_pulso = pulseIn(stDistancia.pin, HIGH);

  // Convierto la medicion en centimetros.
  distancia = tiempo_pulso / 29 / 2;
  
  stDistancia.valor_previo = stDistancia.valor_actual;
  stDistancia.valor_actual = distancia;
}

bool evento_sensor_peso()
{
  long lectura = analogRead(stFlex.pin);
  stFlex.valor_previo = stFlex.valor_actual;
  stFlex.valor_actual = lectura;

  return true;
}