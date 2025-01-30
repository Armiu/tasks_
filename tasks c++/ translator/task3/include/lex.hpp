#ifndef LEX_HPP
#define LEX_HPP
#include "enum.hpp"
#include <iostream>

class Lex {
    type_of_lex t_lex;
    int v_lex;
public:
    Lex(type_of_lex t = LEX_NULL, int v = 0) : t_lex(t), v_lex(v) {}
    type_of_lex get_type ();
    int get_value ();
    friend std::ostream& operator<<(std::ostream &s, Lex l);
};

#endif