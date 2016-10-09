#!/usr/bin/make -f

# Makefile for config_parse
# Author: Stefan Misik (mail@stefanmisik.eu)

all clean:
	$(MAKE) -C src $@
	$(MAKE) -C test $@

.PHONY: FORCE all clean

FORCE:
