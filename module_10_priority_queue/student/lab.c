enum { IDS = 3, EPOCHS = 3 };

struct Session {
	int login;
	int logout;
};

struct User {
	int id;
	int epoch;
	struct Session now;
};
struct User pq[IDS * EPOCHS];
int front, rear;

void init_pqueue(void) {
	front = 0;
	rear = -1;
}

int compare(struct User x, struct User y) {
	return x.now.logout < y.now.logout;
}

void enqueue(struct User user) {
	int i = rear + 1;
	while (i > front && compare(user, pq[i - 1])) {
		pq[i] = pq[i - 1];
		i--;
	}
	pq[i] = user;
	rear++;
}

struct User dequeue(void) {
	return pq[front++];
}

struct Session plans[IDS][EPOCHS] = {
	{{5, 6}, {8, 9}, {11, 13}},
	{{2, 5}, {7, 8}, {12, 15}},
	{{1, 3}, {5, 7}, {9, 14}}
};

struct User next_epoch(struct User user) {
	int ep = ++user.epoch;
	if (ep < EPOCHS) {
		user.now = plans[user.id][ep];
	}
	return user;
}

void init_meeting(void) {
	init_pqueue();
	struct User user = {.epoch = 0};
	for (int i = 0; i < IDS; i++) {
		user.id = i;
		user.now = plans[i][0];
		enqueue(user);
	}
}

int latest_login(void) {
	int latest = -1;
	for (int i = front; i <= rear; i++) {
		int cur = pq[i].now.login;
		if (cur > latest) {
			latest = cur;
		}
	}
	return latest;
}

int meeting_time(void) {
	init_meeting();
	int t = latest_login();
	struct User out = dequeue();

	while (t >= out.now.logout) {
		out = next_epoch(out);
		if (out.epoch >= EPOCHS) { return -1; }
		if (out.now.login > t) {
			t = out.now.login;
		}
		enqueue(out);
		out = dequeue();
	}
	return t;
}
