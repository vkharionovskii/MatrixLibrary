#include "g_test.h"

TEST_F(Test, TestSum) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 3;
    expected(0, 1) = 4;
    expected(1, 0) = 5;
    expected(1, 1) = 6;

    ASSERT_EQ((*t1 + *t2).EqMatrix(expected), true);
    t1->SumMatrix(*t2);
    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestSumException) {
    try {
        *t1 + *t3;
    } catch (std::out_of_range &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestSub) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = -1;
    expected(0, 1) = 0;
    expected(1, 0) = 1;
    expected(1, 1) = 2;

    ASSERT_EQ((*t1 - *t2).EqMatrix(expected), true);
    t1->SubMatrix(*t2);
    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestSubException) {
    try {
        *t1 - *t3;
    } catch (std::out_of_range &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestMulNumber) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 4;
    expected(0, 1) = 8;
    expected(1, 0) = 12;
    expected(1, 1) = 16;

    ASSERT_EQ((*t1 * 4).EqMatrix(expected), true);
    t1->MulNumber(4);
    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestMulMatrix) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 6;
    expected(0, 1) = 6;
    expected(1, 0) = 14;
    expected(1, 1) = 14;

    ASSERT_EQ(((*t1) * (*t2)).EqMatrix(expected), true);
    t1->MulMatrix(*t2);
    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestMulMatrixException) {
    try {
        (*t1) * (*t3);
    } catch (std::range_error &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestAssignment) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 3;
    expected(0, 1) = 4;
    expected(1, 0) = 5;
    expected(1, 1) = 6;

    *t1 = expected;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestEqualMatrix) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 3;
    expected(0, 1) = 4;
    expected(1, 0) = 5;
    expected(1, 1) = 6;

    *t1 = expected;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestAssignmentSum) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 3;
    expected(0, 1) = 4;
    expected(1, 0) = 5;
    expected(1, 1) = 6;

    *t1 += *t2;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestAssignmentSub) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = -1;
    expected(0, 1) = 0;
    expected(1, 0) = 1;
    expected(1, 1) = 2;

    *t1 -= *t2;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestAssignmentMulNumber) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 4;
    expected(0, 1) = 8;
    expected(1, 0) = 12;
    expected(1, 1) = 16;

    *t1 *= 4;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestAssignmentMulMatrix) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 6;
    expected(0, 1) = 6;
    expected(1, 0) = 14;
    expected(1, 1) = 14;

    *t1 *= *t2;

    ASSERT_EQ((*t1).EqMatrix(expected), true);
}

TEST_F(Test, TestIndexElements) { ASSERT_EQ((*t1)(1, 1), 4); }

TEST_F(Test, TestIndexElementsException) {
    try {
        ASSERT_EQ((*t1)(2, 1), 4);
    } catch (std::out_of_range &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestDetermenant) { ASSERT_EQ(t1->Determinant(), -2); }

TEST_F(Test, TestDetermenantException) {
    try {
        ASSERT_EQ(t3->Determinant(), -2);
    } catch (std::range_error &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestCalcComplements) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = 4;
    expected(0, 1) = -3;
    expected(1, 0) = -2;
    expected(1, 1) = 1;

    ASSERT_EQ(t1->CalcComplements().EqMatrix(expected), true);
}

TEST_F(Test, TestCalcComplementsException) {
    try {
        t3->CalcComplements();
    } catch (std::range_error &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestInverseMatrix) {
    const S21Matrix expected(2, 2);

    expected(0, 0) = -2;
    expected(0, 1) = 1;
    expected(1, 0) = 1.5;
    expected(1, 1) = -0.5;

    ASSERT_EQ(t1->InverseMatrix().EqMatrix(expected), true);
}

TEST_F(Test, TestInverseMatrixException) {
    try {
        t2->InverseMatrix();
    } catch (std::range_error &error) {
        cout << error.what() << endl;
    }
}

TEST_F(Test, TestConstructorCopy) {
    S21Matrix t(*t1);

    ASSERT_EQ(t.EqMatrix(*t1), true);
}

TEST_F(Test, TestConstructofOffset) {
    *t2 = *t1;
    S21Matrix t = std::move(*t1);

    ASSERT_EQ(t.EqMatrix(*t2), true);
}

TEST_F(Test, TestAssignmentOffset) {
    *t3 = *t1;
    *t2 = t1->CalcComplements();

    ASSERT_EQ(t2->EqMatrix(t1->CalcComplements()), true);
}

TEST_F(Test, TestGetterSetter) {
    const S21Matrix expected(3, 3);

    for (int i = 0; i < expected.GetRows() - 1; ++i) {
        for (int j = 0; j < expected.GetCols() - 1; ++j) {
            expected(i, j) = i * expected.GetCols() + j;
            (*t1)(i, j) = i * expected.GetCols() + j;
        }
    }

    t1->SetCols(3);
    t1->SetRows(3);

    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestGetterSetterSecond) {
    const S21Matrix expected(1, 1);
    expected(0, 0) = 1;

    t1->SetCols(1);
    t1->SetRows(1);

    ASSERT_EQ(t1->EqMatrix(expected), true);
}

TEST_F(Test, TestTranspose) {
    const S21Matrix expected(2, 2);
    expected(0, 0) = 1;
    expected(0, 1) = 3;
    expected(1, 0) = 2;
    expected(1, 1) = 4;

    ASSERT_EQ(t1->Transpose().EqMatrix(expected), true);
}

TEST_F(Test, OperatorOut) {
    cout << *t1 << endl;
    cout << *t2 << endl;
    cout << *t3 << endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
