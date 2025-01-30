#include "ident.hpp"
#ifndef TABLE_IDENT_HPP
#define TABLE_IDENT_HPP

class table_ident {
    Ident * p;
    int size;
    int top;
public:
    table_ident (int max_size = 100) : p(new Ident[max_size]), size(max_size), top(1) {}
    table_ident (const table_ident&);
    table_ident& operator=(const table_ident&);
    ~table_ident();
    Ident& operator[](int k);
    int put(const char *buf);
    int put() { return ++top; }
};

#endif