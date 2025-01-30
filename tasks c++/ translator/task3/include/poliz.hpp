#ifndef POLIZ_HPP
#define POLIZ_HPP
#include "lex.hpp"
#include<iostream>

class Poliz {
    Lex *p;
    int size;
    int free;
public:
    Poliz(int max_size);
    ~Poliz();
    void put_lex(Lex l);
    void put_lex(Lex l, int place);
    void blank();
    int get_free();
    Lex& operator[](int index);
    void print();
};

#endif