#ifndef H_MATRIX
#define H_MATRIX

#include <iostream>
#include <cmath>

class Matrix{
private:
    size_t rows_, cols_;
    double **matrix_{nullptr};
public:
    Matrix(size_t r, size_t c); //
    Matrix() noexcept; //
    Matrix(Matrix &other) noexcept; //
    ~Matrix(); //
    Matrix (Matrix &&other) noexcept; //?
    size_t get_rows() const; //
    size_t get_cols() const; //
    double **get_matrix() const; //
    void set_rows(size_t r); //
    void set_cols(size_t c); //
    void set_matrix(size_t rows, size_t cols, double **matrix); //
    void set_matrix(size_t rows, size_t cols, double *matrix); //
    bool EqMatrix(const Matrix &other); //
    void SumMatrix(const Matrix &other); //
    void SubMatrix(const Matrix &other);
    void MulNumber(const double num);
    void MulMatrix(const Matrix &other);
    Matrix &Transpose();
    Matrix CalcComplements();
    double Determinant();
    Matrix InverseMatrix();
    void round_for_inverse();
    void get_det(double &res);
    int zeros_counter(char &param);
    void minor_matrix(size_t row, size_t col, Matrix &matrix);
    Matrix operator +(const Matrix &other);
    Matrix operator -(const Matrix &other);
    Matrix operator *(const Matrix &other);
    Matrix operator *(const double &num);
    bool operator ==(const Matrix &other);
    Matrix &operator = (const Matrix &other) noexcept;
    Matrix &operator = (Matrix &&other) noexcept;
    Matrix &operator +=(const Matrix &other);
    Matrix &operator -=(const Matrix &other);
    Matrix &operator *=(const Matrix &other);
    Matrix &operator *=(const double &num);
    double operator()(size_t rows, size_t cols) const;
    void zero_main_diag();
    const double* get_row(size_t r) const;
};

#endif