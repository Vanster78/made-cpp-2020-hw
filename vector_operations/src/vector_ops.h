#pragma once
#include <vector>
#include <iostream>


namespace task {

    const double eps = 1e-7;

    std::vector<double> operator+(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        std::vector<double> result(lhs.size());

        for (int i = 0; i < lhs.size(); ++i) {
            result[i] = lhs[i] + rhs[i];
        }

        return result;
    }

    std::vector<double> operator+(const std::vector<double>& vector) {
        std::vector<double> result(vector.size());

        for (int i = 0; i < vector.size(); ++i) {
            result[i] = vector[i];
        }

        return result;
    }

    std::vector<double> operator-(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        std::vector<double> result(lhs.size());

        for (int i = 0; i < lhs.size(); ++i) {
            result[i] = lhs[i] - rhs[i];
        }

        return result;
    }

    std::vector<double> operator-(const std::vector<double>& vector) {
        std::vector<double> result(vector.size());

        for (int i = 0; i < vector.size(); ++i) {
            result[i] = -vector[i];
        }

        return result;
    }

    double operator*(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        double result = 0.0;

        for (int i = 0; i < lhs.size(); ++i) {
            result += lhs[i] * rhs[i];
        }

        return result;
    }

    std::vector<double> operator%(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        std::vector<double> result(lhs.size());

        result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
        result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
        result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

        return result;
    }

    double calculate_length(const std::vector<double>& vector) {
        double result = 0.0;

        for (int i = 0; i < vector.size(); ++i) {
            result += vector[i] * vector[i];
        }

        result = std::sqrt(result);

        return result;
    }

    double calculate_cosine(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        double product = lhs * rhs;

        double lhs_length = calculate_length(lhs);
        double rhs_length = calculate_length(rhs);

        if (lhs_length < eps || rhs_length < eps) {
            return 1.0;
        }

        double cosine = product / lhs_length / rhs_length;

        return cosine;
    }

    bool operator||(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        double cosine = calculate_cosine(lhs, rhs);
        double abs_cosine = std::abs(cosine);

        return std::abs(1 - abs_cosine) < eps;
    }

    bool operator&&(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        double cosine = calculate_cosine(lhs, rhs);

        return std::abs(1 - cosine) < eps;
    }

    std::istream& operator>>(std::istream& input, std::vector<double>& vector) {
        int length;
        input >> length;

        vector.resize(length);

        for (int i = 0; i < vector.size(); ++i) {
            input >> vector[i];
        }

        return input;
    }

    std::ostream& operator<<(std::ostream& output, const std::vector<double>& vector) {
        for (int i = 0; i < vector.size(); ++i) {
            output << vector[i] << (i < vector.size() - 1 ? ' ' : '\n');
        }

        return output;
    }

    void reverse(std::vector<double>& vector) {
        for (int i = 0; i < vector.size() / 2; ++i) {
            std::swap(vector[i], vector[vector.size() - i - 1]);
        }
    }

    std::vector<int> operator&(const std::vector<int>& lhs, const std::vector<int>& rhs) {
        std::vector<int> result(lhs.size());

        for (int i = 0; i < result.size(); ++i) {
            result[i] = lhs[i] & rhs[i];
        }

        return result;
    }

    std::vector<int> operator|(const std::vector<int>& lhs, const std::vector<int>& rhs) {
        std::vector<int> result(lhs.size());

        for (size_t i = 0; i < result.size(); ++i) {
            result[i] = lhs[i] | rhs[i];
        }

        return result;
    }
}  // namespace task
