#include <ArduinoPartsPushButton.h>
#include <ArduinoPartsLed.h>

// pinout
// connect a push button from this pin (7) to ground (GND)
const byte PIN_BUTTON = 7;
// connect a led from this pin (13) to ground (GND) using a 220 ohm resistor
const byte PIN_LED = 13;

// instantiate a push button object with pin number BUTTON_PIN
PushButton butToggle(PIN_BUTTON);
Led led(PIN_LED);

void setup() {
  // initialize the push button object
  butToggle.begin();
  // initialize the led object
  led.begin();
}

void loop() {
  // read the button
  butToggle.read();

  // if the button was released, change the LED state
  if (butToggle.wasReleased()) {
    led.toggle();
  }
}
