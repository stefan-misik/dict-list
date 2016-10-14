#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

# Define tools
CC  = i686-w64-mingw32-gcc

# List of tests
TESTS:= $(shell cat test.list)

# Test environment setup
OUT_PREFIX = test_
DIR        = tests/
TESTED     = ../src/
TEST_ENV   = unit_test.o

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

# Files to clean-up
CLEAN_FILES = $(TEST_OUT) $(TEST_ENV)      \
	      $(addsuffix .o, $(addprefix $(TESTED), $(TESTS)))

################################################################################

all: $(TEST_OUT)

$(addprefix $(OUT_PREFIX), $(TESTS)): $(OUT_PREFIX)%: $(DIR)%.o $(TESTED)%.o $(TEST_ENV)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

$(TESTED)%.o: $(TESTED)%.c
	$(MAKE) -C $(TESTED) $(notdir $@)

%.o: %.c	
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(CLEAN_FILES)

$(TESTS): %: $(OUT_PREFIX)%

.PHONY: FORCE all clean $(TESTS)

FORCE:
