//---------------------------------------------------------------------
// Name: Michael Melusky
// Email: mcm297@psu.edu
// Class: CMPSC 122, Section 2
// Program 1.2
// Due Date: February 20 2020, 11:59 PM
//
// Description: This program collects information from the user
// to create two matrices using a Matrix class definition, and 
// performs several calculations using those matrices.
// The results of each calculation are retrieved and displayed
// to the user in a readable format.
//
// Acknowledgements:
// 1. Please use this portion of the banner comment to list
// any resources or individuals you consulted on the creation
// of this program.
//---------------------------------------------------------------------

#include <iostream>

using namespace std;

class Matrix
{
private:
	// declare member fields for row, columns
public:
	// declare member field for matrix data (int **), It would be better practice to put this under
	// private and create a getter for it.

	// declare non-default constructor, two parameters for row and column size
	// declare destructor

	// declare accessor functions ("getter" functions)

	// declare operator overloads using friend to perform calcuations as well as fill the matrix data and display output
	friend Matrix* operator+(const Matrix&, const Matrix&);
    friend Matrix* operator+(const Matrix&, const Matrix&);
    friend Matrix* operator*(const Matrix&, const Matrix&);
    friend Matrix* operator*(const Matrix&, const int);
    friend ostream& operator<<(ostream&, const Matrix&);
	// as detailed in assignment
};

// Write function bodies for all public Matrix functions 
//

// constructor dynamically  allocates 2D array to hold matrix data based on row/col size

// destructor free up dynamically allocated memory using delete [], remember the "inside-out" rule

// define operator overloads

Matrix* operator+(const Matrix& mLeft, const Matrix& mRight)
{
	Matrix *sum = new Matrix( , ); // pass in correction information to invoke our constructor

	// do calculations

	return sum;
}

// remainder of operator overloads for calculations friended in the Matrix class
// 

ostream& operator<<(ostream& os, const Matrix& m)
{
	// code

	return os; // passing back the ostream reference we are given via os parameter
}

// define overloaded >>, receives and returns istream instead of ostream

int main()
{
	// Remember you have to use >> and << to your matrix object instances to fill and print them

	// When you print Matrix pointers (object pointers), remember to dereference
	// the pointer when you invoke << (output), and it accepts an object reference, not an object pointers


	// Prompt user for information for first matrix
	// Collect input and create instance of Matrix 

	// Prompt user for information for second matrix
	// Collect input and create second instance of Matrix

	// Perform calculations as described in assignment using member functions
	// Be sure to check matrices size for add/sub, and then mult
	Matrix *sum = ; // invoke + operator here

	// Be sure to output details about calculation being performed and the results
	// When you print Matrix pointers (object pointers), remember to dereference
	// the pointer when you invoke << (output), and it accepts an object reference, not an object pointers

	return 0;
}