/*--------------------------------------------------------------------------*
* SensNode Core Library
*---------------------------------------------------------------------------*
* 31-Aug-2015 ShaneG
*
* Defines a common set of functions and structures to use with SensNode
* compatible boards. Although not mandatory to use for SensNode development
* the goal is to make it easy to switch between boards and have a common API.
---------------------------------------------------------------------------*/
#ifndef __SENSNODE_H
#define __SENSNODE_H

// Bring in required definitions
#include <stdint.h>

//---------------------------------------------------------------------------
// Timing
//---------------------------------------------------------------------------

/** Time units
 */
typedef enum {
  TICK        = 0, //!< Raw ticks (processor dependent)
  MICROSECOND = 1, //!< 1/1000000 of a second
  MILLISECOND = 2, //!< 1/1000 of a second
  SECOND      = 3, //!< Whole seconds
  } TIMEUNIT;

/** Get the current system tick count
 *
 * Each processor board maintains a count of system ticks since power up, this
 * function returns the current value of that count. The duration of a single
 * tick is processor independent - use the 'timeExpired()' function to determine
 * if a time period has been exceeded or 'timeElapsed()' to determine the
 * amount of time between two tick counts.
 *
 * @return the current system tick count.
 */
uint32_t getTicks();

/** Calculate the time difference between two tick counts.
 *
 * This function will convert the difference between two tick count values into
 * an actualy time period. Tick count wrap around is accounted for. The return
 * value is the number of whole units rounded down.
 *
 * @param start the tick count at the start of the period
 * @param end the tick count at the end of the period
 * @param units the time units to calculate the difference in.
 *
 * @return the amount of elapsed time in whole units.
 */
uint32_t timeElapsed(uint32_t start, uint32_t end, TIMEUNIT units);

/** Determine if the specified amount of time has expired.
 *
 * This function compares the current tick count with a previously stored
 * start point and determines if the requested amount of time has expired
 * yet.
 *
 * @param reference the starting reference
 * @param duration the time period we are waiting to expire
 * @param units the units the duration is expressed in
 *
 * @return true if the specified duration has expired since the reference
 *              point.
 */
bool timeExpired(uint32_t reference, uint32_t duration, TIMEUNIT units);

//---------------------------------------------------------------------------
// GPIO interface
//---------------------------------------------------------------------------

/** IO direction
 */
enum IODIR {
	INPUT,
	OUTPUT
};

/** Analog pins
 */
enum ANALOG_PIN {
	A0 = 0,
	A1,
	A2,  // NOTE: A2 and A3 are preferred outputs, may not support input
	A3,
	VBAT // NOTE: VBAT is not exposed via headers
};

/** Digital pins
 */
enum DIGITAL_PIN {
	D0 = 0,
	D1,
	D2,
	D3,
	D4,
	D5,
	D6,
	D7,
	D8, // NOTE: D8 -> D11 are not exposed via headers
	D9,
	D10,
	D11
};

/** Initialise an analog pin
 *
 * This function configures an analog pin for input or output (PWM). The
 * function will fail if the pin is not available or does not support the
 * requested direction.
 *
 * @param pin the pin to configure
 * @param dir the direction of the pin (input or output)
 *
 * @return true if the pin was configured as requested
 */
bool analogInit(ANALOG_PIN pin, IODIR dir);

/** Read an analog value
 *
 * Reads a 16 bit value from the specified analog pin. If the physical ADC is
 * not capable of 16 bit resolution the results will be shifted so the
 * resolution available is represented in the most significant bits.
 *
 * @param pin the pin to read
 * @param skip the number of samples to skip before averaging.
 * @param average the number of samples to average into the result. This must
 *        be at least 1 (for no averaging).
 *
 * @return the resulting value scaled to a 16 bit resolution. If an error
 *         occurs or the pin has not been configured or is not available the
 *         value of 0 will be returned.
 */
uint16_t analogRead(ANALOG_PIN pin, int skip, int average);

