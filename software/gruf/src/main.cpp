/*---------------------------------------------------------------------------*
* Grand Unified Flasher (GRUF) - Main Program
*----------------------------------------------------------------------------*
* 27-Oct-2015 ShaneG
*
* Main program for the flashing tool.
*---------------------------------------------------------------------------*/
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <gruf.h>
#include <optionparser.h>

// Version information
#define VER_MAJOR 0
#define VER_MINOR 1

struct Arg: public option::Arg {
  static option::ArgStatus Required(const option::Option& option, bool) {
    return option.arg == 0 ? option::ARG_ILLEGAL : option::ARG_OK;
    }
  };

enum  optionIndex { UNKNOWN, HELP, SILENT, NOISY, SETTYPE, SETNODE, DEVICE, PORT, ERASE };

const option::Descriptor usage[] = {
  { UNKNOWN, 0, "" , ""    , option::Arg::None, "USAGE: gruf [options] hexfile\n\n"
                                              "Options:" },
  { HELP,    0, "" , "help", Arg::None, "  --help  \tPrint usage and exit." },
  { SILENT,  0, "q", "quiet", Arg::None, "  --quiet, -q  \tRun in quiet mode." },
  { NOISY,   0, "v", "verbose", Arg::None, "  --verbose, -v  \tShow verbose information." },
  { SETTYPE, 0, "", "typeid", Arg::Required, "  --typeid uuid  \tSet the type ID." },
  { SETNODE, 0, "", "nodeid", Arg::Required, "  --nodeid uuid  \tSet the node ID." },
  { DEVICE,  0, "d", "device", Arg::Required, "  --device, -d device  \tSpecify the target device." },
  { PORT,    0, "p", "port", Arg::Required, "  --port, -p port  \tSpecify the serial port to use." },
  { ERASE,   0, "e", "erase", Arg::None, "  --erase, -e  \tErase the flash before programming." },
  {0,0,0,0,0,0}
  };

/** Program entry point
 */
int main(int argc, char *argv[]) {
  ILog("Grand Unified Flasher V%d.%02d", VER_MAJOR, VER_MINOR);
  // Parse options
  argc -= (argc>0);
  argv += (argc>0); // skip program name argv[0] if present
  option::Stats  stats(usage, argc, argv);
  option::Option* options = new option::Option[stats.options_max];
  option::Option* buffer  = new option::Option[stats.buffer_max];
  option::Parser parse(usage, argc, argv, options, buffer);
  // Check for errors and help requests
  if(parse.error()) {
    ELog("Unable to process command line options.");
    option::printUsage(std::cout, usage);
    return 1;
    }
  if(options[HELP] || argc == 0) {
    option::printUsage(std::cout, usage);
    return 0;
    }
  // Check for unknown options
  bool badOpts = false;
  for(option::Option* opt = options[UNKNOWN]; opt; opt = opt->next()) {
    ELog("Unknown option: %s", opt->name);
    badOpts = true;
    }
  if(badOpts)
    return 1;
  // Apply options for verbosity
  if(options[SILENT])
    setVerbosity(QUIET);
  if(options[NOISY])
    setVerbosity(VERBOSE);
  // Check for device
  if((options[DEVICE]==NULL)||(options[DEVICE].arg==NULL)||(options[DEVICE].arg[0]=='\0')) {
    ELog("Device type must be specified.");
    return 1;
    }
  if(strcmp(options[DEVICE].arg, "?")==0) {
    // Show a list of device types and exit
    setVerbosity(NORMAL); // In case 'quiet' mode was selected
    listDevices();
    return 0;
    }
  Bootloader *pBootloader = getBootloader(options[DEVICE].arg);
  if(pBootloader==NULL) {
    ELog("Unsupported device type - '%s'. Use --device ? to list supported types.", options[DEVICE].arg);
    return 1;
    }
  // Get custom UUIDs if preset
  bool haveTypeID = false;
  uint8_t typeID[UUID_LENGTH];
  uint8_t nodeID[UUID_LENGTH];
  if(options[SETTYPE]&&options[SETTYPE].arg) {
    if(!uuidParse(typeID, options[SETTYPE].arg)) {
      ELog("Invalid UUID provided for type ID.");
      return 1;
      }
    haveTypeID = true;
    }
  if(options[SETNODE]&&options[SETNODE].arg) {
    if(!uuidParse(nodeID, options[SETNODE].arg)) {
      ELog("Invalid UUID provided for node ID.");
      return 1;
      }
    }
  else {
    // Generate a UUID for the node
    if(!uuidCreate(nodeID)) {
      ELog("Unable to generate a UUID for the node.");
      return 1;
      }
    }
  // Load the firmware data
  if(parse.nonOptionsCount()!=1) {
    ELog("You must specify a hex file on the command line.");
    return 1;
    }
  Firmware *pFirmware = loadFirmware(parse.nonOption(0));
  if(pFirmware==NULL) {
    ELog("Unable to load firmware from '%s'.", parse.nonOption(0));
    return 1;
    }
  // Patch with TYPEID and NODEID values
  uint32_t addr = pFirmware->patchID(Firmware::NODEID, nodeID);
  if(addr==INVALID_ADDRESS)
    ILog("Unable to patch NODEID in firmware. Continuing anyway.");
  else
    ILog("Set NODEID to %s @ 0x%08x.", uuidPrint(nodeID), addr);
  if(haveTypeID) {
    addr = pFirmware->patchID(Firmware::TYPEID, typeID);
    if(addr==INVALID_ADDRESS)
      ILog("Unable to patch TYPEID in firmware. Continuing anyway.");
    else
      ILog("Set TYPEID to %s @ 0x%08x.", uuidPrint(typeID), addr);
    }
  // Make sure we can use the firmware
  if(!pBootloader->validate(pFirmware)) {
    ELog("The selected firmware cannot be loaded on this device.");
    return 1;
    }
  // Make sure we have a port specified
  if((options[PORT]==NULL)||(options[PORT].arg==NULL)||(options[PORT].arg[0]=='\0')) {
    ELog("Port name must be specified.");
    return 1;
    }
  Flasher *pFlasher = attachFlasher(options[PORT].arg);
  if(pFlasher==NULL) {
    ELog("Unable to connect to debug adapter on port '%s'.", options[PORT].arg);
    return 1;
    }
  // Connect it all together
  if(!pBootloader->attach(pFlasher)) {
    ELog("Unable to enter programming mode.");
    return 1;
    }
  if(options[ERASE]) {
    ILog("Erasing target ...");
    if(!pBootloader->erase()) {
      ELog("Erase failed.");
      return 1;
      }
    }
  ILog("Writing firmware ...");
  if(!pBootloader->program(pFirmware)) {
    ELog("Write failed.");
    return 1;
    }
  ILog("Verifying firmware ...");
  if(!pBootloader->verify(pFirmware)) {
    ELog("Verification failed.");
    return 1;
    }
  // All done
  pBootloader->detach();
  return 0;
  }

