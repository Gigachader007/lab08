#include <header.hpp>
// Создает заполненную нулями матрицу n x m.
void Construct(Matrix& out, size_t n, size_t m){
    out.m_ = m;
    out.n_ = n;
    out.data_ = nullptr;
    if(n != 0 && m != 0){
        out.data_ = new int*[n];
        for(int i = 0; i < n; ++i){
            out.data_[i] = new int[m];
            for(int j = 0; j < m; ++j){
                out.data_[i][j] = 0;
            }
        }
    }
}
// Освобождает выделенную память.
void Destruct(Matrix& in){
    if(in.data_){
        for(auto i = 0; i < in.n_; ++i){
            delete[] in.data_[i];
        }
        delete[] in.data_;
    }
}

// Создает копию матрицы |matrix|.
Matrix Copy(const Matrix& matrix){
    Matrix tmp{};
    if(matrix.data_){
        Construct(tmp,matrix.n_,matrix.m_);
        for(int i = 0; i < matrix.n_; ++i){
            for(int j = 0; j < matrix.m_; ++j){
                tmp.data_[i][j] = matrix.data_[i][j];
            }
        }
    }
    return tmp;
}
// Возвращает сумму двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Add(const Matrix& a, const Matrix& b){
    Matrix tmp{};
    if(a.data_ && b.data_ && a.n_ == b.n_ && a.m_ == b.m_){
        Construct(tmp,a.n_,b.m_);
        for(int i = 0; i < a.n_; ++i){
            for(int j = 0; j < a.m_; ++j){
                tmp.data_[i][j] = a.data_[i][j] + b.data_[i][j];
            }
        }
    }
    return tmp;
}
// Возвращает разницу двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Sub(const Matrix& a, const Matrix& b){
    Matrix tmp{};
    if(a.data_ && b.data_ && a.n_ == b.n_ && a.m_ == b.m_){
        Construct(tmp,a.n_,b.m_);
        for(int i = 0; i < a.n_; ++i){
            for(int j = 0; j < a.m_; ++j){
                tmp.data_[i][j] = a.data_[i][j] - b.data_[i][j];
            }
        }
    }
    return tmp;
}
// Возвращает произведение двух матриц.
// Если операция невозможна - вернуть пустую матрицу
Matrix Mult(const Matrix& a, const Matrix& b){
    Matrix tmp{};
    if(a.data_ && b.data_ && a.m_ == b.n_){
        Construct(tmp,a.n_,b.m_);
        for(int i = 0; i < a.n_; ++i){
            for(int j = 0; j < b.m_; ++j){
                for(int k = 0; k < a.m_; ++k){
                    tmp.data_[i][j] += a.data_[i][k] * b.data_[k][j];
                }
            }
        }
    }
    return tmp;
}

// Транспонирование матрицы.
void Transposition(Matrix& matrix){
    Matrix tmp{};
    if(matrix.data_){
        Construct(tmp,matrix.m_,matrix.n_);
        for(auto i = 0; i < matrix.n_; ++i){
            for(auto j = 0; j < matrix.m_; ++j){
                tmp.data_[j][i] = matrix.data_[i][j];
            }
        }
        Destruct(matrix);
        matrix.m_ = tmp.m_;
        matrix.n_ = tmp.n_;
        matrix.data_ = tmp.data_;
    }
}

// Сравнение двух матриц.
bool operator==(const Matrix& a, const Matrix& b){
    if(a.n_ == b.n_ && a.m_ == b.m_){
        if(a.data_ && b.data_){
            bool flag = true;
            for(int i = 0; i < a.n_; ++i){
                for(int j = 0; j < a.m_; ++j){
                    flag &= (a.data_[i][j] == b.data_[i][j]);
                    if(!flag){
                        return false;
                    }
                }
            }
            return flag;
        }
    }
    return false;
}