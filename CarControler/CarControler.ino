/* 
  Autores: Mateus Lima e Rafael Lima
  Descrição: Este é um código que possibilita o controle de um 
             carro bluetooth montado em arduino com uma shield 
             ponte H, através do protocolo serial
*/
/*
  É necessario incluir a biblioteca 'AFMotor' pois simplifica o 
  uso da Shield ponte H
*/

//#include <AFMotor.h>

//selecionamos os canais 3 e 4 para motor direito e esquerdo
//respectivamente

//AF_DCMotor motor_dir(3);
//AF_DCMotor motor_esq(4);

/*
  Aqui definimos a velocidade máxima dos motores porem isso 
  depende tambem da fonte de energia que esteja utilizando 
  para alimentar os motores, logo se o valor atribuido for 
  equivalente a 255, por PWM os motores receberão tensão 
  total da fonte que estiver utilizando.
*/
#define Fator_correcao_Dir 1
#define Fator_correcao_Tra 1

#define Pin_vel_direcional 11
#define Pin_vel_motor_traseiro 10

#define VmaxD 127
#define VmaxT 191

int vel_motor_direcional = 127;
int vel_motor_traseiro = 191;
/*
   Variáveis que controlaram as velocidades do motor direito 
   e esquerdo
*/

//int vSpeed_dir = 200; 
//int vSpeed_esq = 200;

#define Farol_dianteiro 8
#define Farol_traseiro 7
#define Pisca_alerta 2
#define buzina 13
//variável que atribuimos a leitura Serial do módulo bluetooth
#define IN1 3
#define IN2 5
#define IN3 6
#define IN4 9

char state;

void setup() {
  // Inicializa a comunicação serial em 9600 bits.
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(Pin_vel_motor_traseiro,OUTPUT);
  pinMode(Pin_vel_direcional,OUTPUT);
}
void loop() {
  // Atribui os valores da leitura serial na variável "state"
  if (Serial.available() > 0) {
    state  = Serial.read();
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
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'G') {  // Se o estado recebido for igual a 'I', o carro se movimenta para Frente Esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0); 
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'I') {   // Se o estado recebido for igual a 'G', o carro se movimenta para Frente Direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,1);
    digitalWrite(IN4,0);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'B') { // Se o estado recebido for igual a 'B', o carro se movimenta para trás.
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'H') {  // Se o estado recebido for igual a 'H', o carro se movimenta para Trás Esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'J') {  // Se o estado recebido for igual a 'J', o carro se movimenta para Trás Direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,1);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'L') {   // Se o estado recebido for igual a 'L', o carro se movimenta para esquerda.
    digitalWrite(IN1,1);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'R') {   // Se o estado recebido for igual a 'R', o carro se movimenta para direita.
    digitalWrite(IN1,0);
    digitalWrite(IN2,1);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
  }
  else if (state == 'S') {   // Se o estado recebido for igual a 'S', o carro permanece parado.
    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);
    digitalWrite(Pin_vel_direcional,vel_motor_direcional * Fator_correcao_Dir);
    digitalWrite(Pin_vel_motor_traseiro,vel_motor_traseiro * Fator_correcao_Tra);
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
