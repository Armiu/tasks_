#ifndef Strings_HPP
#define Strings_HPP
#include <vector>
#include <iostream>
#include "MyString.hpp"

namespace strings{
    class MyString;
    class BlockString { 
        std::vector<MyString> data;
    public:
        BlockString(const MyString& str);
        BlockString();
        BlockString(const std::vector<MyString>& blocks);
        BlockString(std::initializer_list<std::string> initList); 
        BlockString operator+(const BlockString& other) const;
        BlockString operator*(int value) const;
        const MyString& operator[](int index) const;
        MyString& operator[](int index);
        char operator()(int index) const;
        void addString(const std::string& str);
        MyString combine() const;
        const std::vector<MyString>& getData() const;
        const std::vector<MyString>& getBlocks() const;
        int totalLength() const;
        int size() const;
    };
    BlockString operator*(int multiplier, const BlockString& blockStr);
    BlockString operator*(int multiplier, const MyString& myStr);
    BlockString operator*(const MyString& myStr, int multiplier);
    BlockString operator+(const MyString& myStr, const MyString& myStr_1);
    BlockString operator+(const MyString& myStr, const BlockString& blockStr);
}

#endif // BlockString_HPP