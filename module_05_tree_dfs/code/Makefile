# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang lecture lab-tests
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
LAB_CPPFLAGS := $(CPPFLAGS) -I../..
TEST_CPPFLAGS := $(CPPFLAGS) -DTREE_DFS_TESTING
BUILD_DIR := build
SUPPORT_SOURCES := support/tree_support.c
STARTER_SOURCES := $(SUPPORT_SOURCES) starter/tree_dfs.c
SOLUTION_SOURCES := $(SUPPORT_SOURCES) solution/tree_dfs.c
LAB_DEPENDENCIES := ../student/lab.c ../../module_02_binary_tree/student/lab.c ../../module_04_stack/student/lab.c

.PHONY: all starter-core starter-extension starter-student-tests \
	solution-core solution-extension solution-student-tests lecture lab-tests autopsy clean

all: lecture

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

lecture: lecture/lab_demo.c $(LAB_DEPENDENCIES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) lecture/lab_demo.c -o $(BUILD_DIR)/lab_demo
	$(BUILD_DIR)/lab_demo

lab-tests: tests/test_lab.c $(LAB_DEPENDENCIES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) tests/test_lab.c -o $(BUILD_DIR)/lab_tests
	$(BUILD_DIR)/lab_tests

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
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SUPPORT_SOURCES) autopsy/faulty_preorder.c -o $(BUILD_DIR)/tree_dfs_autopsy
	$(BUILD_DIR)/tree_dfs_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
