#ifndef VEC_CPP
#define VEC_CPP
#include<cmath>
#include<complex>
#include<stdexcept>
#include<polynomial.h>

template<typename T>
Polynomial<T>::Polynomial() :Polynomial(0){}

template<typename T>
Polynomial<T>::Polynomial(const int max_degree): _degree(max_degree) {
	_coefficients = new T[_degree + 1]{0};
}

template<typename T>
Polynomial<T>::Polynomial(const Polynomial<T>& other) : Polynomial<T>(other._degree){
	for (int i = 0; i <= _degree; ++i) {
		this->_coefficients[i] = other._coefficients[i];
	}
}

template<typename T>
Polynomial<T>::~Polynomial(){
	delete[] _coefficients;
}

template<typename T>
bool Polynomial<T>::set(const T& coefficient, int degree) {
	if (degree < 0 || degree > _degree) {
		throw std::runtime_error("degree must be >= 0 and < than max coefficient");
	}
	_coefficients[degree] = coefficient;
	return 1;
}

template<typename T>
T Polynomial<T>::calculate(const T value) const{
	T result = 0;
	for (int i = 0; i <= _degree; ++i) {
		result += _coefficients[i] * pow(value, i);
	}
	return result;
}

template<typename T>
bool Polynomial<T>::shrink_to_fit() {
	int count = 0;
	T zero = { 0 };
	for (int i = _degree; i > 0; --i) {
		if (_coefficients[i] == zero) ++count;
		else break;
	} 

	if (count == 0) return false; // Ничего не укорачивали 
	
	T* new_coefficients = new T[_degree - count + 1]{ 0 };
	_degree -= count;
	for (int i = 0; i <= _degree; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	delete[] _coefficients;
	_coefficients = new_coefficients;

	return true; // Укоротили
}

template<typename T>
bool Polynomial<T>::expand(const int degree) {
	if (degree <= _degree) return false;
	T* new_coefficients = new T[degree + 1]{0};
	for (int i = 0; i <= _degree; ++i) {
		new_coefficients[i] = _coefficients[i];
	}
	_degree = degree;
	delete[] _coefficients;
	_coefficients = new_coefficients;

	return true;
}

template<typename T>
int Polynomial<T>::get_degree() const {
	return _degree;
}

template<typename T>
T Polynomial<T>::operator[](const int degree) const{
	if (degree < 0 || degree > _degree) throw std::runtime_error("degree is not valide");
	return _coefficients[degree];
}

template<typename T>
T& Polynomial<T>::operator[](const int degree) {
	if (degree < 0 || degree > _degree) throw std::runtime_error("degree is not valide");
	return _coefficients[degree];
}

template<typename T>
bool Polynomial<T>::operator==(const Polynomial<T>& second) const {
	Polynomial<T> this_copy = *this;
	Polynomial<T> second_copy = second;

	this_copy.shrink_to_fit();
	second_copy.shrink_to_fit();

	if (this_copy._degree != second_copy._degree) return false;

	for (int i = 0; i <= this_copy._degree; ++i) {
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
	if (this->_degree < second._degree) this->expand(second._degree);

	for (int i = 0; i <= second._degree; ++i) {
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
	if (this->_degree < second._degree) this->expand(second._degree);

	for (int i = 0; i <= second._degree; ++i) {
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
	int size = polynomial.get_degree();

	for (int i = 0; i <= size; ++i) {
		print(stream, polynomial[i], i);
	}

	return stream;
}

template<typename T>
std::ostream& print(std::ostream& stream, const T& coefficient, const int count) {
	if (coefficient == 0) return stream;

	stream.setf(std::ios::showpos);
	stream << coefficient;
	stream.unsetf(std::ios::showpos);
	if (count != 0) stream << "*X";
	if (count != 1 && count != 0) stream << "^" << count;
	return stream;
}

template<typename T>
std::ostream& print(std::ostream& stream, const std::complex<T>& coefficient, const int count) {
	if (coefficient.real() == 0 && coefficient.imag() == 0) return stream;

	stream << "+(" << coefficient.real();
	stream.setf(std::ios::showpos);
	stream << coefficient.imag() << "i)";
	stream.unsetf(std::ios::showpos);
	if (count != 0) stream << "*X";
	if (count != 1 && count != 0) stream << "^" << count;
	return stream;
}

template<typename T>
double* find_solutions(const Polynomial<T>& polynomial) {
	double* results;

	Polynomial<double> copy(polynomial.get_degree());
	for (int i = 0; i <= copy.get_degree(); ++i) copy[i] = double(polynomial[i]);
	copy.shrink_to_fit();

	if (copy.get_degree() != 1 && copy.get_degree() != 2) throw std::runtime_error("degree must be 1 or 2");

	if (copy.get_degree() == 1) {
		if (copy[0] != T(0)) return (results = new double(-((copy[0]) / (copy[1]))));
		else return (results = new double(0));
	}
	
	if (copy.get_degree() == 2) {
		double discriminant = ((copy[1] * copy[1]) - (4.0 * copy[0] * copy[2]));

		if (discriminant < 0) throw std::runtime_error("no solutions");
		if (discriminant == 0) {
			results = new double(-((copy[1]) / (2.0 * copy[2])));
		}
		if (discriminant > 0) {
			results = new double[2];
			results[0] = (((-copy[1] + sqrt(discriminant)) / (2.0 * copy[2])));
			results[1] = (((-copy[1] - sqrt(discriminant)) / (2.0 * copy[2])));
		}
	}

	return results;
}

template<typename T>
std::complex<double>* find_solutions(const Polynomial<std::complex<T>>& polynomial) {
	std::complex<double>* results;

	Polynomial<std::complex<double>> copy(polynomial.get_degree());
	for (int i = 0; i <= copy.get_degree(); ++i) copy[i] = std::complex<double>(polynomial[i]);
	copy.shrink_to_fit();

	if (copy.get_degree() != 1 && copy.get_degree() != 2) throw std::runtime_error("degree must be 1 or 2");

	if (copy.get_degree() == 1) {
		if (copy[0] != std::complex<double>(0)) return (results = new std::complex<double>(-((copy[0]) / (copy[1]))));
		else return (results = new std::complex<double>(0));
	}

	if (copy.get_degree() == 2) {
		std::complex<double> discriminant = ((copy[1] * copy[1]) - (4.0 * copy[0] * copy[2]));

		if (discriminant == std::complex <double>(0)) {
			results = new std::complex<double>(-((copy[1]) / (2.0 * copy[2])));
		}
		else {
			results = new std::complex<double>[2];
			results[0] = (((-copy[1] + sqrt(discriminant)) / (2.0 * copy[2])));
			results[1] = (((-copy[1] - sqrt(discriminant)) / (2.0 * copy[2])));
		}
	}

	return results;
}

#endif