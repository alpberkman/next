
TARGET := next
MAIN ?= $(CURDIR)/main.c

export TARGET
export MAIN


CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -Wno-unused-variable

BASE_DIR := $(CURDIR)
CSRC_DIR := $(BASE_DIR)/csrc
BUILD_DIR := $(BASE_DIR)/build
BIN_DIR := $(BASE_DIR)/bin

export CC
export CFLAGS

export BASE_DIR
export CSRC_DIR
export BUILD_DIR
export BIN_DIR



.PHONY: clean binary run

all: run

#run: $(BUILD_DIR)/$(TARGET)
#	clear
#	./$<

#run2: $(BUILD_DIR)/$(TARGET)
#	clear
#	cat - | $<

run: binary
#	clear
	$(BIN_DIR)/led
#	$(BIN_DIR)/led $(BIN_DIR)/next

binary:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	$(MAKE) -C $(CSRC_DIR)

clean:
#	-$(MAKE) -C $(CSRC_DIR) clean
	-rm -r $(BUILD_DIR)
