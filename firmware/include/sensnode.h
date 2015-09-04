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
#include <stdlib.h>

//---------------------------------------------------------------------------
// Timing and power management
//---------------------------------------------------------------------------

/** Time units
 */
typedef enum {
  TICK = 0,    //!< Raw ticks (processor dependent)
  MICROSECOND, //!< 1/1000000 of a second
  MILLISECOND, //!< 1/1000 of a second
  SECOND,      //!< Whole seconds
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

/** Set the battery shutdown limit
 *
 * Set the ADC reading at which the battery level will trigger a shutdown. The
 * value at power up is 0 (which means never). The actual value will depend on
 * the power source connected and the type of battery. This is intended to
 * protect against draining LiION batteries to too low a level or to shutdown
 * if an unreliable power supply will impact sensor readings.
 *
 * @param level the ADC reading to shutdown at.
 */
void setBatteryLimit(uint16_t level);

/** Power down the device
 *
 * This function will completely power down the device. It is usually only
 * called in situations where continuing to operate would be dangerous or
 * possibly damage the sensor.
 */
void shutdown();

/** Delay the invocation of the application loop for a specified duration
 *
 * This function will block until the specified time period has elapsed but
 * background tasks (network operations, battery monitoring, etc) will continue.
 *
 * @param duration the amount of time to delay for
 * @param units the units the duration is specified in
 */
void delay(uint32_t duration, TIMEUNIT units);

/** Put the processor into sleep mode
 *
 * This function puts the CPU into sleep mode for the specified period of
 * time to conserve power. While the processor is sleeping other background
 * tasks (network operations, battery monitoring, etc) will also be paused.
 *
 * If the processor does not support sleep mode (or doesn't have an RTC to
 * trigger waking) this function will behave like the 'delay()' function.
 *
 * @param duration the amount of time to delay for
 * @param units the units the duration is specified in
 */
void sleep(uint32_t duration, TIMEUNIT units);

//---------------------------------------------------------------------------
// GPIO interface
//---------------------------------------------------------------------------

/** IO direction
 *
 * Direction of IO for digital pins.
 */
enum IODIR {
  INPUT,
  OUTPUT
  };

/** Analog pins
 *
 * Each board exposes up to 4 analog pins on the header. Additionally there is
 * the VBAT analog channel for reading the current battery status.
 */
enum ANALOG {
  PIN_A0 = 0, PIN_A1,
  PIN_A2, PIN_A3,
  PIN_VBAT // NOTE: VBAT is not exposed via headers
  };

/** Digital pins
 *
 * Each board exposes 8 digital pins on the header. There are also 4 extra
 * pins used internally for the action button, indicator LED, power switch
 * and power latching.
 */
enum DIGITAL {
  PIN_D0 = 0, PIN_D1, PIN_D2, PIN_D3,
  PIN_D4, PIN_D5, PIN_D6, PIN_D7,
  // These pins are used internally
  PIN_INDICATOR, PIN_ACTIVITY, PIN_LATCH, PIN_POWER
  };

/** PWM frequency
 *
 * The interface provides a single PWM output pin which may be configured
 * for different frequencies. The actual frequencies are defined by the board.
 */
enum FREQUENCY {
  SLOW = 0, NORMAL, FAST
  };

/** Initialise an analog pin
 *
 * This function configures an analog pin.
 *
 * @param pin the pin to configure
 *
 * @return true if the pin was configured as requested
 */
bool analogInit(int pin);

/** Read an analog value
 *
 * Reads a 16 bit value from the specified analog pin. If the physical ADC is
 * not capable of 16 bit resolution the results will be shifted so the
 * resolution available is represented in the most significant bits.
 *
 * @param pin the pin to read
 *
 * @return the resulting value scaled to a 16 bit resolution. If an error
 *         occurs or the pin has not been configured or is not available the
 *         value of 0 will be returned.
 */
uint16_t analogRead(int pin);

/** Initialise a pin for digital input or output
 *
 * @param pin the digital pin to configure
 * @param dir the direction of the pin (input or output)
 * @param pullup enable or disable the pull up resistor on the pin
 *
 * @return true if the pin was configured as requested, false if the pin is
 *         not available or could not be configured.
 */
bool digitalInit(int pin, IODIR dir, bool pullup = false);

/** Read the current value of the digital pin
 *
 * @param pin the digital pin to read
 *
 * @return true if the pin is currently 'high', false if 'low'
 */
bool digitalRead(int pin);

/** Write a value to the digital pin
 *
 * @param pin the digital pin to write
 * @param value the new value of the pin - true for 'high', false for 'low'
 */
void digitalWrite(int pin, bool value);

/** Initialise the PWM pin
 *
 * @param freq the frequency to run the PWM output at
 *
 * @return true if PWM is available, false if not.
 */
bool pwmInit(FREQUENCY freq);

/** Set the PWM duty cycle
 *
 * @param duty the duty cycle from 0 (always low) to 0xff (always on).
 */
void pwmDuty(uint8_t cycle);

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
    virtual bool init() = 0;

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
    virtual void writeBits(uint8_t address, uint32_t data, int count) = 0;

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
    virtual uint32_t readBits(uint8_t address, int count) = 0;

    /** Write a sequence of byte values to the i2c slave
    *
    * @param address the address of the slave device
    * @param pData pointer to a buffer containing the data to send
    * @param count the number of bytes to transmit
    */
    virtual void writeBytes(uint8_t address, const uint8_t *pData, int count) = 0;

    /** Read a sequence of bytes from the i2c slave
    *
    * @param address the address of the slave device
    * @param pData a pointer to a buffer to receive the data read
    * @param count the maximum number of bytes to read
    *
    * @return the number of bytes read from the slave.
    */
    virtual int readBytes(uint8_t address, uint8_t *pData, int count) = 0;
  };

