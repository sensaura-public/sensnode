/*---------------------------------------------------------------------------*
* SensNode - System initialisation for XMC1100
*----------------------------------------------------------------------------*
* 30-Oct-2015 ShaneG
*
* This code performs the system initialisation required for the XMC1100. As
* well as setting up the default hardware configuration it needs to set up
* the C runtime environment as well. This code is the first code that is
* executed after a system RESET (hard or soft).
*---------------------------------------------------------------------------*/
#include <platform.h>

// Clock speed
#define CLOCK_SPEED 32000000L

// Forward declarations
void init(void);
void clock_init();
void Default_Handler(void);
extern void SysTick_Handler(void);

// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

/** Startup configuration and entry point vectors
 *
 * The XMC1100 remaps interrupt vectors to RAM. These are defined in the
 * "vectors" section below.  The section "vectors" is  placed at the beginning
 * of flash by the linker script.
 *
 * Another useful feature of this chip is that you can pre-program startup
 * conditions such as CPU speed and which periperals.  This is done by writing
 * values in to CLK_VAL1 and CLK_VAL2 below
 */
const void *FlashVectors[] __attribute__((section(".vectors"))) = {
  (void *)0x20004000,      /* @0x10001000 Top of stack  */
  init,                    /* @0x10001004 Reset Handler */
  (void *)0,               /* @0x10001008 (reserved) */
  (void *)0,               /* @0x1000100c (reserved) */
  // If bit[31] == 0 then bits[19:0] are loaded into SCU_CLKCR[19:0]
  // Our configuration: 32MHz MCLK, PCLK = MCLK, RTC = internal 32.768kHz
  (void *)0x00000000,      /* @0x10001010 CLK_VAL1    */
  // If bit[31] == 0 then bits[10:0] are loaded into SCU_CGATCLR0[10:0]
  // Our configuration: Disable CCU40 (bit 2) and WDT (bit 9)
  (void *)((1<<2)|(1<<9))  /* @0x10001014 CLK_VAL2    */
  };

// The remaining interrupt vectors are relocated to RAM where a jump
// table should be placed to the actual interrupt handlers.  The jump
// table takes the following form:
//	ldr R0,=handler_address
//  mov PC,R0
// This pair of instructions fits into 4 bytes which
// fits neatly into a jump table entry.

inline void JumpTable(void) __attribute__(( section(".remapped_vectors")));
inline void JumpTable(void)
{
  asm(" .long 0 "); // -15 reserved
  asm(" .long 0 "); // -14 reserved
  asm(" ldr R0,=Default_Handler "); // -13 HardFault
  asm(" mov PC,R0 ");
  asm(" .long 0 "); // -12 reserved
  asm(" .long 0 "); // -11 reserved
  asm(" .long 0 "); // -10 reserved
  asm(" .long 0 "); // -9 reserved
  asm(" .long 0 "); // -8 reserved
  asm(" .long 0 "); // -7 reserved
  asm(" .long 0 "); // -6 reserved
  asm(" ldr R0,=Default_Handler "); // -5 SVCall
  asm(" mov PC,R0 ");
  asm(" .long 0 "); // -4 reserved
  asm(" .long 0 "); // -3 reserved
  asm(" ldr R0,=Default_Handler "); // -2 PendSV
  asm(" mov PC,R0 ");
  asm(" ldr R0,=SysTick_Handler "); // -1 Systick handler
  asm(" mov PC,R0 ");
  asm(" .long 0 "); // IRQ 0
  asm(" .long 0 "); // IRQ 1
  asm(" .long 0 "); // IRQ 2
  asm(" .long 0 "); // IRQ 3
  asm(" .long 0 "); // IRQ 4
  asm(" .long 0 "); // IRQ 5
  asm(" .long 0 "); // IRQ 6
  asm(" .long 0 "); // IRQ 7
  asm(" .long 0 "); // IRQ 8
  asm(" .long 0 "); // IRQ 9
  asm(" .long 0 "); // IRQ 10
  asm(" .long 0 "); // IRQ 11
  asm(" .long 0 "); // IRQ 12
  asm(" .long 0 "); // IRQ 13
  asm(" .long 0 "); // IRQ 14
  asm(" .long 0 "); // IRQ 15
  asm(" .long 0 "); // IRQ 16
  asm(" .long 0 "); // IRQ 17
  asm(" .long 0 "); // IRQ 18
  asm(" .long 0 "); // IRQ 19
  asm(" .long 0 "); // IRQ 20
  asm(" .long 0 "); // IRQ 21
  asm(" .long 0 "); // IRQ 22
  asm(" .long 0 "); // IRQ 23
  asm(" .long 0 "); // IRQ 24
  asm(" .long 0 "); // IRQ 25
  asm(" .long 0 "); // IRQ 26
  asm(" .long 0 "); // IRQ 27
  asm(" .long 0 "); // IRQ 28
  asm(" .long 0 "); // IRQ 29
  asm(" .long 0 "); // IRQ 30
  asm(" .long 0 "); // IRQ 31
  };

/** Main initialisation
 *
 * Handles static data initialisation, copying IRQ vector table to RAM and
 * initial hardware configuration. Once set up is complete the function invokes
 * main().
 */
void init() {
  unsigned char *src;
  unsigned char *dest;
  unsigned len;
  // Copy initialised data from flash to RAM
  src = &INIT_DATA_VALUES;
  dest = &INIT_DATA_START;
  len = &INIT_DATA_END - &INIT_DATA_START;
  while(len--)
    *dest++ = *src++;
  // Zero out the uninitialized global/static variables
  dest = &BSS_START;
  len = &BSS_END - &BSS_START;
  while(len--)
    *dest++ = 0;
  // Set up the system tick subsystem
  SYST_RVR = CLOCK_SPEED / TICKS_PER_SECOND;
  SYST_CVR = 0;
  SYST_CSR = 3; // Counter enabled, interrupt enable, use system clock
  // TODO: GPIO configuration
  // TODO: Set up RTC
  // TODO: Set up the UART (default 57600 baud)
  USIC0_CH0_CCR =
    BIT1 | // ASC mode
    BIT14; // Receive interrupt enable
  USIC0_CH0_PCR =
    BIT7 | // Interrupt on frame finished
    BIT17; // Enable transmit busy flag
  USIC0_CH0_KSCFG =
    BIT0 | BIT1 |        // Enable module
    BIT8 | BIT9 | BIT11; // Disable UART in suspend mode
  // TODO: Pick an interrupt and enable vectoring for the UART receive
  // Invoke main
  main();
  }

/** Default interrrupt handler
 *
 * This is used for interrupts we don't expect to occur. Just goes into an
 * endless loop.
 */
void Default_Handler() {
  while(1);
  }

