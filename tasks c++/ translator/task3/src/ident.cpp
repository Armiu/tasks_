#include "ident.hpp"

Ident::Ident() {
    declare = false;
    assign = false;
}

Ident::Ident(const char* n) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

Ident::Ident(const Ident& i) {
    type = i.type;
    declare = i.declare;
    assign = i.assign;
    if (i.name) {
        name = new char[strlen(i.name)+1];
        strcpy(name, i.name);
    } 
    else {
        name = nullptr;
    }
}

Ident& Ident::operator=(const Ident& i) {
    type = i.type;
    declare = i.declare;
    assign = i.assign;
    if (i.name) {
        name = new char[strlen(i.name)+1];
        strcpy(name, i.name);
    } 
    else {
        name = nullptr;
    }
    return *this;
}

bool Ident::operator==(const char* n) const {
    return name == n;
}

void Ident::put_name(const char* n) {
    name = new char[strlen(n) + 1];
    strcpy(name, n);
}

char* Ident::get_name() {
    return name;
}

bool Ident::get_declare() {
    return declare;
}

void Ident::put_declare() {
    declare = true;
}

type_of_lex Ident::get_type() {
    return type;
}

void Ident::put_type(type_of_lex t) {
    type = t;
}

bool Ident::get_assign() {
    return assign;
}

void Ident::put_assign() {
    assign = true;
}

int Ident::get_value() {
    return value;
}

void Ident::put_value(int a) {
    value = a;
}