#pragma once
#include <iostream>
#include<complex>

template<typename T>
class Polynomial{
	T* _coefficients;
	int _size; // Max coefficient

	static constexpr float EPSILON = 0.01f;
public:
	
	Polynomial();
	Polynomial(const int max_coefficient);
	Polynomial(const Polynomial<T>& other);
	~Polynomial();

	bool set(const T& coefficient, int degree);
	T calculate(const T value) const;
	bool shrink_to_fit();
	bool expand(const int degree);
	int get_size() const;

	T operator[](const int degree) const;
	T& operator[](const int degree);
	Polynomial<T>& operator+=(const Polynomial<T>& second);
	Polynomial<T>& operator-=(const Polynomial<T>& second);
	Polynomial<T>& operator+(const Polynomial<T>& second) const;
	Polynomial<T>& operator-(const Polynomial<T>& second) const;
	bool operator==(const Polynomial<T>& second) const;
	bool operator!=(const Polynomial<T>& second) const;

	template<typename T>
	friend Polynomial<T>& operator*(const double scalar, Polynomial<T>& polynomial);
	template<typename T>
	friend Polynomial<T>& operator*(Polynomial<T>& polynomial, const double scalar);
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial);

template<typename T>
Polynomial<T>& operator*(const double scalar, Polynomial<T>& polynomial){

	Polynomial<T>* result = new Polynomial<T>(polynomial);

	for (int i = 0; i <= polynomial._size; ++i) {
		(*result)._coefficients[i] *= (T)scalar;
	}

	return *result;
}

template<typename T>
Polynomial<T>& operator*(Polynomial<T>& polynomial, const double scalar){
	return scalar*polynomial;
}

template<typename T>
std::ostream& print(std::ostream& stream, const T& coefficient, const int count);

template<typename T>
std::ostream& print(std::ostream& stream, const std::complex<T>& coefficient, const int count);

template<typename T>
double* search(const Polynomial<T>& polynomial);

template<typename T>
std::complex<double>* search(const Polynomial<std::complex<T>>& polynomial);
#include "../src/polynomial.cpp"