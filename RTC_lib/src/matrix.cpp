#include "include/matrix.h"

#include <iostream>
#include <cmath>
#include <omp.h>
#include <algorithm>

namespace raytracer {

Matrix::Matrix(size_t r, size_t c)
    : rows_(r), cols_(c), data_(r * c)
{
}

Matrix::Matrix()
    : rows_(0), cols_(0)
{
}

Matrix::Matrix(const Matrix &copy)
    : rows_(copy.rows_), cols_(copy.cols_), data_(copy.data_)
{
}

int Matrix::getMatrixSize() const {
    return data_.size();
}

int Matrix::getRowSize() const {
    return rows_;
}

int Matrix::getColSize() const {
    return cols_;
}

std::vector<double> Matrix::getMatrixData() const {
    return data_;
}

void Matrix::setMatrixData(const std::vector<double> &data) {
    data_ = data;
}

bool Matrix::isEqual(const Matrix &m) const {
    for(size_t i = 0; i < data_.size(); ++i) {
        if(fabs(data_[i] - m.data_[i]) > EPSILON) {
            return false;
        }
    }
    return true;
}

bool Matrix::isEmpty() const {
    return std::all_of(data_.begin(), data_.end(), [](double d) { return d == 0.0; });
}

double& Matrix::operator()(size_t row, size_t col) {
    return data_[cols_ * row + col];
}

double Matrix::operator()(size_t row, size_t col) const {
    return data_[cols_ * row + col];
}

double& Matrix::operator[](size_t index) {
    return data_[index];
}

double Matrix::operator[](size_t index) const {
    return data_[index];
}

Matrix Matrix::operator*(const Matrix& m) {
    Matrix output(rows_, cols_);
    for (int i = 0; i < this->getRowSize(); i++) {
        for (int j = 0; j < this->getColSize(); j++) {
            output(i, j) = data_[cols_ * i] * m(0, j) +
                           data_[cols_ * i + 1] * m(1, j) +
                           data_[cols_ * i + 2] * m(2, j) +
                           data_[cols_ * i + 3] * m(3, j);
        }
    }
    return output;
}

Tuple Matrix::operator*(const raytracer::Tuple& t) {
    Tuple output;
    for (int i = 0; i < this->getRowSize(); i++) {
        output(i) = data_[cols_ * i] * t.x +
                    data_[cols_ * i + 1] * t.y +
                    data_[cols_ * i + 2] * t.z +
                    data_[cols_ * i + 3] * t.w;
    }
    return output;
}

Matrix& Matrix::operator=(const Matrix& m) = default;

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
    double output = 0.0;
    if (m1.getRowSize() <= 2) {
        output = m1(0, 0) * m1(1, 1) - m1(0, 1) * m1(1, 0);
    } else {
        for (int i = 0; i < m1.getRowSize(); i++) {
             output += m1(0, i) * cofactor(m1, 0, i);
        }
    }
    return output;
}

Matrix submatrix(const Matrix &m, const int &r, const int &c) {
    Matrix output(m.getRowSize() - 1, m.getColSize() - 1);
    for (int i = 0; i < output.getRowSize(); ++i) {
        int ni = i >= r ? i + 1 : i;
        for (int j = 0; j < output.getColSize(); ++j) {
            int nj = j >= c ? j + 1 : j;
            output(i, j) = m(ni, nj);
        }
    }
    return output;
}

double minor(const Matrix &m, const int& r, const int& c) {
    auto output = submatrix(m, r, c);
    return determinant(output);
}

double cofactor(const Matrix &m, const int &r, const int &c) {
    auto output = minor(m, r, c);
    return (r + c) % 2 != 0 ? -output : output;
}

Matrix inverse(const Matrix &m) {
    Matrix output(m.getRowSize(), m.getColSize());
    double co, det = determinant(m);
    if (det != 0) {
        for (int i = 0; i < m.getRowSize(); i++) {
            for (int j = 0; j < m.getColSize(); j++) {
                co = cofactor(m, i, j);
                output(j, i) = co / det;
            }
        }
    }
    return output;
}

Matrix generateIdentity(const int &r, const int &c) {
    Matrix output(r, c);
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            i == j ? output(i, j) = 1.0 : output(i, j) = 0.0;
        }
    }
    return output;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1.getMatrixSize() != m2.getMatrixSize()) {
        std::cerr << "Matrices need to be the same size.";
    }
    return m1.isEqual(m2);
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !m1.isEqual(m2);
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