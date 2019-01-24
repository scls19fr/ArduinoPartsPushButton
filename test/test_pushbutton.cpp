#include <ArduinoUnitTests.h>

#include "../ArduinoPartsPushButton.h"


unittest(pushbutton)
{
  const byte PIN_BUTTON = 7;

  GhostPushButton but(PIN_BUTTON);
  uint32_t ms = 0;  // millis();
  but.begin(ms);

  ms += 100;
  but.read(ms);
  assertTrue(but.isReleased());
  assertTrue(!but.isPressed());
  assertTrue(!but.wasReleased());
  assertTrue(!but.wasPressed());
  assertTrue(!but.isReleasedFor(1000));
  assertTrue(!but.isPressedFor(1000));
  assertTrue(!but.wasReleasedFor(1000));
  assertTrue(!but.wasPressedFor(1000));

  ms += 100;
  but.press();
  but.read(ms);
  assertTrue(but.isPressed());

  ms += 100;
  but.release();
  but.read(ms);
  assertTrue(but.isReleased());
  // assertTrue(but.lastChange() == 1);

  ms += 1;
  but.press();
  but.read(ms);
  assertTrue(but.isReleased());  // debounced

  ms += 100;
  but.press();
  but.read(ms);
  assertTrue(but.isPressed());

  ms += 2000;
  but.read(ms);
  assertTrue(but.isPressedFor(2000));
}

unittest_main()
