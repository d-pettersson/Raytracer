#include "matrix.h"

#include "gtest/gtest.h"

class MatrixFixture : public ::testing::Test {

protected:
    virtual void SetUp()
    {
        matrix = new raytracer::Matrix();
    }

    virtual void TearDown() {
        delete matrix;
    }

    raytracer::Matrix * matrix;
    raytracer::Matrix m1;
    raytracer::Matrix m2;
    raytracer::Matrix identity;
    raytracer::Matrix resultMatrix;
};

TEST_F(MatrixFixture, Test4x4Matrix) {
    raytracer::Matrix matrix = raytracer::Matrix(4, 4);
    std::vector<double> data = {1,     2,    3,      4,
                                5.5, 6.5,  7.5,    8.5,
                                9,    10,   11,     12,
                                13.5, 14.5, 15.5, 16.5};
    matrix.setMatrixData(data);
    ASSERT_EQ(1, matrix(0, 0));
    ASSERT_EQ(4, matrix(0, 3));
    ASSERT_EQ(5.5, matrix(1, 0));
    ASSERT_EQ(7.5, matrix(1, 2));
    ASSERT_EQ(11, matrix(2, 2));
    ASSERT_EQ(13.5, matrix(3, 0));
    ASSERT_EQ(15.5, matrix(3, 2));
}

TEST_F(MatrixFixture, Test2x2Matrix) {
    raytracer::Matrix matrix = raytracer::Matrix(2, 2);
    std::vector<double> data = {-3, 5, 1, -2};
    matrix.setMatrixData(data);
    ASSERT_EQ(-3, matrix(0, 0));
    ASSERT_EQ(5, matrix(0, 1));
    ASSERT_EQ(1, matrix(1, 0));
    ASSERT_EQ(-2, matrix(1, 1));
}

TEST_F(MatrixFixture, Test3x3Matrix) {
    raytracer::Matrix matrix = raytracer::Matrix(3, 3);
    std::vector<double> data = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.setMatrixData(data);
    ASSERT_EQ(-3, matrix(0, 0));
    ASSERT_EQ(-2, matrix(1, 1));
    ASSERT_EQ(1, matrix(2, 2));
}

TEST_F(MatrixFixture, TestEquality) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 8, 7, 6,
                     5, 4, 3, 2};
    m1.setMatrixData(data);
    m2.setMatrixData(data);
    ASSERT_TRUE(m1.isEqual(m2));
}

TEST_F(MatrixFixture, TestFalseEquality) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 8, 7, 6,
                      5, 4, 3, 2};
    std::vector<double> data2 = {2, 3, 4, 5,
                      6, 7, 8, 9,
                      8, 7, 6, 5,
                      4, 3, 2, 1};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    ASSERT_FALSE(m1.isEqual(m2));
}

// verifies that the rest of the matrix is also readable

TEST_F(MatrixFixture, TestFalseEquality2) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 8, 7, 6,
                      5, 4, 3, 2};
    std::vector<double> data2 = {1, 2, 3, 4,
                      6, 7, 8, 9,
                      8, 7, 6, 5,
                      4, 3, 2, 1};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    ASSERT_FALSE(m1.isEqual(m2));
}

TEST_F(MatrixFixture, TestEmptyOperator) {
    m1 = raytracer::Matrix(4, 4);
    std::vector<double> data = {0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0};
    m1.setMatrixData(data);
    ASSERT_TRUE(m1.isEmpty());
}

TEST_F(MatrixFixture, TestEqualityOperator) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data = {1, 2, 3, 4,
                     5, 6, 7, 8,
                     9, 8, 7, 6,
                     5, 4, 3, 2};
    m1.setMatrixData(data);
    m2.setMatrixData(data);
    ASSERT_EQ(m1, m2);
}

TEST_F(MatrixFixture, TestFalseEqualityOperator) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 8, 7, 6,
                      5, 4, 3, 2};
    std::vector<double> data2 = {2, 3, 4, 5,
                      6, 7, 8, 9,
                      8, 7, 6, 5,
                      4, 3, 2, 1};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    ASSERT_NE(m1, m2);
}

