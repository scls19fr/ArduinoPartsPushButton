#include <ArduinoUnitTests.h>

#include "../ArduinoPartsLed.h"


unittest(unittest_led_on_off_toggle)
{
  const byte PIN_LED = 13;
  Led led(PIN_LED);
  led.begin();
  assertFalse(led.isLit());
  led.on();
  assertTrue(led.isLit());
  led.off();
  assertFalse(led.isLit());
  led.toggle();
  assertTrue(led.isLit());
  led.toggle();
  assertFalse(led.isLit());
}

unittest_main()
