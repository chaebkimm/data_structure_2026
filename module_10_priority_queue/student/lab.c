enum { CAPACITY = 10 };

int queue[CAPACITY];
int size = 0;

int (*comp)(int x, int y);
void init_queue(int (*compare)(int x, int y)) {
	size = 0;
	comp = compare;
}

void enqueue(int data) {
	int pos = size;
	/* equal item lands at the end of the equal elements */
	while (pos > 0 && comp(data, queue[pos - 1])) { pos--; }
	for (int i = size; i > pos; i--) {
		queue[i] = queue[i - 1];
	}
	queue[pos] = data;
	size++;
}

int dequeue(void) {
	int most = queue[0];
	for (int i = 1; i < size; i++) {
		queue[i - 1] = queue[i];
	}
	size--;
	return most;
}

enum { USER_SIZE = CAPACITY, EPOCH_SIZE = 5 };

int timelog[USER_SIZE][EPOCH_SIZE * 2];

struct User {
	int login;
	int logout;
	int epoch;
};
struct User users[USER_SIZE];

void init_users(void) {
	for (int id = 0; id < USER_SIZE; id++) {
		users[id].epoch = 0;
		users[id].login = timelog[id][0];
		users[id].logout = timelog[id][1];
	}
}

int next_epoch(int id) {
	int ep = ++users[id].epoch;
	if (ep >= EPOCH_SIZE) {
		return -1;
	}
	users[id].login = timelog[id][ep * 2];
	users[id].logout = timelog[id][ep * 2 + 1];
	return 0;
}

int earlier_logoff(int user_x, int user_y) {
	return users[user_x].logout < users[user_y].logout;
}

int all_login(void) {
	init_users();

	int meeting_time = 0;
	for (int id = 0; id < USER_SIZE; id++) {
		if (users[id].login > meeting_time) {
			meeting_time = users[id].login;
		}
	}

	init_queue(earlier_logoff);
	for (int id = 0; id < USER_SIZE; id++) {
		enqueue(id);
	}
	int out_id = dequeue();

	while (meeting_time >= users[out_id].logout) {
		if (next_epoch(out_id) == -1) { return -1; }
		if (users[out_id].login > meeting_time) { meeting_time = users[out_id].login; }
		enqueue(out_id);
		out_id = dequeue();
	}
	return meeting_time;
}
