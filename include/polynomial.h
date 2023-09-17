#pragma once
#include <iostream>

template<typename T>
class Polynomial{
	T* coefficients;
	int size;

	static const float epsilon = 0.01f;
private:
	
	Polynomial(const int max_coefficient);
	Polynomial(const T& other);
	~Polynomial();

	bool set(const T& coefficient, int degree);
	T calculate(const T value) const;
	bool shrink_to_fit();
	bool expand(const int degree);

	T operator[](const int degree) const;
	T& operator[](const int degree);
	T& operator+(const Polynomial& second);
	T& operator-(const Polynomial& second);
	T& operator*(const T& second);
	bool operator==(const T& second) const;
	bool operator!=(const T& second) const;

};

std::ostream& operator<<(std::ostream stream&, const Polynomial& polynomial);