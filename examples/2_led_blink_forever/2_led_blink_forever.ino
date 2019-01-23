#include <ArduinoPartsLed.h>

// pinout
const byte PIN_LED = 13;

// instantiate a led object with pin number PIN_LED
Led led(PIN_LED);

// instantiate a BlinkTask object with led
BlinkTask task(led);

uint32_t ms = 0;

void setup() {
  ms = millis();

  // initialize the led object
  led.begin(ms);
  task.start(500, 200);
  // led.blink_task.start(500, 200);
}

void loop() {
  ms = millis();
  task.update(ms);
  // led.update(ms);
}
