#include "include/matrix.h"

#include "gtest/gtest.h"

class MatrixFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        matrix = new raytracer::Matrix();
        m1 = new raytracer::Matrix();
        m2 = new raytracer::Matrix();
        identity = new raytracer::Matrix();
        result = new raytracer::Matrix();
        tuple = new raytracer::Tuple();
        tResult = new raytracer::Tuple();
        data = new std::vector<double>();
        d1 = new std::vector<double>();
        d2 = new std::vector<double>();
    }

    virtual void TearDown() {
        delete matrix;
        delete m1;
        delete m2;
        delete identity;
        delete result;
        delete tuple;
        delete tResult;
        delete data;
        delete d1;
        delete d2;
    }

    raytracer::Matrix * matrix;
    raytracer::Matrix * m1;
    raytracer::Matrix * m2;
    raytracer::Matrix * identity;
    raytracer::Matrix * result;
    raytracer::Tuple * tuple;
    raytracer::Tuple * tResult;
    std::vector<double> * data;
    std::vector<double> * d1;
    std::vector<double> * d2;
};

TEST_F(MatrixFixture, Test4x4Matrix) {
    * matrix = raytracer::Matrix(4, 4);
    * data = {1,    2,    3,    4,
              5.5,  6.5,  7.5,  8.5,
              9,    10,   11,   12,
              13.5, 14.5, 15.5, 16.5};
    matrix->setMatrixData(* data);
    EXPECT_EQ(1, (* matrix)(0, 0));
    EXPECT_EQ(4, (* matrix)(0, 3));
    EXPECT_EQ(5.5, (* matrix)(1, 0));
    EXPECT_EQ(7.5, (* matrix)(1, 2));
    EXPECT_EQ(11, (* matrix)(2, 2));
    EXPECT_EQ(13.5, (* matrix)(3, 0));
    ASSERT_EQ(15.5, (* matrix)(3, 2));
}

TEST_F(MatrixFixture, Test2x2Matrix) {
    * matrix = raytracer::Matrix(2, 2);
    * data = {-3, 5, 1, -2};
    matrix->setMatrixData(* data);
    EXPECT_EQ(-3, (* matrix)(0, 0));
    EXPECT_EQ(5, (* matrix)(0, 1));
    EXPECT_EQ(1, (* matrix)(1, 0));
    ASSERT_EQ(-2, (* matrix)(1, 1));
}

TEST_F(MatrixFixture, Test3x3Matrix) {
    * matrix = raytracer::Matrix(3, 3);
    * data = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix->setMatrixData(* data);
    EXPECT_EQ(-3, (* matrix)(0, 0));
    EXPECT_EQ(-2, (* matrix)(1, 1));
    ASSERT_EQ(1, (* matrix)(2, 2));
}

TEST_F(MatrixFixture, TestEquality) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * data = {1, 2, 3, 4,
              5, 6, 7, 8,
              9, 8, 7, 6,
              5, 4, 3, 2};
    m1->setMatrixData(* data);
    m2->setMatrixData(* data);
    ASSERT_TRUE(m1->isEqual(* m2));
}

TEST_F(MatrixFixture, TestFalseEquality) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * d1 = {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2};
    * d2 = {2, 3, 4, 5,
            6, 7, 8, 9,
            8, 7, 6, 5,
            4, 3, 2, 1};
    m1->setMatrixData(* d1);
    m2->setMatrixData(* d2);
    ASSERT_FALSE(m1->isEqual(* m2));
}

// verifies that the rest of the matrix is also readable

TEST_F(MatrixFixture, TestFalseEquality2) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * d1 = {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2};
    * d2 = {1, 2, 3, 4,
            6, 7, 8, 9,
            8, 7, 6, 5,
            4, 3, 2, 1};
    m1->setMatrixData(* d1);
    m2->setMatrixData(* d2);
    ASSERT_FALSE(m1->isEqual(* m2));
}

TEST_F(MatrixFixture, TestEmptyOperator) {
    * m1 = raytracer::Matrix(4, 4);
    * data = {0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 0,
              0, 0, 0, 0};
    m1->setMatrixData(* data);
    ASSERT_TRUE(m1->isEmpty());
}

TEST_F(MatrixFixture, TestEqualityOperator) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * data = {1, 2, 3, 4,
              5, 6, 7, 8,
              9, 8, 7, 6,
              5, 4, 3, 2};
    m1->setMatrixData(* data);
    m2->setMatrixData(* data);
    ASSERT_EQ(* m1, * m2);
}

TEST_F(MatrixFixture, TestFalseEqualityOperator) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * d1 = {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2};
    * d2 = {2, 3, 4, 5,
            6, 7, 8, 9,
            8, 7, 6, 5,
            4, 3, 2, 1};
    m1->setMatrixData(* d1);
    m2->setMatrixData(* d2);
    ASSERT_NE(* m1, * m2);
}

