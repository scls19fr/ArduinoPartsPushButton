/*!\file ArduinoPartsPushButton.h
** \author Sébastien Celles
** \date 2019/01/23
** \copyright MIT License (c) 2019, Sébastien Celles
** \brief PushButton handling library.
** \details PushButton handling library.
**          Debounce push button, detect presses, releases, and long presses
**			    This library was designed for Arduino boards
**/

#include "ArduinoPartsPushButton.h"

/*
Implementation of abstract class
GhostPushButton for mocking purpose
*/

bool AbstractPushButton::read() {
  uint32_t ms = millis();
  bool pinVal = readPinValue();  // call virtual pure function
  if (ms - m_lastChange < m_debounceTime) {
    m_changed = false;
  } else {
    m_lastState = m_state;
    m_state = pinVal;
    m_changed = (m_state != m_lastState);
    if (m_changed) m_lastChange = ms;
  }
  m_time = ms;
  return m_state;
}

bool AbstractPushButton::isPressed() {
  return m_state;
}

bool AbstractPushButton::isReleased() {
  return !m_state;
}

bool AbstractPushButton::wasPressed() {
  return m_state && m_changed;
}

bool AbstractPushButton::wasReleased() {
  return !m_state && m_changed;
}

bool AbstractPushButton::pressedFor(uint32_t ms) {
  return m_state && m_time - m_lastChange >= ms;
}

bool AbstractPushButton::releasedFor(uint32_t ms) {
  return !m_state && m_time - m_lastChange >= ms;
}

uint32_t AbstractPushButton::lastChange() {
  return m_lastChange;
}

/*
Implementation of PushButton
*/

void PushButton::begin() {
  pinMode(m_pin, m_pullupEnabled ? INPUT_PULLUP : INPUT);
  m_state = readPinValue();
  m_time = millis();
  m_lastState = m_state;
  m_changed = false;
  m_lastChange = m_time;
}

bool PushButton::readPinValue() {
  bool pinVal = digitalRead(m_pin);
  if (m_invert) pinVal = !pinVal;
  return pinVal;
}

/*
Implementation of GhostPushButton (for mocking purpose)
*/

void GhostPushButton::press() {
  m_ghost_state = true;
}

void GhostPushButton::release() {
  m_ghost_state = false;
}

void GhostPushButton::begin() {
  release();
  m_state = m_ghost_state;
  m_time = millis();
  m_lastState = m_state;
  m_changed = false;
  m_lastChange = m_time;
}

bool GhostPushButton::readPinValue() {
  bool pinVal = m_ghost_state;
  if (m_invert) pinVal = !pinVal;
  return pinVal;
}
