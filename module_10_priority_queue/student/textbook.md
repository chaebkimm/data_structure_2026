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

An array for the waiting data, and the two positions `front` and `rear`. The array needs one position for each logout time in the plan. The queue also needs the rule that says which data has higher priority. The rule is a function, and the queue keeps that function’s address so that it can call it, which lets the same queue code work with any rule.

### What should we do to initialize the priority queue?

Store the rule, and set `front` to `0` and `rear` to `-1`. The first data should go into position `0`, and putting data in increments `rear`, so `rear` starts at `-1`. The queue starts empty, and it is empty when `front` is one position after `rear`, so `front` starts at `0`.

### What should we do to put new data in?

We assume the array has a free position after `rear`. Start from the data at `rear` and compare it with the new data. If the new data has higher priority, move the stored data to the position after it, and go on to the data before it. Stop when the stored data has the same or higher priority, or when the data at `front` has been passed, so the search never reaches the positions before `front`. Check for `front` before comparing: then, if there is no data, the search stops before the first comparison, and the position left open is the free position after `rear`. Put the new data into the position left open, and increment `rear`. 

### What should we do to take data out?

We assume there is data to take out. Take out the data at `front`, and increment `front`. The position it leaves is not used again until the queue is initialized again, so the array needs room for all the data that goes in, not only for the data waiting at one time.

### What data does the meeting problem need?

A table of the plan, with one row for each user, holding that user’s login and logout times in time order. For each user, store the current login time, logout time, and the number of the selected pair in that user’s row. The queue holds only the users’ numbers.

### What rule do we give the priority queue?

The user who logs out earlier has higher priority, so here the highest priority goes with the smallest time. The rule receives two users’ numbers and looks up their logout times to compare them.

### What should we do to start looking for the meeting time?

Set every user to the first login and logout in the plan. Find the latest login time by comparing all the users’ login times. Initialize the priority queue with the rule, put every user’s number in, and take one out: that user has the earliest logout time.

### How do we check whether a meeting is possible?

When the earliest logout time is later than the latest login time, the meeting time is the latest login time.

### What should we do while no meeting is possible?

Move the user with the earliest logout time on to the next planned login and logout. If there is none, there is no meeting at all, and we stop. If the new login time is later than the latest login time, it becomes the latest login time. Put the user’s number back in, take out the next one, and check again. 

## New C syntax explained

### How do we keep a function’s address in a variable?

With a function pointer. It is declared like the function itself, with `(*name)` in place of the function’s name:

```c
int (*compare)(int x, int y);
```

`compare` can hold the address of any function that takes two `int` values and returns an `int`. The parentheses are needed: without them, the line declares a function that returns a pointer.

### How do we get a function’s address?

Put `&` before the function’s name, as for a variable. Here the address of `earlier_logout` is given to `init_queue`, whose parameter is a function pointer:

```c
void init_queue(int (*compare_fp)(int x, int y));

init_queue(&earlier_logout);
```

### How do we call the function through the pointer?

Write the pointer’s name where the function’s name would go:

```c
compare(data, queue[pos - 1])
```

This calls the function whose address `compare` holds. The queue code never names `earlier_logout`, so the same code works with any rule.

## C code

### Priority queue implementation

#### Global variables

```c
enum { CAPACITY = 10 };

int queue[CAPACITY];
int front, rear;

/* Function pointer for comparing elements */
int (*compare)(int x, int y);
```

#### Initialize global variables

```c
void init_queue(int (*compare_fp)(int x, int y)) {
	front = 0;
	rear = -1;
	compare = compare_fp;
}
```

#### Put data into the priority queue

```c
void enqueue(int data) {
	int pos = rear + 1;
	while (pos > front && compare(data, queue[pos - 1])) {
		queue[pos] = queue[pos - 1];
		pos--;
	}
	queue[pos] = data;
	rear++;
}
```

#### Take data out of the priority queue

```c
int dequeue(void) {
	int most = queue[front];
	front++;
	return most;
}
```

### Meeting time problem

#### Keep each user’s current login and logout

```c
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
```

#### Set every user to the first login and logout

```c
void init_users(void) {
	for (int id = 0; id < N_USERS; id++) {
		users[id].epoch = 0;
		users[id].login = timelogs[id][0];
		users[id].logout = timelogs[id][1];
	}
}
```

#### Move a user on to the next login and logout

```c
int next_epoch(int id) {
	int ep = ++users[id].epoch;
	if (ep >= N_EPOCHS) {
		return -1;
	}
	users[id].login = timelogs[id][ep * 2];
	users[id].logout = timelogs[id][ep * 2 + 1];
	return 0;
}
```

#### Find the latest login time

```c
int latest_login_time(void) {
	int latest_time = 0; /* times are never negative */
	for (int id = 0; id < N_USERS; id++) {
		if (users[id].login > latest_time) {
			latest_time = users[id].login;
		}
	}
	return latest_time;
}
```

#### Put every user in and take out the earliest logout

```c
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
```

#### Move the earliest logout on until everyone is logged in

```c
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
```
