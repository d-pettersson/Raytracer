#include "matrix.h"

#include <iostream>
#include <utility>
#include <cmath>

namespace raytracer {

Matrix::Matrix(size_t r, size_t c)
    :rows{r}, cols{c}, matrixData(r*c)
{
}

Matrix::Matrix()
    :rows{0}, cols{0}
{
}

Matrix::Matrix(const Matrix &copy)
    :rows{copy.rows}, cols{copy.cols}, matrixData{copy.matrixData}
{

}

int Matrix::getMatrixSize() const {
    return matrixData.size();
}

int Matrix::getRowSize() const {
    return rows;
}

int Matrix::getColSize() const {
    return cols;
}

std::vector<double> Matrix::getMatrixData() const {
    return matrixData;
}

void Matrix::setMatrixData(const std::vector<double>& data) {
    matrixData = data;
}

bool Matrix::isEqual(const Matrix& m2) const {
    for (int i = 0; i < this->getRowSize(); i++) {
        for (int j = 0; j < this->getColSize(); j++) {
            if (matrixData[cols * i + j] != m2(i, j))
                return false;
        };
    }
    return true;
}

double& Matrix::operator()(size_t row, size_t col) {
    return matrixData[cols * row + col];
}

double Matrix::operator()(size_t row, size_t col) const {
    return matrixData[cols * row + col];
}

double& Matrix::operator[](size_t index) {
    return matrixData[index];
}

double Matrix::operator[](size_t index) const {
    return matrixData[index];
}

Matrix Matrix::operator*(const Matrix& m) {
    Matrix output = Matrix(rows, cols);
    for (int i = 0; i < this->getRowSize(); i++) {
        for (int j = 0; j < this->getColSize(); j++) {
            output(i, j) = matrixData[cols * i] * m(0, j) +
                           matrixData[cols * i + 1] * m(1, j) +
                           matrixData[cols * i + 2] * m(2, j) +
                           matrixData[cols * i + 3] * m(3, j);
        }
    }
    return output;
}

raytracer::Tuple Matrix::operator*(const raytracer::Tuple& t) {
    raytracer::Tuple output = Tuple();
    for (int i = 0; i < this->getRowSize(); i++) {
        output(i) = matrixData[cols * i] * t.x +
                    matrixData[cols * i + 1] * t.y +
                    matrixData[cols * i + 2] * t.z +
                    matrixData[cols * i + 3] * t.w;
    }
    return output;
}

Matrix transpose(const Matrix& m1) {
    Matrix output(m1.getRowSize(), m1.getColSize());
    for (int i = 0; i < m1.getRowSize(); i++) {
        for (int j = 0; j < m1.getColSize(); j++) {
            output(i, j) = m1[m1.getRowSize() * j + i];
        }
    }
    return output;
}

double determinant(const Matrix& m1) {
    return m1(0, 0) * m1(1, 1) - m1(0, 1) * m1(1, 0);
}

Matrix submatrix(const Matrix& m1, const int& r, const int& c) {
    Matrix output = Matrix(m1.getRowSize() - 1, m1.getColSize() - 1);
    for (int i = 0; i < output.getRowSize(); ++i) {
        size_t ni = i >= r ? i + 1 : i;
        for (int j = 0; j < output.getColSize(); ++j) {
            size_t nj = j >= c ? j + 1 : j;
            output(i, j) = m1(ni, nj);
        }
    }
    return output;
}

double minor(const Matrix& m1, const int& r, const int& c) {
    Matrix output = submatrix(m1, r, c);
    return determinant(output);
}

double cofactor(const Matrix& m1, const int& r, const int& c) {
    double output = minor(m1, r, c);
    return (r + c) % 2 != 0 ? -output : output;
};

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

std::ostream& operator<<(std::ostream &os, const Matrix& m1) {
    for (int i = 0; i < m1.getRowSize(); i++) {
        for (int j = 0; j < m1.getRowSize(); j++) {
            os << m1(i, j) << " ";
        }
        os << '\n';
    }
    return os;
}

} // namespace raytracer