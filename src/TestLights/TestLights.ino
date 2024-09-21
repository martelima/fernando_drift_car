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

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, COLOR_RED);
    pixels.setPixelColor(LED_RIGHT, COLOR_RED);
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, COLOR_GREEN);
    pixels.setPixelColor(LED_RIGHT, COLOR_GREEN);
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, COLOR_BLUE);
    pixels.setPixelColor(LED_RIGHT, COLOR_BLUE);
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, COLOR_WHITE);
    pixels.setPixelColor(LED_RIGHT, COLOR_BLUE);
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, COLOR_BLUE);
    pixels.setPixelColor(LED_RIGHT, COLOR_WHITE);
    pixels.show();
    delay(TIME_DELAY);
}