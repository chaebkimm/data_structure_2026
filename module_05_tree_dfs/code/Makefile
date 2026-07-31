# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DTREE_DFS_TESTING
BUILD_DIR := build
SUPPORT_SOURCES := support/tree_support.c support/tree_node_stack.c
STARTER_SOURCES := $(SUPPORT_SOURCES) starter/tree_dfs.c
SOLUTION_SOURCES := $(SUPPORT_SOURCES) solution/tree_dfs.c

.PHONY: all starter-core starter-extension starter-student-tests \
	solution-core solution-extension solution-student-tests autopsy clean

all: starter-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

starter-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCES) tests/test_core.c -o $(BUILD_DIR)/starter_core
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(STARTER_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STARTER_SOURCES) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCES) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOLUTION_SOURCES) tests/test_student.c -o $(BUILD_DIR)/solution_student_tests
	$(BUILD_DIR)/solution_student_tests

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_preorder.c -o $(BUILD_DIR)/tree_dfs_autopsy
	$(BUILD_DIR)/tree_dfs_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
