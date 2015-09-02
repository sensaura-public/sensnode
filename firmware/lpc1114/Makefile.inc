# LPC1114 Build Definitions
#----------------------------------------------------------------------------
# 02-Sep-2015 ShaneG
#
# Sets additional make settings for the LPC1114 target
#----------------------------------------------------------------------------

CPPFLAGS += -DTARGET_LPC1114
OBJECTS += $(patsubst %.cpp,%.o,$(wildcard lpc1114/*.cpp))

