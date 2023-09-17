#pragma once
#include <iostream>

template<typename T>
class Polynomial{
	T* coefficients;
	int size;

	const float epsilon = 0.01f;
public:
	
	Polynomial(const int max_coefficient);
	Polynomial(const T& other);
	~Polynomial();

	bool set(const T& coefficient, int degree);
	T calculate(const T value) const;
	bool shrink_to_fit();
	bool expand(const int degree);

	T operator[](const int degree) const;
	T& operator[](const int degree);
	T& operator+(const Polynomial<T>& second);
	T& operator-(const Polynomial<T>& second);
	T& operator*(const T& second);
	bool operator==(const T& second) const;
	bool operator!=(const T& second) const;

};

template<typename T>
std::ostream& operator<<(std::ostream& stream, const Polynomial<T>& polynomial);