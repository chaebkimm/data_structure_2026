# GNU Make recipe for Git Bash, MSYS2, WSL, Linux, or macOS.
# Override the compiler when needed: make CC=clang solution-core
CC := gcc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?= -Iinclude
TEST_CPPFLAGS := $(CPPFLAGS) -DTREE_TESTING
SANITIZER_FLAGS ?= -fsanitize=address,undefined -fno-omit-frame-pointer
BUILD_DIR := build
SUPPORT_SOURCE := support/tree_support.c
STARTER_SOURCES := starter/avl_rotations.c starter/avl_tree.c
SOLUTION_SOURCES := solution/avl_rotations.c solution/avl_tree.c

.PHONY: all starter-compile starter-core starter-extension \
	starter-student-tests solution-core solution-extension \
	solution-student-tests autopsy autopsy-unsafe clean

all: solution-core

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

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
	$(CC) $(CFLAGS) -DAUTOPSY_INSPECT_ONLY autopsy/faulty_left_rotation.c -o $(BUILD_DIR)/left_rotation_autopsy_inspect
	$(BUILD_DIR)/left_rotation_autopsy_inspect

autopsy-unsafe: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SANITIZER_FLAGS) autopsy/faulty_left_rotation.c -o $(BUILD_DIR)/left_rotation_autopsy_unsafe
	@echo "Unsafe autopsy compiled but not run: $(BUILD_DIR)/left_rotation_autopsy_unsafe"

clean:
	$(RM) -r $(BUILD_DIR)
