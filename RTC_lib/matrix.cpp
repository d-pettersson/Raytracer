#include "matrix.h"

#include <iostream>

namespace raytracer {

Matrix::Matrix(int r, int c)
    :rows{r}, cols{c}
{
    matrixData = new double[r * c];
}

Matrix::Matrix()
    :rows{0}, cols{0}
{
}

double Matrix::getMatrixData() const {
    return * matrixData;
}

int Matrix::getMatrixSize() const {
    return cols * rows;
}

void Matrix::setMatrixData(double data[]) {
    matrixData = data;
}

bool Matrix::isEqual(const Matrix& m2) const {
    for (int i = 0; i < this->getMatrixSize(); i++) {
        for (int j = 0; j < m2.getMatrixSize(); j++) {
            return matrixData[cols * i + j] == m2(i, j);
        }
    }
    return false;
}

double& Matrix::operator()(int row, int col) {
    return matrixData[cols * row + col];
}

double& Matrix::operator()(int row, int col) const {
    return matrixData[cols * row + col];
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.getMatrixSize() != m2.getMatrixSize()) {
        std::cerr << "Matrices need to be the same size.";
    } else {
        return m1.isEqual(m2);
    }
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    if (m1.getMatrixSize() != m2.getMatrixSize()) {
        std::cerr << "Matrices need to be the same size.";
    } else {
        return !m1.isEqual(m2);
    }
}

Matrix operator*(const Matrix& m1, const Matrix& m2) {
    for (int i = 0; i < this->getMatrixSize(); i++) {
        for (int j = 0; j < m2.getMatrixSize(); j++) {

        }
}

} // namespace raytracer