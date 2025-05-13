#include "matrix.h"

void Matrix::set_matrix(size_t rows, size_t cols, double **matrix){
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and cols must be positive");
    }
    if (matrix == nullptr) {
        throw std::invalid_argument("Input matrix cannot be nullptr");
    }
    double **new_matrix = new double*[rows]{0};
    for(size_t i = 0; i < rows; ++i){
        new_matrix[i] = new double[cols]{0};
        for(size_t j = 0; j < cols; ++j){
               new_matrix[i][j] = matrix[i][j];
        }
    }
    for(size_t i = 0; i < rows_; ++i){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    rows_ = rows, cols_ = cols;
    matrix_ = new_matrix;
};

void Matrix::set_matrix(size_t rows, size_t cols, double *matrix){
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Rows and cols must be positive");
    }
    if (matrix == nullptr) {
        throw std::invalid_argument("Input matrix cannot be nullptr");
    }
    double **new_matrix = new double*[rows]{0};
    size_t counter = 0;
    for(size_t i = 0; i < rows; ++i){
        new_matrix[i] = new double[cols]{0};
        for(size_t j = 0; j < cols; ++j){
            new_matrix[i][j] = matrix[counter++];
        }
    }
    for(size_t i = 0; i < rows_; ++i){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    rows_ = rows, cols_ = cols;
    matrix_ = new_matrix;
};

size_t Matrix::get_rows() const {
    return rows_;
};

size_t Matrix::get_cols() const {
    return cols_;
};

double ** Matrix::get_matrix() const {
    return matrix_;
};

void Matrix::set_rows(size_t r){
    if(r < 1){
        throw std::out_of_range("Invalid count of rows (< 1)");
    }
    if(r > rows_){
        double **new_matrix = new double*[r]{0};
        for(size_t i = 0; i < r; ++i){
            new_matrix[i] = new double[cols_]{0};
            for(size_t j = 0; j < cols_; ++j){
                if(i < rows_){
                    new_matrix[i][j] = matrix_[i][j];
                }
            }
        }
        for(size_t i = 0; i < rows_; ++i){
            delete [] matrix_[i];
        }
        delete [] matrix_;
        matrix_ = new_matrix;
    }
    else if(r < rows_){
        double **new_matrix = new double*[r]{0};
        for(size_t i = 0; i < r; ++i){
            new_matrix[i] = new double[cols_]{0};
            for(size_t j = 0; j < cols_; ++j){
                new_matrix[i][j] = matrix_[i][j];
            }
        }
        for(size_t i = 0; i < rows_; ++i){
            delete [] matrix_[i];
        }
        delete [] matrix_;
        matrix_ = new_matrix;
    }
    rows_= r;
};

void Matrix::set_cols(size_t c){
    if(c < 1){
        throw std::out_of_range("Invalid count of cols (<1)");
    }
    if(c > cols_){
        for(size_t i = 0; i < rows_; ++i){
            double *new_column = new double[c]{0};
            for(size_t j = 0; j < cols_; ++j){
                new_column[j] = matrix_[i][j];
            }
            delete [] matrix_[i];
            matrix_[i] = new_column;
        }
    }
    else if(c < cols_){
        for(size_t i = 0; i < rows_; ++i){
            double *new_column = new double[c]{0};
            for(size_t j = 0; j < c; ++j){
                new_column[j] = matrix_[i][j];
            }
            delete [] matrix_[i];
            matrix_[i] = new_column;
        }
    }
    cols_ = c;
};

Matrix::Matrix(size_t r, size_t c) : rows_(r), cols_(c) {
    if(r < 1 || c < 1){
        throw std::invalid_argument("Invalid count of rows or cols (< 1)");
    }
    matrix_ = new double*[rows_]{0};
    for(size_t i = 0; i < rows_; ++i){
        matrix_[i] = new double[cols_]{0};
    }
};

