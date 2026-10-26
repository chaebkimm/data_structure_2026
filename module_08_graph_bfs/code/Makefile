# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DGRAPH_BFS_TESTING
BUILD_DIR := build
SUPPORT_SOURCES := support/graph_matrix.c support/graph_adj_list.c \
	support/graph_bfs_support.c support/vertex_queue.c
STARTER_SOURCES := $(SUPPORT_SOURCES) starter/graph_bfs.c
SOLUTION_SOURCES := $(SUPPORT_SOURCES) solution/graph_bfs.c

.PHONY: all core lab-compile student-tests starter-core starter-extension starter-student-tests \
	solution-core solution-extension solution-student-tests autopsy clean

all: core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

LAB_DIR ?= ../student
REPOSITORY_ROOT ?= ../..
LAB_SOURCES := $(LAB_DIR)/lab_driver.c $(LAB_DIR)/lab.c $(LAB_DIR)/queue.c $(LAB_DIR)/tree_bfs.c \
	$(REPOSITORY_ROOT)/module_07_linked_list/student/lab.c \
	$(REPOSITORY_ROOT)/module_02_binary_tree/student/lab.c

$(BUILD_DIR)/lab_core: $(LAB_SOURCES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(REPOSITORY_ROOT) $(LAB_DIR)/lab_driver.c -o $@

lab-compile: $(BUILD_DIR)/lab_core

core: lab-compile
	$(BUILD_DIR)/lab_core

student-tests: core

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
	$(CC) $(CFLAGS) autopsy/faulty_frontier.c -o $(BUILD_DIR)/graph_bfs_autopsy
	$(BUILD_DIR)/graph_bfs_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
