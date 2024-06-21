#include "s21_matrix_oop.h"

int main() {
    cout << "Hello World!" << endl;
    try {
        int rows = -2;
        int cols = -2;
        S21Matrix x(rows, cols);

        for (int i = 0; i < x.GetRows(); ++i) {
            for (int j = 0; j < x.GetCols(); ++j) {
                x(i, j) = i * x.GetCols() + j;
            }
        }

        rows = 2;
        cols = 1;
        S21Matrix y(rows, cols);

        for (int i = 0; i < y.GetRows(); ++i) {
            for (int j = 0; j < y.GetCols(); ++j) {
                y(i, j) = i * y.GetCols() + j;
            }
        }
        x += y;

        cout << y << endl;
        cout << x << endl;
    } catch (std::out_of_range &error) {
        cout << error.what() << endl;
    }

    return 0;
}
