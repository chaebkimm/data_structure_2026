struct GraphNode {
	char data;
	int adj_list[10];
	int adj_size;
};

struct GraphNode nodes[10];
int nodes_size = 0;

void alphabet_nodes_init() {
	nodes_size = 10;
	for (int i = 0; i < 10; i++) {
		nodes[i].data = 'A' + i;
		nodes[i].adj_size = 0;
	}
}

void edges_init() {
	int edges[9][2] = {
		{0, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5},
		{3, 4}, {3, 5}, {4, 5}, {6, 7}};
	for (int i = 0; i < 9; i++) {
		int u = edges[i][0];
		int v = edges[i][1];
		int u_adj_end = nodes[u].adj_size++;
		int v_adj_end = nodes[v].adj_size++;
		nodes[u].adj_list[u_adj_end] = v;
		nodes[v].adj_list[v_adj_end] = u;
	}
}

int visit_num[10] = {0};
int visit_time = 0;

void save_visit_num(int i) {
	visit_num[i] = ++visit_time;
	for (int j = 0; j < nodes[i].adj_size; j++) {
		int adj = nodes[i].adj_list[j];
		if (visit_num[adj] == 0) {
			save_visit_num(adj);
		}
	}
}

int group[10] = {0};
int current_group = 0;

void mark_group(int i) {
	visit_num[i] = ++visit_time;
	group[i] = current_group;

	for (int j = 0; j < nodes[i].adj_size; j++) {
		int adj = nodes[i].adj_list[j];

		if (visit_num[adj] == 0) {
			mark_group(adj);
		}
	}
}

void mark_all_groups() {
	for (int i = 0; i < nodes_size; i++) {
		if (visit_num[i] == 0) {
			current_group++;
			mark_group(i);
		}
	}
}

int back_num[10] = {0};
int parent[10] = {0};

void save_back_num(int i) {
	back_num[i] = visit_num[i] = ++visit_time;
	for (int j = 0; j < nodes[i].adj_size; j++) {
		int adj = nodes[i].adj_list[j];
		if (visit_num[adj] == 0) {
			parent[adj] = i;
			save_back_num(adj);
			if (back_num[i] > back_num[adj]) {
				back_num[i] = back_num[adj];
			}
		} else if (adj != parent[i]) {
			if (back_num[i] > visit_num[adj]) {
				back_num[i] = visit_num[adj];
			}
		}
	}
}