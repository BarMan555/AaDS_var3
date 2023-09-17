#ifndef VEC_CPP
#define VEC_CPP
#include <polynomial.h>

template<typename T>
Polynomial<T>::Polynomial(const int max_coefficient): _size(max_coefficient) {
	_coefficients = new T[_size + 1];
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& other) : Polynomial<T>(other._size){
	for (int i = 0; i < _size; ++i) {
		this->_coefficients[i] = other._coefficients[i];
	}
}

template<typename T>
Polynomial<T>::~Polynomial(){
	delete[] _coefficients;
}

#endif