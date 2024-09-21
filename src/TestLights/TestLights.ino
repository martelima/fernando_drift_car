#include <Adafruit_NeoPixel.h>

const unsigned int PIN_LEDSTRIP = A0;
const unsigned int NUM_LEDS = 2;
const long TIME_DELAY = 500;

const uint16_t LED_LEFT = 0;
const uint16_t LED_RIGHT = 1;

Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LEDSTRIP, NEO_BRG + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, pixels.Color(150, 0, 0));
    pixels.setPixelColor(LED_RIGHT, pixels.Color(150, 0, 0));
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, pixels.Color(0, 150, 0));
    pixels.setPixelColor(LED_RIGHT, pixels.Color(0, 150, 0));
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, pixels.Color(0, 0, 150));
    pixels.setPixelColor(LED_RIGHT, pixels.Color(0, 0, 150));
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, pixels.Color(150, 150, 150));
    pixels.setPixelColor(LED_RIGHT, pixels.Color(0, 0, 150));
    pixels.show();
    delay(TIME_DELAY);

    pixels.clear();  // Set all pixel colors to 'off'
    pixels.setPixelColor(LED_LEFT, pixels.Color(0, 0, 150));
    pixels.setPixelColor(LED_RIGHT, pixels.Color(150, 150, 150));
    pixels.show();
    delay(TIME_DELAY);
}