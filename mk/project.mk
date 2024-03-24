
CC ?= gcc
CFLAGS := -Wall
ifdef DEBUG
    CFLAGS += -g -DDEBUG
endif
COBJFLAGS := $(CFLAGS) -c

vpath %.c $(REPO_ROOT)/src:$(REPO_ROOT)/tests
vpath %.h $(REPO_ROOT)/src

Makefile: $(REPO_ROOT)/bin/mk $(REPO_ROOT)/mk/*
	$(REPO_ROOT)/bin/mk

%.o: %.c Makefile
	$(CC) $(COBJFLAGS) -o $@ $<

%: %.c Makefile
	$(CC) $(CFLAGS) -o $@ $<

