#include "BlockString.hpp"

namespace strings{
    BlockString::BlockString(const MyString& str) : data({str}) {}

    BlockString::BlockString() {}

    BlockString::BlockString(const std::vector<MyString>& blocks) : data(blocks) {}

    void BlockString::addString(const std::string& str) {
        if (str.empty()) {
            throw std::invalid_argument("Input string is empty");
        }
        data.push_back(MyString(str));  
    }

    BlockString BlockString::operator+(const BlockString& other) const {
        BlockString result(*this);
        result.data.insert(result.data.end(), other.data.begin(), other.data.end());
        return result;
    }

    BlockString BlockString::operator*(int value) const {
        if (value < 0) {
            throw std::invalid_argument("Multiplier is negative");
        }
        std::vector<MyString> result;
        for (int i = 0; i < value; ++i) {
            result.insert(result.end(), data.begin(), data.end());
        }
        return BlockString(result);
    }

    const std::vector<MyString>& BlockString::getBlocks() const {
        return data;
    }
    
    const MyString& BlockString::operator[](int index) const {
        if (index < 0 || index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    MyString& BlockString::operator[](int index) {
        if (index < 0 || index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    
    char BlockString::operator()(int index) const {
        if (index < 0 || index >= totalLength()) {
            throw std::out_of_range("Index out of range");
        }
        int totalLength = 0;
        for (const auto& str : data) {
            if (totalLength + str.getLength() > index) {
                return str.getData()[index - totalLength];
            }
            totalLength += str.getLength();
        }
        throw std::out_of_range("Index out of range");
    }

    const std::vector<MyString>& BlockString::getData() const { return data; }

    BlockString::BlockString(std::initializer_list<std::string> initList) {
        for (const auto& str : initList) {
            data.push_back(MyString(str.c_str()));
        }
    }

    MyString BlockString::combine() const {
        std::string combined;
        for (const auto& str : data) {
            combined += str.getData();
        }
        return MyString(combined.c_str());
    }

    int BlockString::totalLength() const {
        int total = 0;
        for (const auto& line : data) {
            total += line.getLength();
        }
        return total;
    }
    int BlockString::size() const { return data.size(); }
}

    strings::BlockString strings::operator*(int multiplier, const strings::BlockString& blockStr) {
        std::vector<strings::MyString> result;
        for (int i = 0; i < multiplier; ++i) {
            result.insert(result.end(), blockStr.getData().begin(), blockStr.getData().end());
        }
        return strings::BlockString(result);
    }

    strings::BlockString strings::operator*(int multiplier, const strings::MyString& myStr) {
        strings::BlockString blockStr(myStr);
        return blockStr * multiplier;
    }

    strings::BlockString strings::operator*(const strings::MyString& myStr, int multiplier) {
        strings::BlockString blockStr(myStr);
        return blockStr * multiplier;
    }

    strings::BlockString strings::operator+(const strings::MyString& myStr, const strings::MyString& myStr_1) {
        strings::BlockString blockStr(std::vector<strings::MyString>{myStr, myStr_1});
        return blockStr;
    }

    strings::BlockString strings::operator+(const MyString& myStr, const BlockString& blockStr) {
        std::vector<strings::MyString> newData = blockStr.getData();
        newData.insert(newData.begin(), myStr);
        return strings::BlockString(newData);
    }
    
