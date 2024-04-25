
TARGET := next
MAIN := $(CURDIR)/main.c

export TARGET
export MAIN


CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -Wno-unused-variable

BASE_DIR := $(CURDIR)
CSRC_DIR := $(BASE_DIR)/csrc
BUILD_DIR := $(BASE_DIR)/build
BIN_DIR := $(BASE_DIR)/bin
EXTERNALS_DIR := $(CURDIR)/externals

export CC
export CFLAGS

export BASE_DIR
export CSRC_DIR
export BUILD_DIR
export BIN_DIR
export EXTERNALS_DIR



.PHONY: clean run

all: binary run

run: binary
#	$(BIN_DIR)/led $(shell whereis cat | cut -d' ' -f2 )
#	$(BIN_DIR)/led $(BIN_DIR)/$(TARGET)
	$(BIN_DIR)/$(TARGET)

binary:
#	git submodule update --recursive --remote
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	$(MAKE) -C $(CSRC_DIR)
	$(MAKE) -C $(EXTERNALS_DIR)


clean:
#	-$(MAKE) -C $(CSRC_DIR) clean
	-$(MAKE) -C $(EXTERNALS_DIR) clean
	-rm -r $(BUILD_DIR)
