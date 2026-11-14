/* Priority queue implementation
 * Slots are never reused, so CAPACITY must cover every enqueue:
 * survey() enqueues at most N_USERS * N_EPOCHS times. No full/empty checks. */
enum { CAPACITY = 10 };

int queue[CAPACITY];
int front, rear;

/* Function pointer for comparing elements */
int (*compare)(int x, int y);
void init_queue(int (*compare_fp)(int x, int y)) {
	front = 0;
	rear = -1;
	compare = compare_fp;
}

/* Insert an element; among equal priorities, earlier arrivals stay in front */
void enqueue(int data) {
	int pos = rear + 1;
	while (pos > front && compare(data, queue[pos - 1])) {
		queue[pos] = queue[pos - 1];
		pos--;
	}
	queue[pos] = data;
	rear++;
}

/* Remove and return the highest priority element by moving front.
 * Nothing is shifted, but the slot is never reused. */
int dequeue(void) {
	int most = queue[front];
	front++;
	return most;
}

/* Process time logs to get current login status */
enum { N_USERS = 3, N_EPOCHS = 3 };

int timelogs[N_USERS][N_EPOCHS * 2] = {
	{5, 6, 8, 9, 11, 13}, 
	{2, 5, 7, 8, 12, 15}, 
	{1, 3, 5, 7, 9, 14}
};

struct User {
	int login;
	int logout;
	int epoch;
};
struct User users[N_USERS];

void init_users(void) {
	for (int id = 0; id < N_USERS; id++) {
		users[id].epoch = 0;
		users[id].login = timelogs[id][0];
		users[id].logout = timelogs[id][1];
	}
}

int next_epoch(int id) {
	int ep = ++users[id].epoch;
	if (ep >= N_EPOCHS) {
		return -1;
	}
	users[id].login = timelogs[id][ep * 2];
	users[id].logout = timelogs[id][ep * 2 + 1];
	return 0;
}

/* Survey to determine the optimal meeting time */

/* Return the latest of the users' current login times */
int latest_login_time(void) {
	int latest_time = 0; /* times are never negative */
	for (int id = 0; id < N_USERS; id++) {
		if (users[id].login > latest_time) {
			latest_time = users[id].login;
		}
	}
	return latest_time;
}

/* x and y are user ids; the user who logs out earlier has higher priority */
int earlier_logout(int user_x, int user_y) {
	return users[user_x].logout < users[user_y].logout;
}

/* Put every user in the queue and return the one who logs out first */
int first_logout_id(void) {
	init_queue(&earlier_logout);
	for (int id = 0; id < N_USERS; id++) {
		enqueue(id);
	}
	return dequeue();
}

/* Find the earliest time when every user is logged in, or -1 if none.
 * The candidate is the latest current login. While some user has already
 * logged out by then, move that user to their next login and raise the
 * candidate if that login is later. */
int survey(void) {
	init_users();
	int meeting_time = latest_login_time();
	int out_id = first_logout_id();
	
	/* Survey to find the earliest meeting time */
	while (meeting_time >= users[out_id].logout) {
		/* Move this user to their next login; stop if there is none */
		if (next_epoch(out_id) == -1) {
			return -1;
		}
		/* Update the meeting time if this user has a later login time */
		if (users[out_id].login > meeting_time) {
			meeting_time = users[out_id].login;
		}
		/* Reinsert the user into the priority queue */
		enqueue(out_id);
		/* Get the next user with the earliest logout time */
		out_id = dequeue();
	}
	return meeting_time;
}

/* Trace with the sample data:
 *   start: candidate 5; first out: user 2 (logout 3)
 *   user 2 -> login 5;  candidate 5;  next out: user 1 (logout 5)
 *   user 1 -> login 7;  candidate 7;  next out: user 0 (logout 6)
 *   user 0 -> login 8;  candidate 8;  next out: user 2 (logout 7)
 *   user 2 -> login 9;  candidate 9;  next out: user 1 (logout 8)
 *   user 1 -> login 12; candidate 12; next out: user 0 (logout 9)
 *   user 0 -> login 11; candidate 12; next out: user 0 (logout 13)
 *   13 > 12, so the meeting time is 12 */