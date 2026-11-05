enum {CAPACITY = 10};

int queue[CAPACITY];
int size = 0;

int is_empty_queue(void) { return size == 0; }

int (*comp)(int, int);

void enqueue(int data) { 
    int pos = 0;
    while (pos < size && !comp(data, queue[pos])) {pos++;}
    for (int i = size; i > pos; i--) {
        queue[i] = queue[i - 1];
    }
    queue[pos] = data;
    size++;
}

int dequeue(void) { 
    int most = queue[0];
    for (int i = 0; i < size - 1; i++) {
        queue[i] = queue[i + 1];
    }
    size--;
    return most;
}

void init_queue(int (*compare)(int, int)) {
    comp = compare; 
    size = 0;
}

enum {USER_SIZE = CAPACITY, EPOCH_SIZE = 5};

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
    if (ep >= EPOCH_SIZE) {return -1;}
    users[id].login = timelog[id][ep * 2];
    users[id].logout = timelog[id][ep * 2 + 1];  
    return 0;
}

int earlier_logoff(int i, int j) {
    return users[i].logout < users[j].logout;
}

int all_login(void) {
    init_users();

    int last = 0;
    for (int id = 0; id < USER_SIZE; id++) {
        if (users[id].login > users[last].login) {last = id;}
    }

    init_queue(earlier_logoff);
    for (int id = 0; id < USER_SIZE; id++) {
        enqueue(id);
    }
    int go = dequeue();

    while (users[last].login > users[go].logout) {
        if (next_epoch(go) == -1) {return -1;}
        enqueue(go);
        if (users[go].login > users[last].login) {last = go;}
        go = dequeue();
    }
    return users[last].login;
}
