CC = cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
LAB_DIR ?= ../student
BUILD_DIR ?= build
.PHONY: all core student-tests demo clean
all: core student-tests demo
$(BUILD_DIR):
	mkdir -p $@
$(BUILD_DIR)/core: tests/test_lab_core.c $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LAB_DIR) tests/test_lab_core.c -o $@
$(BUILD_DIR)/student: tests/test_lab_student.c $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LAB_DIR) tests/test_lab_student.c -o $@
$(BUILD_DIR)/demo: $(LAB_DIR)/lab_driver.c $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(LAB_DIR)/lab_driver.c -o $@
core: $(BUILD_DIR)/core
	$(BUILD_DIR)/core
student-tests: $(BUILD_DIR)/student
	$(BUILD_DIR)/student
demo: $(BUILD_DIR)/demo
	$(BUILD_DIR)/demo
clean:
	$(RM) -r $(BUILD_DIR)