TEST_F(MatrixFixture, TestRowSize) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    std::vector<double> data1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 8, 7, 6,
                      5, 4, 3, 2};
    m1.setMatrixData(data1);
}

TEST_F(MatrixFixture, Test4x4MatrixMultiplication) {
    std::vector<double> data1 = {1, 2, 3, 4,
                      5, 6, 7, 8,
                      9, 8, 7, 6,
                      5, 4, 3, 2};
    std::vector<double> data2 = {-2, 1, 2,  3,
                      3, 2, 1, -1,
                      4, 3, 6,  5,
                      1, 2, 7,  8};
    std::vector<double> result = {20, 22,  50,  48,
                       44, 54, 114, 108,
                       40, 58, 110, 102,
                       16, 26,  46,  42};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    m2 = raytracer::Matrix(4, 4);
    m2.setMatrixData(data2);
    resultMatrix = raytracer::Matrix(4, 4);
    resultMatrix.setMatrixData(result);
    ASSERT_EQ(resultMatrix, m1 * m2);
}

TEST_F(MatrixFixture, TestMatrixTupleMultiplication) {
    std::vector<double> data1 = {1, 2, 3, 4,
                                 2, 4, 4, 2,
                                 8, 6, 4, 1,
                                 0, 0, 0, 1};
    raytracer::Tuple tuple = {1, 2, 3,  1};
    raytracer::Tuple result = {18, 24,  33,  1};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    ASSERT_EQ(result, m1 * tuple);
}

TEST_F(MatrixFixture, TestIdentityMatrixMultiplication) {
    std::vector<double> data1 = {0, 1, 2, 4,
                                 1, 2, 4, 8,
                                 2, 4, 8, 16,
                                 4, 8, 16, 32};
    std::vector<double> identityData = {1, 0, 0, 0,
                                        0, 1, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 1};
    raytracer::Tuple tuple = {1, 2, 3,  4};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    identity = raytracer::Matrix(4, 4);
    identity.setMatrixData(identityData);
    ASSERT_EQ(m1, m1 * identity);
    ASSERT_EQ(tuple, identity * tuple);
}

TEST_F(MatrixFixture, TransposingMatrix) {
    std::vector<double> data1 = {0, 9, 3, 0,
                                 9, 8, 0, 8,
                                 1, 8, 5, 3,
                                 0, 0, 5, 8};
    std::vector<double> transposed = {0, 9, 1, 0,
                                      9, 8, 8, 0,
                                      3, 0, 5, 5,
                                      0, 8, 3, 8};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    m2 = raytracer::Matrix(4, 4);
    m2.setMatrixData(transposed);
    resultMatrix = raytracer::Matrix(4, 4);
    resultMatrix = transpose(m1);
    ASSERT_EQ(resultMatrix, m2);
}

TEST_F(MatrixFixture, DeterminantMatrix) {
    std::vector<double> data1 = {1, 5,
                                 -3, 2};
    m1 = raytracer::Matrix(2, 2);
    m1.setMatrixData(data1);
    double det = raytracer::determinant(m1);
    double result = 17.0;
    ASSERT_EQ(result, det);
}

TEST_F(MatrixFixture, Submatrix1) {
    std::vector<double> data1 = {1, 5, 0,
                                 -3, 2, 7,
                                 0, 6, -3};
    std::vector<double> data2 = {-3, 2,
                                  0, 6};
    m1 = raytracer::Matrix(3, 3);
    m1.setMatrixData(data1);
    m2 = raytracer::Matrix(2, 2);
    m2.setMatrixData(data2);
    raytracer::Matrix sub = submatrix(m1, 0, 2);
    ASSERT_EQ(m2, sub);
}

TEST_F(MatrixFixture, Submatrix2) {
    std::vector<double> data1 = {-6, 1, 1, 6,
                                 -8, 5, 8, 6,
                                 -1, 0, 8, 2,
                                 -7, 1, -1, 1};
    std::vector<double> data2 = {-6, 1, 6,
                                 -8, 8, 6,
                                 -7, -1, 1};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    m2 = raytracer::Matrix(3, 3);
    m2.setMatrixData(data2);
    raytracer::Matrix sub = submatrix(m1, 2, 1);
    ASSERT_EQ(m2, sub);
}

