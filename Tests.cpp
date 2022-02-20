#include <gtest/gtest.h>
#include "matrix.h"
#include "matrix.cpp"
using namespace BMSTU;

TEST(MatrixTests, default_getrows_getcols_isempty) {
    Matrix<int> m1;
    ASSERT_EQ(m1.GetRows(), 0);
    ASSERT_EQ(m1.GetCols(), 0);
    ASSERT_TRUE(m1.IsEmpty());
}

TEST(MatrixTests, size_construction_cell_function) {
    Matrix<int> m1(2, 3);
    const Matrix<int> m2(2, 3, 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(m1.cell(i, j), 0);
            ASSERT_EQ(m2.cell(i, j), 3);
        }
    }
    ASSERT_EQ(m1.GetRows(), 2);
    ASSERT_EQ(m1.GetCols(), 3);
    ASSERT_EQ(m2.GetRows(), 2);
    ASSERT_EQ(m2.GetCols(), 3);
}
TEST(MatrixTests, initializer_list_operator_and_get_index_operator) {
    Matrix<int> m1 {{1, 2, 3},{4, 4, 4}};
    const Matrix<int> m2 {{5, 6}, {7, 7}, {8, 9}};
    ASSERT_EQ(m1.GetRows(), 2);
    ASSERT_EQ(m1.GetCols(), 3);
    ASSERT_EQ(m2.GetRows(), 3);
    ASSERT_EQ(m2.GetCols(), 2);
    ASSERT_EQ(m1[0][1], 2);
    ASSERT_EQ(m1[1][2], 4);
    ASSERT_EQ(m2[0][1], 6);
    ASSERT_EQ(m2[2][0], 8);
}
TEST(MatrixTests, copy_assigments_constructor_operator) {
    const Matrix<int> m1 {{1, 2}};
    Matrix<int> m2(m1);
    Matrix<int> m3;
    const Matrix<int> m4 {{3}};
    m3 = m4;
    Matrix<int> m5;
    m5 = {{3, 4}};
    ASSERT_EQ(m2.GetRows(), 1);
    ASSERT_EQ(m2.GetCols(), 2);
    ASSERT_EQ(m4.GetRows(), 1);
    ASSERT_EQ(m4.GetCols(), 1);
    ASSERT_EQ(m3.GetRows(), 1);
    ASSERT_EQ(m3.GetCols(), 1);
    ASSERT_EQ(m5.GetRows(), 1);
    ASSERT_EQ(m5.GetCols(), 2);
    ASSERT_EQ(m2[0][0], 1);
    ASSERT_EQ(m2[0][1], 2);
    ASSERT_EQ(m3[0][0], 3);
    ASSERT_EQ(m4[0][0], 3);
    ASSERT_EQ(m5[0][0], 3);
    ASSERT_EQ(m5[0][1], 4);
}
TEST(MatrixTests, sum_difference_scalar_operators) {
    Matrix<int> m0 {{1}};
    Matrix<int> m1 {{1, 2}};
    Matrix<int> m2 {{9, 8}};
    Matrix<int> m3(m1+m2);
    ASSERT_EQ(m3[0][0], 10);
    ASSERT_EQ(m3[0][1], 10);
    m3 = m1 - m2;
    ASSERT_EQ(m3[0][0], -8);
    ASSERT_EQ(m3[0][1], -6);
    m3 = m1*4;
    ASSERT_EQ(m3[0][0], 4);
    ASSERT_EQ(m3[0][1], 8);
    ASSERT_ANY_THROW(m0+m1);
    ASSERT_ANY_THROW(m0-m1);
}
TEST(MatrixTests, multiplication_and_trans_operators) {
    Matrix<int> m0 {{1, 1}, {1, 1}, {1, 1}};
    const Matrix<int> m1 {{1, 2}, {2, 2}, {1, 1}};
    const Matrix<int> m2 {{1, 1}, {1, 1}};
    Matrix<int> m3;
    m3 = m1*m2;
    ASSERT_EQ(m1.GetRows(), 3);
    ASSERT_EQ(m3.GetRows(), 3);
    ASSERT_EQ(m2.GetCols(), 2);
    ASSERT_EQ(m3.GetCols(), 2);
    ASSERT_EQ(m3[0][0], 3);
    ASSERT_EQ(m3[0][1], 3);
    ASSERT_EQ(m3[1][0], 4);
    ASSERT_EQ(m3[1][1], 4);
    ASSERT_EQ(m3[2][0], 2);
    ASSERT_EQ(m3[2][1], 2);
    ASSERT_ANY_THROW(m0*m3);
    m3 = m1.trans();
    ASSERT_EQ(m3.GetRows(), 2);
    ASSERT_EQ(m3.GetCols(), 3);
    ASSERT_EQ(m3[1][0], 2);
    ASSERT_EQ(m3[1][1], 2);
    ASSERT_EQ(m3[1][2], 1);
    m3 = m0.trans();
    ASSERT_EQ(m3.GetRows(), 2);
    ASSERT_EQ(m3.GetCols(), 3);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(m3[i][i], 1);
        }
    }
}
TEST(MatrixTests, single_zero_matrices) {
    SingleMatrix<int> M1(2);
    ZeroMatrix<int> N1(2, 3);
    ASSERT_EQ(M1.GetRows(), 2);
    ASSERT_EQ(M1.GetCols(), 2);
    ASSERT_EQ(N1.GetRows(), 2);
    ASSERT_EQ(N1.GetCols(), 3);
    ASSERT_EQ(M1[0][0], 1);
    ASSERT_EQ(M1[1][1], 1);
    ASSERT_EQ(M1[0][1], 0);
    ASSERT_EQ(M1[1][0], 0);
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            ASSERT_EQ(N1[i][j], 0);
        }
    }
}
TEST(MatrixTests, exeption) {
    Matrix<int> m1{{1, 2},
                         {3, 4},
                         {5, 6}};
    Matrix<int> m2{{1},
                         {2},
                         {3}};

    ASSERT_THROW(m1*m2, MatricesBinaryOperationException);
}
///zadanye s zacheta
TEST(MatrixTests, over) {
    static int m1[MAX][MAX] {{21, 2}, {8, 2}, {54, 1}};
    static int m2[MAX][MAX] {{33, 12,1}, {1, 1,1}};
    int m3[MAX][MAX]{{0,0,0},{0,0,0},{0,0,0}};
    impli(m1,m2,m3);
    print(m3, 3, 3);


}
///variant 2
TEST(MatrixTests, implic) {
    static Matrix<int> m1{{1, 2},
                         {2, 2},
                         {1, 1}};
    static Matrix<int> m2{{1, 1, 2},
                         {1, 1, 1}};
    Matrix<int> m3;
    m3 = m1 * m2;
    umnoprint(m3,3,3);
}
///





/// Create function for print matrix to console out
/// aka
/*
 * void print(... matrix){
 *
 *     const int MAX = 100;
    void print(Matrix<int> m1[][MAX] ,int m,int n){
        for (int i = 0;i < m;i++) {
            for (int j = 0; j < n; j++) {
                std::cout << m1[i][j] << std::endl;
            }
        }
    }
    int varik() {

    Matrix<int> m1{{1, 2},
                   {3, 4},
                   {5, 6}};
    print(m1, 3, 2);
    return 0;
}
 * }
 */
