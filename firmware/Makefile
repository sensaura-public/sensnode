# Makefile for SensNode firmware libraries
#----------------------------------------------------------------------------
# 02-Sep-2015 ShaneG
#
# Unified make file for the SensNode firmware library. This will build all
# drivers and processor specific code into a single library with a startup
# object. Specify the TARGET on the command (defaults to 'lpc1114').
#----------------------------------------------------------------------------

# Target files
LIBNAME=lib/$(TARGET)/libsensnode.a
INITOBJ=lib/$(TARGET)/init.o

# What tools to use
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
AS=arm-none-eabi-as
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar

# Basic configuration
CPPFLAGS=-mcpu=cortex-m0 -mthumb -g -Iinclude

# Files we want
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard common/*.cpp))
OBJECTS += $(patsubst %.cpp,%.o,${shell find drivers -name '*.cpp' -type f -print})

# Target specific definitions
TARGET ?= lpc1114
ifeq (,$(wildcard $(TARGET)/Makefile.inc))
    $(error No definitions for target $(TARGET))
endif
include $(TARGET)/Makefile.inc

# Master rules
all: $(LIBNAME) $(INITOBJ)

clean:
	rm -f $(OBJECTS) $(LIBNAME) $(INITOBJ)

#----------------------------------------------------------------------------
# Compilation and linking rules
#----------------------------------------------------------------------------

$(INITOBJ): $(TARGET)/init.o
	cp $< $@

$(LIBNAME): $(OBJECTS)
	mkdir -p lib/$(TARGET)
	$(AR) rcs $@ $(OBJECTS)