/** Write an analog value
 *
 * This function adjusts the PWM output on the analog pin to the specified
 * value. The duty cycle is scaled from 0 (value = 0) to 100% (value = 0xffff).
 *
 * @param pin the pin to write to
 * @param value the value to output
 */
void analogWrite(ANALOG_PIN pin, uint16_t value);

/** Initialise a pin for digital input or output
 *
 * @param pin the digital pin to configure
 * @param dir the direction of the pin (input or output)
 * @param pullup enable or disable the pull up resistor on the pin
 *
 * @return true if the pin was configured as requested, false if the pin is
 *         not available or could not be configured.
 */
bool digitalInit(DIGITAL_PIN pin, IODIR dir, bool pullup);

/** Read the current value of the digital pin
 *
 * @param pin the digital pin to read
 *
 * @return true if the pin is currently 'high', false if 'low'
 */
bool digitalRead(DIGITAL_PIN pin);

/** Write a value to the digital pin
 *
 * @param pin the digital pin to write
 * @param value the new value of the pin - true for 'high', false for 'low'
 */
void digitalWrite(DIGITAL_PIN pin, bool value);

//---------------------------------------------------------------------------
// I2C Operations
//
// Each board provides a primary I2C interface on D7/D6 (SDA/SCL) which is
// accessed through the 'i2c' global instance. When I2C is used those pins
// may no longer be used as general digital IO.
//---------------------------------------------------------------------------

/** I2C interface
 *
 * An implementation that uses the hardware interface on the process is
 * provided in the global variable 'i2c'. Additional interfaces may also be
 * exposed including 'bit banging' implementations.
 *
 * Drivers that use the I2C interface should take a reference to this class
 * rather than use the global instance to allow them to be attached to
 * alternative implementations.
 */
class I2C {
  public:
    /** Initialise the I2C interface
    *
    * @return true if the interface was initialise.
    */
    virtual bool init();

    /** Write a bit stream to the I2C device
    *
    * This function is used to send a sequence of bits to the i2c slave device
    * identified by the address.
    *
    * @param address the address of the slave device
    * @param data the data to send, the lowest 'count' bits will be sent in
    *             MSB order.
    * @param count the number of bits to write.
    */
    virtual void writeBits(uint8_t address, uint32_t data, int count);

    /** Read a bit stream from the I2C device
    *
    * This function is used to read a sequence of bits from the i2c slave
    * identified by the address.
    *
    * @param address the address of the slave device
    * @param count the number of bits to read
    *
    * @return a 32 bit value containing the bits read in the least significant
    *         bits.
    */
    virtual uint32_t readBits(uint8_t address, int count);

    /** Write a sequence of byte values to the i2c slave
    *
    * @param address the address of the slave device
    * @param pData pointer to a buffer containing the data to send
    * @param count the number of bytes to transmit
    */
    virtual void writeBytes(uint8_t address, const uint8_t *pData, int count);

    /** Read a sequence of bytes from the i2c slave
    *
    * @param address the address of the slave device
    * @param pData a pointer to a buffer to receive the data read
    * @param count the maximum number of bytes to read
    *
    * @return the number of bytes read from the slave.
    */
    virtual int readBytes(uint8_t address, uint8_t *pData, int count);
  };

// The primary I2C interface
extern I2C i2c;

//---------------------------------------------------------------------------
// SPI Operations
//
// Each board provides a primary SPI interface on D5, D4 & D3 (MISO, MOSI & SCK)
// which is accessed through the 'spi' global instance. When SPI is used those
// pins may no longer be used as general digital IO.
//---------------------------------------------------------------------------

// Bit masks for SPI transfer modes
#define MSB_FIRST     0x04
#define LSB_FIRST     0x00
#define POLARITY_HIGH 0x02
#define POLARITY_LOW  0x00
#define PHASE_HIGH    0x01
#define PHASE_LOW     0x00

