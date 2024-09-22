#define PINLED 13
#define PINMOTOR1 11

#define MOTOR_BACK_IN3 6
#define MOTOR_BACK_IN4 9
#define MOTOR_BACK_SPEED 11

#define MOTOR_DIRECTION_IN1 3
#define MOTOR_DIRECTION_IN2 5
#define MOTOR_DIRECTION_ENABLE 10

const uint8_t MAX_SPEED_ALLOWED = 100;
const uint8_t MOTOR_DEAD_ZONE = 32;

int speedMotor,speedStep;

void setup() {
  
  Serial.begin(9600);

  pinMode(MOTOR_DIRECTION_IN1,OUTPUT);
  pinMode(MOTOR_DIRECTION_IN2,OUTPUT);
  pinMode(MOTOR_BACK_IN3,OUTPUT);
  pinMode(MOTOR_BACK_IN4,OUTPUT);
  pinMode(MOTOR_BACK_SPEED,OUTPUT);
  pinMode(MOTOR_DIRECTION_ENABLE,OUTPUT);
}

void loop() {
  // Set Motor and Direction
  digitalWrite(MOTOR_DIRECTION_IN1,0);
  digitalWrite(MOTOR_DIRECTION_IN2,0);
  digitalWrite(MOTOR_BACK_IN3,1);
  digitalWrite(MOTOR_BACK_IN4,0);

  // Set Speed
  analogWrite(MOTOR_BACK_SPEED,speedMotor);
  speedStep = (speedMotor >= MAX_SPEED_ALLOWED)?-1:(speedMotor < 10) ?1:speedStep;
  speedMotor += speedStep;

  // Print Speed and timer
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(speedMotor);
  
  delay(300);
}