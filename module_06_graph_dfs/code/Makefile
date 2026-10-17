# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang lecture lecture-ppt lab-tests
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
LAB_CPPFLAGS := $(CPPFLAGS) -I../..
TEST_CPPFLAGS := $(CPPFLAGS) -DGRAPH_DFS_TESTING
BUILD_DIR := build
SUPPORT_SOURCES := support/graph_matrix.c support/vertex_stack.c
STARTER_SOURCES := $(SUPPORT_SOURCES) starter/graph_dfs.c
SOLUTION_SOURCES := $(SUPPORT_SOURCES) solution/graph_dfs.c
LAB_DEPENDENCIES := ../student/lab.c ../../module_03_graph/student/lab.c ../../module_04_stack/student/lab.c

.PHONY: all starter-core starter-extension starter-student-tests \
	starter-self-loop solution-core solution-extension \
	solution-self-loop self-loop lecture lecture-ppt lab-tests autopsy clean

all: lecture

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

starter-self-loop: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(STARTER_SOURCES) tests/test_self_loop.c -o $(BUILD_DIR)/starter_self_loop
	$(BUILD_DIR)/starter_self_loop

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCES) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SOLUTION_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-self-loop: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOLUTION_SOURCES) tests/test_self_loop.c -o $(BUILD_DIR)/solution_self_loop
	$(BUILD_DIR)/solution_self_loop

self-loop: solution-self-loop

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_cycle_dfs.c -o $(BUILD_DIR)/graph_dfs_autopsy
	$(BUILD_DIR)/graph_dfs_autopsy

clean:
	$(RM) -r $(BUILD_DIR)

# Array-based lecture lab; the matrix-based targets above are legacy exercises.
lecture: lecture/lab_demo.c $(LAB_DEPENDENCIES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) lecture/lab_demo.c -o $(BUILD_DIR)/lab_demo
	$(BUILD_DIR)/lab_demo

lecture-ppt: lecture/ppt_demo.c $(LAB_DEPENDENCIES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) lecture/ppt_demo.c -o $(BUILD_DIR)/ppt_demo
	$(BUILD_DIR)/ppt_demo

lab-tests: tests/test_lab.c $(LAB_DEPENDENCIES) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) tests/test_lab.c -o $(BUILD_DIR)/lab_tests
	$(BUILD_DIR)/lab_tests
