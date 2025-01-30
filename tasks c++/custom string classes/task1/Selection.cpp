#include "Selection.hpp"

namespace strings {
    Selection::Selection(const std::vector<int>& selection) : selection(selection) {}

    Selection::Selection() {}

    MyString Selection::operator()(const MyString& str) const {
        char* result = new char[selection.size() + 1];
        for (size_t i = 0; i < selection.size(); ++i) {
            int index = selection[i];
            if (index >= 0 && index < str.getLength()) {
                result[i] = str.getData()[index];
            } else {
                result[i] = '?';
            }
        }
        result[selection.size()] = '\0';
        MyString res(result);
        delete[] result;
        return res;
    }

    Selection::Selection(int num) {
        selection.push_back(num);
    }

    Selection Selection::operator()(const BlockSelection &blockSel) const {
        Selection res;
        for(int i = 0; i < selection.size(); ++i) {
            if(selection[i] > blockSel.totalLength() || selection[i] < 0) {
                    res.selection.push_back(-1);
            }
            else {
                res.selection.push_back(blockSel(selection[i]));
            }
        }
        return res;
    }
    
    int Selection::operator[](int n) const {
        if (n < 0 || n >= selection.size()) {
            throw std::out_of_range("Index out of range");
        }
        return selection.at(n);
    }

    int & Selection::operator[](int n) {
        if (n < 0 || n >= selection.size()) {
            throw std::out_of_range("Index out of range");
        }
        return selection.at(n);
    }

    MyString Selection::operator()(const BlockString& blockStr) const {
        if (blockStr.totalLength() < selection.size()) {
            throw std::length_error("BlockString is too short for selection");
        }
        char* result = new char[selection.size() + 1];
        for (size_t i = 0; i < selection.size(); ++i) {
            int index = selection[i];
            if (index < 0 || index >= blockStr.totalLength()) {
                result[i] = -1;
            } else {
                result[i] = blockStr(index);
            }
        }
        result[selection.size()] = '\0';
        MyString res(result);
        delete[] result;
        return res;
    }

    int Selection::size() const { return selection.size(); }

    const std::vector<int>& Selection::getIndices() const {
        return selection;
    }
}