TEST_F(MatrixFixture, MinorMatrix) {
    std::vector<double> data1 = {3, 5, 0,
                                 2, -1, -7,
                                 6, -1, 5};
    m1 = raytracer::Matrix(3, 3);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(2, 2);
    m2 = submatrix(m1, 1, 0);

    double det = determinant(m2);
    double min = minor(m1, 1, 0);
    double result = 25.0;

    ASSERT_EQ(result, det);
    ASSERT_EQ(result, min);
}

TEST_F(MatrixFixture, CofactorMatrix) {
    std::vector<double> data1 = {3, 5, 0,
                                 2, -1, -7,
                                 6, -1, 5};
    m1 = raytracer::Matrix(3, 3);
    m1.setMatrixData(data1);

    double min1 = minor(m1, 0, 0);
    double result1 = -12.0;
    double cofactor1 = cofactor(m1, 0, 0);

    double min2 = minor(m1, 1, 0);
    double resultMin2 = 25;
    double cofactor2 = cofactor(m1, 1, 0);
    double resultCofactor2 = -25;

    ASSERT_EQ(result1, min1);
    ASSERT_EQ(result1, cofactor1);
    ASSERT_EQ(resultMin2, min2);
    ASSERT_EQ(resultCofactor2, cofactor2);
}

TEST_F(MatrixFixture, DeterminantMatrix3x3) {
    std::vector<double> data1 = {1, 2, 6,
                                 -5, 8, -4,
                                 2, 6, 4};
    m1 = raytracer::Matrix(3, 3);
    m1.setMatrixData(data1);
    double cofactor1 = cofactor(m1, 0, 0);
    double result1 = 56;

    double cofactor2 = cofactor(m1, 0, 1);
    double result2 = 12;

    double cofactor3 = cofactor(m1, 0, 2);
    double result3 = -46;

    double det = determinant(m1);
    double result4 = -196;

    ASSERT_EQ(result1, cofactor1);
    ASSERT_EQ(result2, cofactor2);
    ASSERT_EQ(result3, cofactor3);
    ASSERT_EQ(result4, det);
}

TEST_F(MatrixFixture, DeterminantMatrix4x4) {
    std::vector<double> data1 = {-2, -8, 3, 5,
                                 -3, 1, 7, 3,
                                 1, 2, -9, 6,
                                 -6, 7, 7, -9};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);
    double cofactor1 = cofactor(m1, 0, 0);
    double result1 = 690;

    double cofactor2 = cofactor(m1, 0, 1);
    double result2 = 447;

    double cofactor3 = cofactor(m1, 0, 2);
    double result3 = 210;

    double cofactor4 = cofactor(m1, 0, 3);
    double result4 = 51;

    double det = determinant(m1);
    double result5 = -4071;

    ASSERT_EQ(result1, cofactor1);
    ASSERT_EQ(result2, cofactor2);
    ASSERT_EQ(result3, cofactor3);
    ASSERT_EQ(result4, cofactor4);
    ASSERT_EQ(result5, det);

}

TEST_F(MatrixFixture, TestInvertibletMatrix) {
    std::vector<double> data1 = {6, 4, 4, 4,
                                 5, 5, 7, 6,
                                 4, -9, 3, -7,
                                 9, 1, 7, -6};
    std::vector<double> data2 = {-4, 2, -2, -3,
                                 9, 6, 2, 6,
                                 0, -5, 1, -5,
                                 0, 0, 0, 0};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(4, 4);
    m2.setMatrixData(data2);

    double det1 = determinant(m1);
    double result1 = -2120;

    double det2 = determinant(m2);
    double result2 = 0;

    ASSERT_EQ(result1, det1);
    ASSERT_EQ(result2, det2);
}

