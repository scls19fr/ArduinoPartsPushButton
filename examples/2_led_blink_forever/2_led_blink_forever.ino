#include <ArduinoPartsLed.h>
#include <ArduinoPartsPushButton.h>

// pinout
// connect a push button from this pin (7) to ground (GND)
const byte PIN_BUTTON_0 = 7;
// connect a led from this pin (13) to ground (GND) using a 220 ohm resistor
const byte PIN_LED_0 = 13;

const uint32_t ON_DELAY = 1000;
const uint32_t OFF_DELAY = 2000;

// instantiate a push button object with pin number PIN_BUTTON_0
PushButton but(PIN_BUTTON_0);
// instantiate a led object with pin number PIN_LED_0
Led led(PIN_LED_0);

// instantiate a BlinkTask object with led
BlinkTask blinkTask(led);

uint32_t ms = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  
  ms = millis();

  // initialize the push button object
  but.begin(ms);
  
  // initialize the led object
  led.begin(ms);
  //led.off();
  // blinkTask.start(ON_DELAY, OFF_DELAY);
  // led.blinkTask.start(ON_DELAY, OFF_DELAY);
}

void loop() {
  ms = millis();

  // read the button
  but.read(ms);

  if (but.wasPressedFor(4000)) {
    if (blinkTask.isActive()) {
      Serial.println("stop blinkTask");
      blinkTask.stop();
    }
  } else if (but.wasPressedFor(100)) {
    if (!blinkTask.isActive()) {
      Serial.println("start blinkTask forever");
      blinkTask.start(ON_DELAY, OFF_DELAY);
    }
  }

  blinkTask.update(ms);
  // led.update(ms);

}