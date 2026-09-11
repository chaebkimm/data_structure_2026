# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override on the command line when needed: make CC=clang starter-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
BUILD_DIR := build

.PHONY: all solution-core solution-extension starter-core \
	starter-extension starter-student-tests lecture autopsy clean

all: starter-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) solution/int_list.c tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) solution/int_list.c tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

starter-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/int_list.c tests/test_core.c -o $(BUILD_DIR)/starter_core
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/int_list.c tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) starter/int_list.c tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

lecture: | $(BUILD_DIR)
	$(CC) $(CFLAGS) lecture/simplified_array_list.c -o $(BUILD_DIR)/lecture
	$(BUILD_DIR)/lecture

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) autopsy/faulty_append.c -o $(BUILD_DIR)/autopsy
	$(BUILD_DIR)/autopsy

clean:
	$(RM) -r $(BUILD_DIR)
