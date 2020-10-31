#pragma once

#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>


namespace task {

    const double EPS = 1e-6;


    class OutOfBoundsException : public std::exception {};
    class SizeMismatchException : public std::exception {};

    class Vector {

    public:

        Vector();
        explicit Vector(size_t size);
        Vector(const Vector& copy);

        size_t length() const;

        double& operator[](size_t ind);
        const double& operator[](size_t ind) const;

        Vector& operator=(const Vector& a);
        ~Vector();

    private:

        size_t size;
        double* arr;
    };

    class Matrix {

    public:

        Matrix();
        Matrix(size_t rows, size_t cols);
        Matrix(const Matrix& copy);
        Matrix& operator=(const Matrix& a);

        double& get(size_t row, size_t col);
        const double& get(size_t row, size_t col) const;
        void set(size_t row, size_t col, const double& value);
        void resize(size_t new_rows, size_t new_cols);

        Vector& operator[](size_t row);
        const Vector& operator[](size_t row) const;

        Matrix& operator+=(const Matrix& a);
        Matrix& operator-=(const Matrix& a);
        Matrix& operator*=(const Matrix& a);
        Matrix& operator*=(const double& number);

        Matrix operator+(const Matrix& a) const;
        Matrix operator-(const Matrix& a) const;
        Matrix operator*(const Matrix& a) const;
        Matrix operator*(const double& a) const;

        Matrix operator-() const;
        Matrix operator+() const;

        double det() const;
        void transpose();
        Matrix transposed() const;
        double trace() const;

        std::vector<double> getRow(size_t row);
        std::vector<double> getColumn(size_t column);

        bool operator==(const Matrix& a) const;
        bool operator!=(const Matrix& a) const;

        size_t get_h() const;
        size_t get_w() const;

    private:

        friend double rec_det(const Matrix& a);
        Vector* rows;
        size_t h;
        size_t w;
    };


    double rec_det(const Matrix& a);
    Matrix operator*(const double& a, const Matrix& b);

    std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
    std::istream& operator>>(std::istream& input, Matrix& matrix);



}  // namespace task
