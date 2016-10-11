#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

# Define tools
CC  = i686-w64-mingw32-gcc
TEST_ENV = unit_test.o

# Project properties
OUT_PREFIX = test_
TESTS      = dict_list
DIR        = tests/
TESTED     = ../src/

# Flags
CFLAGS   = -c
LDFLAGS  = 
LDLIBS   = 
################################################################################

# Debug flags
ifeq ($(DBG),y)
	CFLAGS   += -D_DEBUG -ggdb -Wall
	LDFLAGS  += -ggdb
endif

# Test executables
TEST_OUT = $(addprefix $(OUT_PREFIX),$(TESTS)) 

################################################################################

all: $(TEST_OUT)

$(OUT_PREFIX)%:: $(DIR)%.o $(TESTED)%.o
	$(CC) $(LDFLAGS) $(OBJ) -o $@ $(LDLIBS)

$(TESTED)%.o: $(TESTED)%.c
	$(MAKE) -C $(TESTED) $(notdir $@)

%.o: %.c	
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(TEST_OUT) $(TEST_ENV)


.PHONY: FORCE all clean

FORCE:
