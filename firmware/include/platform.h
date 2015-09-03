/*---------------------------------------------------------------------------*
* Platform specific definitions
*----------------------------------------------------------------------------*
* 01-Sep-2015 ShaneG
*
* This file defines the common functions and structures used by the platform
* and bring in hardware specific definitions for the target processor
*---------------------------------------------------------------------------*/
#ifndef __PLATFORM_H
#define __PLATFORM_H

// Required definitions
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/** System initialisation function
 */
void systemInit();

/** Default interrupt handler
 */
void defaultInterruptHandler();

/** Main program
 */
int main();

// Define some bitmasks
#define BIT0 (1 << 0)
#define BIT1 (1 << 1)
#define BIT2 (1 << 2)
#define BIT3 (1 << 3)
#define BIT4 (1 << 4)
#define BIT5 (1 << 5)
#define BIT6 (1 << 6)
#define BIT7 (1 << 7)
#define BIT8 (1 << 8)
#define BIT9 (1 << 9)
#define BIT10 (1 << 10)
#define BIT11 (1 << 11)
#define BIT12 (1 << 12)
#define BIT13 (1 << 13)
#define BIT14 (1 << 14)
#define BIT15 (1 << 15)
#define BIT16 (1 << 16)
#define BIT17 (1 << 17)
#define BIT18 (1 << 18)
#define BIT19 (1 << 19)
#define BIT20 (1 << 20)
#define BIT21 (1 << 21)
#define BIT22 (1 << 22)
#define BIT23 (1 << 23)
#define BIT24 (1 << 24)
#define BIT25 (1 << 25)
#define BIT26 (1 << 26)
#define BIT27 (1 << 27)
#define BIT28 (1 << 28)
#define BIT29 (1 << 29)
#define BIT30 (1 << 30)
#define BIT31 (1 << 31)

// Macros to reduce typing later on
#define  REGISTER_32(ADDRESS) (*((volatile unsigned int *)(ADDRESS)))
#define  REGISTER_16(ADDRESS) (*((volatile uint16_t *)(ADDRESS)))
#define  REGISTER_8(ADDRESS) (*((volatile uint8_t *)(ADDRESS)))

#define  PTR_32(ADDRESS) (((volatile unsigned int *)(ADDRESS)))
#define  PTR_16(ADDRESS) (((volatile uint16_t *)(ADDRESS)))
#define  PTR_8(ADDRESS)  (((volatile uint8_t *)(ADDRESS)))

// Macros to enable/disable global interrupts
#define enable_interrupts() asm(" cpsie i ")
#define disable_interrupts() asm(" cpsid i ")

// Bring in target specific hardware definitions
#ifdef TARGET_LPC1114
#  include <boards/lpc1114.h>
#elif TARGET_STM32F030
#  include <boards/stm32f030.h>
#elif TARGET_STM32F070
#  include <boards/stm32f070.h>
#elif TARGET_XMC1100
#  include <boards/xmc1100.h>
#else
#  error "Unsupported or undefined target platform"
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __PLATFORM_H */
