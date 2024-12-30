/* 
  Autores: Mateus Lima e Rafael Lima
  Descrição: Este é um código que possibilita o controle de um 
             carro bluetooth montado em arduino com uma shield 
             ponte H, através do protocolo serial
*/

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

const unsigned int PIN_LEDSTRIP = A0;
const unsigned int NUM_LEDS = 2;
const long TIME_DELAY = 1000;

const uint16_t LED_LEFT = 0;
const uint16_t LED_RIGHT = 1;

Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LEDSTRIP, NEO_BRG + NEO_KHZ800);

const uint32_t COLOR_RED = pixels.Color(150, 0, 0);
const uint32_t COLOR_GREEN = pixels.Color(0, 150, 0);
const uint32_t COLOR_BLUE = pixels.Color(0, 0, 150);
const uint32_t COLOR_WHITE = pixels.Color(150, 150, 150);
const uint32_t COLOR_OFF = pixels.Color(0, 0, 0);

/*
  Aqui definimos a velocidade máxima dos motores porem isso 
  depende tambem da fonte de energia que esteja utilizando 
  para alimentar os motores, logo se o valor atribuido for 
  equivalente a 255, por PWM os motores receberão tensão 
  total da fonte que estiver utilizando.
*/
#define Fator_correcao_Dir 1
#define Fator_correcao_Tra 1

#define PIN_SPEED_DIRECTION 10
#define PIN_SPEED_MOTOR_BACK 11

#define VmaxD 127
#define VmaxT 191

#define Farol_dianteiro 8
#define Farol_traseiro 7
#define Pisca_alerta 2
#define buzina 13

#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9

const int SPEED_MOTOR_DIRECTION = 50;

enum CarDirection: int8_t {
  DIRECTION_LEFT = -1,
  DIRECTION_CENTER = 0,
  DIRECTION_RIGHT = 1
};

/**
 * Mapa dos comandos enviados via bluetooth pelo aplicativo
 */
enum CarBTCommands: char {
  CMD_SET_SPEED_0 = '0',
  CMD_SET_SPEED_1 = '1',
  CMD_SET_SPEED_2 = '2',
  CMD_SET_SPEED_3 = '3',
  CMD_SET_SPEED_4 = '4',
  CMD_SET_SPEED_5 = '5',
  CMD_SET_SPEED_6 = '6',
  CMD_SET_SPEED_7 = '7',
  CMD_SET_SPEED_8 = '8',
  CMD_SET_SPEED_9 = '9',
  CMD_SET_SPEED_MAX = 'q',
  CMD_MOVE_LEFT = 'L',
  CMD_MOVE_RIGHT = 'R',
  CMD_MOVE_FORWARDS = 'F',
  CMD_MOVE_FORWARDS_LEFT = 'G',
  CMD_MOVE_FORWARDS_RIGHT = 'I',
  CMD_MOVE_BACKWARDS = 'B',
  CMD_MOVE_BACKWARDS_LEFT = 'H',
  CMD_MOVE_BACKWARDS_RIGHT = 'J',
  CMD_FRONT_LIGHT_ON = 'W',
  CMD_FRONT_LIGHT_OFF = 'w',
  CMD_BACK_LIGHT_ON = 'U',
  CMD_BACK_LIGHT_OFF = 'u',
  CMD_ALERT_LIGHT_ON = 'X',
  CMD_ALERT_LIGHT_OFF = 'x',
  CMD_BUZZ_ON = 'V',
  CMD_BUZZ_OFF = 'v',
  CMD_STOP = 'S'
};

