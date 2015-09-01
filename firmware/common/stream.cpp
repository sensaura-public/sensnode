/*---------------------------------------------------------------------------*
* SensNode output stream support
*----------------------------------------------------------------------------*
* 01-Sep-2015 ShaneG
*
* Implementation of the basic output stream implementation.
*---------------------------------------------------------------------------*/
#include <sensnode.h>

/** Write a single character to the stream
 *
 * @param ch the character to write.
 *
 * @return true if the write was successful
 */
bool OutputStream::write(char ch) {
  return false;
  }

/** Write a sequence of bytes to the ouput stream
 *
 * @param cszString pointer to the buffer containing the data to write
 * @param length the number of bytes to write. If this is less than zero
 *               the string is assumed to be NUL terminated.
 *
 * @return the number of bytes written. This may be less than requested.
 */
int OutputStream::write(const char *cszString, int length) {
  int index, count = 0;
  if(length < 0) {
    for(index=0; cszString[index]; index++) {
      if(write(cszString[index]))
        count++;
      }
    }
  else {
    for(index=0; index<length; index++) {
      if(write(cszString[index]))
        count++;
      }
    }
  return count
  }

/** Write a numeric value in hex
 *
 * @param value the value to write
 * @param digits the minimum number of digits to use.
 *
 * @return the number of characters written
 */
int OutputStream::writeHex(uint32_t value, int digits) {
  // TODO: Implement this
  }

/** Write a numeric value in decimal
 *
 * @param value the value to write
 *
 * @return the number of characters written
 */
int OutputStream::writeInt(uint32_t value) {
  bool emit = false;
  // Special case for 0
  if(value==0) {
    write('0');
    return;
    }
  // Emit the value, skip leading zeros
  for(uint16_t divisor = 10000; divisor > 0; divisor = divisor / 10) {
    uint8_t digit = value / divisor;
    value = value % divisor;
    if((digit>0)||emit) {
      write('0' + digit);
      emit = true;
      }
    }
  }

