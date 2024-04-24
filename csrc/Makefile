
BUILD_DIR := $(BUILD_DIR)/$(notdir $(CURDIR))

export BUILD_DIR


CSRC := $(shell find $(CURDIR) -mindepth 1 -maxdepth 1 -name '*.c' -printf '%P ')
OBJS := $(CSRC:%=$(BUILD_DIR)/%.o)
SUBDIRS := $(shell find $(CURDIR) -mindepth 1 -maxdepth 1 -type d)



.PHONY: clean

all: sub $(BIN_DIR)/$(TARGET)

sub: $(SUBDIRS)
#	$(MAKE) -C $^

$(BIN_DIR)/$(TARGET): $(BIN_DIR)/$(TARGET).o $(MAIN)
	$(CC) $(CFLAGS) -o $@ $^

$(BIN_DIR)/$(TARGET).o: $(OBJS)
	$(LD) -r -o $@ $^

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $^ -c

clean:
#	-$(MAKE) -C $(SUBDIRS) clean
	-rm -r $(BUILD_DIR)
