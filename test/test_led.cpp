#include <ArduinoUnitTests.h>

#include "../ArduinoPartsLed.h"

#define PIN_LED 13

unittest(unittest_led_on_off_toggle)
{
  uint32_t ms = 0;  // millis();

  Led led(PIN_LED);
  led.begin(ms);
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

unittest(unittest_blink_task)
{
  uint32_t ms = 0;  // millis();

  Led led(PIN_LED);
  led.begin(ms);
  assertFalse(led.isLit());

  BlinkTask task(led);
  task.begin(ms);
  task.start(3, 100, 50);
  assertFalse(led.isLit());

  ms += 100;
  task.update(ms);
  assertFalse(led.isLit());

  ms += 50;
  task.update(ms);
  assertFalse(led.isLit());

  ms += 100;
  task.update(ms);
  assertFalse(led.isLit());

  ms += 50;
  task.update(ms);
  assertFalse(led.isLit());

}

unittest_main()
