/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Bootloader Utilities
*----------------------------------------------------------------------------*
* 28-Oct-2015 ShaneG
*
* Defines common definitions shared by bootloader implementations.
*---------------------------------------------------------------------------*/
#ifndef __BOOTLOADER_H
#define __BOOTLOADER_H

class AbstractBootloader : public Bootloader {
  protected:
    const char *m_cszName;
    uint32_t    m_id1;
    uint32_t    m_id2;
    Flasher    *m_flasher;

    /** Constructor
     *
     * Stashes away the device specific information.
     */
    AbstractBootloader(const char *cszName, uint32_t id1, uint32_t id2);

  public:
    /** Attach the bootloader to the given flasher connection
     *
     * @param pFlasher the flasher to attach to.
     */
    virtual bool attach(Flasher *pFlasher);

    /** Detach the bootloader from a flasher.
     */
    virtual void detach();

    /** Default destructor
     */
    virtual ~AbstractBootloader();

  };

#endif /* __BOOTLOADER_H */

