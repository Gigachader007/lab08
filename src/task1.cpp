#include <header.hpp>

// Создает копию строки |str|.
char* CopyString(const char* str){
    auto cp = str;
    int counter = 0;
    while(*(cp++)){
        counter++;
    }
    auto res = new char[counter+1];
    for(auto i = 0; i < counter; i++){
        res[i] = str[i];
    }
    res[counter] = 0;
    return res;
}

// Соединяет две строки в одну новую.
char* ConcatinateStrings(const char* a, const char* b){
    int counter1 = 0, counter2 = 0;
    {
        auto cp = a;
        while(*(cp++)){
            counter1++;
        }
    }
    {
        auto cp = b;
        while(*(cp++)){
            counter2++;
        }
    }
    auto res = new char[counter1 + counter2];
    for(auto i = 0; i < counter1; i++){
        res[i] = a[i];
    }
    for(auto i = 0; i < counter2; i++){
        res[counter1+i] = b[i];
    }
    return res;
}