#include "matrix.h"

namespace task {

    Vector::Vector() {
        size = 1;
        arr = new double[size];
        arr[0] = 1.0;
    }

    Vector::Vector(const size_t size) {
        this->size = size;
        arr = new double[size];

        for (size_t i = 0; i < size; ++i) {
            arr[i] = 0.0;
        }
    }

    Vector::Vector(const Vector& copy) {
        size = copy.length();
        arr = new double[size];

        for (size_t i = 0; i < size; ++i) {
            arr[i] = copy[i];
        }
    }

    size_t Vector::length() const {
        return size;
    }

    double& Vector::operator[](size_t ind) {
        if (ind >= size) {
            throw OutOfBoundsException();
        }

        return arr[ind];
    }

    const double& Vector::operator[](size_t ind) const {
        if (ind >= size) {
            throw OutOfBoundsException();
        }

        return arr[ind];
    }

    Vector& Vector::operator=(const Vector& a) {
        if (&a == this) {
            return *this;
        }

        size = a.length();
        delete[] arr;
        arr = new double[size];

        for (size_t i = 0; i < size; ++i) {
            arr[i] = a[i];
        }

        return *this;
    }

    Vector::~Vector() {
        delete[] arr;
    }

    Matrix::Matrix() {
        h = 1;
        w = 1;
        rows = new Vector[h];
    }

    Matrix::Matrix(size_t rows, size_t cols) {
        h = rows;
        w = cols;
        this->rows = new Vector[h];

        for (size_t i = 0; i < h; ++i) {
            this->rows[i] = Vector(w);

            if (i < cols) {
                this->rows[i][i] = 1.0;
            }
        }
    }

    Matrix::Matrix(const Matrix& copy) {
        h = copy.get_h();
        w = copy.get_w();
        rows = new Vector[h];

        for (size_t i = 0; i < h; ++i) {
            rows[i] = Vector(copy[i]);
        }
    }

    Matrix& Matrix::operator=(const Matrix& a) {
        if (&a == this) {
            return *this;
        }

        h = a.get_h();
        w = a.get_w();

        delete[] rows;
        rows = new Vector[h];

        for (size_t i = 0; i < h; ++i) {
            rows[i] = Vector(a[i]);
        }

        return *this;
    }

    double& Matrix::get(size_t row, size_t col) {
        if (row >= h || col >= w) {
            throw OutOfBoundsException();
        }

        return rows[row][col];
    }

    const double& Matrix::get(size_t row, size_t col) const {
        if (row >= h || col >= w) {
            throw OutOfBoundsException();
        }

        return rows[row][col];
    }

    void Matrix::set(size_t row, size_t col, const double& value) {
        if (row >= h || col >= w) {
            throw OutOfBoundsException();
        }

        rows[row][col] = value;
    }

    void Matrix::resize(size_t new_rows, size_t new_cols) {
        auto new_data = new Vector[new_rows];

        for (size_t i = 0; i < new_rows; ++i) {
            new_data[i] = Vector(new_cols);
        }

        for (size_t i = 0; i < std::min(h, new_rows); ++i) {
            for (size_t j = 0; j < std::min(w, new_cols); ++j) {
                new_data[i][j] = rows[i][j];
            }
        }

        h = new_rows;
        w = new_cols;

        delete[] rows;
        rows = new_data;
    }

    Vector& Matrix::operator[](size_t row) {
        if (row >= h) {
            throw OutOfBoundsException();
        }

        return rows[row];
    }

    const Vector& Matrix::operator[](size_t row) const {
        if (row >= h) {
            throw OutOfBoundsException();
        }

        return rows[row];
    }

