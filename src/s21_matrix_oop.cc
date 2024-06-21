#include "s21_matrix_oop.h"
//  Constructors
S21Matrix::S21Matrix() : rows_(1), cols_(1) {
    // cout << "Defaultttt constructor called" << endl;
    SetEmptyMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols), matrix_(nullptr) {
    // cout << "Constructor called" << endl;
    SetEmptyMatrix();
}

S21Matrix::~S21Matrix() {
    // cout << "Destructor called" << endl;
    CleanMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& copy) {
    // cout << "Copy constructor called" << endl;

    this->rows_ = copy.rows_;
    this->cols_ = copy.cols_;

    this->SetEmptyMatrix();

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            this->matrix_[i][j] = copy.matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& offset) {
    // cout << "Offset constructor called" << endl;

    this->rows_ = offset.rows_;
    this->cols_ = offset.cols_;
    this->matrix_ = offset.matrix_;

    offset.rows_ = 0;
    offset.cols_ = 0;
    offset.matrix_ = nullptr;
}

//  Help Methods
void S21Matrix::SetEmptyMatrix() {
    rows_ = fabs(rows_);
    cols_ = fabs(cols_);

    if (rows_ != 0 && cols_ != 0) {
        matrix_ = new double*[rows_]();

        for (int i = 0; i < rows_; ++i) {
            matrix_[i] = new double[cols_]();
        }
    }
}

void S21Matrix::CleanMatrix() {
    if ((rows_ > 0 && cols_ > 0) && matrix_ != nullptr) {
        for (int i = 0; i < rows_; ++i) {
            delete[] matrix_[i];
        }

        delete[] matrix_;
        matrix_ = nullptr;
    }
}

//  operator =, ==; method eqmatrix_
S21Matrix& S21Matrix::operator=(const S21Matrix& o) {
    // cout << "Operator assignment called" << endl;
    this->IncorrectMatrix();
    o.IncorrectMatrix();

    if (this == &o) {
        return *this;
    }

    if (this->matrix_ != nullptr) {
        this->CleanMatrix();
    }

    this->cols_ = o.cols_;
    this->rows_ = o.rows_;
    this->SetEmptyMatrix();

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            this->matrix_[i][j] = o.matrix_[i][j];
        }
    }

    return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& offset) {  //  assignment operator overload offset
    // cout << "Operator assignment offset called" << endl;
    this->IncorrectMatrix();
    offset.IncorrectMatrix();

    if (this == &offset) {
        return *this;
    }

    if (this->matrix_ != nullptr) {
        this->CleanMatrix();
    }

    this->rows_ = offset.rows_;
    this->cols_ = offset.cols_;
    this->matrix_ = offset.matrix_;

    offset.matrix_ = nullptr;

    return *this;
}

bool S21Matrix::operator==(const S21Matrix& o) const {
    this->IncorrectMatrix();
    o.IncorrectMatrix();

    if (this->cols_ != o.cols_ || this->rows_ != o.rows_) {
        return false;
    }

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            if (fabs(this->matrix_[i][j] - o.matrix_[i][j]) > 1e-7) {
                return false;
            }
        }
    }

    return true;
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const { return (*this == other); }

//  operator +=, +; method summatrix_
S21Matrix& S21Matrix::operator+=(const S21Matrix& o) {
    this->IncorrectMatrix();
    o.IncorrectMatrix();

    if (this->cols_ != o.cols_ || this->rows_ != o.rows_) {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            this->matrix_[i][j] += o.matrix_[i][j];
        }
    }

    return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix& o) const {
    S21Matrix res(this->rows_, this->cols_);
    res = *this;

    return res += o;
}

void S21Matrix::SumMatrix(const S21Matrix& other) { *this += (other); }

//  operator -=, -; method submatrix_
S21Matrix& S21Matrix::operator-=(const S21Matrix& o) {
    this->IncorrectMatrix();
    o.IncorrectMatrix();

    if (this->cols_ == o.cols_ && this->rows_ == o.rows_) {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                this->matrix_[i][j] -= o.matrix_[i][j];
            }
        }
    } else {
        throw std::out_of_range("Incorrect input, matrices should have the same size");
    }

    return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& o) const {
    S21Matrix res(this->rows_, this->cols_);
    res = *this;

    return res -= o;
}

void S21Matrix::SubMatrix(const S21Matrix& other) { *this -= (other); }

//  operator *=, *; method mulmatrix_
S21Matrix& S21Matrix::operator*=(const S21Matrix& o) {
    this->IncorrectMatrix();
    o.IncorrectMatrix();

    S21Matrix res(this->rows_, o.cols_);

    if (this->cols_ == o.rows_) {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < o.cols_; ++j) {
                for (int k = 0; k < o.rows_; k++) {
                    res.matrix_[i][j] += this->matrix_[i][k] * o.matrix_[k][j];
                }
            }
        }
    } else {
        throw(std::range_error("Error!\nCols != Rows\nOperation not possible"));
    }

    *this = res;

    return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& o) const {
    S21Matrix res(this->rows_, o.cols_);
    res = *this;

    return res *= o;
}

void S21Matrix::MulMatrix(const S21Matrix& other) { *this *= other; }

//  operator *=, *; method MulNumber
S21Matrix& S21Matrix::operator*=(double number) {
    this->IncorrectMatrix();

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->cols_; ++j) {
            this->matrix_[i][j] *= number;
        }
    }

    return *this;
}

S21Matrix S21Matrix::operator*(double number) const {
    // cout << "Operator multiplie called" << endl;
    S21Matrix res(this->rows_, this->cols_);
    res = *this;

    return res *= number;
}

