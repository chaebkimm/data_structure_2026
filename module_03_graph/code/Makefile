# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
BUILD_DIR := build

.PHONY: all starter-core starter-student-tests starter-extension \
	solution-core solution-extension autopsy clean

all: starter-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

starter-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/graph_matrix.c tests/test_core.c -o $(BUILD_DIR)/starter_core
	$(BUILD_DIR)/starter_core

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/graph_matrix.c tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/graph_matrix.c tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) solution/graph_matrix.c tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) solution/graph_matrix.c tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) autopsy/faulty_undirected.c -o $(BUILD_DIR)/undirected_autopsy
	$(BUILD_DIR)/undirected_autopsy

clean:
	$(RM) -r $(BUILD_DIR)
