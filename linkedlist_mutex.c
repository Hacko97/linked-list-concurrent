#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

// Maximum value of random numbers
#define MAX_VALUE 65536

// linked list node
struct list_node {
    int    data;
    struct list_node* next;
};

// Variables
struct list_node* head_p = NULL;
pthread_mutex_t mutex;
int no_of_operations_per_thread;
int no_of_operations;
int no_of_insert_per_thread;
int no_of_member_per_thread;
int no_of_delete_per_thread;

// Method declarations
int  Insert(int value);
void initialize(int);
int  Member(int value);
void initializeOperation(int *no);
int  Delete(int value);
void swap(int *a, int *b);
void* doOperations(void*);
void randomize(int *no, int n);
int generateRandom(void);
long current_timestamp(void);
void Free_list();



/*
* main method
*/
int main(int arc, char *argv[]) {
    // Validate the arguments
    if (arc != 7) {
        printf("Invalid number of arguments %d\n", arc);
        return -1;
    }
    // Variables
    long start, finish, elapsed;
    int thread;
    pthread_t* threadHandles;

    // Collect and interpret the arguments
    int no_of_variables = atoi(argv[1]);
    int no_of_threads = atoi(argv[6]);
    no_of_operations= atoi(argv[2]);
    no_of_operations_per_thread = atoi(argv[2]) / no_of_threads;
    no_of_member_per_thread = strtod(argv[3], NULL) * no_of_operations_per_thread;
    no_of_insert_per_thread= strtod(argv[4], NULL) * no_of_operations_per_thread;
    no_of_delete_per_thread = strtod(argv[5], NULL) * no_of_operations_per_thread;


    threadHandles = (pthread_t*) malloc (no_of_threads * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);

    // Initialize the linked list
    initialize(no_of_variables);
    //Initialize the random operations
    int operations[no_of_operations_per_thread];
    initializeOperation(operations);

    // Get the starting time
    start = current_timestamp();

    // Do the operations
    for (thread = 0; thread < no_of_threads; thread++) {

        pthread_create(&threadHandles[thread], NULL, doOperations, (void*)(operations));
    }

    for (thread = 0; thread < no_of_threads; thread++) {
        pthread_join(threadHandles[thread], NULL);
    }

    // Get the ending time
    finish = current_timestamp();


    // Calculate the elapsed time
    elapsed = finish - start;


    Free_list();
    // Print the time to stdout
    printf("%ld", elapsed);
    return 0;
}

// Generate random number within the range.

long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // caculate milliseconds
    return milliseconds;
}

/*
* Generate random number within the range.
*/
int generateRandom() {
    int value = rand() % MAX_VALUE;
    return value;
}

//array with random numbers.

void initialize(int no_of_variables) {
    srand (time(NULL));
    int inserted = 0;
    int i;
    for (i = 0; i < no_of_variables; i++) {
        inserted = Insert(generateRandom());
        if (!inserted) {
            i--;
        }
    }
}

// A function to generate a random permutation of arr[]

void randomize(int *no, int n) {
    // Use a different seed value so that we don't get same
    // result each time we run this program
    srand(time(NULL));

    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n - 1; i > 0; i--) {
        // Pick a random index from 0 to i
        int j = rand() % (i + 1);

        // Swap arr[i] with the element at random index
        swap((no+i), (no+j));
    }
}


void initializeOperation(int *no) {
    int i;
    for (i = 0; i < no_of_operations_per_thread; i++) {
        if (i < no_of_insert_per_thread) {
            *(no + i) = 1;
        } else if (i < no_of_insert_per_thread + no_of_delete_per_thread) {
            *(no + i) = -1;
        } else {
            *(no + i) = 0;
        }
    }
    randomize(no, no_of_operations_per_thread);
}

//function to swap to integers

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// run different operations.

void* doOperations(void *para) {
    int *start = para;
    int i;
    for (i = 0; i < no_of_operations_per_thread; i++) {
        if (*(start + i) == 1) {
            int value = generateRandom();
            pthread_mutex_lock(&mutex);
            Insert(value);

            pthread_mutex_unlock(&mutex);
        } else if (*(start + i) == -1) {
            int value = generateRandom();
            pthread_mutex_lock(&mutex);
            Delete(value);
            pthread_mutex_unlock(&mutex);
        } else {
            int value = generateRandom();
            pthread_mutex_lock(&mutex);
            Member(value);
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
}


//Check whether the number is available.Same in the  lecture slides

int  Member(int value) {
    struct list_node* curr_p;

    curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}


//Insert a number to linked list.same in the lecture slides

int Insert(int value) {
    struct list_node* curr_p = head_p;
    struct list_node* pred_p = NULL;
    struct list_node* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = malloc(sizeof(struct list_node));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL)
            head_p = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    } else {
        return 0;
    }
}

// Delete the given number from the linked list.same as the lecture slides

int Delete(int value) {
    struct list_node* curr_p = head_p;
    struct list_node* pred_p = NULL;

    /* Find value */
    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) {
            head_p = curr_p->next;
            free(curr_p);
        } else {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    } else {
        return 0;
    }
}

void Free_list() {
    struct list_node* succ_p;
    struct list_node *curr_p;

    if (head_p == NULL) return;
    curr_p = head_p;
    while (curr_p != NULL) {
        succ_p = curr_p->next;
        free(curr_p);
        curr_p = succ_p;
    }

}
