Zuokun Yu

zy2170

Lab 3

Part1: Works exactly as specified in lab

Part2: Works exactly as specifified in lab


No cool hacks :(



==2327== Memcheck, a memory error detector
==2327== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==2327== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==2327== Command: ./mylist-test
==2327== 
testing addFront(): 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing flipSignDouble(): -9.0 -8.0 -7.0 -6.0 -5.0 -4.0 -3.0 -2.0 -1.0 
testing flipSignDouble() again: 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 
testing findNode(): OK
popped 9.0, the rest is: [ 8.0 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 8.0, the rest is: [ 7.0 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 7.0, the rest is: [ 6.0 5.0 4.0 3.0 2.0 1.0 ]
popped 6.0, the rest is: [ 5.0 4.0 3.0 2.0 1.0 ]
popped 5.0, the rest is: [ 4.0 3.0 2.0 1.0 ]
popped 4.0, the rest is: [ 3.0 2.0 1.0 ]
popped 3.0, the rest is: [ 2.0 1.0 ]
popped 2.0, the rest is: [ 1.0 ]
popped 1.0, the rest is: [ ]
testing addAfter(): 1.0 2.0 3.0 4.0 5.0 6.0 7.0 8.0 9.0 
popped 1.0, and reversed the rest: [ 9.0 8.0 7.0 6.0 5.0 4.0 3.0 2.0 ]
popped 9.0, and reversed the rest: [ 2.0 3.0 4.0 5.0 6.0 7.0 8.0 ]
popped 2.0, and reversed the rest: [ 8.0 7.0 6.0 5.0 4.0 3.0 ]
popped 8.0, and reversed the rest: [ 3.0 4.0 5.0 6.0 7.0 ]
popped 3.0, and reversed the rest: [ 7.0 6.0 5.0 4.0 ]
popped 7.0, and reversed the rest: [ 4.0 5.0 6.0 ]
popped 4.0, and reversed the rest: [ 6.0 5.0 ]
popped 6.0, and reversed the rest: [ 5.0 ]
popped 5.0, and reversed the rest: [ ]
==2327== 
==2327== HEAP SUMMARY:
==2327==     in use at exit: 0 bytes in 0 blocks
==2327==   total heap usage: 18 allocs, 18 frees, 288 bytes allocated
==2327== 
==2327== All heap blocks were freed -- no leaks are possible
==2327== 
==2327== For counts of detected and suppressed errors, rerun with: -v
==2327== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
==2379== Memcheck, a memory error detector
==2379== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==2379== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==2379== Command: ./revecho haha yay dude unicorns
==2379== 
unicorns
dude
yay
haha

dude found
==2379== 
==2379== HEAP SUMMARY:
==2379==     in use at exit: 0 bytes in 0 blocks
==2379==   total heap usage: 4 allocs, 4 frees, 64 bytes allocated
==2379== 
==2379== All heap blocks were freed -- no leaks are possible
==2379== 
==2379== For counts of detected and suppressed errors, rerun with: -v
==2379== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)


Part 1: Implementation of a linked list. Functions include:
struct Node *addFront(struct List *list, void *data)
void traverseList(struct List *list, void (*f)(void *))
void flipSignDouble(void *data)
int compareDouble(const void *data1, const void *data2) 
struct Node *findNode(struct List *list, const void *dataSought, int (*compar)(const void *, const void *))
void *popFront(struct List *list)
void removeAllNodes(struct List *list)
struct Node *addAfter(struct List *list, 
struct Node *prevNode, void *data)
void reverseList(struct List *list)
A static library that contains the linked list object files is created for part 2

Part 2: Reads any number of command line arguments and prints them in the reverse order. Also determines if the string "dude" is one of the arguments