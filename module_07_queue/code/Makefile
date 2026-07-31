# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DEVENT_QUEUE_TESTING
BUILD_DIR := build
STARTER_SOURCE := starter/event_queue.c
SOLUTION_SOURCE := solution/event_queue.c

.PHONY: all starter-core starter-extension starter-student-tests \
	solution-core solution-extension autopsy clean

all: starter-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

starter-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCE) tests/test_core.c -o $(BUILD_DIR)/starter_core
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STARTER_SOURCE) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCE) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_wrap.c -o $(BUILD_DIR)/queue_autopsy
	$(BUILD_DIR)/queue_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
