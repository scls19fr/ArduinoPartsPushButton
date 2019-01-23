/*!\file ArduinoPartsLed.cpp
** \author Sébastien Celles
** \date 2019/01/23
** \copyright MIT License (c) 2019, Sébastien Celles
** \brief Led handling library.
** \details Led handling library.
**			    This library was designed for Arduino boards
**/

#include "ArduinoPartsLed.h"

void Led::begin() {
  pinMode(m_pin, OUTPUT);
  off();
}

void Led::on() {
  if (m_lit_state) {
    digitalWrite(m_pin, HIGH);
  } else {
    digitalWrite(m_pin, LOW);
  }
  m_state = true;
}

void Led::off() {
  if (m_lit_state) {
    digitalWrite(m_pin, LOW);
  } else {
    digitalWrite(m_pin, HIGH);
  }
  m_state = false;
}

void Led::toggle() {
  m_state = !m_state;
  lit(m_state);
}

void Led::lit(bool state) {
  if (state) {
    on();
  } else {
    off();
  }
}

bool Led::isLit() {
  return m_state;
}

void Led::update() {

}

void Led::blink(uint8_t times, uint32_t on_delay, uint32_t off_delay) {
  on_delay = 0;
  off_delay = 0;
}

void Led::blinkForever(uint32_t on_delay, uint32_t off_delay) {
  on_delay = 0;
  off_delay = 0;
}

bool Led::isBlinking() {
  return false;
}

void Led::stop() {

}
