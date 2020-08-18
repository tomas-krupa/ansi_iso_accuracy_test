/**
 * @file Directory.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <functional>
#include <memory>

/**
 * @brief Directory
 *
 * @ingroup g_Directory
 *
 * Defines basic operations over directories.
 */
template<class TDerived>
class Directory
{
public:
  bool exists() const { return static_cast<TDerived*>(this)->exists(); };
  void create() { static_cast<TDerived*>(this)->create(); };

  virtual ~Directory() = default;

  Directory(const Directory&) = delete;
  Directory(Directory&&) = delete;
  Directory& operator=(const Directory&) = delete;
  Directory& operator=(Directory&&) = delete;

protected:
  Directory() = default;
};
