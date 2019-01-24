#include <ArduinoPartsLed.h>

// pinout
const byte PIN_LED_0 = 13;

// instantiate a led object with pin number PIN_LED_0
Led led(PIN_LED_0);

// instantiate a BlinkTask object with led
BlinkTask blinkTask(led);

uint32_t ms = 0;

void setup() {
  ms = millis();

  // initialize the led object
  led.begin(ms);
  blinkTask.start(500, 200);
  // led.blinkTask.start(500, 200);
}

void loop() {
  ms = millis();
  blinkTask.update(ms);
  // led.update(ms);
}
