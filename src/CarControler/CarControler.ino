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

int vel_motor_direcional = 127;
int vel_motor_traseiro = 191;

#define Farol_dianteiro 8
#define Farol_traseiro 7
#define Pisca_alerta 2
#define buzina 13

#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9

enum CarDirection: int8_t {
  DIRECTION_LEFT = -1,
  DIRECTION_CENTER = 0,
  DIRECTION_RIGHT = 1
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
  static char state = 'S';

  // Atribui os valores da leitura serial na variável "state"
  if (Serial.available() > 0) {
    state = Serial.read();
    Serial.write(state);
  }
  /*
    Aqui controlamos a velocidade que o carro bluetooth irá
    se locomover, portanto multiplicamos a velocidade maxima
    por valores decimais para reduzir proporcionamente as 
    velocidades dos motores direito e esquerdo. 
    
    Quando a variavel "state" assumir o caractere 7,através do meio 
    serial, as velocidades são correspondentes à 70% da velocidade 
    máxima dos motores
  */
  if (state == '0') {
    vel_motor_direcional = VmaxD * 0;
    vel_motor_traseiro = VmaxT * 0;
  }
  else if (state == '1') {
    vel_motor_direcional = VmaxD * 0.1;
    vel_motor_traseiro = VmaxT * 0.1;
  }
  else if (state == '2') {
    vel_motor_direcional = VmaxD * 0.2;
    vel_motor_traseiro = VmaxT * 0.2;
  }
  else if (state == '3') {
    vel_motor_direcional = VmaxD * 0.3;
    vel_motor_traseiro = VmaxT * 0.3;
  }
  else if (state == '4') {
    vel_motor_direcional = VmaxD * 0.39;
    vel_motor_traseiro = VmaxT * 0.39; 
  }
  else if (state == '5') {
    vel_motor_direcional = VmaxD * 0.5;
    vel_motor_traseiro = VmaxT * 0.5;
  }
  else if (state == '6') {
    vel_motor_direcional = VmaxD * 0.6;
    vel_motor_traseiro = VmaxT * 0.6;
  }
  else if (state == '7') {
    vel_motor_direcional = VmaxD * 0.7;
    vel_motor_traseiro = VmaxT * 0.7;
  }
  else if (state == '8') {
    vel_motor_direcional = VmaxD * 0.78;
    vel_motor_traseiro = VmaxT * 0.78;
  }
  else if (state == '9') {
    vel_motor_direcional = VmaxD * 0.9;
    vel_motor_traseiro = VmaxT * 0.9;
  }
  else if (state == 'q') {
    vel_motor_traseiro = VmaxT;
  }
  // Se o estado recebido for igual a 'F', o carro se movimenta para frente.
  if (state == 'F') {
    setCarDirection(DIRECTION_CENTER);
    setCarSpeed(vel_motor_traseiro);
    setLightsColor(COLOR_BLUE,COLOR_BLUE);
  }
  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    setCarDirection(DIRECTION_LEFT);
    setCarSpeed(vel_motor_traseiro);
    setLightsColor(COLOR_WHITE,COLOR_BLUE);
  }
  else if (state == 'I') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    setCarDirection(DIRECTION_RIGHT);
    setCarSpeed(vel_motor_traseiro);
    setLightsColor(COLOR_BLUE,COLOR_WHITE);
  }
  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    setCarDirection(DIRECTION_CENTER);
    setCarSpeed(-vel_motor_traseiro);
    setLightsColor(COLOR_RED,COLOR_RED);
  }
  else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    setCarDirection(DIRECTION_LEFT);
    setCarSpeed(-vel_motor_traseiro);
    setLightsColor(COLOR_WHITE,COLOR_RED);
  }
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    setCarDirection(DIRECTION_RIGHT);
    setCarSpeed(-vel_motor_traseiro);
    setLightsColor(COLOR_RED,COLOR_WHITE);
  }
  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    setCarDirection(DIRECTION_LEFT);
    setCarSpeed(0);
    setLightsColor(COLOR_WHITE,COLOR_OFF);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    setCarDirection(DIRECTION_RIGHT);
    setCarSpeed(0);
    setLightsColor(COLOR_OFF,COLOR_WHITE);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    setCarDirection(DIRECTION_CENTER);
    setCarSpeed(0);
    setLightsColor(COLOR_OFF,COLOR_OFF);
  }
  else if (state == 'W') {   // Se o estado recebido for igual a 'W', Farol dianteiro acende.
  }
  else if (state == 'w') {   // Se o estado recebido for igual a 'w', Farol dianteiro apaga.
  }
  else if (state == 'U') {   // Se o estado recebido for igual a 'U', Farol traseiro acende.
  }
  else if (state == 'u') {   // Se o estado recebido for igual a 'u', Farol traseiro apaga.
  }
  else if (state == 'V') {   // Se o estado recebido for igual a 'V', liga buzina.
  }
  else if (state == 'v') {   // Se o estado recebido for igual a 'v', desliga buzina.
  }
  else if (state == 'X') {   // Se o estado recebido for igual a 'X', Pisca alerta acende.
  }
  else if (state == 'x') {   // Se o estado recebido for igual a 'x', Pisca alerta apaga.
    
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
    digitalWrite(PIN_SPEED_MOTOR_BACK,speed);
  }
  else if(speed < 0)
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(PIN_SPEED_MOTOR_BACK,-speed);
  }
  else
  {
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(PIN_SPEED_MOTOR_BACK,0);
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
      digitalWrite(PIN_SPEED_DIRECTION,vel_motor_direcional * Fator_correcao_Dir);
      break;
    }

    case DIRECTION_RIGHT:
    {
      digitalWrite(IN1,0);
      digitalWrite(IN2,1);
      digitalWrite(PIN_SPEED_DIRECTION,vel_motor_direcional * Fator_correcao_Dir);
      break;
    }
    
    case DIRECTION_CENTER:
    default:
    {
      digitalWrite(IN1,0);
      digitalWrite(IN2,0);
      digitalWrite(PIN_SPEED_DIRECTION,0);
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