Matrix::Matrix() noexcept : rows_(0), cols_(0){
    matrix_ = nullptr;
};

Matrix::Matrix(Matrix &other) noexcept {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double*[rows_]{0};
    for(size_t i = 0; i < rows_; ++i){
        matrix_[i] = new double[cols_]{0};
    }
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; ++j){
            matrix_[i][j] = other.matrix_[i][j];
        }
    }
};

Matrix::Matrix (Matrix &&other) noexcept {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    other.rows_ = 0, other.cols_ = 0;
};

Matrix::~Matrix(){
    for(size_t i = 0; i < rows_; ++i){
        delete [] matrix_[i];
    }
    delete [] matrix_;
};

bool Matrix::EqMatrix(const Matrix &other){
    bool flag_eq = true;
    if(rows_ != other.rows_ || cols_ != other.cols_){
        flag_eq = false;
    }
    for(size_t i = 0; i < rows_ && flag_eq; ++i){
        for(size_t j = 0; j < cols_ && flag_eq; j++){
            if(this -> matrix_[i][j] != other.matrix_[i][j]){
                flag_eq =false;
            }
        }
    }
    return flag_eq;
};

void Matrix::SumMatrix(const Matrix &other){
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw std::invalid_argument("Matrix dimensions mismatch for addition");
    }
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; j++){
            this -> matrix_[i][j] += other.matrix_[i][j];
        }
    }
};

void Matrix::SubMatrix(const Matrix &other){
    if(rows_ != other.rows_ || cols_ != other.cols_){
        throw std::invalid_argument("Matrix dimensions mismatch for substaction");
    }
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; j++){
            this -> matrix_[i][j] -= other.matrix_[i][j];
        }
    }
};

void Matrix::MulNumber(const double num){
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; j++){
            this -> matrix_[i][j] *= num;
        }
    }
};

