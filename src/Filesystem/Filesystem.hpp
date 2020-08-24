/**
 * @file Filesystem.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <memory>
#include <string>

#include <string>

#include "File.hpp"

class Path;

namespace filesystem {
enum class WriteMode
{
  Append,
  Truncate,
  Read
};
}
/**
 * @brief Filesystem
 *
 * Defines basic filesystem operations.
 */
template<class TDerivedFilesystem, class TDirectory, class TDerivedFile>
class Filesystem
{
public:
  std::unique_ptr<TDerivedFile> createInputFile(const std::string& path) const
  {
    return static_cast<TDerivedFilesystem*>(this)->createInputFile(path);
  }

  std::unique_ptr<TDerivedFile> createOutputFile(const std::string& path,
                                                 filesystem::WriteMode mode) const
  {
    return static_cast<TDerivedFilesystem*>(this)->createOutputFile(path, mode);
  }

  std::unique_ptr<TDirectory> createDirectory(const std::string& path) const
  {
    return static_cast<TDerivedFilesystem*>(this)->createDirectory(path);
  }

  bool exists(const std::string& path) const
  {
    return static_cast<TDerivedFilesystem*>(this)->exists(path);
  }

  /*  std::unique_ptr<Path> createPath(const std::string& path)
    {
      return static_cast<TDerivedFilesystem*>(this)->createPath(path);
    }*/

  virtual ~Filesystem() = default;

  Filesystem(const Filesystem&) = delete;
  Filesystem(Filesystem&&) = delete;
  Filesystem& operator=(const Filesystem&) = delete;
  Filesystem& operator=(Filesystem&&) = delete;

protected:
  Filesystem() = default;
};