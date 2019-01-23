#include <ArduinoPartsPushButton.h>

// pinout
// connect a push button from this pin (7) to ground (GND)
const byte BUTTON_PIN = 7;
// connect a led from this pin (13) to ground (GND) using a 220 ohm resistor
const byte LED_PIN = 13;

// instantiate a push button object with pin number BUTTON_PIN
PushButton butToggle(BUTTON_PIN);

void setup() {
  // initialize the pushbutton object
  butToggle.begin();
  // set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // a variable to keep the current LED status
  static bool ledState;

  // read the button
  butToggle.read();

  // if the button was released, change the LED state
  if (butToggle.wasReleased()) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
  }
}
