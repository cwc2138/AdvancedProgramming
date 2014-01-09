#ifndef __TLIST_H__
#define __TLIST_H__

using namespace std;
#include <vector>
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

	TList<T> operator+=(const TList<T>& right);

	friend ostream& operator<< <T>(ostream& os, const TList<T>& rhs);

	T& operator[](int index);

	const T& operator[](int index) const;

    private:
	vector <T> vec;
};
template <typename T>
int TList<T>::isEmpty() const{
    return vec.empty();
}

template <typename T>
int TList<T>::size() const{
    return vec.size();
}

template <typename T>
void TList<T>::addFront(const T& obj){
    vec.insert(vec.begin(), obj);
}

template <typename T>
T TList<T>::popFront(){
    T obj = vec.front();
    vec.erase(vec.begin());
    return obj;
}

template <typename T>
void TList<T>::reverse(){
    typename vector<T>::iterator it;
    TList<T> temp;

    for(it = vec.begin(); it != vec.end(); it++){
	temp.addFront(*it);
    }

    vec.swap(temp.vec);
}

template <typename T>
TList<T> TList<T>::operator+=(const TList<T>& right){
    vec.insert(vec.end(), right.vec.begin(), right.vec.end());
    return *this;
}

template <typename T>
TList<T> operator+(const TList<T>& left, const TList<T>& right){
    TList<T> temp(left);
    temp += right;
    return temp;
}

template <typename T>
ostream& operator<< (ostream& os, const TList<T>& rhs){
    os << "[";
    typename vector<T>::const_iterator it;
    for(it = rhs.vec.begin(); it != rhs.vec.end(); it++){
	os << *it << " ";
    }
    os << "]";
    return os;
}

template <typename T>
T& TList<T>::operator[](int index){
    return vec[index];
}

template <typename T>
const T& TList<T>::operator[](int index) const{
    return ((TList<T>& )*this)[index];
}
#endif
