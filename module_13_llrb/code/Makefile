CC ?= cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
BUILD_DIR ?= build

.PHONY: all demo check
all: demo check

demo: $(BUILD_DIR)/demo
	$(BUILD_DIR)/demo

check: $(BUILD_DIR)/check
	$(BUILD_DIR)/check

$(BUILD_DIR)/%: %.c llrb.c llrb.h
	mkdir -p "$(BUILD_DIR)"
	$(CC) $(CPPFLAGS) $(CFLAGS) llrb.c $< $(LDFLAGS) -o "$@"
