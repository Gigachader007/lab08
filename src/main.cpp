#include <header.hpp>

#include <iostream>

int main(){
    auto res = CopyString("Hello world!\n"); 
    std::cout << res; 
    std::cout << ConcatinateStrings("Hello ", "World!") << std::endl; //memory leak
    
    Matrix m1;
    Construct(m1,4,4);
    for(auto i = 0; i < 4; ++i){
        m1.data_[i][i] = 1;
    }

    Matrix m2;
    Construct(m2,4,4);
    for(auto i = 0; i < 4; ++i){
        for(auto j = 0; j < 4; ++j){
            m2.data_[i][j] = 4*i-5*j;
        }
    }

    Matrix m3;
    Construct(m3,4,4);
    for(auto i = 0; i < 4; ++i){
        for(auto j = 0; j < 4; ++j){
            m3.data_[i][j] = 2*i-3*j;
        }
    }

    std::cout << int(m2 == Mult(m1,m2)) << std::endl;
    std::cout << int(Mult(m3,m2) == Mult(m2,m3)) << std::endl;
    auto m2_sub = Copy(m2);
    Transposition(m2_sub);
    std::cout << int(m2_sub == m2) << std::endl;
}