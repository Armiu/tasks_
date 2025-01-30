#include "t_id.hpp"

table_ident::table_ident(const table_ident& t) {
    size = t.size;
    p = new Ident[size];
    top = t.top;
    for (int i = 1; i < top; ++i) {
        p[i] = t.p[i];
    }
}

table_ident::~table_ident() {
    delete []p;
}

Ident& table_ident::operator[] (int k) {
    return p[k];
}

int table_ident::put (const char *buf) {
    for (int j = 1; j < top; ++j) {
        if (!strcmp(buf, p[j].get_name()))
            return j;
    }
    p[top].put_name(buf);
    return top++;
}

table_ident& table_ident::operator=(const table_ident& t) {
    size = t.size; 
    p = new Ident[size]; 
    top = t.top;
    for (int i = 1; i < top; ++i) {
        p[i] = t.p[i];
    }
    return *this;
}