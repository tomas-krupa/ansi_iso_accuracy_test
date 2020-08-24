/**
 * @file Storage.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include <string>

/**
 * @brief Storage
 *
 * Storage facade providing a simple interface to hold a data.
 */
template<class TDerived, class TRecord, class TIdentifier>
class Storage
{
public:

  void store(const TRecord &record)  {
    static_cast<TDerived*>(this)->store(record);
  }

  std::unique_ptr<TRecord> load(const TIdentifier &id)
  {
    return static_cast<TDerived*>(this)->load(id);
  }

  virtual ~Storage() = default;

  Storage(const Storage&) = delete;
  Storage(Storage&&) = delete;
  Storage& operator=(const Storage&) = delete;
  Storage& operator=(Storage&&) = delete;

protected:
  Storage() = default;
};