    Matrix& Matrix::operator+=(const Matrix& a) {
        if (h != a.get_h() || w != a.get_w()) {
            throw SizeMismatchException();
        }

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                rows[i][j] += a[i][j];
            }
        }

        return *this;
    }

    Matrix& Matrix::operator-=(const Matrix& a) {
        if (h != a.get_h() || w != a.get_w()) {
            throw SizeMismatchException();
        }

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                rows[i][j] -= a[i][j];
            }
        }

        return *this;
    }

    Matrix& Matrix::operator*=(const Matrix& a) {
        if (w != a.get_h()) {
            throw SizeMismatchException();
        }

        size_t result_h = h;
        size_t inner_dim = w;
        size_t result_w = a.get_w();

        Matrix result(result_h, result_w);

        for (size_t i = 0; i < result_h; ++i) {
            for (size_t j = 0; j < result_w; ++j) {
                result[i][j] = 0;
                for (size_t k = 0; k < inner_dim; ++k) {
                    result[i][j] += rows[i][k] * a[k][j];
                }
            }
        }

        *this = result;

        return *this;
    }

    Matrix& Matrix::operator*=(const double& number) {
        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                rows[i][j] *= number;
            }
        }

        return *this;
    }

    Matrix Matrix::operator+(const Matrix& a) const {
        if (h != a.get_h() || w != a.get_w()) {
            throw SizeMismatchException();
        }

        auto result = Matrix(*this);
        result += a;

        return result;
    }


    Matrix Matrix::operator-(const Matrix& a) const {
        if (h != a.get_h() || w != a.get_w()) {
            throw SizeMismatchException();
        }

        auto result = Matrix(*this);
        result -= a;

        return result;
    }

    Matrix Matrix::operator*(const Matrix& a) const {
        if (w != a.get_h()) {
            throw SizeMismatchException();
        }

        auto result = Matrix(*this);
        result *= a;

        return result;
    }

    Matrix Matrix::operator*(const double& a) const {
        auto result = Matrix(*this);
        result *= a;

        return result;
    }

    Matrix Matrix::operator-() const {
        Matrix result(h, w);

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                result[i][j] = -rows[i][j];
            }
        }

        return result;
    }

    Matrix Matrix::operator+() const {
        return Matrix(*this);
    }

    double Matrix::det() const {
        if (h != w) {
            throw SizeMismatchException();
        }

        return rec_det(*this);
    }

    void Matrix::transpose() {
        *this = transposed();
    }

    Matrix Matrix::transposed() const {
        Matrix result(w, h);

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                result[j][i] = rows[i][j];
            }
        }

        return result;
    }

    double Matrix::trace() const {
        if (h != w) {
            throw SizeMismatchException();
        }

        double result = 0.0;

        for (size_t i = 0; i < h; ++i) {
            result += rows[i][i];
        }

        return result;
    }

    std::vector<double> Matrix::getRow(size_t row) {
        if (row >= h) {
            throw OutOfBoundsException();
        }

        std::vector<double> result(w);

        for (size_t j = 0; j < w; ++j) {
            result[j] = rows[row][j];
        }

        return result;
    }

    std::vector<double> Matrix::getColumn(size_t column) {
        if (column >= w) {
            throw OutOfBoundsException();
        }

        std::vector<double> result(h);

        for (size_t i = 0; i < h; ++i) {
            result[i] = rows[i][column];
        }

        return result;
    }

    bool Matrix::operator==(const Matrix& a) const {
        if (h != a.get_h() || w != a.get_w()) {
            return false;
        }

        for (size_t i = 0; i < h; ++i) {
            for (size_t j = 0; j < w; ++j) {
                if (std::abs(rows[i][j] - a[i][j]) > EPS) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Matrix::operator!=(const Matrix& a) const {
        return !(*this == a);
    }

    size_t Matrix::get_h() const {
        return h;
    }

    size_t Matrix::get_w() const {
        return w;
    }

    double rec_det(const Matrix& a) {
        size_t n = a.get_h();

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return a[0][0];
        }

        double det = 0, sub_det;
        int p_j;
        Matrix b(n - 1, n - 1);

        for (int curr = 0; curr < n; ++curr) {
            for (int i = 1; i < n; ++i) {
                p_j = 0;

                for (int j = 0; j < n; ++j) {
                    if (j == curr) {
                        continue;
                    }

                    b[i - 1][p_j++] = a[i][j];
                }
            }

            sub_det = rec_det(b);
            if (curr % 2) {
                det -= a[0][curr] * sub_det;
            } else {
                det += a[0][curr] * sub_det;
            }
        }

        return det;
    }

    Matrix operator*(const double &a, const Matrix &b) {
        return b * a;
    }

    std::ostream &operator<<(std::ostream &output, const Matrix &matrix) {
        for (size_t i = 0; i < matrix.get_h(); ++i) {
            for (size_t j = 0; j < matrix.get_w(); ++j) {
                output << matrix[i][j] << (j == matrix.get_w() - 1 ? '\n' : ' ');
            }
        }

        return output;
    }

    std::istream &operator>>(std::istream &input, Matrix &matrix) {
        size_t rows, cols;
        input >> rows >> cols;

        matrix = Matrix(rows, cols);

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                input >> matrix[i][j];
            }
        }

        return input;
    }

}
