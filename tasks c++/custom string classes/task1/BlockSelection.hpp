#ifndef BLOCKSELECTION_HPP
#define BLOCKSELECTION_HPP
#include <iostream>
#include "Selection.hpp"
#include "BlockString.hpp"
#include "MyString.hpp"
#include <vector>

namespace strings{
    class Selection;
    class BlockSelection {
        std::vector<Selection> selections;
    public:
        BlockSelection();
        BlockSelection(const std::initializer_list<std::vector<int>>& initList);
        BlockSelection(const Selection& selection);
        BlockSelection(const std::vector<std::vector<int>>& v);
        BlockSelection(const std::vector<Selection>& selections);
        BlockString operator()(const std::string& str) const;
        int& operator()(int n);
        int operator()(int n) const;
        BlockSelection operator*(int times) const;
        BlockSelection operator+(const BlockSelection& other) const;
        const Selection& operator[](int index) const;
        Selection& operator[](int index);
        BlockSelection operator()(const BlockSelection& other) const;
        BlockString operator()(const BlockString& blockStr) const;
        const std::vector<Selection>& getSelections() const;
        int size() const;
        int totalLength() const;
    };
    BlockSelection operator*(int multiplier, const BlockSelection& blockSel);
    BlockSelection operator*(int multiplier, const Selection& sel);
    BlockSelection operator*(const Selection& sel, int multiplier);
    BlockSelection operator+(const Selection& sel, const Selection& sel_1);
    BlockSelection operator+(const Selection& sel, const BlockSelection& blockSel);
}

#endif // BLOCKSELECTION_HPP