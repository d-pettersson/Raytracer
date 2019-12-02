/**
 * The <code>Matrix</code> class is the base class for transformations.
 *
 * @param[in] size_t r
 * @param[in] size_t c
 */

#ifndef RTC_MATRIX_H
#define RTC_MATRIX_H

#include "tuple.h"

#include <vector>

namespace raytracer {

class Matrix {
    public:
        /**
         * Create a <code>Matrix</code> object from the components
         *
         * @param[in] int rows
         * @param[in] int cols
         */
        Matrix(size_t rows, size_t cols);
        Matrix();

        Matrix(const Matrix &copy);

        /**
         * Return size of <code>Matrix</code>
         *
         * @return int
         */
        int getMatrixSize() const;

        /**
         * Return row size of <code>Matrix</code>
         *
         * @return int
         */
        int getRowSize() const;

        /**
        * Return col size of <code>Matrix</code>
        *
        * @return int
        */
        int getColSize() const;

        /**
         * Return data member of <code>Matrix</code>
         *
         * @return std::vector<double>
         */
        std::vector<double> getMatrixData() const;

        /**
         * Set data member of <code>Matrix</code>
         *
         * @param[in] const std::vector<double> &data
         */
        void setMatrixData(const std::vector<double> &data);

        /**
         * Compares two <code>Matrix</code> for equality.
         *
         * @param[in] const Matrix& m1
         * @return bool
         */
        bool isEqual(const Matrix &m) const;
        bool isEmpty() const;

        Matrix operator*(const Matrix &m);
        Tuple operator*(const raytracer::Tuple &t);

        Matrix& operator=(const Matrix &m);

        double& operator()(size_t row, size_t col);
        double operator()(size_t row, size_t col) const;

        double& operator[](size_t index);
        double operator[](size_t index) const;

private:
        size_t rows_;
        size_t cols_;
        std::vector<double> data_;
};

/**
 * Returns the transpose of <code>Matrix</code>
 *
 * @param[in] const Matrix& m1
 * @return Matrix
 */
Matrix transpose(const Matrix& m1);

/**
 * Returns the determinant of <code>Matrix</code>
 *
 * @param[in] const Matrix& m1
 * @return double
 */
double determinant(const Matrix& m1);

/**
 * Returns a submatrix of <code>Matrix</code>
 *
 * @param[in] const Matrix& m1
 * @param[in] const int& r
 * @param[in] const int& c
 * @return double
 */
Matrix submatrix(const Matrix& m, const int& r, const int& c);

/**
 * Returns the minor of selected submatrix
 *
 * @param[in] const Matrix& m1
 * @param[in] const int& r
 * @param[in] const int& c
 * @return Matrix
 */
double minor(const Matrix& m, const int& r, const int& c);

/**
 * Returns the cofactor of the selected submatrix
 *
 * @param[in] const Matrix& m1
 * @param[in] const int& r
 * @param[in] const int& c
 * @return double
 */
double cofactor(const Matrix& m, const int& r, const int& c);

/**
 * Returns the inverse of the <code>Matrix</code>
 *
 * @param[in] const Matrix& m1
 * @return Matrix
 */
Matrix inverse(const Matrix& m);

/**
 * Generates an identity <code>Matrix</code>
 *
 * @param[in] const int& r
 * @param[in] const int& c
 * @return Matrix
 */
Matrix generateIdentity(const int& r, const int& c);

bool operator==(const Matrix& m1, const Matrix& m2);
bool operator!=(const Matrix& m1, const Matrix& m2);

std::ostream& operator<<(std::ostream& os, const Matrix& m);

} // namespace raytracer



#endif //RTC_MATRIX_H