TEST_F(MatrixFixture, TestRowSize) {
    * m1 = raytracer::Matrix(4, 4);
    * m2 = raytracer::Matrix(4, 4);
    * data = {1, 2, 3, 4,
              5, 6, 7, 8,
              9, 8, 7, 6,
              5, 4, 3, 2};
    m1->setMatrixData(* data);
    ASSERT_EQ(4, m1->getRowSize());
}

TEST_F(MatrixFixture, Test4x4MatrixMultiplication) {
    * d1 = {1, 2, 3, 4,
            5, 6, 7, 8,
            9, 8, 7, 6,
            5, 4, 3, 2};
    * d2 = {-2, 1, 2,  3,
            3, 2, 1, -1,
            4, 3, 6,  5,
            1, 2, 7,  8};
    * data = {20, 22,  50,  48,
              44, 54, 114, 108,
              40, 58, 110, 102,
              16, 26,  46,  42};
    * m1 = raytracer::Matrix(4,4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    m2->setMatrixData(* d2);
    * result = raytracer::Matrix(4, 4);
    result->setMatrixData(* data);
    ASSERT_EQ(* result, * m1 * * m2);
}

TEST_F(MatrixFixture, TestMatrixTupleMultiplication) {
    * data = {1, 2, 3, 4,
            2, 4, 4, 2,
            8, 6, 4, 1,
            0, 0, 0, 1};
    * tuple = {1, 2, 3,  1};
    * tResult = {18, 24,  33,  1};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* data);
    ASSERT_EQ(* tResult, * m1 * * tuple);
}

TEST_F(MatrixFixture, TestIdentityMatrixMultiplication) {
    * d1 = {0, 1, 2, 4,
            1, 2, 4, 8,
            2, 4, 8, 16,
            4, 8, 16, 32};
    * d2 = {1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1};
    * tuple = {1, 2, 3,  4};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * identity = raytracer::Matrix(4, 4);
    identity->setMatrixData(* d2);
    EXPECT_EQ(* m1, * m1 * * identity);
    ASSERT_EQ(* tuple, * identity * * tuple);
}

TEST_F(MatrixFixture, TransposingMatrix) {
    * d1 = {0, 9, 3, 0,
            9, 8, 0, 8,
            1, 8, 5, 3,
            0, 0, 5, 8};
    * d2 = {0, 9, 1, 0,
            9, 8, 8, 0,
            3, 0, 5, 5,
            0, 8, 3, 8};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    m2->setMatrixData(* d2);
    * result = raytracer::Matrix(4, 4);
    * result = transpose(* m1);
    ASSERT_EQ(* result, * m2);
}

TEST_F(MatrixFixture, DeterminantMatrix) {
    * data = {1, 5,
             -3, 2};
    * m1 = raytracer::Matrix(2, 2);
    m1->setMatrixData(* data);
    ASSERT_EQ(17.0, determinant(* m1));
}

TEST_F(MatrixFixture, Submatrix1) {
    * d1 = {1, 5,  0,
           -3, 2,  7,
            0, 6, -3};
    * d2 = {-3, 2,
             0, 6};
    * m1 = raytracer::Matrix(3, 3);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(2, 2);
    m2->setMatrixData(* d2);
    ASSERT_EQ(* m2, submatrix(* m1, 0, 2));
}

TEST_F(MatrixFixture, Submatrix2) {
    * d1 = {-6, 1, 1, 6,
            -8, 5, 8, 6,
            -1, 0, 8, 2,
            -7, 1, -1, 1};
    * d2 = {-6, 1, 6,
            -8, 8, 6,
            -7, -1, 1};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(3, 3);
    m2->setMatrixData(* d2);
    ASSERT_EQ(* m2, submatrix(* m1, 2, 1));
}

TEST_F(MatrixFixture, MinorMatrix) {
    * data = {3,  5,  0,
              2, -1, -7,
              6, -1,  5};
    * m1 = raytracer::Matrix(3, 3);
    m1->setMatrixData(* data);
    * m2 = raytracer::Matrix(2, 2);
    * m2 = submatrix(* m1, 1, 0);
    EXPECT_EQ(25.0, determinant(* m2));
    ASSERT_EQ(25.0, minor(* m1, 1, 0));
}

TEST_F(MatrixFixture, CofactorMatrix) {
    * data = {3,  5,  0,
              2, -1, -7,
              6, -1,  5};
    * m1 = raytracer::Matrix(3, 3);
    m1->setMatrixData(* data);
    EXPECT_EQ(-12.0, minor(* m1, 0, 0));
    EXPECT_EQ(-12.0, cofactor(* m1, 0, 0));
    EXPECT_EQ(25, minor(* m1, 1, 0));
    ASSERT_EQ(-25, cofactor(* m1, 1, 0));
}