void Matrix::MulMatrix(const Matrix &other){
    if(cols_ != other.rows_){
        throw std::invalid_argument("Matrix dimensions mismatch for multiplication");
    }
    Matrix result(this -> rows_, other.cols_);
    for(size_t i = 0; i < this -> rows_; ++i){
        for(size_t j = 0; j < other.rows_; ++j){
            for(size_t k = 0; k < other.cols_; ++k){
                result.matrix_[i][k] += this -> matrix_[i][j] * other.matrix_[j][k];
            }
        }
    }
    for(size_t i = 0; i < rows_; ++i){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    this -> rows_ = result.rows_, this -> cols_ = result.cols_;
    matrix_ = new double*[rows_]{0};
    for(size_t i = 0; i < result.rows_; ++i){
        matrix_[i] = new double[cols_]{0};
        for (size_t j = 0; j < result.cols_; ++j){
            this -> matrix_[i][j] = result.matrix_[i][j];
        }
    }
};

Matrix &Matrix::Transpose(){
    Matrix res(this -> cols_, this -> rows_);
    for(size_t i = 0; i < this -> rows_; ++i){
        for(size_t j = 0; j < this -> cols_; ++j){
            res.matrix_[j][i] = this -> matrix_[i][j];
        }
    }
    for(size_t i = 0; i < this -> rows_; ++i){
        delete [] matrix_[i];
    }
    delete [] matrix_;
    rows_ = res.rows_, cols_ = res.cols_;
    matrix_ = new double*[rows_];
    for(size_t i = 0; i < rows_; ++i){
        matrix_[i] = new double[cols_];
        for(size_t j = 0; j < cols_; ++j){
            matrix_[i][j] = res.matrix_[i][j];
        }
    }
    return *this;
};

Matrix Matrix::CalcComplements(){
    if(rows_ != cols_){
        throw std::domain_error("Algebraic complements require a square matrix");
    }
    Matrix res(rows_, cols_);
    if(rows_ == 1){
        res.matrix_[0][0] = 1;
    }
    else{
        for (size_t i = 0; i < rows_; ++i) {
            for (size_t j = 0; j < cols_; ++j) {
                Matrix minor(rows_ - 1, cols_ - 1);
                this -> minor_matrix(i, j, minor);
                double tmp_det_result = minor.Determinant();
                res.matrix_[i][j] = tmp_det_result * pow(-1, i + j);
            }
        }
    }
    return res;
};

void Matrix::minor_matrix(size_t row, size_t col, Matrix &matrix) {
    size_t tmp_i = 0, tmp_j = 0;
    for (size_t i = 0; i < rows_; ++i) {
        tmp_j = 0;
        for (size_t j = 0; j < cols_; ++j) {
            if (i != row && j != col)
                matrix.matrix_[tmp_i][tmp_j++] = this -> matrix_[i][j];
        }
        if (i != row) tmp_i++;
    }
};

double Matrix::Determinant(){
    double res;
    if(rows_ != cols_){
        throw std::domain_error("Determinant require a square matrix");
    }
    get_det(res);
    return res;
};

void Matrix::get_det(double &res){
    if (this -> rows_ == 1) res = this -> matrix_[0][0];
    if (this -> cols_ == 2)
    res=
        this -> matrix_[0][0] * this -> matrix_[1][1] - this -> matrix_[0][1] * this -> matrix_[1][0];
    if (this -> cols_ == 3)
    res = this -> matrix_[0][0] * this -> matrix_[1][1] * this -> matrix_[2][2] +
        this -> matrix_[0][1] * this -> matrix_[1][2] * this -> matrix_[2][0] +
        this -> matrix_[1][0] * this -> matrix_[2][1] * this -> matrix_[0][2] -
        this -> matrix_[0][2] * this -> matrix_[1][1] * this -> matrix_[2][0] -
        this -> matrix_[1][0] * this ->matrix_[0][1] * this -> matrix_[2][2] -
        this -> matrix_[1][2] * this -> matrix_[2][1] * this -> matrix_[0][0];
    if (this -> cols_ > 3) {
        char param;
        res = 0;
        int str = zeros_counter(param);
        for (size_t j = 0; j < this -> rows_; ++j) {
            size_t curr_row = ((param == 'c') ? j : str),
                curr_col = ((param == 'c') ? str : j);
            Matrix minor(this -> rows_ - 1, this -> cols_ - 1);
            if ((this -> matrix_[curr_row][curr_col])) {
                minor_matrix(curr_row, curr_col, minor);
                double minor_determinant;
                minor.get_det(minor_determinant);
                minor_determinant *= this -> matrix_[curr_row][curr_col] * pow(-1, str + j);
                res += minor_determinant;
            }
        }
    }
};

int Matrix::zeros_counter(char &param){
    size_t zero_counter, max_zero_row = 0, max_zero_col = 0, row = 0, col = 0;
    for (size_t i = 0; i < this -> rows_; ++i) {
        zero_counter = 0;
        for (size_t j = 0; j < this -> cols_; ++j){
            if (!(this -> matrix_[i][j])) zero_counter++;
        }
        if (zero_counter > max_zero_row) {
            max_zero_row = zero_counter;
            row = i;
        }
    }
    for (size_t i = 0; i < this -> cols_; ++i) {
        zero_counter = 0;
        for (size_t j = 0; j < this -> cols_; ++j) {
            if (!(this -> matrix_[j][i])) zero_counter++;
        }
        if (zero_counter > max_zero_col) {
            max_zero_col = zero_counter;
            col = i;
        }
    }
    param = ((max_zero_col > max_zero_row) ? 'c' : 'r');
    return ((max_zero_col > max_zero_row) ? col : row);
};

void Matrix::round_for_inverse(){
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; ++j){
            matrix_[i][j] = std::round(matrix_[i][j] * 1e10) / 1e10;
        }
    }
}

