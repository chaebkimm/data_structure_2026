# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DDIJKSTRA_TESTING
BUILD_DIR ?= build
LAB_DIR ?= ../student
GRAPH_ROOT ?= ../..
GRAPH_SOURCE := $(GRAPH_ROOT)/module_03_graph/student/lab.c
SUPPORT_SOURCES := support/weighted_graph.c support/dijkstra_frontier.c
STARTER_SOURCE := starter/dijkstra.c
SOLUTION_SOURCE := solution/dijkstra.c

.PHONY: all lab-compile core student-tests comparison starter-core starter-extension starter-student-tests \
	solution-core solution-extension solution-student-tests autopsy clean

all: core student-tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

lab-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(GRAPH_ROOT) -c $(LAB_DIR)/lab.c -o $(BUILD_DIR)/lab.o

$(BUILD_DIR)/lab_core: tests/test_lab.c $(LAB_DIR)/lab.c $(GRAPH_SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) -I$(GRAPH_ROOT) tests/test_lab.c -o $@

core: $(BUILD_DIR)/lab_core
	$(BUILD_DIR)/lab_core

$(BUILD_DIR)/lab_student: tests/test_lab_student.c $(LAB_DIR)/lab.c $(GRAPH_SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) -I$(GRAPH_ROOT) tests/test_lab_student.c -o $@

student-tests: $(BUILD_DIR)/lab_student
	$(BUILD_DIR)/lab_student

$(BUILD_DIR)/lab_comparison: tests/compare_lab.c $(LAB_DIR)/lab.c $(GRAPH_SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) -I$(GRAPH_ROOT) tests/compare_lab.c -o $@

comparison: $(BUILD_DIR)/lab_comparison
	$(BUILD_DIR)/lab_comparison

starter-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCE) tests/test_core.c -o $(BUILD_DIR)/starter_core
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCE) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCE) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCE) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCE) tests/test_student.c -o $(BUILD_DIR)/solution_student_tests
	$(BUILD_DIR)/solution_student_tests

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_overflow.c -o $(BUILD_DIR)/dijkstra_overflow_autopsy
	$(BUILD_DIR)/dijkstra_overflow_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
