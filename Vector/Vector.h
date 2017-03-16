/*
	Practice implementation by dha8
	Vectors - resizable arrays
	personal notes:
	-template code must have the definition in the file. Compiler mostly ignores
	the code, but calls upon it once type is set.
	-did not consider IndexOutofBoundsException
*/

#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector
{
public:
	Vector();
	Vector(const unsigned int & n);
	Vector(const Vector<T> & v);
	Vector<T> & operator=(const Vector<T> & v); // return a reference, to allow assignment chaining.
	T & operator[](const int & n);	
	T * begin(); // returning ptrs can return NULL's, unlike references where exceptions need to be thrown.
	T * end();
	size_t getSize();

	void append(const T & t);
	void insert(const T & t, const unsigned int & index);
	~Vector();

private:

	void grow(); // double the capacity

	unsigned int size;
	unsigned int capacity;
	T * buffer;
};

//class definition
	template<class T>
	Vector<T>::Vector() : size(0), capacity(1), buffer(new T[capacity]) {} // buffer not null, to make code maintainable.
	
	template<class T>
	Vector<T>::Vector(const unsigned int & n) : size(n), capacity(n*2), buffer(new T[capacity]) {}
	
	template<class T>
	Vector<T>::Vector(const Vector<T> & v) : size(v.size), capacity(v.capacity), buffer(new T[capacity]) {
		for (int i = 0; i < size; ++i) buffer[i] = v.buffer[i];
	}
	
	template<class T>
	Vector<T> & Vector<T>::operator=(const Vector<T> & v){ // deep copy.
		//check for self-assignment
		if (this == &v) return *this;
		delete[] buffer;
		size = v.size;
		capacity = v.capacity;
		buffer = new T[capacity];
		for (int i = 0; i < size; ++i) buffer[i] = v.buffer[i];
		return *this;
	}

	template<class T>
	T & Vector<T>::operator[](const int & index) {
		return buffer[index];
	}	

	template<class T>
	T * Vector<T>::begin() { return &buffer[0]; }
	
	template<class T>
	T * Vector<T>::end() { return &buffer[size - 1]; }

	template<class T>
	size_t Vector<T>::getSize() { return size; }

	template<class T>
	void Vector<T>::append(const T & t){
		if (size == capacity) grow();
		buffer[size] = t;
		size++;
	}
	
	template<class T>
	void Vector<T>::insert(const T & t, const unsigned int & index){
		if (size == capacity) grow();
		buffer[index] = t;
		size++;
	}
	
	template<class T>
	Vector<T>::~Vector() { delete[] buffer; }

	template<class T>
	void Vector<T>::grow() {
		T * temp = new T[capacity * 2];
		capacity *= 2;
		for (unsigned int i = 0; i < size; ++i) { temp[i] = buffer[i]; }
		delete[] buffer;
		buffer = temp;
	}

#endif
