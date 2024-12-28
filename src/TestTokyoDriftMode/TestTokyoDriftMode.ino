// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#include "pitches.h"

const unsigned int PIN_LEDSTRIP = A0;
const unsigned int BUZZER_PIN = 12;
const unsigned int NUM_LEDS = 2;

const uint16_t LED_LEFT = 0;
const uint16_t LED_RIGHT = 1;


Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LEDSTRIP, NEO_BRG + NEO_KHZ800);

const uint32_t COLOR_RED = pixels.Color(150, 0, 0);
const uint32_t COLOR_GREEN = pixels.Color(0, 150, 0);
const uint32_t COLOR_BLUE = pixels.Color(0, 0, 150);
const uint32_t COLOR_WHITE = pixels.Color(150, 150, 150);
const uint32_t COLOR_OFF = pixels.Color(0, 0, 0);


int melody[] = {
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_F5, REST,
  NOTE_F5, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_GS5, NOTE_FS5, NOTE_F5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_AS4, REST,
  NOTE_AS4, REST,
  NOTE_AS4, NOTE_B4, NOTE_DS5, NOTE_F5, REST,
  NOTE_F5, REST,
  REST
};

int durations[] = {
  4, 4,
  4, 4,
  4, 4,
  4, 4, 3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  3, 3, 4,
  4, 4, 4, 4,
  1
};

uint32_t colors[] = 
{
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, NOTE_F5, COLOR_OFF,
  NOTE_F5, COLOR_OFF,
  NOTE_GS5, NOTE_FS5, NOTE_F5, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  NOTE_GS5, NOTE_FS5, NOTE_F5, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_OFF,
  COLOR_RED, COLOR_BLUE, COLOR_GREEN, NOTE_F5, COLOR_OFF,
  NOTE_F5, COLOR_OFF,
  COLOR_OFF
};

int note = 0;

void setup()
{
  // Inicia Buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Inicia Fita let
  pixels.begin();
  pixels.clear();
}

void loop()
{
   int size = (sizeof(durations) / sizeof(int)) - 1;

   note = (note < size)? note + 1: 0;

   //to calculate the note duration, take one second divided by the note type.
   //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
   int duration = 1000 / durations[note];
   tone(BUZZER_PIN, melody[note], duration);

   // Color Effects
   pixels.setPixelColor(LED_LEFT,colors[note]);
   pixels.setPixelColor(LED_RIGHT,colors[note]);
   pixels.show();

   //to distinguish the notes, set a minimum time between them.
   //the note's duration + 30% seems to work well:
   int pauseBetweenNotes = duration;
   delay(pauseBetweenNotes);

   //stop the tone playing:
   noTone(BUZZER_PIN);
}
