#include <stdio.h>
#include <stdlib.h>
#include "strlist.h"

static void die(const char *msg){
    perror(msg);
    exit(1);
}

StrList::StrList(){
    initList(&list);
}

StrList::StrList(const StrList& l){
    initList(&list);
    struct Node *newNode = l.list.head;
    while(newNode){
	MyString *s = new MyString(*(MyString *)newNode->data);
	if(::addFront(&list, s) == NULL){
	    die("addFront() failed");
	}
	newNode = newNode->next;
    }
    reverse();
}

StrList::~StrList(){
    while(list.head){
    	MyString *s = (MyString *)::popFront(&list);
	delete s;
    }
}

StrList& StrList::operator=(const StrList& l){
    if(this == &l){
	return *this;
    }
    while(list.head){
	MyString *s = (MyString *)::popFront(&list);
	delete s;
    }

    struct Node *newNode = l.list.head;
    while(newNode){
	MyString *s = new MyString(*(MyString *)newNode->data);
	if(::addFront(&list, s) == NULL){
	    die("addFront() failed");
	}
	newNode = newNode->next;
    }
    reverse();
    return *this;
}

int StrList::size() const{
    int size = 0;
    struct Node *newNode = list.head;
    while(newNode){
	size++;
	newNode = newNode->next;
    }
    return size;
}

void StrList::addFront(const MyString& s){
    MyString *temp = new MyString(s);
    if(::addFront(&list, temp) == NULL){
	die("addFront() failed");
    }
}

MyString StrList::popFront(){
    MyString *temp = (MyString *)::popFront(&list);
    MyString temp2(*temp);
    delete temp;
    return temp2;
}

void StrList::reverse(){
    ::reverseList(&list);
}

StrList& StrList::operator+=(const StrList& l){
    reverse();
    struct Node *newNode = l.list.head;
    while(newNode){
	MyString *s = new MyString(*(MyString *)newNode->data);
	if(::addFront(&list, s) == NULL){
	    die("addFront() failed");
	}
	newNode = newNode->next;
    }
    reverse();
    return *this;
}

StrList operator+(const StrList& left, const StrList& right){
    StrList temp(left);
    temp += right;
    return temp;
}

ostream &operator<<(ostream& os, const StrList& l){
    os << "{";
    struct Node *newNode = l.list.head;
    while(newNode){
	os << *(MyString *)newNode->data << " ";
	newNode = newNode->next;
    }
    os << "}";
    return os;
}

MyString& StrList::operator[](int index){
    struct Node *newNode = list.head;
    for(int counter = 0; counter < index; counter++){
	newNode = newNode->next;
    }
    return *(MyString *)newNode->data;
}

const MyString& StrList::operator[](int index) const{
    return ((StrList& )*this)[index];
}

