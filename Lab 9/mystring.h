#ifndef __MYSTRING_H__
#define __MYSTRING_H__

using namespace std;

#include <iostream>
class MyString {

    public:

	// default constructor
	MyString();

	// constructor
	MyString(const char* p);

	// destructor
	~MyString();

	// copy constructor 
	MyString(const MyString& s);

	// assignment operator
	MyString& operator=(const MyString& s);

	//+= operator
	MyString& operator+=(const MyString& s);

	// returns the length of the string
	int length() const { return len; }
	
	// operator+
	//friend MyString operator+(const MyString& s1, const MyString& s2); No longer needs to be a friend since
	//we don;t directly access data fields

	// put-to operator
	friend ostream& operator<<(ostream& os, const MyString& s);

	// get-from operator
	friend istream& operator>>(istream& is, MyString& s);

	// operator[]
	char& operator[](int i);

	// operator[] const
	const char& operator[](int i) const;

	friend bool operator<(const MyString& s1, const MyString& s2);

	friend bool operator==(const MyString& s1, const MyString& s2);

	friend bool operator!=(const MyString& s1, const MyString& s2);

	friend bool operator>(const MyString& s1, const MyString& s2);

	friend bool operator<=(const MyString& s1, const MyString& s2);

	friend bool operator>=(const MyString& s1, const MyString& s2);

    private:

	char* data;

	int len;
};

MyString operator+(const MyString& s1, const MyString& s2);

#endif
