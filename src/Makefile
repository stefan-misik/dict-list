#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

# Define tools
CC = i686-w64-mingw32-gcc
AR = ar

# Project properties
OUT = libconfig_parse.a
SRC = dict_list.c

# Flags
CFLAGS   = -c
LDFLAGS  =
LDLIBS   = 
################################################################################

# If shared library is being built
ifeq ($(suffix $(OUT)),.so)
	CFLAGS   += -fpic
	LDFLAGS  += -shared
endif

# Debug flags
ifeq ($(DBG),y)
	CFLAGS   += -D_DEBUG -ggdb -Wall
	LDFLAGS  += -ggdb
endif

# Object files
OBJ := $(addsuffix .o,$(basename $(SRC))) $(RES:.rc=.o)
	
# Dependencies
DEP := $(addsuffix .d,$(basename $(SRC)))
################################################################################

all: $(OUT)

# Pull in dependency info
-include $(DEP)

$(basename $(OUT)).so: $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(basename $(OUT)).a: $(OBJ)	
	$(AR) rcs $@ $^

%.o: %.c	
	$(CC) $(CFLAGS) $< -o $@
	
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

clean:
	$(RM) $(basename $(OUT)).a $(basename $(OUT)).so $(OBJ) $(DEP)


.PHONY: FORCE all clean

FORCE:
