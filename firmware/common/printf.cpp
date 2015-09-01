/*---------------------------------------------------------------------------*
* SensNode string formatting support
*----------------------------------------------------------------------------*
* 19-Nov-2014 ShaneG
*
* Implement the portable string formatting functions.
*---------------------------------------------------------------------------*/
#include <sensnode.h>
#include <stdarg.h>

//---------------------------------------------------------------------------
// Helper functions
//---------------------------------------------------------------------------

static char *g_buffer;
static int   g_length;
static int   g_index;

/** Extend OutputStream to write to a memory location
 */
class BufferOutputStream : public OutputStream {
  public:
    /** Write a single character to the stream
     *
     * @param ch the character to write.
     *
     * @return true if the write was successful
     */
    virtual bool write(char ch) {
      if(g_index==g_length)
        return false;
      g_buffer[g_index++] = ch;
      }

  };

// Share the single implementation
static BufferOutputStream g_output = BufferOutputStream();

/** Do the actual formatting
 *
 * This function uses the current two characters of the input string to
 * determine what to send to the serial port.
 *
 * @param pStream pointer to the output stream
 * @param ch1 the current character of the format string
 * @param ch2 the next character of the format string
 * @param args the argument list containing the embedded items
 *
 * @return true if both characters should be skipped, false if we only need
 *              to move ahead by one.
 */
static bool _printf(OutputStream *pStream, int& written, char ch1, char ch2, va_list *args) {
  bool skip = true;
  // Fail fast
  if(ch1=='%') {
    // Use the second character to determine what is requested
    if((ch2=='%')||(ch2=='\0')) {
      if(pStream->write('%'))
        written++;
      }
    else if(ch2=='c') {
      if(pStream->write(va_arg(*args, int)))
        written++;
      }
    else {
      switch(ch2) {
        case 'u':
          written += pStream->writeInt(va_arg(*args, unsigned int));
          break;
        case 'x':
          written += pStream->writeHex(va_arg(*args, unsigned int));
          break;
        case 's':
          written += pStream->write(va_arg(*args, char *));
          break;
        default:
          if(pStream->write(ch2))
            written++;
          break;
        }
      }
    }
  else {
    if(pStream.write(ch1))
      written++;
    skip = false;
    }
  return skip;
  }

//---------------------------------------------------------------------------
// Public API
//---------------------------------------------------------------------------


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
  va_list args;
  va_start(args, cszString);
  char ch1, ch2 = *cszString;
  int written = 0;
  for(int index=1; ch2!='\0'; index++) {
    ch1 = ch2;
    ch2 = cszString[index];
    if(_printf(pStream, written, ch1, ch2, &args)) {
      // Move ahead an extra character so we wind up jumping by two
      ch1 = ch2;
      ch2 = cszString[++index];
      }
    }
  va_end(args);
  }

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
int sprintf(char *szBuffer, int length, const char *cszString, ...) {
  g_buffer = szBuffer;
  g_length = length;
  g_index = 0;
  // TODO: Implement this
  return 0;
  }

