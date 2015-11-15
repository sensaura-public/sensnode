/*--------------------------------------------------------------------------*
* MCP23008/MSC23S08 Driver Interface
*---------------------------------------------------------------------------*
* 08-Sep-2015 ShaneG
*
* Provides a Digital interface using the 8 bit Microchip IO expanders.
*---------------------------------------------------------------------------*/
#ifndef __MCP23008_H
#define __MCP23008_H

// Bring in required definitions
#include <sensnode.h>

class MCP23X08 {
  public:
    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init() = 0;

    /** Configure a GPIO pin
     *
     * @param pin the pin to configure
     * @param mode the requested mode for the pin
     * @param flags optional flags for the pin.
     *
     * @return true if the pin was configured as requested.
     */
    virtual bool pinConfig(uint8_t pin, PIN_MODE mode, uint8_t flags) = 0;

    /** Read the value of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_INPUT. If the pin
     * was configured for a different mode the result will always be false.
     *
     * @param pin the pin to read
     *
     * @return the current state of the pin.
     */
    virtual bool pinRead(uint8_t pin) = 0;

    /** Change the state of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_OUTPUT. If the
     * pin was configured for a different mode the function will have no effect.
     *
     * @param pin the pin to change the state of
     * @param value the value to set the pin to (true = high, false = low)
     */
    virtual void pinWrite(uint8_t pin, bool value) = 0;
  }

/** Digital interface for the I2C version of the MCP23008 expander
 *
 * Provides access to the 8 digital pins of the IO expander through the standard
 * digital interface.
 */
class MCP23008 : public MCP23X08 {
  private:
    uint8_t m_address; // Slave address of the expander

  public:
    /** Constructor
     *
     * The constructor specifies the communication devices to use to talk to
     * the target chip. No significant initialisation is done.
     *
     * @param address the address of the target device.
     */
    MCP23008(uint8_t address);

    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init();

    /** Configure a GPIO pin
     *
     * @param pin the pin to configure
     * @param mode the requested mode for the pin
     * @param flags optional flags for the pin.
     *
     * @return true if the pin was configured as requested.
     */
    virtual bool pinConfig(uint8_t pin, PIN_MODE mode, uint8_t flags);

    /** Read the value of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_INPUT. If the pin
     * was configured for a different mode the result will always be false.
     *
     * @param pin the pin to read
     *
     * @return the current state of the pin.
     */
    virtual bool pinRead(uint8_t pin);

    /** Change the state of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_OUTPUT. If the
     * pin was configured for a different mode the function will have no effect.
     *
     * @param pin the pin to change the state of
     * @param value the value to set the pin to (true = high, false = low)
     */
    virtual void pinWrite(uint8_t pin, bool value);
  };

/** Digital interface for the SPI version of the MCP23S08 expander
 *
 * Provides access to the 8 digital pins of the IO expander through the standard
 * digital interface.
 */
class MCP23S08 : public MCP23X08 {
  private:
    PIN m_select;  // The select pin to use for the chip

  public:
    /** Constructor
     *
     * The constructor specifies the communication devices to use to talk to
     * the target chip. No significant initialisation is done.
     *
     * @param select the pin number to use for device selection
     */
    MCP23S08(PIN select);

    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init();

    /** Configure a GPIO pin
     *
     * @param pin the pin to configure
     * @param mode the requested mode for the pin
     * @param flags optional flags for the pin.
     *
     * @return true if the pin was configured as requested.
     */
    virtual bool pinConfig(uint8_t pin, PIN_MODE mode, uint8_t flags);

    /** Read the value of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_INPUT. If the pin
     * was configured for a different mode the result will always be false.
     *
     * @param pin the pin to read
     *
     * @return the current state of the pin.
     */
    virtual bool pinRead(uint8_t pin);

    /** Change the state of a digital pin.
     *
     * To use this function the pin must be configured as DIGITAL_OUTPUT. If the
     * pin was configured for a different mode the function will have no effect.
     *
     * @param pin the pin to change the state of
     * @param value the value to set the pin to (true = high, false = low)
     */
    virtual void pinWrite(uint8_t pin, bool value);
  };

#endif /* __MCP23008_H */

