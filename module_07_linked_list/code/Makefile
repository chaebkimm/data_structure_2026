# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
LAB_DIR ?= ../student
LAB_CPPFLAGS := $(CPPFLAGS) -I$(LAB_DIR)
TEST_CPPFLAGS := $(CPPFLAGS) -DLINKED_LIST_TESTING
SANITIZER_FLAGS ?= -fsanitize=address,undefined -fno-omit-frame-pointer
BUILD_DIR ?= build
SUPPORT_SOURCE := support/undirected_edge_list.c
STARTER_SOURCES := starter/linked_list.c starter/dsu.c
SOLUTION_SOURCES := solution/linked_list.c solution/dsu.c

.PHONY: all lab-compile core student-tests starter-compile starter-core starter-extension \
	starter-student-tests solution-core solution-extension \
	solution-student-tests autopsy autopsy-unsafe clean

all: core student-tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/lab_core: tests/test_lab_core.c tests/lab_test_support.h $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) tests/test_lab_core.c -o $@

$(BUILD_DIR)/lab_student: tests/test_lab_student.c tests/lab_test_support.h $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_CPPFLAGS) tests/test_lab_student.c -o $@

lab-compile: $(BUILD_DIR)/lab_core

core: lab-compile
	$(BUILD_DIR)/lab_core

student-tests: $(BUILD_DIR)/lab_student
	$(BUILD_DIR)/lab_student

starter-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(STARTER_SOURCES) tests/test_core.c -o $(BUILD_DIR)/starter_core

starter-core: starter-compile
	$(BUILD_DIR)/starter_core

starter-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(STARTER_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/starter_extension
	$(BUILD_DIR)/starter_extension

starter-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(STARTER_SOURCES) tests/test_student.c -o $(BUILD_DIR)/starter_student_tests
	$(BUILD_DIR)/starter_student_tests

solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(SOLUTION_SOURCES) tests/test_core.c -o $(BUILD_DIR)/solution_core
	$(BUILD_DIR)/solution_core

solution-extension: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(SOLUTION_SOURCES) tests/test_extension.c -o $(BUILD_DIR)/solution_extension
	$(BUILD_DIR)/solution_extension

solution-student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_CPPFLAGS) $(SUPPORT_SOURCE) $(SOLUTION_SOURCES) tests/test_student.c -o $(BUILD_DIR)/solution_student_tests
	$(BUILD_DIR)/solution_student_tests

autopsy: | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DAUTOPSY_INSPECT_ONLY autopsy/faulty_linked_delete.c -o $(BUILD_DIR)/linked_delete_autopsy_inspect
	$(BUILD_DIR)/linked_delete_autopsy_inspect

autopsy-unsafe: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SANITIZER_FLAGS) autopsy/faulty_linked_delete.c -o $(BUILD_DIR)/linked_delete_autopsy_unsafe
	@echo "Unsafe autopsy compiled but not run: $(BUILD_DIR)/linked_delete_autopsy_unsafe"

clean:
	$(RM) -r $(BUILD_DIR)
