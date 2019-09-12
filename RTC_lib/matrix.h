#include <vector>

#ifndef RTC_MATRIX_H
#define RTC_MATRIX_H

namespace raytracer {

class Matrix {
    public:
        Matrix(int rows, int cols);
        Matrix();

        double getMatrixData() const;
        int getMatrixSize() const;
        void setMatrixData(double data[]);
        bool isEqual(const Matrix& m1) const;

        double& operator()(int row, int col);
        double& operator()(int row, int col) const;


    private:
        int rows;
        int cols;
        double * matrixData;
};

bool operator==(const Matrix& m1, const Matrix& m2);
bool operator!=(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m1, const Matrix& m2);

} // namespace raytracer



#endif //RTC_MATRIX_H
