//---------------------------------------------------------------------
// Name: Michael Melusky
// Email: mcm297@psu.edu
// Class: CMPSC 122, Section 2
// Program 1.1
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

	// declare functions to perform calculations and display output
	Matrix* add(const Matrix&); // const is optional, but good practice. if you choose not to use it, make sure you update the definition below.
	// as detailed in assignment
};

// Write function bodies for all public Matrix functions 
//

// constructor dynamically  allocates 2D array to hold matrix data based on row/col size

// destructor free up dynamically allocated memory using delete [], remember the "inside-out" rule

// add member function

Matrix* Matrix::add(const Matrix& m)
{
	Matrix *sum = new Matrix( , ); // pass in correction information to invoke our constructor

	// do calculations

	return sum;
}

// remainder of calculations and member functions (like print)

int main()
{
	// Prompt user for information for first matrix
	// Collect input and create instance of Matrix 

	// Prompt user for information for second matrix
	// Collect input and create second instance of Matrix

	// Perform calculations as described in assignment using member functions
	// Be sure to check matrices size for add/sub, and then mult
	Matrix *sum = ; // invoke add function here

	// Be sure to output details about calculation being performed and the results

	return 0;
}