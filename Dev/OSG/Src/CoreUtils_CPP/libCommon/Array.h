#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

#include <stdlib.h>

template <class T>
struct Array {
	T	 *array;
	int  size;
	
	Array(int sz = 0);
	Array(const Array & a);
 	~Array();

	void	append(T e);
	void	append(Array& a);
	void	append(Array& a, int from);
	void	insert(T e, int index);
	T		remove(int index);
	virtual T& operator[] (int index);
	virtual const T& operator[] (int index) const;
	void	setSize(int sz);
	void	init(int sz, T aTVal = 0);

	Array<T> & operator=(const Array & a);

protected:
	void assertIndex(int index) const;
};

template <class T>
std::ostream& operator <<(std::ostream& os, const Array<T>& a);

template <class T>
Array<T>::Array(int sz) {
	size = sz;
	array = new T[size];
}

template <class T>
Array<T>::~Array() {
	delete [] array;
}

template <class T>
void Array<T>::append(T e) {
	insert(e, size);
}

template <class T>
void Array<T>::insert(T e, int index) {
	if(index != size)
		assertIndex(index);

	T *newarray = new T[size+1];
	int i;

	for(i=0; i<index; i++)
		newarray[i] = array[i];

	newarray[index] = e;

	for(i=index; i<size; i++)
		newarray[i+1] = array[i];

	delete [] array;
	array = newarray;
	size++;
}

template <class T>
T& Array<T>::operator[] (int index) {
	assertIndex(index);
	return array[index];
}

template <class T>
const T& Array<T>::operator[] (int index) const {
	assertIndex(index);
	return array[index];
}

template <class T>
void Array<T>::setSize(int sz) {
	size = sz;
	delete [] array;
	array = new T[size];
}

template <class T>
void Array<T>::init(int sz, T aTVal) {
	setSize(sz);
	unsigned int unI;
	for(unI = 0; unI < sz; unI++) {
		array[unI] = aTVal;
	}
}


template <class T>
void Array<T>::append(Array<T>& a) {
	append(a, 0);
}

/*
 * Appends a starting from the a's index 'from'
 * to the and of this array.
 */
template <class T>
void Array<T>::append(Array<T>& a, int from) {
	T *newarray = new T[size+a.size-from];

	int i; 
	for(i=0; i<size; i++)
		newarray[i] = array[i];

	for(i=from; i<a.size; i++)
		newarray[size+i-from] = a[i];

	delete [] array;
	array = newarray;
	size += a.size-from;
}

template <class T>
T Array<T>::remove(int index) {
	assertIndex(index);

	T *newarray = new T[size-1];
	int i;

	for(i=0; i<index; i++)
		newarray[i] = array[i];

	for(i=index+1; i<size; i++)
		newarray[i-1] = array[i];

	T ret = array[index];
	delete [] array;
	array = newarray;
	size--;
	return ret;
}

template <class T>
void Array<T>::assertIndex(int index) const {
	if(index<0 || index>=size) {
		std::cerr << "Array index out of bounds: "<<index<<std::endl;
		exit(-1);
	}
}

template <class T>
std::ostream& operator <<(std::ostream& os, const Array<T>& a) {
	for(int i=0; i<a.size; i++)
		os << a[i] << ' ';
	return os<<std::endl;
}

template <class T>
Array<T> & Array<T>::operator=(const Array & a) {
    this->setSize(a.size);
	int nI;
	for(nI = 0; nI < size; nI++) {
		array[nI] = a[nI];
	}
	return(*this);
}

template <class T>
Array<T>::Array(const Array<T> & a) {
	array = NULL;
	(*this) = a;
}


typedef Array<int> INT_ARRAY;
typedef Array< INT_ARRAY > INT_TBL;
typedef Array< INT_TBL > INT_VOL;

typedef Array<float> FLOAT_ARRAY;
typedef Array< FLOAT_ARRAY > FLOAT_TBL;
typedef Array< FLOAT_TBL > FLOAT_VOL;

typedef Array<double> DOUBLE_ARRAY;
typedef Array< DOUBLE_ARRAY > DOUBLE_TBL;
typedef Array< DOUBLE_TBL > DOUBLE_VOL;

template <class T>
struct T_TBL : public Array < Array < T > > {
	void init(const int aarrnSizes[2], T aTVal = 0);
};

template <class T>
void T_TBL< T >::init(const int aarrnSizes[2], T aTVal = 0) {

	unsigned int unI;
	 
	setSize(aarrnSizes[0]);
	for(unI = 0; unI < aarrnSizes[0]; unI++) {
		(array[unI]).init(aarrnSizes[1], aTVal);
	}

}


template <class T>
struct T_VOL : public Array < T_TBL < T > > {
	void init(const int aarrnSizes[3], T aTVal = 0);
};

template < class T >
void T_VOL<T>::init(const int aarrnSizes[3], T aTVal = 0) {
	int nI;
	 
	setSize(aarrnSizes[0]);
	for(nI = 0; nI < aarrnSizes[0]; nI++) {
		(array[nI]).init(&(aarrnSizes[1]), aTVal);
	}
}

#endif //ARRAY_H