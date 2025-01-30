#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "lex.hpp"
#include "t_id.hpp"
#include<iostream>
#include<cstring>
#include <fstream>

class Scanner {
    enum state { H, IDENT, NUMB, COM, ALE, DELIM, NEQ };
    static const char * TW[];
    static type_of_lex words[];
    static const char * TD[];
    static type_of_lex dlms[];
    state CS;
    FILE* fp;
    char c;
    char buf[80];
    int buf_top;
    
    void clear();
    void add();
    int look(const char *buf, const char **list);
    void gc();
public:
    Lex get_lex();
    Scanner (const char* program);
};

#endif