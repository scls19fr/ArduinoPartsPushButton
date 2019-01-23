/*!\file ArduinoPartsPushButton.h
** \author Sébastien Celles
** \date 2019/01/23
** \copyright MIT License (c) 2019, Sébastien Celles
** \brief PushButton handling library.
** \details PushButton handling library.
**          Debounce push button, detect presses, releases, and long presses
**			    This library was designed for Arduino boards
**/

#ifndef ARDUINO_PARTS_PUSHBUTTON
#define ARDUINO_PARTS_PUSHBUTTON

#include <Arduino.h>


/*!	\brief Default debounce time
**/
#define PB_DEBOUNCE_TIME_DEFAULT 25


/*!	\brief Default pullup enabled (true)
**/
#define PB_PULLUP_ENABLED_DEFAULT true

/*!	\brief Default invert (true) ie interpret a low logic level as pressed
**/
#define PB_INVERT_DEFAULT true

/*!	\brief Abstract class for push button
**/
class AbstractPushButton {
  public:
    /*!	\brief AbstractPushButton constructor
    **	\param [in] pin - The Arduino pin the button is connected to

    **	\param [in] debounceTime - Debounce time in milliseconds (default 25ms)
    **	\param [in] pullupEnabled - true to enable the AVR internal pullup resistor (default true)
    **	\param [in] invert - true to interpret a low logic level as pressed (default true)

    **	\return nothing
    **/
    AbstractPushButton(uint8_t pin, uint32_t debounceTime=PB_DEBOUNCE_TIME_DEFAULT, uint8_t pullupEnabled=PB_PULLUP_ENABLED_DEFAULT, uint8_t invert=PB_INVERT_DEFAULT)
        : m_pin(pin), m_debounceTime(debounceTime), m_pullupEnabled(pullupEnabled), m_invert(invert) {}

    /*!	\brief Get the current debounced button state.
    **  \retval true for pressed
    **  \retval false for released
    **  \warning Call this function frequently to ensure
    **           the sketch is responsive to user input.
    **/
    bool read();

    /*!	\brief Get pressed state of the push button (at the last call to read()).
    **  \return pressed state of the push button
    **  \retval true if the button state was pressed at the last call to read().
    **  \retval false if the button state wasn't pressed at the last call to read().
    **  \warning Does not cause the button to be read.
    **/
    bool isPressed();

    /*!	\brief Get released state of the push button (at the last call to read()).
    **  \return released state of the push button
    **  \retval true if the button state was released at the last call to read().
    **  \retval false if the button state wasn't released at the last call to read().
    **  \warning Does not cause the button to be read.
    **/
    bool isReleased();

    /*!	\brief Get pressed state of the push button (and it was released previously)
    **  \retval true if the button state at the last call to read() was pressed,
    **          and this was a change since the previous read.
    **  \retval false otherwise
    **/
    bool wasPressed();

    /*!	\brief Get released state of the push button (and it was pressed previously)
    **  \retval true if the button state at the last call to read() was released,
    **          and this was a change since the previous read.
    **  \retval false otherwise
    **/
    bool wasReleased();

    /*! \brief Check to see if the button is pressed and has been in that state 
    **         for a specified time
    **	\param [in] ms - duration (milliseconds)
    **  \retval true if the button state at the last call to read() was pressed,
    **          and has been in that state for at least the given number of milliseconds.
    **  \retval false otherwise
    **/
    bool pressedFor(uint32_t ms);

    /*! \brief Check to see if the button is released and has been in that state 
    **         for a specified time
    **	\param [in] ms - duration (milliseconds)
    **  \retval true if the button state at the last call to read() was released,
    **          and has been in that state for at least the given number of milliseconds.
    **  \retval false otherwise
    **/
    bool releasedFor(uint32_t ms);

    /*! \brief get the time the button last changed state
    **  \return the time in milliseconds (from millis) that the button last
    **          changed state.
    **/
    uint32_t lastChange();

  protected:
    uint8_t m_pin;           //!<  arduino pin number connected to button
    uint32_t m_debounceTime; //!<  debounce time (ms)
    bool m_pullupEnabled;    //!<  internal pullup resistor enabled (or not)
    bool m_invert;           //!<  if true, interpret logic low as pressed, else interpret logic high as pressed
    bool m_state;            //!<  current button state, true=pressed
    bool m_lastState;        //!<  previous button state
    bool m_changed;          //!<  state changed since last read
    uint32_t m_time;         //!<  time of current state (ms from millis)
    uint32_t m_lastChange;   //!<  time of last state change (ms)
  
  private:
    /*! \brief get the value of pin on which button is connected
    **  \return the boolean value.
    **/
    virtual bool readPinValue() = 0;
};

/*!	\brief PushButton class
**/
class PushButton: public AbstractPushButton {
  public:
    /*!	\brief PushButton constructor
    **	\param [in] pin - The Arduino pin the button is connected to

    **	\param [in] debounceTime - Debounce time in milliseconds (default 25ms)
    **	\param [in] pullupEnabled - true to enable the AVR internal pullup resistor (default true)
    **	\param [in] invert - true to interpret a low logic level as pressed (default true)

    **	\return nothing
    **/
    PushButton(uint8_t pin, uint32_t debounceTime=PB_DEBOUNCE_TIME_DEFAULT, uint8_t pullupEnabled=PB_PULLUP_ENABLED_DEFAULT, uint8_t invert=PB_INVERT_DEFAULT)
        : AbstractPushButton(pin, debounceTime, pullupEnabled, invert) {}

    /*!	\brief Initialize a PushButton object
    **  \warning The pin it's connected to is also initialized 
    **/
    void begin();

  private:
    bool readPinValue();
};

/*!	\brief PushButton class for tests / mocking purpose
**/
class GhostPushButton: public AbstractPushButton {
  public:
    /*!	\brief GhostPushButton constructor (for tests / mocking purpose)
    **	\param [in] pin - The Arduino pin the button is connected to

    **	\param [in] debounceTime - Debounce time in milliseconds (default 25ms)
    **	\param [in] pullupEnabled - true to enable the AVR internal pullup resistor (default true)
    **	\param [in] invert - true to interpret a low logic level as pressed (default true)

    **	\return nothing
    **/
    GhostPushButton(uint8_t pin, uint32_t debounceTime=PB_DEBOUNCE_TIME_DEFAULT, uint8_t pullupEnabled=PB_PULLUP_ENABLED_DEFAULT, uint8_t invert=PB_INVERT_DEFAULT)
        : AbstractPushButton(pin, debounceTime, pullupEnabled, invert) {}

    /*!	\brief Initialize a GhostPushButton object
    **  \warning The pin it's connected is not initialized as it's only for mocking purpose
    **/
    void begin();

    /*!	\brief Press (virtually) push button
    **/
    void press();

    /*!	\brief Release (virtually) push button
    **/
    void release();
  
  private:
    bool m_ghost_state;   //!<  current button state for ghost mode, true=pressed

    bool readPinValue();

};

#endif
