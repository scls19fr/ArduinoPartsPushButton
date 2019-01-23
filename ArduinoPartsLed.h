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
    void begin();

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
    void update();

    /*!	\brief Blink led a given number of times
    **	\param [in] times - number of times led should blink
    **	\param [in] on_delay - on delay (milliseconds)
    **	\param [in] off_delay - off delay (milliseconds)
    **/
    void blink(uint8_t times, uint32_t on_delay, uint32_t off_delay);

    /*!	\brief Blink led forever (until stopped)
    **	\param [in] on_delay - on delay (milliseconds)
    **	\param [in] off_delay - off delay (milliseconds)
    **/
    void blinkForever(uint32_t on_delay, uint32_t off_delay);

    /*!	\return true is led is blinking
    **/
    bool isBlinking();

    /*!	\brief Stop blinking
    **/
    void stop();

  private:
    uint8_t m_pin;     //!<  arduino pin number connected to led
    bool m_lit_state;  //!<  if true, interpret logic low as pressed, else interpret logic high as pressed
    bool m_state;      //!<  current led state, true=led on false=led off
};

#endif
