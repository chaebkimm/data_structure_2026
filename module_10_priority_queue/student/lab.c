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
	if (ep >= EPOCHS) {
		user.now.login = user.now.logout = -1;
	} else {
		user.now = plans[user.id][ep];
	}
	return user;
}

void init_survey(void) {
	init_pqueue();
	struct User user;
	user.epoch = 0;
	for (int i = 0; i < IDS; i++) {
		user.id = i;
		user.now = plans[i][0];
		enqueue(user);
	}
}

int latest_login_time(void) {
	int latest = 0;
	for (int i = front; i <= rear; i++) {
		if (pq[i].now.login > latest) {
			latest = pq[i].now.login;
		}
	}
	return latest;
}

int survey(void) {
	init_survey();
	int proposal = latest_login_time();
	struct User out = dequeue();

	while (proposal >= out.now.logout) {
		out = next_epoch(out);
		if (out.now.login == -1) { return -1; }
		if (out.now.login > proposal) {
			proposal = out.now.login;
		}
		enqueue(out);
		out = dequeue();
	}
	return proposal;
}
