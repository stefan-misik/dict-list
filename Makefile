#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

DBG ?= n

all clean:
	$(MAKE) -C src DBG=$(DBG) $@
	$(MAKE) -C test DBG=$(DBG) $@

.PHONY: FORCE all clean

FORCE:
