# Run in code/ in the repository or extracted student release.
CC := cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS ?=
BUILD_DIR ?= build
LAB_DIR ?= ../student
.PHONY: all lab-compile core student-tests comparison clean
all: core student-tests
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
lab-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(LAB_DIR)/lab.c -o $(BUILD_DIR)/lab.o
$(BUILD_DIR)/lab_core: tests/test_lab.c tests/survey_fixtures.h $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) tests/test_lab.c -o $@
core: $(BUILD_DIR)/lab_core
	$(BUILD_DIR)/lab_core
$(BUILD_DIR)/lab_student: tests/test_lab_student.c $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) tests/test_lab_student.c -o $@
student-tests: $(BUILD_DIR)/lab_student
	$(BUILD_DIR)/lab_student
$(BUILD_DIR)/lab_comparison: tests/compare_lab.c tests/survey_fixtures.h $(LAB_DIR)/lab.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I$(LAB_DIR) tests/compare_lab.c -o $@
comparison: $(BUILD_DIR)/lab_comparison
	$(BUILD_DIR)/lab_comparison
clean:
	$(RM) -r $(BUILD_DIR)
