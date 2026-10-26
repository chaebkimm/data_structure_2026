CC = cc
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
# Repository mode. prepare_release.py materializes the same support files locally.
MST_DIR ?= ../../code
DSU_REFERENCE ?= ../../../module_07_linked_list/code/solution/dsu.c
DSU_STUDENT ?= dsu.c
KRUSKAL_STUDENT ?= $(MST_DIR)/starter/kruskal.c
CPPFLAGS = -I$(MST_DIR)/include -DMST_TESTING
BUILD_DIR ?= build
SUPPORT = $(MST_DIR)/support/undirected_edge_list.c $(MST_DIR)/support/prim_frontier.c $(MST_DIR)/support/mst_support.c
PRIM = $(MST_DIR)/solution/prim.c
.PHONY: starter-compile starter-core solution-core student-tests clean
$(BUILD_DIR):
	mkdir -p $@
starter-compile: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DSU_STUDENT) test_dsu.c -o $(BUILD_DIR)/dsu
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DSU_STUDENT) $(SUPPORT) $(PRIM) $(KRUSKAL_STUDENT) $(MST_DIR)/tests/test_core.c -o $(BUILD_DIR)/mst
starter-core: starter-compile
	$(BUILD_DIR)/dsu
	$(BUILD_DIR)/mst
solution-core: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DSU_REFERENCE) test_dsu.c -o $(BUILD_DIR)/dsu-reference
	$(BUILD_DIR)/dsu-reference
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DSU_REFERENCE) $(SUPPORT) $(PRIM) $(MST_DIR)/solution/kruskal.c $(MST_DIR)/tests/test_core.c -o $(BUILD_DIR)/mst-reference
	$(BUILD_DIR)/mst-reference
student-tests: | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DSU_STUDENT) $(SUPPORT) $(PRIM) $(KRUSKAL_STUDENT) test_student.c -o $(BUILD_DIR)/student
	$(BUILD_DIR)/student
clean:
	$(RM) -r $(BUILD_DIR)
