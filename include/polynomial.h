#pragma once
#include <iostream>

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
	Polynomial<T>& operator+(const Polynomial<T>& second);
	Polynomial<T>& operator-(const Polynomial<T>& second);
	bool operator==(const Polynomial<T>& second) const;
	bool operator!=(const Polynomial<T>& second) const;

	template<typename U>
	friend Polynomial<U>& operator*(const double scalar,Polynomial<U>& polynomial);
	template<typename U>
	friend Polynomial<U>& operator*(Polynomial<U>& polynomial, const double scalar);

};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial);

#include "../src/polynomial.cpp"