// The primary I2C interface
extern I2C *i2c;

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
    virtual bool init(int mode = 0) = 0;

    /** Write a sequence of bytes to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pData the buffer containing the data to write
     * @param count the number of bytes to write
     */
    virtual void write(const uint8_t *pData, int count) = 0;

    /** Read a sequence of bytes from the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     * During the read the call will keep MOSI at 0.
     *
     * @param pData pointer to a buffer to receive the data
     * @param count the number of bytes to read.
     */
    virtual void read(uint8_t *pData, int count) = 0;

    /** Read and write to the SPI interface
     *
     * This method assumes the target device has been selected by the caller.
     *
     * @param pOutput a buffer containing the bytes to write to the SPI port
     * @param pInput a buffer to receive the bytes read from the SPI port
     * @param count the number of bytes to transfer. Both buffers must be at
     *        least this size.
     */
    virtual void readWrite(const uint8_t *pOutput, uint8_t *pInput, int count) = 0;
  };

// The primary SPI interface for the board (using D5 = MISO, D6 = MOSI, D7 = CLK)
extern SPI *spi;

/** Software SPI implementation
 *
 * This class provides a bit-banged implementation of the SPI interface on
 * arbitrary digital pins. It can be used with any driver that expects an
 * SPI interface.
 */
class SoftSPI : public SPI {
  private:
    int m_miso;
    int m_mosi;
    int m_sck;
    int         m_mode;

  public:
    /** Constructor
     *
     * Assign the pins to use for communication. The constructor will configure
     * the pins during initialisation.
     */
    SoftSPI(int miso, int mosi, int sck);

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
    virtual bool write(char ch) = 0;

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

/** Serial port interface
 *
 * The serial port extends the OutputStream to allow for reading data. A serial
 * port is not a standard feature on SensNode boards and not exposed by the
 * pin headers. Usually it is provided as a debugging feature only.
 */
class Serial : public OutputStream {
  public:
    /** Initialise the port with the specified baud rate.
     *
     * @param baud the baud rate to use.
     *
     * @return true if the port was configured correctly.
     */
    virtual bool init(int baud) = 0;

    /** Determine if data is available to read
     *
     * @return true if data is available to read.
     */
    virtual bool available() = 0;

    /** Read a single byte from the serial port
     *
     * @return the value of the byte read or -1 if no data is available.
     */
    virtual int read() = 0;

    /** Write a single character to the stream
     *
     * @param ch the character to write.
     *
     * @return true if the write was successful
     */
    virtual bool write(char ch) = 0;
  };

// The default serial port (may be NULL if not present)
extern Serial *serial;

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
void shiftOut(int data, int clock, int mode, uint32_t value, int bits);

/** Shift data in using a clocked transfer
 *
 * @param data the pin to use for the data transfer
 * @param clock the pin to use for the clock
 * @param mode the transfer mode (phase and polarity)
 * @param bits the number of bits to send
 *
 * @return the data value received
 */
uint32_t shiftIn(int data, int clock, int mode, int bits);

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
uint32_t shiftInOut(int in, int out, int clock, int mode, uint32_t value, int bits);

//---------------------------------------------------------------------------
// Debugging support
//---------------------------------------------------------------------------

// The debug output stream (may be NULL if not present)
extern OutputStream *debug;

#ifdef DEBUG
#  define DBG(msg) \
     if(debug) { debug->write("DEBUG: "); debug->write(msg); debug->write("\n"); }
#  define DBGX(msg, ...) \
     if(debug) { debug->write("DEBUG: "); fprintf(debug, msg, __VA_ARGS__); debug->write("\n"); }
#else
#  define DBG(msg)
#  define DBGX(msg, ...)
#endif

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
void setup();

/** User application loop
 *
 * The library repeatedly calls this function in an endless loop. The function
 * will generally be implemented as a state machine and take care to minimise
 * the amount of time spent in the function itself.
 */
void loop();

#endif /* __SENSNODE_H */

