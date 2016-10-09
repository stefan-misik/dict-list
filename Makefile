#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

# Define tools
CXX    = g++

# Project properties
PROJ = config_parse
SRC  = main.c

# Flags
CFLAGS   = -c
CXXFLAGS = -c
LDFLAGS  = 
LDLIBS   = 
################################################################################

# Debug flags
ifeq ($(DBG),y)
	CFLAGS   += -D_DEBUG -ggdb -Wall
	CXXFLAGS += -D_DEBUG -ggdb -Wall
	LDFLAGS  += -ggdb
endif

# Object files
OBJ := $(addsuffix .o,$(basename $(SRC))) $(RES:.rc=.o)
	
# Dependencies
DEP := $(addsuffix .d,$(basename $(SRC)))
################################################################################

all: $(PROJ)

# Pull in dependency info
-include $(DEP)

$(PROJ): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

%.o: %.c	
	$(CC) $(CFLAGS) $< -o $@
	
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) $< -o $@

%.d: %.cpp
	$(CXX) -MM $(CXXFLAGS) $< > $@

clean:
	$(RM) $(PROJ) $(OBJ) $(DEP)


.PHONY: FORCE all clean

FORCE:
