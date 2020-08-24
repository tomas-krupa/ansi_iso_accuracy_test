/**
 * @file CSVIterator.hpp
 *
 * @remarks https://stackoverflow.com/a/1120224
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 20.08.2020
 *
 */

#pragma once

#include "CSVRow.hpp"

class CSVIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = CSVRow;
    using difference_type = std::size_t;
    using pointer = CSVRow *;
    using reference = CSVRow &;

    CSVIterator(std::istream &str) : _str(str.good() ? &str : nullptr) { ++(*this); }

    CSVIterator() : _str(NULL) {}

    // Pre Increment
    CSVIterator &operator++() {
        if (_str) { if (not((*_str) >> _row)) { _str = nullptr; }}
        return *this;
    }

    // Post increment
    CSVIterator operator++(int) {
        CSVIterator tmp(*this);
        ++(*this);
        return tmp;
    }

    CSVRow const &operator*() const { return _row; }

    CSVRow const *operator->() const { return &_row; }

    bool operator==(CSVIterator const &rhs) {
        return ((this == &rhs) || ((this->_str == nullptr) && (rhs._str == nullptr)));
    }

    bool operator!=(CSVIterator const &rhs) { return not((*this) == rhs); }

private:
    std::istream *_str;
    CSVRow _row;
};