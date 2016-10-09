#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

# Define tools
CC  = gcc

# Project properties
OUT = libconfig_parse.so
SRC = dict_list.c

# Flags
CFLAGS   = -c -fpic
LDFLAGS  = -shared
LDLIBS   = 
################################################################################

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

$(OUT): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

%.o: %.c	
	$(CC) $(CFLAGS) $< -o $@
	
%.d: %.c
	$(CC) -MM $(CFLAGS) $< > $@

clean:
	$(RM) $(OUT) $(OBJ) $(DEP)


.PHONY: FORCE all clean

FORCE:
