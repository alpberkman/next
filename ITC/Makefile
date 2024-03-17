
TARGET := next

CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -Wno-unused-variable


MAIN ?= main.c
CSRC_DIRS := ./csrc
BUILD_DIR := ./build

CSRC := $(shell find $(CSRC_DIRS) -name '*.c')
OBJS := $(CSRC:%=$(BUILD_DIR)/%.o)


.PHONY: clean run

all: run

run: $(BUILD_DIR)/$(TARGET)
	clear
	cat - | $<

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/$(TARGET).o $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/$(TARGET).o: $(OBJS)
	$(LD) -r -o $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
	rm -r $(BUILD_DIR)
