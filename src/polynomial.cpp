#ifndef VEC_CPP
#define VEC_CPP
#include <polynomial.h>
#include <stdexcept>
#include <cmath>

template<typename T>
Polynomial<T>::Polynomial(const int max_coefficient): _size(max_coefficient) {
	_coefficients = new T[_size + 1]{0};
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

	T* new_coefficients = new T[degree + 1]{0};
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
T Polynomial<T>::calculate(const T value) const{
	T result = 0;
	for (int i = 0; i <= _size; ++i) {
		result += _coefficients[i] * pow(value, i);
	}
	return result;
}

template<typename T>
bool Polynomial<T>::shrink_to_fit() {
	int count = 0;
	for (int i = _size; i > 0; --i) {
		if (_coefficients[i] == 0) ++count;
		else break;
	}

	if (count == 0) return 0; // ������ �� ����������� 
	
	T* new_coefficients = new T[_size - count + 1]{ 0 };
	_size -= count;
	for (int i = 0; i <= _size; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	delete[] _coefficients;
	_coefficients = new_coefficients;

	return 1; // ���������
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

template<typename T>
bool Polynomial<T>::operator==(const Polynomial<T>& second) const {
	Polynomial<T> this_copy = *this;
	Polynomial<T> second_copy = second;

	this_copy.shrink_to_fit();
	second_copy.shrink_to_fit();

	if (this_copy._size != second_copy._size) return false;

	for (int i = 0; i <= this_copy._size; ++i) {
		if (fabs(this_copy._coefficients[i] - second_copy._coefficients[i]) >= EPSILON) return false;
	}
	return true;
}

template<typename T>
bool Polynomial<T>::operator!=(const Polynomial<T>& second) const {
	return !(*this == second); 
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial) {
	int size = polynomial.get_size();

	if (polynomial == 0) { // ���������� �������� ����������� ���� Polynomial(0). Polynomial(0) = 0 ��� ��������� 
		stream << "0";
		return stream;
	}

	for (int i = 0; i <= size; ++i){
		if (polynomial[i] == 0) continue;
		if (i == 0) {
			stream << polynomial[i];
			continue;
		}

		if ((polynomial[i] > 0 ? 1 : 0) && (polynomial[i-1] != 0)) stream << "+";
		stream << polynomial[i] << "x";
		if (i != 1) stream << "^" << i;
	}

	return  stream;
}


#endif