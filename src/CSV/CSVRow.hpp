/**
 * @file CSVRow.hpp
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

#include <string>
#include <vector>
#include <istream>

class CSVRow
{
    public:
        std::string operator[](std::size_t index) const
        {
            return std::string(&_line[_data[index] + 1], _data[index + 1] -  (_data[index] + 1));
        }
        
        std::size_t size() const
        {
            return _data.size() - 1;
        }
        
        void readNextRow(std::istream& str)
        {
            std::getline(str, _line);

            _data.clear();
            _data.emplace_back(-1);
            std::string::size_type pos = 0;
            while(std::string::npos != (pos = _line.find(',', pos)))
            {
                _data.emplace_back(pos++);
            }
            // This checks for a trailing comma with no data after it.
            pos   = _line.size();
            _data.emplace_back(pos);
        }
        
    private:
        std::string         _line;
        std::vector<int>    _data; //TODO TElement
};

std::istream& operator>>(std::istream& str, CSVRow& data)
{
    data.readNextRow(str);
    return str;
}   