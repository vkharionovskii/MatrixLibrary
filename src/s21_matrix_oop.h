#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <exception>
#include <iostream>

using std::cout;
using std::endl;

class S21Matrix {
private:
    int rows_, cols_;  // Rows and columns
    double** matrix_;  // Pointer to the memory where the matrix is allocated

    void IncorrectMatrix() const;
    void SetEmptyMatrix();
    void CleanMatrix();

    static double HelpDetermenant(const S21Matrix* M);
    static void Minor(int row, int column, const S21Matrix* Matrix, S21Matrix* M);

public:
    S21Matrix();                    // Default constructor +
    S21Matrix(int rows, int cols);  // constructor +

    S21Matrix(const S21Matrix& copy);  // copy +
    S21Matrix(S21Matrix&& offset);     // constructor offset +

    ~S21Matrix();  // Destructor +

    bool EqMatrix(const S21Matrix& other) const;  //  +
    void SumMatrix(const S21Matrix& other);       //  +
    void SubMatrix(const S21Matrix& other);       //  +
    void MulNumber(const double num);             //  +
    void MulMatrix(const S21Matrix& other);       //  +

    S21Matrix Transpose() const;        //  +
    S21Matrix CalcComplements() const;  //  +
    double Determinant() const;         //  +
    S21Matrix InverseMatrix() const;    //  +

    S21Matrix& operator=(const S21Matrix& o);   //  assignment operator overload +
    S21Matrix& operator=(S21Matrix&& offset);   //  assignment operator overload offset+
    bool operator==(const S21Matrix& o) const;  //  equal assignment operator overload +

    double& operator()(int row, int col) const;  // +

    S21Matrix& operator+=(const S21Matrix& o);      //  +
    S21Matrix operator+(const S21Matrix& o) const;  //  +

    S21Matrix& operator-=(const S21Matrix& o);      //  +
    S21Matrix operator-(const S21Matrix& o) const;  //  +

    S21Matrix& operator*=(const S21Matrix& o);  //  +
    S21Matrix& operator*=(double number);       //  +

    S21Matrix operator*(const S21Matrix& o) const;  //  +
    S21Matrix operator*(double number) const;       //  +

    int GetRows() const;
    int GetCols() const;

    void SetRows(int new_rows);
    void SetCols(int new_cols);
};

std::ostream& operator<<(std::ostream& out, const S21Matrix& o);

#endif  // SRC_S21_MATRIX_OOP_H_
