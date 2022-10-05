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
// Acknowledgements:
// 1. Please use this portion of the banner comment to list
// any resources or individuals you consulted on the creation
// of this program.
//Resources:
//W3Schools
//Previously Answered Stack Overflow Questions
//Some random youtube videos about segmentation faults smart pointers which i didnt implement
//---------------------------------------------------------------------

#include <iostream>

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
    Matrix(string name);
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
    // declare operator overloads using friend to perform calcuations as well as fill the matrix data and display output
    friend Matrix* operator+(const Matrix&, const Matrix&);
    friend Matrix* operator-(const Matrix&, const Matrix&);
    friend Matrix* operator*(const Matrix&, const Matrix&);
    friend Matrix* operator*(const Matrix&, int);
    friend ostream& operator<<(ostream&, const Matrix&);
    friend istream & operator >> (istream& in,  Matrix& c);
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
        return 0;
    }
    return elements[row][column]; }

int Matrix::setElement(int row, int column, int value) {
    if(row > this->rows || column > this->columns) {
        cerr << "Out of bounds set command" << "\n";
        return 0;
    }
    int oldValue = this->getElement(row, column);
    this->elements[row][column] = value;
    return oldValue;
}

// define operator overloads

Matrix* operator+(const Matrix& mLeft, const Matrix& mRight)
{
    if(mRight.rows != mLeft.rows || mRight.columns != mLeft.columns) {
        cout << "This Add Operation Cannot Be Preformed Moving On..." << "\n";
        return NULL;
    }
    Matrix *sum = new Matrix(mRight.rows, mRight.columns, "Sum"); // pass in correction information to invoke our constructor

    // do calculations
    for(int row = 0; row < mLeft.rows; row++) {
        for(int column = 0; column < mLeft.columns; column++)
            sum->elements[row][column] = mLeft.getElement(row, column) + mRight.getElement(row, column);
    }
    return sum;
}

Matrix* operator-(const Matrix& mLeft, const Matrix& mRight) {
    if(mRight.rows != mLeft.rows || mRight.columns != mLeft.columns) {
        cout << "This Subtract Operation Cannot Be Preformed Moving On..." << "\n";
        return nullptr;
    }
    Matrix *difference = new Matrix(mRight.rows, mRight.columns, "Difference"); // pass in correction information to invoke our constructor

    // do calculations
    for(int row = 0; row < mLeft.rows; row++) {
        for(int column = 0; column < mLeft.columns; column++)
            difference->elements[row][column] = mLeft.getElement(row, column) - mRight.getElement(row, column);
    }
    return difference;
}

Matrix* operator*(const Matrix& mLeft, const Matrix& mRight) {
    if(mLeft.columns != mRight.rows) {
        cout << "This Matrix Multiplication Cannot Operation Cannot Be Preformed Moving On..." << "\n";
        return nullptr;
    }
    Matrix *product = new Matrix(mLeft.rows, mRight.columns, "Row By Column Multiplication"); // pass in correction information to invoke our constructor

    for(int row = 0; row < mLeft.rows; row++) {
        for(int column = 0; column < mRight.columns; column++) {
            int sum = 0;
            for(int pair = 0; pair < mRight.rows; pair++) {
                sum += mLeft.getElement(row, pair) * mRight.getElement(pair, column);;
            }
            product->setElement(row, column, sum);
        }
    }
    return product;
}

Matrix* operator*(const Matrix& matrix, const int scalar) {
    Matrix *scalarMultiple = new Matrix(matrix.rows, matrix.columns, "Scalar Multiplied"); // pass in correction information to invoke our constructor
    for(int row = 0; row < matrix.rows; row++) {
        for(int column = 0; column < matrix.columns; column++) {
            scalarMultiple->setElement(row, column, matrix.getElement(row, column) * scalar);
        }
    }
    return scalarMultiple;
}

// remainder of operator overloads for calculations friended in the Matrix class
//

