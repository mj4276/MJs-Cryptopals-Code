
CC = gcc
CFLAGS := -Wall -I$(REPO_ROOT)/src -O3 -g
DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
ifdef DEBUG
    CFLAGS += -DDEBUG
endif

vpath %.c $(REPO_ROOT)/src $(REPO_ROOT)/tests
vpath %.h $(REPO_ROOT)/src

Makefile: $(REPO_ROOT)/bin/mk $(REPO_ROOT)/mk/*
	@$(REPO_ROOT)/bin/mk
	@echo "'Makefile' was updated."

# This object file autodependency is based the following article:
# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/
%.o : %.c
%.o : %.c | $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c -o $@ $<

# For this project, I want to make lots of "tests" which each
# correspond to a cryptopals "challenge". The following makes it painless
# to add and compile such tests to my heart's content. Becuase this is a
# small projet, I assume each test depends on all the sources.
# gcc is fast enough ;)
TESTS_TARGETS = $(patsubst %.c,%,$(notdir $(wildcard $(REPO_ROOT)/tests/*)))
SRC_OBJS = $(patsubst %.h,%.o,$(notdir $(wildcard $(REPO_ROOT)/src/*.h)))
% : %.c
$(TESTS_TARGETS) : % : %.c $(SRC_OBJS)
	$(CC) $(CFLAGS) $(DEPFLAGS) -o $@ $^

$(DEPDIR) : 
	@mkdir -p $@

DEPS := $(wildcard $(DEPDIR)/*.d)
$(DEPS):
include $(DEPS)
