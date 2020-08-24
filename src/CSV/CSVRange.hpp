/**
 * @file CSVRange.hpp
 *
 * @remarks https://stackoverflow.com/a/1120224
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 20.08.2020
 *
 */

#include "CSVIterator.hpp"

#pragma once

class CSVRange
{
    std::istream&   stream;
    public:
        CSVRange(std::istream& str)
            : stream(str)
        {}
        CSVIterator begin() const {return CSVIterator{stream};}
        CSVIterator end()   const {return CSVIterator{};}
};