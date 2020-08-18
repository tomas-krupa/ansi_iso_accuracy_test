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
 * Storage facade providing a simple interface to store data.
 */
template<class TDerived>
class Storage
{
public:
  void store(std::string&& data)
  {
    static_cast<TDerived*>(this)->store(std::forward<std::string>(data));
  }

  virtual ~Storage() = default;

  Storage(const Storage&) = delete;
  Storage(Storage&&) = delete;
  Storage& operator=(const Storage&) = delete;
  Storage& operator=(Storage&&) = delete;

protected:
  Storage() = default;
};
