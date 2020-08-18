/**
 * @file BoostFilesystem.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include "BoostMMFile.hpp"

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <memory>

#include "Directory.hpp"
#include "File.hpp"
#include "Filesystem.hpp"

#ifdef _WIN32
#undef CreateDirectory
#endif

/**
 * @brief BoostFilesystem
 *
 * Defines basic BoostFilesystem operations.
 */
template<class TDirectory, class TDerivedFile>
class BoostFilesystem final
  : public File<BoostFilesystem<TDirectory, TDerivedFile>>
{
public:
  std::unique_ptr<TDerivedFile> CreateInputFile(const std::string& path)
  {
    return static_cast<TDirectory*>(this)->CreateInputFile(path);
  }

  std::unique_ptr<TDerivedFile> createInputFile(const std::string& path)
  {
    namespace io = boost::iostreams;

    return std::make_unique<TDerivedFile>(
      path, (int)io::mapped_file_base::mapmode::readonly);
  }

  std::unique_ptr<TDerivedFile> createOutputFile(const std::string& path,
                                                 filesystem::WriteMode mode)
  {
    std::ios_base::openmode openMode(std::ios::out | std::ios::binary);

    auto addWriteMode = [](bool flag,
                           int positive,
                           int negative) { // no jump condition by alexandrescu
      return static_cast<std::ios::openmode>(
        (flag & static_cast<unsigned>(positive)) |
        (flag & static_cast<unsigned>(negative)));
    };

    openMode |= addWriteMode(
      mode == filesystem::WriteMode::Truncate, std::ios::trunc, std::ios::app);

    namespace io = boost::iostreams;

    return std::make_unique<TDerivedFile>(
      path, (int)io::mapped_file_base::mapmode::readwrite);
  }

  std::unique_ptr<TDirectory> createDirectory(const std::string& path)
  {
    namespace fs = boost::filesystem;
    if (fs::create_directory(path)) {
      return std::make_unique<TDirectory>(path);
    }
    return nullptr;
  }

  bool exists(const std::string& path)
  {
    return boost::filesystem::exists(path);
  }

  BoostFilesystem() = default;

  ~BoostFilesystem() = default;

  BoostFilesystem(const BoostFilesystem&) = delete;

  BoostFilesystem(BoostFilesystem&&) = delete;

  BoostFilesystem& operator=(const BoostFilesystem&) = delete;

  BoostFilesystem& operator=(BoostFilesystem&&) = delete;

private:
};