TEST_F(MatrixFixture, DeterminantMatrix3x3) {
    * data = { 1, 2,  6,
              -5, 8, -4,
               2, 6,  4};
    * m1 = raytracer::Matrix(3, 3);
    m1->setMatrixData(* data);
    EXPECT_EQ(56, cofactor(* m1, 0, 0));
    EXPECT_EQ(12, cofactor(* m1, 0, 1));
    EXPECT_EQ(-46, cofactor(* m1, 0, 2));
    ASSERT_EQ(-196, determinant(* m1));
}

TEST_F(MatrixFixture, DeterminantMatrix4x4) {
    * data = {-2, -8,  3,  5,
              -3,  1,  7,  3,
               1,  2, -9,  6,
               -6, 7,  7, -9};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* data);
    EXPECT_EQ(690, cofactor(* m1, 0, 0));
    EXPECT_EQ(447, cofactor(* m1, 0, 1));
    EXPECT_EQ(210, cofactor(* m1, 0, 2));
    EXPECT_EQ(51, cofactor(* m1, 0, 3));
    ASSERT_EQ(-4071, determinant(* m1));

}

TEST_F(MatrixFixture, TestInvertibletMatrix) {
    * d1 = {6,  4, 4,  4,
            5,  5, 7,  6,
            4, -9, 3, -7,
            9,  1, 7, -6};
    * d2 = {-4,  2, -2, -3,
             9,  6,  2,  6,
             0, -5,  1, -5,
             0,  0,  0,  0};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    m2->setMatrixData(* d2);
    EXPECT_EQ(-2120, determinant(* m1));
    ASSERT_EQ(0, determinant(* m2));
}

TEST_F(MatrixFixture, InvertMatrix1) {
    * d1 = {-5,  2,  6, -8,
             1, -5,  1,  8,
             7,  7, -6, -7,
             1, -3,  7,  4};
    * d2 = { 0.21805,  0.45113, 0.24060, -0.04511,
            -0.80827, -1.4577,  -0.44361, 0.52068,
            -0.07895, -0.22368, -0.05263, 0.19737,
            -0.52256, -0.81391, -0.30075, 0.30639};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    * m2 = inverse(* m1);
    * result = raytracer::Matrix(4, 4);
    result->setMatrixData(* d2);

    EXPECT_EQ(532, determinant(* m1));
    EXPECT_EQ(-160, cofactor(* m1, 2, 3));
    EXPECT_DOUBLE_EQ(-160.0/532.0, (* m2)(3, 2));
    EXPECT_EQ(105, cofactor(* m1, 3, 2));
    EXPECT_DOUBLE_EQ(105.0/532.0, (* m2)(2, 3));
    for (int i = 0; i < m1->getRowSize(); i++) {
        for (int j = 0; j < m1->getColSize(); j++) {
            ASSERT_NEAR((* result)(i,j), (* m2)(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix2) {
    * d1 = { 8, -5,  9,  2,
             7,  5,  6,  1,
            -6,  0,  9,  6,
            -3,  0, -9, -4};
    * d2 = {-0.15385, -0.15385, -0.282050, -0.53846,
            -0.07692,  0.12308,  0.02564,   0.03077,
             0.35897,  0.35897,  0.43590,   0.92308,
            -0.69231, -0.69231, -0.76923,  -1.92308};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    * m2 = inverse(* m1);
    * result = raytracer::Matrix(4, 4);
    result->setMatrixData(* d2);

    for (int i = 0; i < m1->getRowSize(); i++) {
        for (int j = 0; j < m1->getColSize(); j++) {
            ASSERT_NEAR((* result)(i,j), (* m2)(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix3) {
    * d1 = {9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2};
    * d2 = {-0.04074, -0.07778, 0.144444, -0.222222,
            -0.07778, 0.03333, 0.36667, -0.33333,
            -0.02901, -0.14630, -0.10926, 0.12963,
            0.17778, 0.06667, -0.26667, 0.33333};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    * m2 = inverse(* m1);
    * result = raytracer::Matrix(4, 4);
    result->setMatrixData(* d2);
    for (int i = 0; i < m1->getRowSize(); i++) {
        for (int j = 0; j < m1->getColSize(); j++) {
            ASSERT_NEAR((* result)(i,j), (* m2)(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix4) {
    * d1 = {3, -9, 7, 3,
            3, -8, 2, -9,
            -4, 4, 4, 1,
            -6, 5, -1, 1};
    * d2 = {8, 2, 2, 2,
            3, -1, 7, 0,
            7, 0, 5, 4,
            6, -2, 0, 5};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* d1);
    * m2 = raytracer::Matrix(4, 4);
    m2->setMatrixData(* d2);
    ASSERT_EQ(* m1, * m1 * * m2 * inverse(* m2));
}

TEST_F(MatrixFixture, IdentityMatrix) {
    * data = {1, 0, 0, 0,
              0, 1, 0, 0,
              0, 0, 1, 0,
              0, 0, 0, 1};
    * m1 = raytracer::Matrix(4, 4);
    m1->setMatrixData(* data);
    ASSERT_EQ(* m1, raytracer::generateIdentity(4, 4));
}

