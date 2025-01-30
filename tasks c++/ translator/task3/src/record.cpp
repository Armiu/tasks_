#include "record.hpp"

void Record::add_var(const Ident &i, int n) {
    records_table[vars.size()+1] = i;
    records_table.put();
    vars.push_back(n);
}

bool Record::is_in_vars(int n) const {
    for (int m : vars) {
        if (m == n) return true;
    }
    return false;
}

Ident& Record::operator[](int n) {
    int addr = 0;
    for (int m : vars) {
        ++addr;
        if (m == n) return records_table[addr];
    }
    throw "Record variable mismatch";
}

