#include "MyString.hpp"

namespace strings {

    MyString::MyString(const char* str) {
        if (str == nullptr) {
            throw std::invalid_argument("Input string is null");
        }
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    MyString::MyString(const std::string& str) {
        length = str.size();
        data = new char[length + 1];
        std::copy(str.begin(), str.end(), data);
        data[length] = '\0'; 
    }

    MyString::MyString() {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    }
    MyString::MyString(const MyString& other) {
        if (other.data == nullptr) {
            throw std::invalid_argument("Other string data is null");
        }
        length = other.length;
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    MyString::~MyString() {
        delete[] data;
    }
    
    const char* MyString::getData() const { return data; }
    int MyString::getLength() const { return length; }

    MyString& MyString::operator=(const MyString& other) {
        if (this != &other) {
            delete[] data; 

            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
    
}
