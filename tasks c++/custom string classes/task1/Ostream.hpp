#include<iostream>
#include "MyString.hpp"
#include "BlockString.hpp"
#include "Selection.hpp"
#include "BlockSelection.hpp"
namespace strings{
    
    enum f {
        array,
        plain
    };
    class output
    {   
        f format;
        std::ostream &a;
    public:
        output(std::ostream&);
        output& operator<<(f); 
        template <typename T> output& operator<<(const T& t)
        {
            a<<t;
            return *this;
        }
        output& operator<<(const MyString &s);
        output& operator<<(const BlockString &bl);
        output& operator<<(const Selection&s);
        output& operator<<(const BlockSelection &bl);
    };
    inline output cout = std::cout;
}