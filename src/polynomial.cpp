#ifndef VEC_CPP
#define VEC_CPP
#include <polynomial.h>
#include <stdexcept>

template<typename T>
Polynomial<T>::Polynomial(const int max_coefficient): _size(max_coefficient) {
	_coefficients = new T[_size + 1];
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& other) : Polynomial<T>(other._size){
	for (int i = 0; i <= _size; ++i) {
		this->_coefficients[i] = other._coefficients[i];
	}
}

template<typename T>
Polynomial<T>::~Polynomial(){
	delete[] _coefficients;
}

template<typename T>
bool Polynomial<T>::set(const T& coefficient, int degree) {
	if (degree < 0) {
		throw std::runtime_error("degree must be >= 0");
	}

	if (degree <= _size) {
		_coefficients[degree] = coefficient;
		return 1;
	}

	T* new_coefficients = new T[degree + 1];
	for (int i = 0; i <= degree; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	new_coefficients[degree] = coefficient;

	delete[] _coefficients;
	_coefficients = new_coefficients;
	_size = degree;

	return 1;
}

template<typename T>
int Polynomial<T>::get_size() const {
	return _size;
}

template<typename T>
T Polynomial<T>::operator[](const int degree) const{
	if (degree < 0 || degree > _size) throw std::runtime_error("degree is not valide");
	return _coefficients[degree];
}

template<typename T>
T& Polynomial<T>::operator[](const int degree) {
	if (degree < 0 || degree > _size) throw std::runtime_error("degree is not valide");
	return _coefficients[degree];
}

//template<typename T>
//std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial) {
//	int size = polynomial.get_size();
//
//	for (int i = 0; i <= size; ++i){
//		if(polynomial[i])
//	}
//	return  stream;
//}


#endif