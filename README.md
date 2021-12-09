# linked-list-concurrent
Implement a linked list as a:
1. Serial program
2. Parallel program (based on Pthreads) with one mutex for the entire linked list
3. Parallel program (based on Pthreads) with read-write locks for the entire linked list

Your implementation should support Member( ), Insert( ), and Delete( ) functions. Populate the linked list with n random, but unique values. Make sure to set a different random seed for each execution. Each value should be between 0 and 2^16 – 1. Then perform m random Member, Insert, and Delete operations (simultaneously) on the link list. Let mMember, mInsert, and mDelete be the fractions of operations of each type. You may use any values within 0 and 2^16 – 1 while performing these three operations. However, to simplify the implementation, a new value inserted into the list cannot be a value already in the list (it could be a value that was initially added to the list, but later removed).
