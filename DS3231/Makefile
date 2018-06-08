#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
#
#############################################################################

# source files in this project (main.cpp is automatically assumed)
SOURCES := i2cBus.cpp time.cpp DS3231.cpp bitParser.cpp timestamp.cpp MFRC522.cpp spiBus.cpp

# header files in this project
HEADERS := i2cBus.hpp time.hpp DS3231.hpp bitParser.hpp timestamp.hpp MFRC522.hpp spiBus.hpp

# other places to look for files for this project
SEARCH  :=

# set RELATIVE to the next higher directory
# and defer to the Makefile.* there
RELATIVE := ..
include $(RELATIVE)/Makefile.due
