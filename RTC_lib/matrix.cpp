#include "matrix.h"

#include <iostream>
#include <utility>

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

Matrix Matrix::transpose() const {
    Matrix output(rows, cols);
    for (int i = 0; i < this->getRowSize(); i++) {
        for (int j = 0; j < this->getColSize(); j++) {
            output(i, j) = matrixData[rows * j + i];
        }
    }
    return output;
}

double& Matrix::operator()(size_t row, size_t col) {
    return matrixData[cols * row + col];
}

double Matrix::operator()(size_t row, size_t col) const {
    return matrixData[cols * row + col];
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

double determinant(const Matrix& m1) {
    return m1(0, 0) * m1(1, 1) - m1(0, 1) * m1(1, 0);
}

Matrix submatrix(const Matrix& m1, const int& r, const int& c) {
    Matrix output = Matrix(m1.getRowSize() - 1, m1.getColSize() - 1);
    std::vector<double> data2 = {0, 0,
                                 0, 0};
    output.setMatrixData(data2);
    return output;
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