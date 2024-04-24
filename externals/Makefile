
BUILD_DIR := $(BUILD_DIR)/$(notdir $(CURDIR))

export BUILD_DIR


CSRC := $(shell find $(CURDIR) -mindepth 1 -maxdepth 1 -name '*.c' -printf '%P ')
OBJS := $(CSRC:%=$(BUILD_DIR)/%.o)
SUBDIRS := $(shell find $(CURDIR) -mindepth 1 -maxdepth 1 -type d)



.PHONY: clean

all: sub copy

copy:
	$(shell cp */bin/* $(BIN_DIR)/)

sub: $(SUBDIRS)
	$(MAKE) -C $^

clean:
	-$(MAKE) -C $(SUBDIRS) clean