Matrix Matrix::InverseMatrix(){
    if(rows_ != cols_){
        throw std::domain_error("Inverse matrix require a square matrix");
    }
    Matrix res(rows_, cols_);
    for(size_t i = 0; i < rows_; ++i){
        for(size_t j = 0; j < cols_; ++j){
            if(i == j) res.matrix_[i][j] = 1;
        }
    }
    for(size_t i = 0; i < rows_; ++i){
        size_t tmp_i = i;
        while(matrix_[tmp_i][i] == 0){
            tmp_i++;
            if(matrix_[tmp_i][i] != 0){
                std::swap(matrix_[i], matrix_[tmp_i]);
                std::swap(res.matrix_[i], res.matrix_[tmp_i]);
            }
            else if(tmp_i == rows_ - 1){
                throw std::runtime_error("Matrix is singular (all leading elements are zero), inverse does not exist");  
            }
        }
        double tmp_el = matrix_[i][i];
        for(size_t j = 0; j < cols_; ++j){
            matrix_[i][j] /= tmp_el;
            res.matrix_[i][j] /= tmp_el;
        }
        for(size_t k = 0; k < rows_; ++k){
            if(k != i){
                tmp_el = matrix_[k][i];
                for(size_t l = 0; l < cols_; ++l){
                    matrix_[k][l] -= matrix_[i][l] * tmp_el;
                    res.matrix_[k][l] -= res.matrix_[i][l] * tmp_el;
                }
            }
        }
    }
    res.round_for_inverse();
    return res;
};

Matrix Matrix::operator +(const Matrix &other){
    Matrix res = *this;
    res += other;
    return res;
};

Matrix Matrix::operator -(const Matrix &other){
    Matrix res = *this;
    res -= other;
    return res;
};

Matrix Matrix::operator *(const Matrix &other){
    Matrix res = *this;
    res *= other;
    return res;
};

Matrix Matrix::operator *(const double &num){
    Matrix res = *this;
    res *= num;
    return res;
}

bool Matrix::operator ==(const Matrix &other){
    return this -> EqMatrix(other);
};

Matrix &Matrix::operator = (const Matrix &other) noexcept{
    if(this != &other){
        if(matrix_ != nullptr){
            for(size_t i = 0; i < rows_; ++i){
                delete [] matrix_[i];
            }
            delete [] matrix_;
        }
        rows_ = other.rows_, cols_ = other.cols_;
        matrix_ = new double*[rows_];
        for(size_t i = 0; i < rows_; ++i){
            matrix_[i] = new double[cols_]{0};
            for(size_t j = 0; j < cols_; ++j){
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
    return *this;
};
    
Matrix &Matrix::operator +=(const Matrix &other){
    this -> SumMatrix(other);
    return *this;
};
    
Matrix &Matrix::operator -=(const Matrix &other){
    this -> SubMatrix(other);
    return *this;
};
    
Matrix &Matrix::operator *=(const Matrix &other){
    this -> MulMatrix(other);
    return *this;
};
    
Matrix &Matrix::operator *=(const double &num){
    this -> MulNumber(num);
    return *this;
};

double Matrix::operator()(size_t rows, size_t cols) const{
    if(rows >= rows_ || cols >= cols_ || cols < 0 || rows < 0){
        throw std::out_of_range("Index or indexes are out of range");
    }
    return matrix_[rows][cols];
};


void Matrix::zero_main_diag(){
    if(rows_ == cols_){
        for(size_t i = 0; i < rows_; ++i){
            matrix_[i][i] = 0;
        }
    }
};

const double* Matrix::get_row(size_t r) const {
    return (r >= 0 && r < rows_) ? matrix_[r] : nullptr;
};

Matrix &Matrix::operator = (Matrix &&other) noexcept{
    this -> matrix_ = other.matrix_;
    other.matrix_ = nullptr;
    this -> rows_ = other.rows_;
    other.rows_ = 0;
    this -> cols_ = other.cols_;
    other.cols_ = 0;
    return *this;
};