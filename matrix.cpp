#include "matrix.h"
#include <iostream>
using namespace BMSTU;

template<typename Type>
Matrix<Type>::Matrix(size_t rows, size_t cols, const Type &value) : rows_(rows), cols_(cols), matrix_(new Type[rows*cols]) {
    for (size_t i = 0; i < rows_*cols_; i++) {
        matrix_[i] = value;
    }
}

template<typename Type>
Matrix<Type>::Matrix(const std::initializer_list<std::initializer_list<Type>> &init) : rows_(init.size()), cols_((*(init.begin())).size()) {
    matrix_ = new Type[rows_*cols_];
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < cols_; ++j) {
            matrix_[i*cols_+j] = *((*(init.begin()+i)).begin() +j);
        }
    }
}

template<typename Type>
Matrix<Type>::Matrix(const Matrix<Type> &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new Type[rows_*cols_];
    std::copy(other.matrix_, other.matrix_+rows_*cols_, matrix_);
}

template<typename Type>
Matrix<Type>::Matrix(Matrix<Type> &&rvl) noexcept{
    rows_ = rvl.rows_;
    cols_ = rvl.cols_;
    matrix_ = rvl.matrix_;
    rvl.matrix_ = nullptr;
    rvl.rows_ = 0;
    rvl.cols_ = 0;
}

template<typename Type>
Matrix<Type> &Matrix<Type>::operator=(const Matrix<Type> &other) {
    delete[] matrix_;
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new Type[rows_*cols_];
    std::copy(other.matrix_, other.matrix_+rows_*cols_, matrix_);
    return *this;
}

template<typename Type>
Matrix<Type> &Matrix<Type>::operator=(Matrix<Type> &&rvl) noexcept {
    delete[] matrix_;
    rows_ = rvl.rows_;
    cols_ = rvl.cols_;
    matrix_ = rvl.matrix_;
    rvl.matrix_ = nullptr;
    rvl.rows_ = 0;
    rvl.cols_ = 0;
    return *this;
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &other) const{
    if (rows_!= other.rows_ || cols_!=other.cols_) {
        throw MatricesBinaryOperationException("Error in sum operator! Wrong size!");
    }
    Matrix<Type> new_matrix(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            new_matrix.matrix_[i*cols_+j] = matrix_[i*cols_+j]+other.matrix_[i*cols_+j];
        }
    }
    return new_matrix;
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &other) const {
    if (rows_!= other.rows_ || cols_!=other.cols_) {
        throw MatricesBinaryOperationException("Error in difference operator! Wrong size!");
    }
    Matrix<Type> new_matrix(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            new_matrix.matrix_[i*cols_+j] = matrix_[i*cols_+j]-other.matrix_[i*cols_+j];
        }
    }
    return new_matrix;
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator*(const Matrix<Type> &other) const {
    if (cols_!=other.rows_) {
        throw MatricesBinaryOperationException("Error in multiplication operator! Wrong size!");
    }
    Matrix<Type> new_matrix(rows_, other.cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < other.cols_; ++j) {
            Type result = Type{};
            for (size_t k = 0; k < cols_; ++k) {
                result += matrix_[i*cols_+k]*other.matrix_[k*other.cols_+j];
            }
            new_matrix.matrix_[i*new_matrix.cols_+j] = result;
        }
    }
    return new_matrix;
}

template<typename Type>
Matrix<Type> Matrix<Type>::operator*(const Type &item) const {
    Matrix<Type> new_matrix(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            new_matrix.matrix_[i*cols_+j] = matrix_[i*cols_+j] * item;
        }
    }
    return new_matrix;
}

template<typename Type>
Matrix<Type> Matrix<Type>::trans(){
    Matrix<Type> new_matrix(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            new_matrix.matrix_[j*rows_+i] = matrix_[i*cols_+j];
        }
    }
    return new_matrix;
}

template<typename Type>
const Matrix<Type> Matrix<Type>::trans() const{
    Matrix<Type> new_matrix(cols_, rows_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            new_matrix.matrix_[j*rows_+i] = matrix_[i*cols_+j];
        }
    }
    return new_matrix;
}
void print(int mat[][MAX] ,int m,int n){
    for (int i = 0;i < m;i++) {
        for (int j = 0; j < n; j++) {
            std:: cout << mat[i][j] << " ";
        }
        std:: cout << "\n";
    }
}
void impli(int mat1[MAX][MAX],int mat2[MAX][MAX],int mat3[MAX][MAX]){
    for(int i=0; i < MAX; i++)
        for(int j=0; j < MAX; j++)
        {
            mat3[i][j]=0;
            for(int k=0; k < MAX; k++)
                mat3[i][j]+=mat1[i][k]*mat2[k][j];
        }
}

void umnoprint(Matrix<int>m1,int m,int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << m1[i][j] << " ";
        }
        std::cout << "\n";
    }
}
