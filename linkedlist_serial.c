#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

// Maximum value of random numbers
#define MAX_VALUE 65536

// Struct for linked list node
struct list_node {
    int data;
    struct list_node *next;
};

// Variables
struct list_node *head_p = NULL;
int no_of_operations;
int no_of_insert_per_thread;
int no_of_member_per_thread;
int no_of_delete_per_thread;

// Method declarations
int Insert(int value);
int Member(int value);
int Delete(int value);
void doOperations(int *pInt);
void initialize(int);
void initializeOperation(int *no);
void swap(int *a, int *b);
void randomize(int *no, int n);
long getCurrentTime(void);
int generateRandom(void);
void Free_list();


/*
* main method
*/
int main(int arc, char *argv[]) {
    // Validate the arguments
    if (arc != 6) {
        printf("Invalid number of arguments %d\n", arc);
        return -1;
    }
    // Variables
    long start, finish, elapsed;

    // Collect and interpret the arguments
    int no_of_variables = atoi(argv[1]);
    no_of_operations = atoi(argv[2]);
    no_of_member_per_thread = strtod(argv[3], NULL) * no_of_operations; //Member function call count
    no_of_insert_per_thread = strtod(argv[4], NULL) * no_of_operations; //Insert function call count
    no_of_delete_per_thread = strtod(argv[5], NULL) * no_of_operations; //Delete function call count



    // Initializing the linked list
    initialize(no_of_variables);

    //Initialize the random operations
    int operations[no_of_operations];
    initializeOperation(operations);

    // Get the starting time
    start = getCurrentTime();

    // Do the operations
    doOperations(operations);

    // Get the ending time
    finish = getCurrentTime();

    // Calculate the elapsed time
    elapsed = finish - start;

//    free(operations);
    Free_list();
    // Print the time to stdout
    printf("%ld\n", elapsed);
    return 0;
}

//get current time in milli seconds
long getCurrentTime() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000; // caculate milliseconds
    return milliseconds;
}

// Generate random number within the range.
int generateRandom() {
    int value = rand() % MAX_VALUE;
    return value;
}

//array with random numbers.
void initialize(int no_of_variables) {
    srand(time(NULL));
    int Inserted = 0;
    int i;
    for (i = 0; i < no_of_variables; i++) {
        Inserted = Insert(generateRandom());
        if (!Inserted) {
            i--;
        }
    }
}

void initializeOperation(int *no) {
    int i;
    for (i = 0; i < no_of_operations; i++) {
        if (i < no_of_insert_per_thread) {
            *(no + i) = 1;
        } else if (i < no_of_insert_per_thread + no_of_delete_per_thread) {
            *(no + i) = -1;
        } else {
            *(no + i) = 0;
        }
    }
    randomize(no,  no_of_operations);
}

//function to swap to integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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

//Insert a number to linked list.same in the lecture slides
int Insert(int value) {
    struct list_node *curr_p = head_p;
    struct list_node *pred_p = NULL;
    struct list_node *temp_p;

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


//Check whether the number is available.Same in the  lecture slides
int Member(int value) {
    struct list_node *curr_p;

    curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}

// run different operations.
void doOperations(int *operation) {
    long i;
    for (i = 0; i < no_of_operations; i++) {
        if (*(operation + i) == 1) {
            int value = generateRandom();
            Insert(value);
        } else if (*(operation + i) == -1) {
            int value = generateRandom();
            Delete(value);
        } else {
            int value = generateRandom();
            Member(value);
        }
    }
}



// Delete the given number from the linked list.same as the lecture slides
int Delete(int value) {
    struct list_node *curr_p = head_p;
    struct list_node *pred_p = NULL;

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