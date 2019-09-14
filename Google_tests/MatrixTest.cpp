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
    std::cout << m1;
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
    std::cout << identity * tuple;
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
    resultMatrix = m1.transpose();
    ASSERT_EQ(resultMatrix, m2);
}

TEST_F(MatrixFixture, DeterminantMatrix) {
    std::vector<double> data1 = {1, 5,
                                 -3, 2};
    m1 = raytracer::Matrix(2, 2);
    m1.setMatrixData(data1);
    double determinant = 17.0;
    ASSERT_EQ(determinant, raytracer::determinant(m1));
}

TEST_F(MatrixFixture, Submatrix1) {
    std::vector<double> data1 = {1, 5, 0,
                                 -3, 2, 7,
                                 0, 6, 3};
    std::vector<double> data2 = {-3, 2,
                                  0, 6};
    m1 = raytracer::Matrix(3, 3);
    m1.setMatrixData(data1);
    m2 = raytracer::Matrix(2, 2);
    m2.setMatrixData(data2);
//    std::cout << m1 << '\n' << submatrix(m1, 0, 2);
    ASSERT_EQ(m2, submatrix(m1, 0, 2));
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
    ASSERT_EQ(m2, submatrix(m1, 2, 1));
}