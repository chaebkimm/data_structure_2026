/* maze data */

enum { N = 5 };

int maze[N][N] = {
	{0, 0, 0, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 1, 1, 1, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 0, 0}
};

struct point {
	int y;
	int x;
};

int is_wall(struct point p) { return maze[p.y][p.x] == 0; }

/* iteration helpers */

struct point cur_point;
int state;

void init_iter(struct point p) {
	cur_point = p;
	state = 0;
}

int has_next_iter(void) { return state < 4; }

/* only for interior points */
struct point next_iter(void) {
	struct point p = cur_point;
	switch (state) {
		case 0: p.x += 1; break;
		case 1: p.x -= 1; break;
		case 2: p.y += 1; break;
		case 3: p.y -= 1; break;
	}
	++state;
	return p;
}

/* queue */

struct point queue[N * N];
int front = 0;
int rear = -1;

void init_queue(void) {
	front = 0;
	rear = -1;
}
int is_empty_queue(void) { return front > rear; }
void enqueue(struct point data) { queue[++rear] = data; }
struct point dequeue(void) { return queue[front++]; }

/* breadth-first search */

int distance[N][N];
void set_distance(struct point p, int d) { distance[p.y][p.x] = d; }
int get_distance(struct point p) { return distance[p.y][p.x]; }

enum { INF = N * N };
void init_bfs(struct point s) {
	init_queue();
	struct point p;
	for (p.y = 0; p.y < N; p.y++) {
		for (p.x = 0; p.x < N; p.x++) {
			set_distance(p, INF);
		}
	}
	if (!is_wall(s)) {
		set_distance(s, 0);
		enqueue(s);
	} 
}

/* start must be within the maze; a wall start leaves all distances INF */
void bfs(struct point start) {
	init_bfs(start);
	while (!is_empty_queue()) {
		struct point cur = dequeue();
		int cur_dist = get_distance(cur);
		init_iter(cur);
		while (has_next_iter()) {
			struct point p = next_iter();
			if (is_wall(p) || get_distance(p) != INF) {
				continue;
			}
			set_distance(p, cur_dist + 1);
			enqueue(p);
		}
	}
}