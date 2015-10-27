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

enum  optionIndex { UNKNOWN, HELP, SILENT, NOISY, SETTYPE, SETNODE, DEVICE, PORT };

const option::Descriptor usage[] = {
  { UNKNOWN, 0, "" , ""    , option::Arg::None, "USAGE: gruf [options] hexfile\n\n"
                                              "Options:" },
  { HELP,    0, "" , "help", Arg::None, "  --help  \tPrint usage and exit." },
  { SILENT,  0, "q", "quiet", Arg::None, "  --quiet, -q  \tRun in quiet mode." },
  { NOISY,   0, "v", "verbose", Arg::None, "  --verbose, -v  \tShow verbose information." },
  { SETTYPE, 0, "", "typeid", Arg::Required, "  --typeid uuid  \tSet the type ID." },
  { SETNODE, 0, "", "nodeid", Arg::Required, "  --nodeid uuid  \tSet the node ID." },
  { DEVICE,  0, "d", "device", Arg::Required, "  --device, -d device  \tSpecify the target device." },
  { PORT, 0, "p", "port", Arg::Required, "  --port, -p port  \tSpecify the serial port to use." },
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
  if(parse.error())
    return 1;
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
  if(parse.nonOptionsCount()!=1) {
    ELog("One (and one only) hex file must be specified.");
    return 1;
    }
  // Validate existing options
  return 0;
  }

