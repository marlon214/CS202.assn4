/**/
#pragma once

#include <iostream>

using namespace std;

//Custom exception class for when Vector sizes don't match
class DimensionMismatchException: public exception
{
	string message;
public:
	DimensionMismatchException() { this->message = ""; }
	DimensionMismatchException(string message) { this->message = message; }
	string what() { return message; }
};

/* A math style vector class consisting of a single row of numbers.
We'll write operators to do math, print, and other common operations */
class Vector
{
	float* contents; //Array of the contents of the vector
	int size; //Size of the array

public:

	friend Vector operator + (Vector v1, Vector v2);
	friend float operator * (Vector v1, Vector v2);
	void operator = (Vector other);
	friend ostream& operator << (ostream& out, const Vector& v);
	friend istream& operator >> (istream& in, Vector& v);

	Vector() { size = 0; contents = nullptr; }
	Vector(int size);
	Vector(const Vector& other);
	~Vector();
};