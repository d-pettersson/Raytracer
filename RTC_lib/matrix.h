/**
 * The <code>Matrix</code> class is the base data class for transformations.
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
         * Returns a <code>Matrix</code> object from the components
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
         * Return the data inside of <code>Matrix</code>
         *
         * @return std::vector<double>
         */
        std::vector<double> getMatrixData() const;

        /**
         * Sets the data inside of <code>Matrix</code>
         *
         * @param[in] std::vector<data>
         */
        void setMatrixData(const std::vector<double>& data);

        /**
         * Compares two <code>Matrix</code> for equality.
         *
         * @param[in] Matrix m1
         * @return bool
         */
        bool isEqual(const Matrix& m1) const;

        Matrix operator*(const Matrix& m);
        raytracer::Tuple operator*(const raytracer::Tuple& t);
        raytracer::Point operator*(const raytracer::Point& t);
        raytracer::Vector operator*(const raytracer::Vector& t);

        Matrix& operator=(const Matrix& m1);

        double& operator()(size_t row, size_t col);
        double operator()(size_t row, size_t col) const;

        double& operator[](size_t index);
        double operator[](size_t index) const;

private:
        size_t rows;
        size_t cols;
        std::vector<double> matrixData;
};

/**
 * Returns the transpose of <code>Matrix</code>
 *
 * @param[in] Matrix m1
 * @return Matrix
 */
Matrix transpose(const Matrix& m1);

/**
 * Returns the determinant of <code>Matrix</code>
 *
 * @param[in] Matrix m1
 * @return double
 */
double determinant(const Matrix& m1);

/**
 * Returns a submatrix of <code>Matrix</code>
 *
 * @param[in] Matrix m1
 * @param[in] int r
 * @param[in] int c
 * @return double
 */
Matrix submatrix(const Matrix& m1, const int& r, const int& c);

/**
 * Returns the minor of selected submatrix
 *
 * @param[in] Matrix m1
 * @param[in] int r
 * @param[in] int c
 * @return Matrix
 */
double minor(const Matrix& m1, const int& r, const int& c);

/**
 * Returns the cofactor of the selected submatrix
 *
 * @param[in] Matrix m1
 * @param[in] int r
 * @param[in] int c
 * @return double
 */
double cofactor(const Matrix& m1, const int& r, const int& c);

/**
 * Returns the inverse of the <code>Matrix</code>
 *
 * @param[in] Matrix m1
 * @return Matrix
 */
Matrix inverse(const Matrix& m1);

/**
 * Generates an identity <code>Matrix</code>
 *
 * @param[in] r
 * @param[in] c
 * @return Matrix
 */
Matrix generateIdentity(const int& r, const int& c);

bool operator==(const Matrix& m1, const Matrix& m2);
bool operator!=(const Matrix& m1, const Matrix& m2);

std::ostream& operator<<(std::ostream& os, const Matrix& m);


} // namespace raytracer



#endif //RTC_MATRIX_H