void S21Matrix::MulNumber(const double num) { *this *= num; }

//  operator ()
double& S21Matrix::operator()(int row, int col) const {
    this->IncorrectMatrix();

    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Incorrect input, index is out of range");
    }

    return this->matrix_[row][col];
}

//  Methods for matrix
S21Matrix S21Matrix::Transpose() const {
    this->IncorrectMatrix();

    S21Matrix res(this->cols_, this->rows_);

    if (this->rows_ && this->cols_) {
        for (int i = 0; i < this->rows_; ++i) {
            for (int j = 0; j < this->cols_; ++j) {
                res.matrix_[j][i] = this->matrix_[i][j];
            }
        }
    }

    return res;
}

// Determenant and help function for determenant
void S21Matrix::Minor(int row, int column, const S21Matrix* Matrix, S21Matrix* M) {
    // cout << "Method Minor called" << endl;
    if (Matrix->matrix_ != NULL) {
        int k = 0;
        int z = 0;

        for (int i = 0; i < Matrix->rows_; ++i) {
            k = i;
            if (k > row - 1) {
                k--;
            }

            for (int j = 0; j < Matrix->cols_; ++j) {
                z = j;
                if (z > column - 1) {
                    z--;
                }

                if (i != (row - 1) && j != (column - 1)) {
                    M->matrix_[k][z] = Matrix->matrix_[i][j];
                }
            }
        }
    }
}

double S21Matrix::HelpDetermenant(const S21Matrix* Matrix) {
    double res = 0.0;

    if (Matrix->rows_ == 2 && Matrix->cols_ == 2) {
        res = Matrix->matrix_[0][0] * Matrix->matrix_[1][1] - Matrix->matrix_[0][1] * Matrix->matrix_[1][0];
    } else {
        for (int i = 0; i < Matrix->rows_; ++i) {
            S21Matrix* M = NULL;
            M = new S21Matrix(Matrix->rows_ - 1, Matrix->cols_ - 1);

            S21Matrix::Minor(1, i + 1, Matrix, M);

            res += pow((-1), i) * Matrix->matrix_[0][i] * S21Matrix::HelpDetermenant(M);

            M->~S21Matrix();
        }
    }

    return res;
}

double S21Matrix::Determinant() const {
    // cout << "Method Determinant called" << endl;
    this->IncorrectMatrix();

    double res = 0;
    if (this->rows_ == this->cols_) {
        res = this->matrix_[0][0];
        if (this->rows_ > 1) {
            res = S21Matrix::HelpDetermenant(this);
        }
    } else {
        throw(std::range_error("Error!\nMatrix is not square"));
    }

    return res;
}

S21Matrix S21Matrix::CalcComplements() const {
    // cout << "Method Calc Complements called" << endl;
    this->IncorrectMatrix();
    if (this->cols_ != this->rows_) {
        throw(std::range_error("Error!\nMatrices not square"));
    }

    S21Matrix res(this->rows_, this->cols_);

    for (int i = 0; i < this->rows_; ++i) {
        for (int j = 0; j < this->rows_; ++j) {
            double result = 0.0;
            S21Matrix* M = new S21Matrix(this->rows_ - 1, this->cols_ - 1);

            Minor(i + 1, j + 1, this, M);
            result = M->Determinant();
            res.matrix_[i][j] = pow((-1), i + j) * result;
            M->~S21Matrix();
            delete M;
            M = nullptr;
        }
    }

    return res;
}

S21Matrix S21Matrix::InverseMatrix() const {
    // cout << "Method inverse matrix called" << endl;
    this->IncorrectMatrix();
    double det = 0;

    det = this->Determinant();
    if (det == 0.0) {
        throw(std::range_error("Error!\nDetermenant is 0"));
    }

    S21Matrix res = this->CalcComplements();
    res = res.Transpose();
    res.MulNumber((1.0 / det));

    return res;
}

void S21Matrix::IncorrectMatrix() const {
    // cout << "Method incorrect Matrix called" << endl;
    if (this->matrix_ == nullptr || this->rows_ < 0 || this->cols_ < 0) {
        throw(std::range_error("Error!\nIncorrect matrix"));
    }
}

int S21Matrix::GetRows() const { return (this->rows_); }

int S21Matrix::GetCols() const { return (this->cols_); }

void S21Matrix::SetRows(int new_rows) {
    S21Matrix res(new_rows, cols_);
    int count = 0;

    if (rows_ > new_rows)
        count = new_rows;
    else if (rows_ < new_rows)
        count = rows_;

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < cols_; ++j) {
            res.matrix_[i][j] = this->matrix_[i][j];
        }
    }

    *this = res;
}

void S21Matrix::SetCols(int new_cols) {
    S21Matrix res(rows_, new_cols);
    int count = 0;

    if (cols_ > new_cols)
        count = new_cols;
    else if (cols_ < new_cols)
        count = cols_;

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < count; ++j) {
            res.matrix_[i][j] = this->matrix_[i][j];
        }
    }

    *this = res;
}

std::ostream& operator<<(std::ostream& out, const S21Matrix& o) {
    int i = 0;
    int rows = o.GetRows();
    int cols = o.GetCols();
    cout << "rows = " << rows << " cols = " << cols << endl << endl;

    while (i < rows) {
        out << "|";
        int j = 0;
        while (j < cols) {
            out << o(i, j) << "\t";
            ++j;
        }
        out << "|" << endl;
        ++i;
    }

    return out;
}
