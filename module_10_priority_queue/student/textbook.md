# Chapter 10. Choosing by Priority

A queue processes data in arrival order. Sometimes the data with the highest priority is needed. We will implement a simple data structure for this. As an example, we will use it to find the earliest time when every user plans to be logged in.

## Thinking logically

### What data structure fits if we need to process the highest-priority data next?

A data structure similar to a queue or a stack fits: data goes in, waits, and is taken out one at a time. The only thing that changes is the rule for what comes out next, which is now the data with the highest priority.

### How do we implement a simple data structure for this?

Arrival order no longer determines which data comes out next. We keep the data in priority order, so the first data is always the one to take out. 

### Which positions describe the current data?

The waiting data sits in an array in priority order, from the highest-priority data at front to the lowest-priority data at rear. Taking data out increments front, and putting new data in increments rear. 

### Which positions describe the empty data structure?

When only one piece of data is waiting, front and rear are the same position. Taking that data out increments front, so the data structure is empty when front is one position after rear.

### How does new data find its place?

All the data with lower priority than the new data should be to the right of the new data. So we move that data one position to the right, and the new data goes into the vacant position.

### How do we take out the highest-priority data?

The highest-priority data is at front, so we take that data out. 

### Given each user’s planned login and logout times, when can everyone meet?

Everyone can meet at a time when every user has logged in and no user has logged out yet. Each user plans to log in and log out several times, and we look for the earliest time when all of them are logged in. 

### What are the key properties we need to keep track of to solve the problem?

We look at one login and logout of each user at a time, starting with the first ones. Among these, we want to track the latest login time and the earliest logout time. Everyone has logged in by the latest login time, and no one has logged out before the earliest logout time. If the earliest logout time is later than the latest login time, we can set the meeting time to the latest login time.

### What changes if no meeting is possible with the current login and logout of each user?

As time passes, the user with the earliest logout time logs out. Then we move on to that user’s next planned login and logout. The earliest logout time and the latest login time are updated, and we compare them again.

### How do we update the latest login time?

The user with the latest login time cannot be the user who is moving on. If it were the same user, the latest login time would be earlier than the earliest logout time, and the meeting could have been held. So the latest login time is still among the logins we are looking at, and we only have to compare it with the new login time and take the later one.

### How do we update the earliest logout time?

Because the user with the earliest logout time has moved on, we have to find which user has the earliest logout time now. Keeping the users in logout order makes the next earliest logout available, and this is what we built the data structure for. 

## Calculating efficiency

### How much work is putting new data in?

Suppose n pieces of data are waiting. If the new data has the highest priority, it is compared with all n, and all n move. So putting data in takes at most n comparisons and n moves, and the work grows with the amount of waiting data.

### How much work is taking data out?

A fixed amount of work. The highest-priority data is already at front, so nothing is compared and nothing moves, however much data is waiting.

### How much work is finding the latest login?

Every login time in the plan is compared with the latest login time at most once: the first ones at the start, and each later one when its user moves on. So the work is at most one comparison for each login in the plan.

### How much work is finding the earliest logout?

A user is put into the data structure at most once for each logout time in the plan. Each time, it takes fewer comparisons and moves than there are users. So the work is at most the number of logouts in the plan times the number of users.

### How much storage is needed?

Every time a user is put in, the user takes a new position, because the positions before front are not used again. So the array needs one position for each logout time in the plan, although at most all the users are waiting at one time.

## Glossary

### Priority

What decides which data comes out next. In the meeting problem, the user who logs out earlier has the higher priority.

### Priority queue

A data structure in which the data with the highest priority comes out next, whatever the arrival order. It is the “data structure” of this chapter.

### Enqueue

To put new data into a queue or a priority queue. Here new data is put at its place in priority order.

### Dequeue

To take data out of a queue or a priority queue. In a priority queue, the data taken out is the one with the highest priority.

### Front

The position of the data that comes out next. Here it holds the highest-priority data.

### Rear

The position of the last waiting data. Here it holds the lowest-priority data.

### Epoch

The number of the login and logout we are currently looking at for a user, counted from `0`.

## Invariant

### What is always true about the waiting data?

The waiting data is in priority order: no data has higher priority than the data before it. This is true at the start, when there is no data. Putting data in keeps it true, because new data is placed after all the stored data with the same or higher priority. Taking data out keeps it true, because removing the first data leaves the rest in order. This is why the highest-priority data is always at front when data is waiting.

### What is always true about front and rear?

The waiting data sits exactly in the positions from front to rear, so front is never more than one position after rear. Both only increase: putting data in increments rear, and taking data out increments front. Two assumptions keep this true: we put data in only when there is a free position after rear, and we take data out only when there is data.

### What keeps the order valid when logout times change?

A user’s logout time changes only when the user moves on, and by then the user has been taken out. The users still waiting keep their logout times, so their order stays valid.

### What is always true while we look for the meeting time?

No meeting is possible before the latest login time. This is true at the start, because before that time the user who logs in last has not logged in yet. When a user moves on, that user is logged out from the earliest logout time until the new login time, so no meeting is possible before the new login time either. So when the earliest logout time is later than the latest login time, the latest login time is not just a possible meeting time: it is the earliest one.

## Coding plan

### What data does the priority queue need?

An array for the waiting data, and the two positions `front` and `rear`. The array needs one position for each logout time in the plan. Each piece of data is a whole user: the user’s number, which login and logout we are looking at, and those two times.

