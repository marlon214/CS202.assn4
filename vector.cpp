/*
Name: Marlon Alejandro, 5002573038, 1001, ASSIGNMENT_4
Description: Develop overload operator functions for our custom vector class
Input: User inputed
Output: Output to terminal
*/

#include <iostream>
#include <fstream>
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	Vector v1, v2, v3;
	ifstream infile;
	infile.open("input.txt");
	if (!infile.good())
	{
		cout << "Could not open input.txt. Did you put it in the same directory?" << endl;
		return 1;
	}

	//Read in each of the vectors
	infile >> v1 >> v2 >> v3;

	//Test all of our operations:
	cout << "v1 = " << v1 << endl;
	cout << "v2 = " << v2 << endl;

	Vector v4 = v3;

	cout << "Testing = ..." << endl;
	cout << "Checking if v3 and v4 are the same" << endl;
	cout << "v3 = " << v3 << endl;
	cout << "v4 = " << v4 << endl;

	cout << "Testing math operations" << endl;
	cout << "v1 + v2 = " << v1 + v2 << endl;
	cout << "v1 * v2 = " << v1 * v2 << endl;

	cout << "Testing an invalid operation" << endl;
	try {
		cout << v1 * v3 << endl;
	}
	catch (DimensionMismatchException& e)
	{
		cout << "Encountered an error when multiplying:" << e.what() << endl;
	}
}

//---------------- Vector operator and function implementations ----------------

/**/
Vector operator + (Vector v1, Vector v2)
{
	//Add the two vectors together elementwise if they have the same 
	//size/dimensionality and return a result Vector
	//Else throw an exception

//As an example of how to construct a result vector, this line was left in
//You'll still need to set the members and add code around it
	if(v1.size!=v2.size){
		throw DimensionMismatchException();
	}

	Vector result = Vector(v1.size); 
	for(int i =0; i <v1.size; i++){
		result.contents[i]=v1.contents[i]+v2.contents[i];
	}
	return result;
}

/**/
float operator * (Vector v1, Vector v2)
{
	//Find the scalar dot product if their dimensions match, otherwise
	//throw an exception.
	//Recall that the dot product is the sum of all elementwise products
	//(See the rubric for the detailed explanation)
	if(v1.size!=v2.size){
		throw DimensionMismatchException("v1 and v2 are of different sizes and could not be multiplied");
	}

	float result=0.0;
	for(int i =0; i <v1.size; i++){
		result+=v1.contents[i]*v2.contents[i];
	}
	return result; //Returns your result instead of 0
}

/**/
void Vector::operator = (Vector other)
{

	//Make a deep copy of the other vector's contents and copy over
	//any other member variables

	//Make sure to deallocate any existing contents array if it exists
	delete[] contents;
	contents = new float[other.size];
	this->size= other.size;

	for(int i = 0; i<size; i++){
		contents[i]=other.contents[i];
	}
}

/**/
ostream& operator << (ostream& out, const Vector& v)
{
	//Print the vector to the out stream in the form <x0, x1, x1, ..., xn-1>
	//Return the stream when done
	out << '<';
	for(int i =0; i <v.size-1; i++){
		out << v.contents[i] << ", ";
	}
	out << v.contents[v.size-1] << '>';
	return out;
}

/**/
istream& operator >> (istream& in, Vector& v)
{
	//Reads a vector from a stream by first reading the size, then
	//the elements that will fill up the Vector
	//Make sure to allocate the array somehow before reading in values
	//and deallocate any existing space beforehand
	//Return the stream when done

	//You can assume no error checking is needed; the user enters everything fine
	int size=0;
	in >> size; //cin size value
	float* temp = new float[size]; // create temporary float array
	for(int i =0; i <size; i++){
		in >> temp[i];	// store array values
	}
	delete[] v.contents;// delete previous array
	v.contents=temp;// and point it to our temp array
	temp=nullptr;
	delete[] temp; // deallocate array of temp
	v.size=size; 

	return in;
}

/**/
Vector::Vector(int size)
{
	//Allocate an array of the given size and store the size param in
	//the size memeber
	contents= new float[size]; // initialize memory for array
	this->size=size;			// initialize size variable

}

/**/
Vector::Vector(const Vector& other)
{
	//A copy constructor should make a copy of the existing other
	//Vector. This should be nearly identical to an = overload,
	//just without the need to deallocate any existing memory
	//(since this is a creation event, memory can't be already allocated beforehand)
	this->size= other.size;
	this->contents= new float[other.size]; // allocate memory for our array
	for(int i = 0; i<size; i++){
		contents[i]=other.contents[i];	// copies the content of the prexsisitng array
	}
}

/**/
Vector::~Vector()
{
	//Deallocate the existing contents array if it exists
	//This should be 2 lines max
	delete[] contents;

}
