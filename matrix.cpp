//---------------------------------------------------------------------
// Name: Ridha
// Email: rac6115@psu.edu
// Class: CMPSC 122, Section 2
// Program 1.2
// Due Date: October 6th, 11:59 PM
//
// Description: This program collects information from the user
// to create two matrices using a Matrix class definition, and
// performs several calculations using those matrices.
// The results of each calculation are retrieved and displayed
// to the user in a readable format.
//
//Resources:
//W3Schools
//Previously Answered Stack Overflow Questions
//Some random youtube videos about segmentation faults smart pointers which i didnt implement
//---------------------------------------------------------------------

#include <iostream>
#include <time.h>

using namespace std;

class Matrix
{
private:
    // declare member fields for row, columns
    int rows, columns;
public:
    string name;
    // declare member field for matrix data (int **), It would be better practice to put this under
    // private and create a getter for it.
    int** elements;

    // declare non-default constructor, two parameters for row and column size
    Matrix(int rows, int columns, string name);
    Matrix(int rows, int columns);
    // declare destructor
    ~Matrix();
    // declare accessor functions ("getter" functions)
    int getElement(int row, int column) const;
    int setElement(int row, int column, int value);

    int getRows();
    int getColumns();

    // declare functions to perform calculations and display output
    Matrix* add(const Matrix&); // const is optional, but good practice. if you choose not to use it, make sure you update the definition below.
    // as detailed in assignment
    Matrix* subtract(const Matrix&);
    Matrix* multiply(const Matrix&);
    Matrix* multiply(const int scalar);
    void print() const;

};

// Write function bodies for all public Matrix functions
//

// constructor dynamically  allocates 2D array to hold matrix data based on row/col size
Matrix::Matrix(int rows, int columns, string name) {
    this->rows = rows;
    this->columns = columns;
    this->name = name;

    elements = new int*[rows];
    for(int row = 0; row < rows; row++) {
        elements[row] = new int[columns];
    }

    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            this->elements[row][column] = 0;
        }
    }
}
Matrix::Matrix(int rows, int columns) {
    this->rows = rows;
    this->columns = columns;
    this->name = "Default";

    elements = new int*[rows];
    for(int row = 0; row < rows; row++) {
        elements[row] = new int[columns];
    }

    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            this->elements[row][column] = 0;
        }
    }
}
// destructor free up dynamically allocated memory using delete [], remember the "inside-out" rule
Matrix::~Matrix()
{
    for(int row = 0; row < rows; row++)   {
        delete elements[row];
    }
    delete []elements;
}

// add member function

int Matrix::getRows() { return rows; }
int Matrix::getColumns() { return columns; }

int Matrix::getElement(int row, int column) const {
    if(row >= this->rows || column >= this->columns) {
        cerr << "Out of bounds get command: " << row << " x " <<  column << " from " << rows << " x " << columns << "\n";
        return NULL;
    }
    return elements[row][column]; }

int Matrix::setElement(int row, int column, int value) {
    if(row > this->rows || column > this->columns) {
        cerr << "Out of bounds set command" << "\n";
        return NULL;
    }
    int oldValue = this->getElement(row, column);
    this->elements[row][column] = value;
    return oldValue;
}

Matrix* Matrix::add(const Matrix& otherMatrix)
{
    if(otherMatrix.rows != this->rows || otherMatrix.columns != this->columns) {
        cout << "This Add Operation Cannot Be Preformed Moving On..." << "\n";
        return NULL;
    }
    Matrix *sum = new Matrix(otherMatrix.rows, otherMatrix.columns, "Sum"); // pass in correction information to invoke our constructor

    // do calculations
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++)
            sum->elements[row][column] = this->getElement(row, column) + otherMatrix.getElement(row, column);
    }
    return sum;
}

Matrix* Matrix::subtract(const Matrix& otherMatrix) {
    if(otherMatrix.rows != this->rows || otherMatrix.columns != this->columns) {
        cout << "This Subtract Operation Cannot Be Preformed Moving On..." << "\n";
        return nullptr;
    }
    Matrix *difference = new Matrix(otherMatrix.rows, otherMatrix.columns, "Difference"); // pass in correction information to invoke our constructor

    // do calculations
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++)
            difference->elements[row][column] = this->getElement(row, column) - otherMatrix.getElement(row, column);
    }
    return difference;
}

Matrix* Matrix::multiply(const Matrix& otherMatrix) {
    if(this->columns != otherMatrix.rows) {
        cout << "This Matrix Multiplication Cannot Operation Cannot Be Preformed Moving On..." << "\n";
        return nullptr;
    }
    Matrix *product = new Matrix(this->rows, otherMatrix.columns, "Row By Column Multiplication"); // pass in correction information to invoke our constructor

    for(int row = 0; row < this->rows; row++) {
        for(int column = 0; column < otherMatrix.columns; column++) {
            int sum = 0;
            for(int pair = 0; pair < otherMatrix.rows; pair++) {
                sum += this->getElement(row, pair) * otherMatrix.getElement(pair, column);;
            }
            product->setElement(row, column, sum);
        }
    }
    return product;
}

Matrix* Matrix::multiply(const int scalar) {
    Matrix *scalarMultiple = new Matrix(rows, columns, "Scalar Multiplied"); // pass in correction information to invoke our constructor
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            scalarMultiple->setElement(row, column, this->getElement(row, column) * scalar);
        }
    }
    return scalarMultiple;
}

void Matrix::print() const {
    cout << this->name << ":\n";
    if(rows == 0 || columns == 0) {
        cout << "This is an empty matrix\n\n";
        return;
    }

    for(int row = 0; row < rows; row++) {
        cout << "| ";
        for(int column = 0; column < columns; column++)
            cout << getElement(row, column) << " ";
        cout << "|" << "\n";
    }
    for(int underscore = 0; underscore < columns * 3 + 2; underscore++) {
        cout << "_";
    }
    cout << "\n";

}

Matrix userGeneratedMatrix(string name) {
    int rows, columns;
    cout << "How many rows in Matrix " << name << ": ";
    cin >> rows;
    cout << "How many columns in Matrix " << name << ": ";
    cin >> columns;
    Matrix newMatrix(rows, columns, name);

    cout << "Expecting " << rows * columns << " elements. \n";
    cout << "What are your elements, space seperated: ";

    string rawInput = " ";
    cout << "Enter a number, or numbers separated by a space, between 1 and 1000." << endl;

    // get a line of space seperated numbers from cin and make an array of them
    for(int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            cin >> newMatrix.elements[row][column];
        }
    }

    return newMatrix;
}

int main() {
    Matrix matrixOne = userGeneratedMatrix("One");
    Matrix matrixTwo = userGeneratedMatrix("Two");

    matrixOne.print();
    matrixTwo.print();

    // Addition
    Matrix* sumMatrix = matrixOne.add(matrixTwo);
    if(sumMatrix != NULL) { sumMatrix->print(); }

    // Subtraction
    Matrix* differenceMatrix = matrixOne.subtract(matrixTwo);
    if(differenceMatrix!= NULL) { differenceMatrix->print(); }

    // Multiplication
    Matrix* matrixProduct = matrixOne.multiply(matrixTwo);
    if(matrixProduct != NULL) { matrixProduct->print(); }

    // Scalar Multiplication
    srand(time(NULL));
    int randomScalar = rand() % 10;
    cout << "Multiplying multiplying Matrix One by random scalar: " << randomScalar << "\n";
    Matrix* scalarProduct = matrixOne.multiply(randomScalar);
    scalarProduct->print();
    cout << "\n";
    cout << "Thank you!\n\n-Ridha Chowdhury";


    return 505;
}
