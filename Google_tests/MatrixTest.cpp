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
    raytracer::Matrix resultMatrix;

};

TEST_F(MatrixFixture, Test4x4Matrix) {
    raytracer::Matrix matrix = raytracer::Matrix(4, 4);
    double data[] = {1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
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
    double data[] = {-3, 5, 1, -2};
    matrix.setMatrixData(data);
    ASSERT_EQ(-3, matrix(0, 0));
    ASSERT_EQ(5, matrix(0, 1));
    ASSERT_EQ(1, matrix(1, 0));
    ASSERT_EQ(-2, matrix(1, 1));
}

TEST_F(MatrixFixture, Test3x3Matrix) {
    raytracer::Matrix matrix = raytracer::Matrix(3, 3);
    double data[] = {-3, 5, 0, 1, -2, -7, 0, 1, 1};
    matrix.setMatrixData(data);
    ASSERT_EQ(-3, matrix(0, 0));
    ASSERT_EQ(-2, matrix(1, 1));
    ASSERT_EQ(1, matrix(2, 2));
}

TEST_F(MatrixFixture, TestEquality) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    m1.setMatrixData(data);
    m2.setMatrixData(data);
    ASSERT_TRUE(m1.isEqual(m2));
}

TEST_F(MatrixFixture, TestFalseEquality) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    double data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    double data2[] = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    ASSERT_FALSE(m1.isEqual(m2));
}

TEST_F(MatrixFixture, TestEqualityOperator) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    m1.setMatrixData(data);
    m2.setMatrixData(data);
    ASSERT_EQ(m1, m2);
}

TEST_F(MatrixFixture, TestFalseEqualityOperator) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    double data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    double data2[] = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    ASSERT_NE(m1, m2);
}

TEST_F(MatrixFixture, Test4x4MatrixMultiplication) {
    m1 = raytracer::Matrix(4, 4);
    m2 = raytracer::Matrix(4, 4);
    resultMatrix = raytracer::Matrix(4, 4);
    double data1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
    double data2[] = {-2, 1, 2, 3, 3, 2, 1, -1, 4, 3, 6, 5, 1, 2, 7, 8};
    double result[] = {20, 22, 50, 48, 44, 54, 114, 108, 40, 58, 110, 102, 16, 26, 46, 42};
    m1.setMatrixData(data1);
    m2.setMatrixData(data2);
    resultMatrix.setMatrixData(result);
    ASSERT_EQ(resultMatrix, m1 * m2);
}