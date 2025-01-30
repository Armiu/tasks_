#ifndef EXECUTER_HPP
#define EXECUTER_HPP
#include "parser.hpp"
#include "t_id.hpp"
#include "lex.hpp"
#include "poliz.hpp"
#include "ident.hpp"
#include "stack.hpp"

#include <vector>
#include <iostream>
#include <cstring>

extern table_ident TID;

class Executer {
    Lex pc_el;
    Ident *curr_id;
public:
    void execute(Poliz& prog, std::vector<Record>& recs);
};

#endif