#include "tuple.h"

#include <vector>

#ifndef RTC_MATRIX_H
#define RTC_MATRIX_H

namespace raytracer {

class Matrix {
    public:
        Matrix(size_t rows, size_t cols);
        Matrix();

        Matrix(const Matrix &copy);

        int getMatrixSize() const;
        int getRowSize() const;
        int getColSize() const;
        std::vector<double> getMatrixData() const;
        void setMatrixData(const std::vector<double>& data);
        bool isEqual(const Matrix& m1) const;

        Matrix transpose() const;

        Matrix operator*(const Matrix& m);
        raytracer::Tuple operator*(const raytracer::Tuple& t);

        double& operator()(size_t row, size_t col);
        double operator()(size_t row, size_t col) const;


private:
        size_t rows;
        size_t cols;
        std::vector<double> matrixData;

};

double determinant(const Matrix& m1);
Matrix submatrix(const Matrix& m1, const int& r, const int& c);

bool operator==(const Matrix& m1, const Matrix& m2);
bool operator!=(const Matrix& m1, const Matrix& m2);
std::ostream& operator<<(std::ostream& os, const Matrix& m);


} // namespace raytracer



#endif //RTC_MATRIX_H