void setup() {
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);

  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(PIN_SPEED_MOTOR_BACK,OUTPUT);
  pinMode(PIN_SPEED_DIRECTION,OUTPUT);

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
}
void loop() {
  static int carSpeed = VmaxT;
  static CarBTCommands state = CMD_STOP;

  // Atribui os valores da leitura serial na variável "state"
  if (Serial.available() > 0) {
    state = Serial.read();
    Serial.write(state);
  }

  switch(state)
  {
    /*
      Aqui controlamos a velocidade que o carro bluetooth irá
      se locomover, portanto multiplicamos a velocidade maxima
      por valores decimais para reduzir proporcionamente as 
      velocidades dos motores direito e esquerdo. 
      
      Quando a variavel "state" assumir o caractere 7,através do meio 
      serial, as velocidades são correspondentes à 70% da velocidade 
      máxima dos motores
    */
    case CMD_SET_SPEED_0:
    {
      carSpeed = 0;
      break;
    }
    case CMD_SET_SPEED_1:
    {
      carSpeed = VmaxT / 10;
      break;
    }
    case CMD_SET_SPEED_2:
    {
      carSpeed = (2 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_3:
    {
      carSpeed = (3 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_4:
    {
      carSpeed = (4 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_5:
    {
      carSpeed = (5 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_6:
    {
      carSpeed = (6 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_7:
    {
      carSpeed = (7 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_8:
    {
      carSpeed = (8 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_9:
    {
      carSpeed = (9 * VmaxT) / 10;
      break;
    }
    case CMD_SET_SPEED_MAX:
    {
      carSpeed = VmaxT;
      break;
    }

    /*
      Aqui controlamos a direção do carro e acionamento dos motores 
     */
    case CMD_MOVE_FORWARDS:
    {
      setCarDirection(DIRECTION_CENTER);
      setCarSpeed(carSpeed);
      setLightsColor(COLOR_BLUE,COLOR_BLUE);
      break;
    }
    case CMD_MOVE_FORWARDS_LEFT:
    {
      setCarDirection(DIRECTION_LEFT);
      setCarSpeed(carSpeed);
      setLightsColor(COLOR_WHITE,COLOR_BLUE);
      break;
    }
    case CMD_MOVE_FORWARDS_RIGHT:
    {
      setCarDirection(DIRECTION_RIGHT);
      setCarSpeed(carSpeed);
      setLightsColor(COLOR_BLUE,COLOR_WHITE);
      break;
    }
    case CMD_MOVE_BACKWARDS:
    {
      setCarDirection(DIRECTION_CENTER);
      setCarSpeed(-carSpeed);
      setLightsColor(COLOR_RED,COLOR_RED);
      break;
    }
    case CMD_MOVE_BACKWARDS_LEFT:
    {
      setCarDirection(DIRECTION_LEFT);
      setCarSpeed(-carSpeed);
      setLightsColor(COLOR_WHITE,COLOR_RED);
      break;
    }
    case CMD_MOVE_BACKWARDS_RIGHT:
    {
      setCarDirection(DIRECTION_RIGHT);
      setCarSpeed(-carSpeed);
      setLightsColor(COLOR_RED,COLOR_WHITE);
      break;
    }
    case CMD_MOVE_LEFT:
    {
      setCarDirection(DIRECTION_LEFT);
      setCarSpeed(0);
      setLightsColor(COLOR_WHITE,COLOR_OFF);
      break;
    }
    case CMD_MOVE_RIGHT:
    {
      setCarDirection(DIRECTION_RIGHT);
      setCarSpeed(0);
      setLightsColor(COLOR_OFF,COLOR_WHITE);
      break;
    }
    case CMD_STOP:
    {
      setCarDirection(DIRECTION_CENTER);
      setCarSpeed(0);
      setLightsColor(COLOR_OFF,COLOR_OFF);
      break;
    }

    /*
      Aqui temos algums comandos extras do aplicativo
    */
    case CMD_FRONT_LIGHT_ON:
    case CMD_FRONT_LIGHT_OFF:
    case CMD_BACK_LIGHT_ON:
    case CMD_BACK_LIGHT_OFF:
    case CMD_ALERT_LIGHT_ON:
    case CMD_ALERT_LIGHT_OFF:
    case CMD_BUZZ_ON:
    case CMD_BUZZ_OFF:
    default:
    {
      // Comandos não mapeados por hora
      break;
    }
  }
}


/**
 * Controla a velocidade e direção do motor de trás
 */
void setCarSpeed(const int speed)
{
  if(speed > 0)
  {
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    analogWrite(PIN_SPEED_MOTOR_BACK,speed);
  }
  else if(speed < 0)
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    analogWrite(PIN_SPEED_MOTOR_BACK,-speed);
  }
  else
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    analogWrite(PIN_SPEED_MOTOR_BACK,0);
  }
}

/**
 * Controla a direção do carro através do motor da frente
 */
void setCarDirection(CarDirection direction){
  switch (direction)
  {
    case DIRECTION_LEFT:
    {
      digitalWrite(IN1,1);
      digitalWrite(IN2,0);
      analogWrite(PIN_SPEED_DIRECTION,SPEED_MOTOR_DIRECTION);
      break;
    }

    case DIRECTION_RIGHT:
    {
      digitalWrite(IN1,0);
      digitalWrite(IN2,1);
      analogWrite(PIN_SPEED_DIRECTION,SPEED_MOTOR_DIRECTION);
      break;
    }
    
    case DIRECTION_CENTER:
    default:
    {
      digitalWrite(IN1,0);
      digitalWrite(IN2,0);
      analogWrite(PIN_SPEED_DIRECTION,0);
      break;
    }
  }
}

/**
 * Controla as luzes em baixo do carro
 */
void setLightsColor(const uint32_t color_left, const uint32_t color_right)
{
  pixels.clear();  // Set all pixel colors to 'off'
  pixels.setPixelColor(LED_LEFT, color_left);
  pixels.setPixelColor(LED_RIGHT, color_right);
  pixels.show();
} 