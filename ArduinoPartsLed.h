/*!\file ArduinoPartsLed.h
** \author Sébastien Celles
** \date 2019/01/23
** \copyright MIT License (c) 2019, Sébastien Celles
** \brief Led handling library.
** \details Led handling library.
**			    This library was designed for Arduino boards
**/

#ifndef ARDUINO_PARTS_LED
#define ARDUINO_PARTS_LED

#include <Arduino.h>

/*!	\brief Default lit state (true)
**/
#define LED_LIT_STATE_DEFAULT true

/*!	\brief Light emitting diode
**/
class Led {
  public:
    /*!	\brief Led constructor
    **	\param [in] pin - The Arduino pin the led is connected to
    **	\param [in] lit_state - false to turn on led by bringing cathode to low state. (default true)
    **	\return nothing
    **/
    Led(uint8_t pin, uint8_t lit_state=LED_LIT_STATE_DEFAULT)
        : m_pin(pin), m_lit_state(lit_state) {}

    /*!	\brief Initialize a PushButton object
    **  \warning The pin it's connected to is also initialized 
    **/
    void begin(uint32_t ms);

    /*!	\brief Switch on led
    **/
    void on();

    /*!	\brief Switch off led
    **/
    void off();

    /*!	\brief Toggle led
    **/
    void toggle();

    /*!	\brief Switch on or off led according state
    **	\param [in] state - state=false (off) state=true (on)
    **/
    void lit(bool state);

    /*!	\brief Get led state (on or off)
    **  \retval true if the led is on
    **  \retval false if the led is off
    **/
    bool isLit();

    /*!	\brief Set physically Led state according internal state
    **/
    void update(uint32_t ms);

  private:
    uint8_t m_pin;     //!<  arduino pin number connected to led
    bool m_lit_state;  //!<  if true, interpret logic low as pressed, else interpret logic high as pressed
    bool m_state;      //!<  current led state, true=led on false=led off
};

/*!	\brief Blink task
**/
class BlinkTask {
  public:
    /*!	\brief BlinkTask constructor
    **/
    BlinkTask(const Led &led)
        : m_led(led), m_initial_lit_state(false),
        m_active(false), m_stop_request(false),
        m_times(0), m_times_remaining(0), m_forever(false),
        m_on_delay(0), m_off_delay(0), 
        m_ms(0), m_next_ms(0) {}

    /*!	\brief Initialize a BlinkTask object
    **/
    void begin(uint32_t ms);

    /*!	\brief Start blinking a given number of times
    **/
    void start(uint8_t times, uint32_t on_delay, uint32_t off_delay);

    /*!	\brief Start blinking forever
    **/
    void start(uint32_t on_delay, uint32_t off_delay);

    /*!	\brief Stop blinking
    **/
    void stop();

    /*!	\return true if task is active
    **/
    bool isActive();

    /*!	\brief Update BlinkTask
    **/
    void update(uint32_t ms);

  private:
    Led m_led;

    bool m_initial_lit_state;

    bool m_active;  //!<  active state
    bool m_stop_request;  //!<  stop request

    uint8_t m_times;  //!<  number of times it should blink
    uint8_t m_times_remaining;  //!<  number of times it should blink
    bool m_forever;  //!<  blinking state

    uint32_t m_on_delay;
    uint32_t m_off_delay;

    uint32_t m_ms;
    uint32_t m_next_ms;
    void schedule(uint32_t ms);
};

#endif
