#include "lex.hpp"

type_of_lex Lex::get_type() { 
    return t_lex; 
}
int Lex::get_value() { 
    return v_lex; 
}
std::ostream& operator<<(std::ostream &s, Lex l) {
    s << '(' << l.get_type() << ',' << l.get_value() << ");";
    return s;
}