/** SPI interface
 *
 * An implementation that uses the hardware interface on the processor is
 * provided in the global variable 'spi'. Additional interfaces may also be
 * exposed including 'bit banging' implementations.
 *
 * Drivers that use the SPI interface should take a reference to this class
 * rather than use the global instance to allow them to be attached to
 * alternative implementations.
 */
class SPI {
  public:
    /** Initialise the SPI interface with the specific mode
     *
     * This method may be called multiple times to change the operating mode.
     * The mode values supported are:
     *
     * Mode CPOL CPHA
     *  0    0    0
     *  1    0    1
     *  2    1    0
     *  3    1    1
     */
    virtual bool init(int mode = 0);

    /** Write a sequence of bytes to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pData the buffer containing the data to write
     * @param count the number of bytes to write
     */
    virtual void write(const uint8_t *pData, int count);

    /** Read a sequence of bytes from the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     * During the read the call will keep MOSI at 0.
     *
     * @param pData pointer to a buffer to receive the data
     * @param count the number of bytes to read.
     */
    virtual void read(uint8_t *pData, int count);

    /** Read and write to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pOutput a buffer containing the bytes to write to the SPI port
     * @param pInput a buffer to receive the bytes read from the SPI port
     * @param count the number of bytes to transfer. Both buffers must be at
     *        least this size.
     */
    virtual void readWrite(const uint8_t *pOutput, uint8_t *pInput, int count);
  };

// The primary SPI interface for the board (using D5 = MISO, D6 = MOSI, D7 = CLK)
extern SPI spi;

/** Software SPI implementation
 *
 * This class provides a bit-banged implementation of the SPI interface on
 * arbitrary digital pins. It can be used with any driver that expects an
 * SPI interface.
 */
class SoftSPI : public SPI {
  private:
    DIGITAL_PIN m_miso;
    DIGITAL_PIN m_mosi;
    DIGITAL_PIN m_sck;
    int         m_mode;

  public:
    /** Constructor
     *
     * Assign the pins to use for communication. The constructor will configure
     * the pins during initialisation.
     */
    SoftSPI(DIGITAL_PIN miso, DIGITAL_PIN mosi, DIGITAL_PIN sck);

    /** Initialise the SPI interface with the specific mode
     *
     * This method may be called multiple times to change the operating mode.
     * The mode values supported are:
     *
     * Mode CPOL CPHA
     *  0    0    0
     *  1    0    1
     *  2    1    0
     *  3    1    1
     */
    virtual bool init(int mode = 0);

    /** Write a sequence of bytes to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pData the buffer containing the data to write
     * @param count the number of bytes to write
     */
    virtual void write(const uint8_t *pData, int count);

    /** Read a sequence of bytes from the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     * During the read the call will keep MOSI at 0.
     *
     * @param pData pointer to a buffer to receive the data
     * @param count the number of bytes to read.
     */
    virtual void read(uint8_t *pData, int count);

    /** Read and write to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pOutput a buffer containing the bytes to write to the SPI port
     * @param pInput a buffer to receive the bytes read from the SPI port
     * @param count the number of bytes to transfer. Both buffers must be at
     *        least this size.
     */
    virtual void readWrite(const uint8_t *pOutput, uint8_t *pInput, int count);
  };

//---------------------------------------------------------------------------
// Helper functions and classes
//---------------------------------------------------------------------------

/** A simple stream interface to write data
 */
class OutputStream {
  public:
    /** Write a single character to the stream
     *
     * @param ch the character to write.
     *
     * @return true if the write was successful
     */
    virtual bool write(char ch);

    /** Write a sequence of bytes to the ouput stream
     *
     * @param cszString pointer to the buffer containing the data to write
     * @param length the number of bytes to write. If this is less than zero
     *               the string is assumed to be NUL terminated.
     *
     * @return the number of bytes written. This may be less than requested.
     */
    int write(const char *cszString, int length = -1);

    /** Write a numeric value in hex
     *
     * @param value the value to write
     * @param digits the minimum number of digits to use.
     *
     * @return the number of characters written
     */
    int writeHex(uint32_t value, int digits = 0);

