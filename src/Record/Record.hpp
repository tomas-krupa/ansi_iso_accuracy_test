/**
 * @file Record.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 19.08.2020
 *
 */

#pragma once

/**
 * @brief Record
 *
 * Record is a simple interface to hold and match data.
 */
template <class TDerived, class TScore>
class Record
{
public:
    TScore match(const Record& rec){
                return static_cast<TDerived*>(this)->match(rec);
    };
    int getId() const {
        return static_cast<TDerived*>(this)->getId();
    };

    virtual ~Record() = default;

  Record(const Record&) = delete;
  Record(Record&&) = delete;
  Record& operator=(const Record&) = delete;
  Record& operator=(Record&&) = delete;

protected:
  Record() = default;
};
