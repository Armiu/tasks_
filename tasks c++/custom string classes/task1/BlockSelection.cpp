#include <BlockSelection.hpp>

namespace strings {

    BlockSelection::BlockSelection(const std::initializer_list<std::vector<int>>& initList) {
        for (const auto& sel : initList) {
            selections.push_back(Selection(sel));
        }
    }

    BlockSelection::BlockSelection() {}

    BlockString BlockSelection::operator()(const std::string& str) const {
        BlockString result;
        for (const auto& selection : selections) {
            std::string newStr;
            for (int index : selection.getIndices()) {  // Assume Selection has a getIndices method
                if (index < str.size()) {
                    newStr += str[index];
                }
            }
            result.addString(newStr);  // Assume BlockString has an addString method
        }
        return result;
    }


    BlockSelection::BlockSelection(const std::vector<std::vector<int>>& v) {
        for (const auto& vec : v) {
            selections.push_back(Selection(vec));
        }
    }

    BlockSelection::BlockSelection(const std::vector<Selection>& selections) : selections(selections) {}
    
    BlockString BlockSelection::operator()(const BlockString& blockStr) const {
        std::vector<MyString> result;
        MyString combinedStr = blockStr.combine(); // combine all strings in blockStr
        for (const auto& selection : selections) {
            result.push_back(selection(combinedStr));
        }
        return BlockString(result);
    }

    BlockSelection BlockSelection::operator*(int times) const {
        if (times < 0) {
            throw std::invalid_argument("Multiplier cannot be negative");
        }
        std::vector<Selection> newSelections;
        for (int i = 0; i < times; ++i) {
            newSelections.insert(newSelections.end(), selections.begin(), selections.end());
        }
        return BlockSelection(newSelections);
    }

    BlockSelection BlockSelection::operator+(const BlockSelection& other) const {
        if (other.selections.empty()) {
            throw std::invalid_argument("Cannot add empty BlockSelection");
        }
        std::vector<Selection> newSelections = selections;
        newSelections.insert(newSelections.end(), other.selections.begin(), other.selections.end());
        return BlockSelection(newSelections);
    }

    
    const Selection& BlockSelection::operator[](int index) const {
        if (index < 0 || index >= selections.size()) {
            throw std::out_of_range("Index out of range");
        }
        return selections[index];
    }

    Selection& BlockSelection::operator[](int index) {
        if (index < 0 || index >= selections.size()) {
            throw std::out_of_range("Index out of range");
        }
        return selections[index];
    }

    BlockSelection::BlockSelection(const Selection& selection) {
            selections.push_back(selection);
        }

    BlockSelection BlockSelection::operator()(const BlockSelection& other) const {
        BlockSelection result;
        for (const auto& selection : selections) {
            BlockSelection currentResult = selection(other);
            result = result + currentResult;
        }
        return result;
    }

    int& BlockSelection::operator()(int n)
    {
        int count = 0, index = 0;
        while(1)
        {
            if(selections[index].size() + count > n)
            {
                return selections[index][n-count];
            }
            else
            {
                count+= selections[index].size();
                ++index;
            }
        }
        throw std::out_of_range("Index out of range");
    }
    int BlockSelection::operator()(int n) const
    {
        int count = 0, index = 0;
        while(1)
        {
            if(selections[index].size() + count > n)
            {
                return selections[index][n-count];
            }
            else
            {
                count+= selections[index].size();
                ++index;
            }
        }
        throw std::out_of_range("Index out of range");
    }
    
    const std::vector<Selection>& BlockSelection::getSelections() const {
        return selections;
    }

    int BlockSelection::size() const { return selections.size(); }

    int BlockSelection::totalLength() const {
        int total = 0;
        for (const auto& selection : selections) {
            total += selection.size();
        }
        return total;
    }
}
    strings::BlockSelection strings::operator*(int multiplier, const strings::BlockSelection& blockSel) {
        std::vector<strings::Selection> result;
        for (int i = 0; i < multiplier; ++i) {
            result.insert(result.end(), blockSel.getSelections().begin(), blockSel.getSelections().end());
        }
        return strings::BlockSelection(result);
    }

    strings::BlockSelection strings::operator*(int multiplier, const strings::Selection& sel) {
        strings::BlockSelection blockSel(std::vector<strings::Selection>{sel});
        return multiplier * blockSel;
    }

    strings::BlockSelection strings::operator*(const strings::Selection& sel, int multiplier) {
        strings::BlockSelection blockSel(std::vector<strings::Selection>{sel});
        return multiplier * blockSel;
    }

    strings::BlockSelection strings::operator+(const strings::Selection& sel, const strings::Selection& sel_1) {
        strings::BlockSelection blockSel(std::vector<strings::Selection>{sel, sel_1});
        return blockSel;
    }
    strings::BlockSelection strings::operator+(const strings::Selection& sel, const strings::BlockSelection& blockSel) {
        std::vector<strings::Selection> newData = blockSel.getSelections();
        newData.insert(newData.begin(), sel);
        return strings::BlockSelection(newData);
    }

    