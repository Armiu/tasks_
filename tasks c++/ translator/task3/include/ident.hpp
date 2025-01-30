#ifndef IDENT_HPP
#define IDENT_HPP
#include "lex.hpp"
#include <cstring>

class Ident {
    char * name = nullptr;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
public:
    Ident();
    Ident(const char* n);
    Ident(const Ident&);
    Ident& operator=(const Ident&);
    bool operator== (const char* n) const;
    void put_name(const char* n);
    char* get_name();
    bool get_declare();
    void put_declare();
    type_of_lex get_type();
    void put_type(type_of_lex t);
    bool get_assign();
    void put_assign();
    int get_value();
    void put_value(int a);
};

#endif