#ifndef MYSTRING_HPP
#define MYSTRING_HPP
#include <iostream>
#include <cstring>
#include <string>

namespace strings{
    class MyString {
        char* data;
        int length;
    public:    
        MyString(const char* str);
        MyString(const std::string& str);
        MyString();
        MyString(const MyString& other);
        MyString& operator=(const MyString& other);
        ~MyString();
        const char* getData() const;
        int getLength() const;
    };   
}

#endif // MYSTRING_HPP