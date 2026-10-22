CC = cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
CPPFLAGS = -I. -DLQ_TESTING
BUILD_DIR ?= build
.PHONY: starter-compile starter-core solution-core student-tests clean
$(BUILD_DIR):
	mkdir -p $@
starter-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) support.c starter/linked_queue.c tests/test_core.c -o $(BUILD_DIR)/starter
starter-core: starter-compile
	$(BUILD_DIR)/starter
solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) support.c solution/linked_queue.c tests/test_core.c -o $(BUILD_DIR)/solution
	$(BUILD_DIR)/solution
student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) support.c starter/linked_queue.c tests/test_student.c -o $(BUILD_DIR)/student
	$(BUILD_DIR)/student
clean:
	$(RM) -r $(BUILD_DIR)
