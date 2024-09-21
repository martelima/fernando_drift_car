const int PIN_BUZZER = 12; //buzzer to arduino pin 12
const int FREQ = 335;

void setup(){
  pinMode(PIN_BUZZER, OUTPUT); // Set buzzer - pin 9 as an output
}

void loop(){
  tone(PIN_BUZZER, FREQ); // Send 1KHz sound signal...
  delay(1000);            // ...for 1 sec
  noTone(PIN_BUZZER);     // Stop sound...
  delay(1000);             // ...for 1sec
}