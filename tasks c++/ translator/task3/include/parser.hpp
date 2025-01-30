#ifndef PARSER_HPP
#define PARSER_HPP
#include "scanner.hpp"
#include "lex.hpp"
#include "poliz.hpp"
#include "t_id.hpp"
#include "stack.hpp"
#include "ident.hpp"
#include "record.hpp"
#include <vector>

extern table_ident TID;
extern std::vector<Record> recs;

class Parser {
    Lex curr_lex; 
    type_of_lex c_type;
    int c_val;
    Scanner scan;
    Stack <int, 100> st_int;
    Stack <type_of_lex, 100> st_lex;

    void P(); 
    void D1();
    void D(int = -1);
    void Rec();
    void B();
    void S();
    void E();
    void E1();
    void T();
    void F();

    void dec (type_of_lex type, int); 
    int check_id();
    void check_op();
    void check_not();
    void eq_type();
    void eq_bool();
    int check_id_in_read();

    void gl();
public:
    std::vector<Record> recs;
    Poliz prog; 
    Parser (const char *program): scan(program), prog(1000) {}
    void analyze();
};

#endif