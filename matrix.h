#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#pragma once
#include <iostream>
#include <exception>
#include <algorithm>
namespace BMSTU {
    using namespace std;
    class MatricesBinaryOperationException : public runtime_error {
    public:
        using runtime_error::runtime_error;
    };
    template<typename Type>
    class Matrix {
    public:
        Matrix() noexcept = default;
        Matrix(size_t rows, size_t cols, const Type &value = Type{});
        Matrix(const std::initializer_list<std::initializer_list<Type>> &init);
        Matrix(const Matrix<Type> &other);
        Matrix(Matrix<Type> &&rvl) noexcept;
        Matrix &operator=(const Matrix<Type> &other);
        Matrix &operator=(Matrix<Type> &&rvl) noexcept;
        Matrix operator+(const Matrix<Type> &other) const;
        Matrix operator-(const Matrix<Type> &other) const;
        Matrix operator*(const Matrix<Type> &other) const;
        Matrix operator*(const Type &item) const;
        ~Matrix() {delete[] matrix_;}
        size_t GetRows() const noexcept {return rows_;}
        size_t GetCols() const noexcept {return cols_;}
        bool IsEmpty() const noexcept {return matrix_ == nullptr;}
        Matrix trans();
        const Matrix trans() const;
        Type &cell(size_t row, size_t col) {return matrix_[row*cols_+col];}
        const Type &cell(size_t row, size_t col) const {return matrix_[row*cols_+col];}
        Type* operator[](size_t index) noexcept {
            Type* row;
            row = new Type[cols_];
            std::copy(matrix_+index*cols_, matrix_+(index+1)*cols_, row);
            return row;
        }
        const Type* operator[](size_t index) const noexcept {
            Type* row;
            row = new Type[cols_];
            std::copy(matrix_+index*cols_, matrix_+(index+1)*cols_, row);
            return row;
        }
    protected:
        Type* matrix_ = nullptr;
        size_t rows_ = 0;
        size_t cols_ = 0;
    };

    template<typename Type>
    class SingleMatrix : public Matrix<Type>{
    public:
        explicit SingleMatrix(size_t size) : Matrix<Type>(size, size, 0), size_(size){
            for(size_t i = 0; i < size_; i++) {
                Matrix<Type>::matrix_[i*size_+i] = 1;
            }
        }
    private:
        size_t size_;
    };

    template<typename Type>
    class ZeroMatrix : public Matrix<Type>{
    public:
        explicit ZeroMatrix(size_t rows, size_t cols)
        : Matrix<Type>(rows, cols, 0), _rows(rows), _cols(cols){}
    private:
        size_t _rows;
        size_t _cols;
    };
}

#endif //MATRIX_MATRIX_H
