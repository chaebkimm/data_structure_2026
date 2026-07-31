# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DMST_TESTING
BUILD_DIR := build
SUPPORT_SOURCES := support/dsu.c support/undirected_edge_list.c \
	support/prim_frontier.c support/mst_support.c
STARTER_SOURCES := starter/prim.c starter/kruskal.c
SOLUTION_SOURCES := solution/prim.c solution/kruskal.c

.PHONY: all starter-compile starter-core starter-extension \
	starter-student-tests solution-core solution-extension \
	solution-student-tests autopsy clean

all: solution-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

starter-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCES) tests/test_core.c -o $(BUILD_DIR)/starter_core

starter-core: starter-compile
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(STARTER_SOURCES) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCES) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCES) $(SOLUTION_SOURCES) tests/test_student.c -o $(BUILD_DIR)/solution_student_tests
	$(BUILD_DIR)/solution_student_tests

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) autopsy/faulty_endpoint_cycle.c -o $(BUILD_DIR)/endpoint_cycle_autopsy
	$(BUILD_DIR)/endpoint_cycle_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
