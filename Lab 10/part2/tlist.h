#ifndef __TLIST_H__
#define __TLIST_H_

using namespace std;
#include <list>
#include <iostream>

template <typename T>
class TList;
template <typename T>
ostream& operator<<(ostream& os, const TList<T>& rhs);
template <typename T>
TList<T> operator+(const TList<T>& left, const TList<T>& right);

template <typename T>
class TList{
    public:
	int isEmpty() const;

	int size() const;

	void addFront(const T& obj);

	T popFront();

	void reverse();

	TList& operator+=(const TList<T>& right);

	friend ostream& operator<< <T>(ostream& os, const TList<T>& rhs);

	T& operator[](int index);

	const T& operator[](int index) const;
    private:
	list<T> l;
};

template <typename T>
int TList<T>::isEmpty() const{
    return l.isEmpty();
}

template <typename T>
int TList<T>::size() const{
    return l.size();
}

template <typename T>
void TList<T>::addFront(const T& obj){
    l.push_front(obj);
}

template <typename T>
T TList<T>::popFront(){
    T obj = l.front();
    l.pop_front();
    return obj;
}

template <typename T>
void TList<T>::reverse(){
    l.reverse();
}

template <typename T>
TList<T>& TList<T>::operator+=(const TList<T>& right){
    typename list<T>::const_iterator it;
    for(it = right.l.begin(); it != right.l.end(); it++){
	l.push_back(*it);
    }
    return *this;
}

template <typename T>
TList<T> operator+(const TList<T>& lhs, const TList<T>& rhs){
    TList<T> t(lhs);
    t += rhs;
    return t;
}

template <typename T>
ostream& operator<<(ostream& os, const TList<T>& rhs){
    os << "{";
    typename list<T>::const_iterator it;
    for(it = rhs.l.begin(); it != rhs.l.end(); it++){
	os << *it << " ";
    }
    os << "}";
    return os;
}

template <typename T>
T& TList<T>::operator[](int index){
    typename list<T>::iterator it;
    it = l.begin();
    for(int i = 0; i < index; i++){
	it++;
    }
    return *it;
}

template <typename T>
const T& TList<T>::operator[](int index) const{
    return ((TList<T>& )*this)[index]; //cast
}
#endif

