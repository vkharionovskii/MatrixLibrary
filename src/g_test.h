#ifndef SRC_G_TEST_H_
#define SRC_G_TEST_H_

#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

class Test : public ::testing::Test {
protected:
    S21Matrix *t1;
    S21Matrix *t2;
    S21Matrix *t3;

public:
    Test() { /* init protected members here */
        t1 = new S21Matrix(2, 2);
        t2 = new S21Matrix(2, 2);
        t3 = new S21Matrix(1, 2);
    }

    ~Test() { /* free protected members here */
        delete t1;
        delete t2;
        delete t3;
    }

    void SetUp() {
        // cout << "SetUp..." << endl;
        (*t1)(0, 0) = 1;
        (*t1)(0, 1) = 2;
        (*t1)(1, 0) = 3;
        (*t1)(1, 1) = 4;

        (*t2)(0, 0) = 2;
        (*t2)(0, 1) = 2;
        (*t2)(1, 0) = 2;
        (*t2)(1, 1) = 2;

        (*t3)(0, 0) = 2;
        (*t3)(0, 1) = 12;
    }

    void TearDown() {}
};

#endif  // SRC_G_TEST_H_
