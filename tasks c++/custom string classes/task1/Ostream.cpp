#include"Ostream.hpp"

namespace strings
{
    output::output(std::ostream&b):a(b){}

    output& output::operator<<(f r)
    {
        format = r;
        return *this;
    }

    output& output::operator<<(const MyString &s) {
        a << s.getData();
        return *this;
    }

    output& output::operator<<(const BlockString &bl) {
        if (bl.size() == 0) {
            throw std::invalid_argument("BlockString is empty");
        }
        if (format == array) {
            a<<"{";
            for(int i = 0;i<bl.size()-1;++i) {
                (*this)<< '"' << bl[i]<< '"' <<", ";
            }
            (*this)<< '"' << bl[bl.size()-1]<< '"' <<"}";
        }
        if (format == plain) {
            for(int i = 0;i<bl.size();++i) {
                (*this)<<bl[i];
            }
        }
        return *this;
    }

    output& output::operator<<(const Selection& s) {
        if (s.size() == 0) {
            throw std::invalid_argument("Selection is empty");
        }
        a<<"{";
        for(int i = 0;i<s.size()-1;++i) {
            a<<s[i]<<", ";
        }
        a<<s[s.size()-1]<<"}";
        return *this;
    }
    output& output::operator<<(const BlockSelection& bl) {
        if (bl.size() == 0) {
            throw std::invalid_argument("BlockSelection is empty");
        }
        a<<"{";
        for(int i = 0; i < bl.size()-1; ++i) {
            (*this)<<bl[i]<<", ";
        }
        (*this)<<bl[bl.size()-1]<<"}";
        return *this;
    }
}

