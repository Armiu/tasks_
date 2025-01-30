#ifndef SELECTION_HPP
#define SELECTION_HPP
#include <vector>
#include "MyString.hpp"
#include "BlockString.hpp"
#include "BlockSelection.hpp"
namespace strings {
    class BlockSelection;
    class Selection {
        std::vector<int> selection;
    public:
        Selection();
        Selection(int num);
        Selection(const std::vector<int>& selection);
        MyString operator()(const MyString& str) const ;
        int operator[](int n) const;
        int & operator[](int n);
        Selection operator()(const BlockSelection& blockSel) const;
        MyString operator()(const BlockString& blockStr) const;
        const std::vector<int>& getIndices() const;
        int size() const;
    };
}
#endif // SELECTION_HPP
