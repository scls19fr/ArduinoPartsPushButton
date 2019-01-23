#include <ArduinoPartsPushButton.h>
#include <ArduinoPartsLed.h>

// pinout
// connect a push button from this pin (7) to ground (GND)
const byte PIN_BUTTON = 7;
// connect a led from this pin (13) to ground (GND) using a 220 ohm resistor
const byte PIN_LED = 13;

// instantiate a push button object with pin number PIN_BUTTON
PushButton butToggle(PIN_BUTTON);
// instantiate a led object with pin number PIN_LED
Led led(PIN_LED);

uint32_t ms = 0;

void setup() {
  ms = millis();

  // initialize the push button object
  butToggle.begin(ms);
  // initialize the led object
  led.begin(ms);
}

void loop() {
  ms = millis();

  // read the button
  butToggle.read(ms);

  // if the button was released, change the LED state
  if (butToggle.wasReleased()) {
    led.toggle();
  }
}
