# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DHASH_TABLE_TESTING
BUILD_DIR := build
STARTER_SOURCE := starter/hash_table.c
SOLUTION_SOURCE := solution/hash_table.c

.PHONY: all starter-compile starter-core starter-extension \
	starter-student-tests solution-core solution-extension \
	solution-student-tests autopsy clean

all: solution-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

starter-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCE) tests/test_core.c -o $(BUILD_DIR)/starter_core

starter-core: starter-compile
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCE) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCE) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCE) tests/test_student.c -o $(BUILD_DIR)/solution_student_tests
	$(BUILD_DIR)/solution_student_tests

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_delete_empty.c -o $(BUILD_DIR)/hash_table_autopsy
	$(BUILD_DIR)/hash_table_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