ostream& operator<<(ostream& os, const Matrix& matrix)
{
    os << matrix.name << ":\n";
    if(matrix.rows == 0 || matrix.columns == 0) {
        os << "This is an empty matrix\n\n";
        return os;
    }

    for(int row = 0; row < matrix.rows; row++) {
        os << "| ";
        for(int column = 0; column < matrix.columns; column++)
            os << matrix.getElement(row, column) << " ";
        os << "|" << "\n";
    }
    for(int underscore = 0; underscore < matrix.columns * 3 + 2; underscore++) {
        os << "_";
    }
    os << "\n";

    return os; // passing back the ostream reference we are given via os parameter
}

// define overloaded >>, receives and returns istream instead of ostream
istream & operator >> (istream& is, Matrix& matrix) {
    cout << "How many rows in Matrix " << matrix.name << ": ";
    is >> matrix.rows;
    cout << "How many columns in Matrix " << matrix.name << ": ";
    is >> matrix.columns;
    matrix.name = "Default";

    matrix.elements = new int*[matrix.rows];
    for(int row = 0; row < matrix.rows; row++) {
        matrix.elements[row] = new int[matrix.columns];
    }

    cout << "Expecting " << matrix.rows * matrix.columns << " elements. \n";
    cout << "What are your elements, space seperated: ";
    for(int row = 0; row < matrix.rows; row++) {
        for(int column = 0; column < matrix.columns; column++) {
            cin >> matrix.elements[row][column];
        }
    }
    return is;
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

Matrix::Matrix(string name) {
    this->name = name;
}

/*istream & operator >> (istream &in,  Matrix &c)
{
    cout << "Enter Real Part ";
    in >> c.real;
    cout << "Enter Imaginary Part ";
    in >> c.imag;
    return in;
}*/

Matrix userGeneratedMatrix(string name) {
    int rows, columns;
    cout << "How many rows in Matrix " << name << ": ";
    cin >> rows;
    cout << "How many columns in Matrix " << name << ": ";
    cin >> columns;
    Matrix newMatrix(rows, columns, name);

    string elements;
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

int main()
{
    // Remember you have to use >> and << to your matrix object instances to fill and print them
    Matrix matrixOne("First");
    Matrix matrixTwo("Second");


    // When you print Matrix pointers (object pointers), remember to dereference
    // the pointer when you invoke << (output), and it accepts an object reference, not an object pointers

    // Prompt user for information for first matrix
    // Collect input and create instance of Matrix
    cout << "Lets set up the first matrix! \n";
    cin >> matrixOne;
    cout << matrixOne;


    // Prompt user for information for second matrix
    // Collect input and create second instance of Matrix
    cout << "Lets set up the second matrix! \n";
    cin >> matrixTwo;
    cout << matrixTwo;

    // Perform calculations as described in assignment using member functions
    // Be sure to check matrices size for add/sub, and then mult

    // Addition
    Matrix* sumMatrix = matrixOne + matrixTwo;
    if(sumMatrix != NULL) { cout << *sumMatrix << "\n"; }

    // Subtraction
    Matrix* differenceMatrix = matrixOne- matrixTwo;
    if(differenceMatrix!= NULL) { cout << *differenceMatrix << "\n"; }

    // Multiplication
    Matrix* matrixProduct = matrixOne * matrixTwo;
    if(matrixProduct != NULL) { cout << *matrixProduct << "\n"; }

    // Scalar Multiplication
    srand(time(NULL));
    int randomScalar = (rand() % 9) + 1;
    cout << "Multiplying Matrix One by random scalar: " << randomScalar << "\n";
    Matrix* scalarProduct = matrixOne * randomScalar;
    cout << *scalarProduct << "\n";
    cout << "\n";
    cout << "Thank you!\n\n-Ridha Chowdhury";


    // Be sure to output details about calculation being performed and the results
    // When you print Matrix pointers (object pointers), remember to dereference
    // the pointer when you invoke << (output), and it accepts an object reference, not an object pointers

    return 505;
}