TEST_F(MatrixFixture, InvertMatrix1) {
    std::vector<double> data1 = {-5, 2, 6, -8,
                                 1, -5, 1, 8,
                                 7, 7, -6, -7,
                                 1, -3, 7, 4};
    std::vector<double> result = {0.21805, 0.45113, 0.24060, -0.04511,
                                 -0.80827, -1.4577, -0.44361, 0.52068,
                                 -0.07895, -0.22368, -0.05263, 0.19737,
                                 -0.52256, -0.81391, -0.30075, 0.30639};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(4, 4);
    m2 = inverse(m1);

    raytracer::Matrix resultMat = raytracer::Matrix(4, 4);
    resultMat.setMatrixData(result);

    double det = determinant(m1);
    double detResult = 532;

    double cofactor1 = cofactor(m1, 2, 3);
    double result1 = -160;

    double d1 = m2(3, 2);
    double dResult1 = -160.0/532.0;

    double cofactor2 = cofactor(m1, 3, 2);
    double result2 = 105;

    double d2 = m2(2, 3);
    double dResult2 = 105.0/532.0;

    EXPECT_EQ(detResult, det);
    EXPECT_EQ(result1, cofactor1);
    EXPECT_DOUBLE_EQ(dResult1, d1);
    EXPECT_EQ(result2, cofactor2);
    EXPECT_DOUBLE_EQ(dResult2, d2);
    for (int i = 0; i < m1.getRowSize(); i++) {
        for (int j = 0; j < m1.getColSize(); j++) {
            ASSERT_NEAR(resultMat(i,j), m2(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix2) {
    std::vector<double> data1 = {8, -5, 9, 2,
                                 7, 5, 6, 1,
                                 -6, 0, 9, 6,
                                 -3, 0, -9, -4};
    std::vector<double> result = {-0.15385, -0.15385, -0.282050, -0.53846,
                                  -0.07692, 0.12308, 0.02564, 0.03077,
                                  0.35897, 0.35897, 0.43590, 0.92308,
                                  -0.69231, -0.69231, -0.76923, -1.92308};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(4, 4);
    m2 = inverse(m1);

    raytracer::Matrix resultMat = raytracer::Matrix(4, 4);
    resultMat.setMatrixData(result);

    for (int i = 0; i < m1.getRowSize(); i++) {
        for (int j = 0; j < m1.getColSize(); j++) {
            ASSERT_NEAR(resultMat(i,j), m2(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix3) {
    std::vector<double> data1 = {9, 3, 0, 9,
                                 -5, -2, -6, -3,
                                 -4, 9, 6, 4,
                                 -7, 6, 6, 2};
    std::vector<double> result = {-0.04074, -0.07778, 0.144444, -0.222222,
                                  -0.07778, 0.03333, 0.36667, -0.33333,
                                  -0.02901, -0.14630, -0.10926, 0.12963,
                                  0.17778, 0.06667, -0.26667, 0.33333};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(4, 4);
    m2 = inverse(m1);

    raytracer::Matrix resultMat = raytracer::Matrix(4, 4);
    resultMat.setMatrixData(result);

    for (int i = 0; i < m1.getRowSize(); i++) {
        for (int j = 0; j < m1.getColSize(); j++) {
            ASSERT_NEAR(resultMat(i,j), m2(i,j), 0.001);
        }
    }
}

TEST_F(MatrixFixture, InvertMatrix4) {
    std::vector<double> data1 = {3, -9, 7, 3,
                                 3, -8, 2, -9,
                                 -4, 4, 4, 1,
                                 -6, 5, -1, 1};
    std::vector<double> data2 = {8, 2, 2, 2,
                                 3, -1, 7, 0,
                                 7, 0, 5, 4,
                                 6, -2, 0, 5};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::Matrix(4, 4);
    m2.setMatrixData(data2);

    raytracer::Matrix resultMat = raytracer::Matrix(4, 4);
    resultMat = m1 * m2;
    ASSERT_EQ(m1, resultMat * inverse(m2));
}

TEST_F(MatrixFixture, IdentityMatrix) {
    std::vector<double> data1 = {1, 0, 0, 0,
                                 0, 1, 0, 0,
                                 0, 0, 1, 0,
                                 0, 0, 0, 1};
    m1 = raytracer::Matrix(4, 4);
    m1.setMatrixData(data1);

    m2 = raytracer::generateIdentity(4, 4);
}

