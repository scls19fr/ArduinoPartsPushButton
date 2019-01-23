#include <ArduinoUnitTests.h>

#include "../ArduinoPartsPushButton.h"


unittest(pushbutton)
{
  const byte PIN_BUTTON = 7;

  GhostPushButton but(PIN_BUTTON);
  uint32_t ms = 0;  // millis();
  but.begin(ms);
  assertTrue(but.isReleased());
  ms += 100;
  but.press();
  but.read(ms);
  //assertTrue(but.isPressed());
  //but.release();
  //but.read();
  //assertTrue(but.isReleased());
}

unittest_main()