### What should we do to initialize the priority queue?

Set `front` to `0` and `rear` to `-1`. The first data should go into position `0`, and putting data in increments `rear`, so `rear` starts at `-1`. The queue starts empty, and it is empty when `front` is one position after `rear`, so `front` starts at `0`.

### What should we do to put new data in?

We assume the array has a free position after `rear`. Start from the data at `rear` and compare it with the new data. If the new data has higher priority, move the stored data to the position after it, and go on to the data before it. Stop when the stored data has the same or higher priority, or when the data at `front` has been passed, so the search never reaches the positions before `front`. Check for `front` before comparing: then, if there is no data, the search stops before the first comparison, and the position left open is the free position after `rear`. Put the new data into the position left open, and increment `rear`. 

### What should we do to take data out?

We assume there is data to take out. Take out the data at `front`, and increment `front`. The position it leaves is not used again until the queue is initialized again, so the array needs room for all the data that goes in, not only for the data waiting at one time.

### What data does the meeting problem need?

A table of the plan, with one row for each user, holding that user’s logins and logouts as pairs in time order. Each user in the queue carries its own number, the number of the pair it is on, and a copy of that pair.

### What rule do we give the priority queue?

The user who logs out earlier has higher priority, so here the highest priority goes with the smallest time. The rule receives two users and compares the logout times they carry.

### What should we do to start looking for the meeting time?

Initialize the priority queue, and put every user in with the first login and logout in the plan. Find the latest login time by comparing the login times of all the users in the queue, starting from `-1`, which is smaller than any time. Take one user out: that user has the earliest logout time.

### How do we check whether a meeting is possible?

When the earliest logout time is later than the latest login time, the meeting time is the latest login time.

### What should we do while no meeting is possible?

Move the user with the earliest logout time on to the next planned login and logout. If there is none, there is no meeting at all, and we stop. If the new login time is later than the latest login time, it becomes the latest login time. Put the user back in, take out the next one, and check again.

## New C syntax explained

### How can a structure hold another structure?

A member of a structure can itself be a structure. A user holds the current login and logout as one `struct Session`, and the times are reached with two dots, as in `out.now.logout`:

```c
struct Session {
	int login;
	int logout;
};

struct User {
	int id;
	int epoch;
	struct Session now;
};
```

### What happens when a structure is assigned or passed?

The same as with an `int`: the whole value is copied. Passing a user to `compare` or `enqueue`, getting one back from `dequeue` or `next_epoch`, and `u.now = plans[u.id][ep];` all make copies, and none of them changes the plan table.

### How do we set only some members when creating a structure?

Name each member with a dot. Members that are not named become `0`:

```c
struct User u = {.epoch = 0};
```

## C code

### Priority queue implementation

#### Users and their current login and logout

```c
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
```

#### Priority queue

```c
/* Slots are never reused: one slot for every enqueue, one per session */
struct User pq[IDS * EPOCHS];
int front, rear;
```

#### Initialize the priority queue

```c
void init_pqueue(void) {
	front = 0;
	rear = -1;
}
```

#### The user who logs out earlier has higher priority

```c
/* Nonzero if x has higher priority; strict <, so ties keep arrival order */
int compare(struct User x, struct User y) {
	return x.now.logout < y.now.logout;
}
```

#### Put data into the priority queue

```c
void enqueue(struct User user) {
	int i = rear + 1;
	/* Test front first, so pq[i - 1] is never read once front is passed */
	while (i > front && compare(user, pq[i - 1])) {
		pq[i] = pq[i - 1];
		i--;
	}
	pq[i] = user;
	rear++;
}
```

#### Take data out of the priority queue

```c
struct User dequeue(void) {
	return pq[front++]; /* the data at front, then front moves on */
}
```

### Meeting time problem

#### The plan

```c
struct Session plans[IDS][EPOCHS] = {
	{{5, 6}, {8, 9}, {11, 13}},
	{{2, 5}, {7, 8}, {12, 15}},
	{{1, 3}, {5, 7}, {9, 14}}
};
```

#### Move a user on to the next login and logout

```c
struct User next_epoch(struct User u) {
	int ep = ++u.epoch;
	/* After the last session, epoch is EPOCHS and now is left as it was */
	if (ep < EPOCHS) {
		u.now = plans[u.id][ep];
	}
	return u;
}
```

#### Put every user in with the first login and logout

```c
void init_meeting(void) {
	init_pqueue();
	struct User u = {.epoch = 0};
	for (int i = 0; i < IDS; i++) {
		u.id = i;
		u.now = plans[i][0];
		enqueue(u);
	}
}
```

#### Find the latest login time

```c
/* Called once, right after init_meeting(), while every user is queued */
int latest_login(void) {
	int latest = -1; /* smaller than any time */
	for (int i = front; i <= rear; i++) {
		int cur = pq[i].now.login;
		if (cur > latest) {
			latest = cur;
		}
	}
	return latest;
}
```

#### Move the earliest logout on until everyone is logged in

```c
int meeting_time(void) {
	init_meeting();
	int t = latest_login();
	struct User out = dequeue();

	/* A user who logs out at t has already left, hence >= */
	while (t >= out.now.logout) {
		out = next_epoch(out);
		if (out.epoch >= EPOCHS) {
			return -1;
		}
		if (out.now.login > t) {
			t = out.now.login;
		}
		enqueue(out);
		out = dequeue();
	}
	return t;
}
```