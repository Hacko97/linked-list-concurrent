
******************* Commands to compile C files **************************
1.Serial Linkedlist
	gcc -g -Wall -o linkedlist_serial linkedlist_serial.c

2.Linked list with Mutex
	gcc -g -Wall -o linkedlist_mutex linkedlist_mutex.c -lm -lpthread

3.Linked list with read write lock
	gcc -g -Wall -o linkedlist_r_w_lock linkedlist_r_w_lock.c -lm -lpthread

***************************************************************************

****************** Commands to run the compiled files *********************
1.Serial Linkedlist
        ./linkedlist_serial <num of elements> <num of operations> <fraction of member> <fraction of insert> <fraction of delete>

2.Linked list with Mutex
        ./linkedlist_mutex <num of elements> <num of operations> <fraction of member> <fraction of insert> <fraction of delete> <no of threads>
 
3.Linked list with read write lock
        ./linkedlist_r_w_lock <num of elements> <num of operations> <fraction of member> <fraction of insert> <fraction of delete> <no of threads>

********************Examples**********************************************************
Case 3 : n = 1000, m = 10000, mMember = 0.50, mInsert = 0.25, mDelete = 0.25
1.Serial Linkedlist
        ./linkedlist_serial 1000 10000 0.5 0.25 0.25

2.Linked list with Mutex - Number of threads - 4
        ./linkedlist_mutex 1000 10000 0.5 0.25 0.25 4

3.Linked list with read write lock - Number of threads - 8
        ./linkedlist_rw_lock 1000 10000 0.5 0.25 0.25 8
 

******************************************************************************
***Run the python file to find average, standard deviation and no of samples**
    python evaluate.py

*******************************************************************************