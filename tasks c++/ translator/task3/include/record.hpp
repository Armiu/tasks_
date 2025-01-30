#ifndef RECORD_HPP
#define RECORD_HPP
#include "t_id.hpp"
#include "stack.hpp"
#include "ident.hpp"
#include <vector>

class Record {
    table_ident records_table;
    std::vector<int> vars;
public:
    Record() : records_table(100) {}
    Record(const Record&) = default;
    void add_var(const Ident &i, int n);
    bool is_in_vars(int n) const;
    Ident& operator[](int n); 
};

#endif