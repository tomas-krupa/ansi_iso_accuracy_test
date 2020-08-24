/**
 * @file File.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <fstream>
#include <utility>
#include <vector>

class Path;

/**
 * @brief File
 *
 * Defines basic file operations and attributes.
 */
template<class TDerived>
class File
{
public:
  void open() { static_cast<TDerived*>(this)->open(); }

  void close() { static_cast<TDerived*>(this)->close(); }

  void write(const std::string& data) { static_cast<TDerived*>(this)->write(data); }

  std::vector<unsigned char> read() { return static_cast<TDerived*>(this)->read(); }

  bool isOpen() { return static_cast<TDerived*>(this)->isOpen(); }

  const Path& getPath() const noexcept
  {
    static_cast<TDerived*>(this)->getPath();
  }

  virtual ~File() = default;

  File(const File&) = delete;
  File(File&&) = delete;
  File& operator=(const File&) = delete;
  File& operator=(File&&) = delete;

protected:
  File() = default;
};