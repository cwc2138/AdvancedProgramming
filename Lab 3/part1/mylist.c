#include "mylist.h"
#include <stdlib.h>
#include <stdio.h>

struct Node *addFront(struct List *list, void *data){
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));

    if(newNode == NULL){
	perror("malloc failed");
	return NULL;
    }
    (*newNode).data = data;

    if((*list).head == 0){
	(*newNode).next = NULL;
	(*list).head = newNode;
	return newNode;
    }
    else{
	(*newNode).next = (*list).head;
	(*list).head = newNode;
	return newNode;
    }
}

void traverseList(struct List *list, void(*f)(void *)){
    struct Node *headCopy = (*list).head;
    while(headCopy){
	f((*headCopy).data);
	headCopy = (*headCopy).next;
    } 
}

struct Node *findNode(struct List *list, const void *dataSought, int(*compar)(const void *, const void *)){
    struct Node *headCopy = (*list).head;
    while((headCopy)){
	if(compar(((*headCopy).data), dataSought) == 0){
	    return headCopy;
	}
	headCopy = (*headCopy).next;
    }
    return NULL;
}

int compareDouble(const void *data1, const void *data2){
    if(*(double *)data1 == *(double *)data2){
	return 0;
    }
    else{
	return 1;
    }
}

void flipSignDouble(void *data){
    *(double *)data = -1 * *(double *)data;
}

void *popFront(struct List *list){
    void *data;
    struct Node *toFree;
    if((*list).head == NULL){
	return NULL;
    }
    else{
	data = (*(*list).head).data;
	toFree = (*list).head;
	(*list).head = (*(*list).head).next;
	free(toFree);
	return data;
    }
}

void removeAllNodes(struct List *list){
    while((*list).head != NULL){
	popFront(list);
    }
}


struct Node *addAfter(struct List *list, struct Node *prevNode, void *data){

    if(prevNode == NULL){
	addFront(list, data);
    }
    else{
	struct Node *headCopy = (*list).head;

	struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
	(*newNode).data = data;

       	while(headCopy){
    	    if((*headCopy).data == (*prevNode).data){
    		(*newNode).next = (*headCopy).next;
    		(*headCopy).next = newNode;
    		return newNode;
    	    }
    	    else{
	     	headCopy = (*headCopy).next;
    	    }
	}
    }
}

void reverseList(struct List *list){
    struct Node *prv = NULL;
    struct Node *cur = (*list).head;
    struct Node *nxt = NULL;

    while(cur){
	nxt = (*cur).next;
	(*cur).next = prv;
	prv = cur;
	cur = nxt;
    }

    (*list).head = prv;
}