    /** Write a numeric value in decimal
     *
     * @param value the value to write
     *
     * @return the number of characters written
     */
    int writeInt(uint32_t value);
  };

/** Print a formatted string
 *
 * This function supports a subset of the 'printf' string formatting syntax.
 * Allowable insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 16 bit value.
 *  %U - Display an unsigned integer in decimal. The matching argument may
 *       be any 32 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 16 bit value.
 *  %X - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 32 bit value.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *
 * @param pStream pointer to the output stream to write to
 * @param cszString pointer to a nul terminated format string.
 *
 * @return the number of character actually printed.
 */
int fprintf(OutputStream *pStream, const char *cszString, ...);

/** Print a formatted string
 *
 * This function supports a subset of the 'printf' string formatting syntax.
 * Allowable insertion types are:
 *
 *  %% - Display a % character. There should be no entry in the variable
 *       argument list for this entry.
 *  %u - Display an unsigned integer in decimal. The matching argument may
 *       be any 32 bit value.
 *  %x - Display an unsigned integer in hexadecimal. The matching argument may
 *       be any 32 bit value.
 *  %b - Display a single byte in hexadecimal.
 *  %c - Display a single ASCII character. The matching argument may be any 8
 *       bit value.
 *  %s - Display a NUL terminated string from RAM. The matching argument must
 *       be a pointer to a RAM location.
 *
 * @param szBuffer pointer to the buffer to place the string in
 * @param length the size of the buffer.
 * @param cszString pointer to a nul terminated format string in RAM.
 *
 * @return the number of characters (excluding the terminating NUL) that
 *         were written. If this value is equal to length the resulting
 *         string will not be NUL terminated.
 */
int sprintf(char *szBuffer, int length, const char *cszString, ...);

/** Initialise the CRC calculation
 *
 * Initialises the CRC value prior to processing data.
 *
 * @return the initial CRC value.
 */
uint16_t crcInit();

/** Update the CRC value with an additional data byte.
 *
 * @param crc the current CRC value
 * @param data the data byte to add to the calculation
 *
 * @return the updated CRC value.
 */
uint16_t crcByte(uint16_t crc, uint8_t data);

/** Add a sequence of bytes from a buffer.
 *
 * @param crc the current CRC value
 * @param pData pointer to the memory buffer
 * @param length the number of bytes to process.
 *
 * @return the updated CRC value.
 */
uint16_t crcData(uint16_t crc, const uint8_t *pData, int length);

/** Shift data out using clocked transfer
 *
 * @param data the pin to use for the data transfer
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param value the value to send
 * @param bits the number of bits to send
 */
void shiftOut(DIGITAL_PIN data, DIGITAL_PIN clock, int mode, uint32_t value, int bits);

/** Shift data in using a clocked transfer
 *
 * @param data the pin to use for the data transfer
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param bits the number of bits to send
 *
 * @return the data value received
 */
uint32_t shiftIn(DIGITAL_PIN data, DIGITAL_PIN clock, int mode, int bits);

/** Exchange data in using a clocked transfer
 *
 * @param in the pin to use for input data
 * @param out the pin to use for output data
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param value the value to send
 * @param bits the number of bits to send
 *
 * @return the data value received
 */
uint32_t shiftInOut(DIGITAL_PIN in, DIGITAL_PIN out, DIGITAL_PIN clock, int mode, uint32_t value, int bits);

//---------------------------------------------------------------------------
// Application interface
//---------------------------------------------------------------------------

/** User application initialisation
 *
 * The library will call this function once at startup to allow the user
 * application to do any initialisation it needs. At the time this function
 * is called all IO pins will have been set to their default states and the
 * network subsystem initialised (if not yet connected).
 */
void init();

/** User application loop
 *
 * The library repeatedly calls this function in an endless loop. The function
 * will generally be implemented as a state machine and take care to minimise
 * the amount of time spent in the function itself.
 */
void loop();

#endif /* __SENSNODE_H */

