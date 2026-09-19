struct GraphNode {
	char data;
	int adj_list[10];
	int adj_cap;
	int adj_size;
};

struct GraphNode nodes[10];
int nodes_cap = 10;
int nodes_size = 0;

void alphabet_nodes_init() {
	nodes_size = nodes_cap;

	for (int i = 0; i < nodes_cap; i++) {
		nodes[i].data = 'A' + i;
		nodes[i].adj_cap = 10;
		nodes[i].adj_size = 0;
	}
}

void edges_init() {
	int edges[9][2] = {{0, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
					   {3, 4}, {3, 5}, {4, 5}, {6, 7}};
	int edges_count = 9;
	for (int i = 0; i < edges_count; i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		int u_adj_end = nodes[u].adj_size++;
		int v_adj_end = nodes[v].adj_size++;
		nodes[u].adj_list[u_adj_end] = v;
		nodes[v].adj_list[v_adj_end] = u;
	}
}

int visited[10] = {0};

void visited_init() {
	for (int i = 0; i < nodes_size; i++) {
		visited[i] = 0;
	}
}

void graph_recursion(int i) {
    char data_read = nodes[i].data;
    for (int j = 0; j < nodes[i].adj_size; j++) {
        int neighbor = nodes[i].adj_list[j];
        if (visited[neighbor] == 0) {
            visited[neighbor] = 1;
            graph_recursion(neighbor);
        }		
	}
}

int group[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int groups_count = 0;
int current_group = 0;

void search_connected_group(int i) {
    group[i] = current_group;

    for (int j = 0; j < nodes[i].adj_size; j++) {
        int neighbor = nodes[i].adj_list[j];

        if (visited[neighbor] == 0) {
            visited[neighbor] = 1;
            search_connected_group(neighbor);
        }
    }
}

void mark_all_groups() {
	visited_init();
	groups_count = 0;

	for (int i = 0; i < nodes_size; i++) {
		if (visited[i] == 0) {
            visited[i] = 1;
			current_group = groups_count++;
			search_connected_group(i);
		}
	}
}

int search_num[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int search_time = 0;

void save_search_num(int i) {
	search_num[i] = search_time++;
	for (int j = 0; j < nodes[i].adj_size; j++) {
		int neighbor = nodes[i].adj_list[j];
		if (visited[neighbor] == 0) {
            visited[neighbor] = 1;
			save_search_num(neighbor);
		}
	}
}

int start_index = 0;

void save_search_nums() {
	visited_init();
	search_time = 0;
    visited[start_index] = 1;
	save_search_num(start_index);
}

int back_num[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int parent[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void save_back_num(int i) {
	back_num[i] = search_num[i];
	for (int j = 0; j < nodes[i].adj_size; j++) {
		int neighbor = nodes[i].adj_list[j];
		if (visited[neighbor] == 0) {
            visited[neighbor] = 1;
			parent[neighbor] = i;
			save_back_num(neighbor);
			if (back_num[i] > back_num[neighbor]) {
				back_num[i] = back_num[neighbor];
			}
		} else if (neighbor != parent[i]) {
			if (back_num[i] > search_num[neighbor]) {
				back_num[i] = search_num[neighbor];
			}
		}
	}
}

void save_back_nums() {
	visited_init();
    visited[start_index] = 1;
    parent[start_index] = -1;
	save_back_num(start_index);
}