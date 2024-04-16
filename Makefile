
CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -Wno-unused-variable

BASE_DIR := $(CURDIR)
CSRC_DIR := $(BASE_DIR)/csrc
BUILD_DIR := $(BASE_DIR)/build
BIN_DIR := $(BASE_DIR)/bin

TARGET := next
MAIN ?= $(BASE_DIR)/main.c

export CC
export CFLAGS

export BASE_DIR
export CSRC_DIR
export BUILD_DIR
export BIN_DIR

export TARGET
export MAIN



.PHONY: clean binary run

all: run

#run: $(BUILD_DIR)/$(TARGET)
#	clear
#	./$<

#run2: $(BUILD_DIR)/$(TARGET)
#	clear
#	cat - | $<

run: binary
	clear
	bin/led
#	$(BIN_DIR)/led $(BIN_DIR)/next

binary:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BIN_DIR)
	$(MAKE) -C $(CSRC_DIR)

clean:
#	-$(MAKE) -C $(CSRC_DIR) clean
	-rm -r $(BUILD_DIR)
