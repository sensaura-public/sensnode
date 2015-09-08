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

/** Digital interface for the I2C version of the MCP23008 expander
 *
 * Provides access to the 8 digital pins of the IO expander through the standard
 * digital interface.
 */
class MCP23008 : public Digital {
  private:
    I2C    *m_i2c;     // The I2C interface to use
    uint8_t m_address; // Slave address of the expander

  public:
    /** Constructor
     *
     * The constructor specifies the communication devices to use to talk to
     * the target chip. No significant initialisation is done.
     *
     * @param i2c the I2C interface to use to communicate with the chip
     * @param address the address of the target device.
     */
    MCP23008(I2C *i2c, uint8_t address);

    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init();

    /** Determine the number of pins available
     *
     * @return the number of pins supported by the interface.
     */
    virtual int pins();

    /** Initialise a pin for digital input or output
     *
     * @param pin the digital pin to configure
     * @param dir the direction of the pin (input or output)
     * @param pullup enable or disable the pull up resistor on the pin
     *
     * @return true if the pin was configured as requested, false if the pin is
     *         not available or could not be configured.
     */
    virtual bool init(int pin, IODIR dir, bool pullup = false);

    /** Read the current value of the digital pin
     *
     * @param pin the digital pin to read
     *
     * @return true if the pin is currently 'high', false if 'low'
     */
    virtual bool read(int pin);

    /** Write a value to the digital pin
     *
     * @param pin the digital pin to write
     * @param value the new value of the pin - true for 'high', false for 'low'
     */
    virtual void write(int pin, bool value);
  };

/** Digital interface for the SPI version of the MCP23S08 expander
 *
 * Provides access to the 8 digital pins of the IO expander through the standard
 * digital interface.
 */
class MCP23S08 : public Digital {
  private:
    SPI     *m_spi;     // The SPI interface to use
    Digital *m_digital; // The digital interface for the select pin
    int      m_select;  // The select pin to use for the chip

  public:
    /** Constructor
     *
     * The constructor specifies the communication devices to use to talk to
     * the target chip. No significant initialisation is done.
     *
     * @param spi the SPI interface used to communicate with the device
     * @param digital the Digital interface used to control the select pin
     * @param select the pin number to use for device selection
     */
    MCP23S08(SPI *spi, Digital *digital, int select);

    /** Initialise the digital pin interface
     *
     * Configure the interface prior to use. Note that the core implementations
     * are initialised at start up and do not require explicit initialisation by
     * the application.
     *
     * @return true if the initialise succeeded.
     */
    virtual bool init();

    /** Determine the number of pins available
     *
     * @return the number of pins supported by the interface.
     */
    virtual int pins();

    /** Initialise a pin for digital input or output
     *
     * @param pin the digital pin to configure
     * @param dir the direction of the pin (input or output)
     * @param pullup enable or disable the pull up resistor on the pin
     *
     * @return true if the pin was configured as requested, false if the pin is
     *         not available or could not be configured.
     */
    virtual bool init(int pin, IODIR dir, bool pullup = false);

    /** Read the current value of the digital pin
     *
     * @param pin the digital pin to read
     *
     * @return true if the pin is currently 'high', false if 'low'
     */
    virtual bool read(int pin);

    /** Write a value to the digital pin
     *
     * @param pin the digital pin to write
     * @param value the new value of the pin - true for 'high', false for 'low'
     */
    virtual void write(int pin, bool value);
  };

#endif /* __MCP23008_H */

