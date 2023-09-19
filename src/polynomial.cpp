#ifndef VEC_CPP
#define VEC_CPP
#include<cmath>
#include<complex>
#include<stdexcept>
#include<polynomial.h>

template<typename T>
Polynomial<T>::Polynomial() :Polynomial(0){}

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
	if (degree < 0 || degree > _size) {
		throw std::runtime_error("degree must be >= 0 and < than max coefficient");
	}
	_coefficients[degree] = coefficient;
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
	T zero = { 0 };
	for (int i = _size; i > 0; --i) {
		if (_coefficients[i] == zero) ++count;
		else break;
	} 

	if (count == 0) return false; // Ничего не укорачивали 
	
	T* new_coefficients = new T[_size - count + 1]{ 0 };
	_size -= count;
	for (int i = 0; i <= _size; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	delete[] _coefficients;
	_coefficients = new_coefficients;

	return true; // Укоротили
}

template<typename T>
bool Polynomial<T>::expand(const int degree) {
	if (degree <= _size) return false;
	T* new_coefficients = new T[degree + 1]{0};
	for (int i = 0; i <= _size; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	_size = degree;
	delete[] _coefficients;
	_coefficients = new_coefficients;

	return true;
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
		if (abs(this_copy._coefficients[i] - second_copy._coefficients[i]) >= EPSILON) return false;
	}
	return true;
}

template<typename T>
bool Polynomial<T>::operator!=(const Polynomial<T>& second) const {
	return !(*this == second); 
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+=(const Polynomial<T>& second) {
	if (this->_size < second._size) this->expand(second._size);

	for (int i = 0; i <= second._size; ++i) {
		_coefficients[i] += second._coefficients[i];
	}

	return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator+(const Polynomial<T>& second) const{
	Polynomial<T>* result = new Polynomial<T>(*this);
	return (*result += second);
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-=(const Polynomial<T>& second) {
	if (this->_size < second._size) this->expand(second._size);

	for (int i = 0; i <= second._size; ++i) {
		_coefficients[i] -= second._coefficients[i];
	}

	return *this;
}

template<typename T>
Polynomial<T>& Polynomial<T>::operator-(const Polynomial<T>& second) const{
	Polynomial<T>* result = new Polynomial<T>(*this);
	return (*result -= second);
}

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial) {
	int size = polynomial.get_size();

	if (polynomial == 0) { // Компиялтор вызывает конструктор вида Polynomial(0). Polynomial(0) = 0 при сравнении 
		stream << "0";
		return stream;
	}

	for (int i = 0; i <= size; ++i){
		if (polynomial[i] == 0) continue;
		if (i == 0) {
			stream << polynomial[i];
			continue;
		}

		if (polynomial[i] > 0 ? 1 : 0) stream << "+";
		stream << polynomial[i] << "x";
		if (i != 1) stream << "^" << i;
	}

	return  stream;
}

template<>
std::ostream& operator<< <std::complex<double>> (std::ostream& stream, const Polynomial<std::complex<double>>& polynomial) {
	int size = polynomial.get_size();

	if (polynomial == 0) { // Компиялтор вызывает конструктор вида Polynomial(0). Polynomial(0) = 0 при сравнении 
		stream << "0";
		return stream;
	}

	for (int i = 0; i <= size; ++i) {
		if (polynomial[i] == static_cast<std::complex<double>>(0)) continue;
		if (i == 0) {
			stream << "(" << polynomial[i].real();
			if (polynomial[i].imag() > 0) stream << "+";
			stream << polynomial[i].imag() << "i" << ")";
			continue;
		}

		stream << "+";

		stream << "(" << polynomial[i].real();
		if (polynomial[i].imag() >= 0) stream << "+";
		stream << polynomial[i].imag() << "i)*X";

		if (i != 1) stream << "^" << i;
	}

	return  stream;
}

#endif