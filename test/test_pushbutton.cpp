#include <ArduinoUnitTests.h>

#include "../ArduinoPartsPushButton.h"


unittest(unittest_pushbutton)
{
  const byte PIN_BUTTON = 7;
  GhostPushButton but(PIN_BUTTON);
  but.begin();
  assertTrue(but.isReleased());
  delay(100);
  but.press();
  but.read();
  //assertTrue(but.isPressed());
  //but.release();
  //but.read();
  //assertTrue(but.isReleased());
}

unittest_main()
