/*!\file ArduinoPartsLed.cpp
** \author Sébastien Celles
** \date 2019/01/23
** \copyright MIT License (c) 2019, Sébastien Celles
** \brief Led handling library.
** \details Led handling library.
**			    This library was designed for Arduino boards
**/

#include "ArduinoPartsLed.h"

/*
Implementation of Led class
*/

void Led::begin(uint32_t ms) {
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

void Led::update(uint32_t ms) {
  // blink_task.update(ms);
}


/*
Implementation of BlinkTask class
*/

void BlinkTask::begin(uint32_t ms) {
  m_ms = ms;
  m_initial_lit_state = m_led.isLit();
}

void BlinkTask::schedule(uint32_t ms) {
  if (m_led.isLit()) {
    m_next_ms = ms + m_on_delay;
  } else {
    m_next_ms = ms + m_off_delay;
  }
}

void BlinkTask::start(uint8_t times, uint32_t on_delay, uint32_t off_delay) {
  if (!m_active) {
    m_on_delay = on_delay;
    m_off_delay = off_delay;
    m_times = times * 2;
    m_times_remaining = m_times;
    m_forever = times == 0;
    schedule(m_ms);
    m_active = true;
  }
}

void BlinkTask::start(uint32_t on_delay, uint32_t off_delay) {
  start(0, on_delay, off_delay);
}

void BlinkTask::stop() {
  Serial.println("stop");
  m_stop_request = true;
}

bool BlinkTask::isActive() {
  return m_active;
}

void BlinkTask::update(uint32_t ms) {
  m_ms = ms;
  bool terminated = false;
  if (m_active && (m_forever || m_times_remaining > 0)) {
    if (m_stop_request) {
      terminated = true;
    }
    if (m_ms >= m_next_ms) {
      m_led.toggle();
      if (!m_forever) {
        m_times_remaining -= 1;
        if (m_times_remaining == 0) {
          terminated = true;
        }
      }
      schedule(ms);
    }
  }

  if (terminated) {
    Serial.println("terminated");
    m_led.lit(m_initial_lit_state);
    m_stop_request = false;
    m_active = false;
  }
}
