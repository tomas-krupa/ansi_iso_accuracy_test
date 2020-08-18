/**
 * @file FileStorage.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include "Storage.hpp"
#include <Filesystem/BoostMMFile.hpp>
#include <Filesystem/File.hpp>
#include <ciso646>
#include <memory>

/**
 * @brief Storage
 *
 * Simple implementation of storage facade.
 */
template<typename TFile>
class FileStorage final : public Storage<FileStorage<TFile>>
{
public:
  void store(std::string&& str)
  {
    if (not file->isOpen()) {
      file->open();
    }
    file->write(str + '\n');
  }

  explicit FileStorage(std::unique_ptr<TFile>&& f)
    : file(std::forward<std::unique_ptr<TFile>>(f))
  {}

  ~FileStorage() { file->close(); }

  FileStorage(const FileStorage&) = delete;
  FileStorage(FileStorage&&) = delete;
  FileStorage& operator=(const FileStorage&) = delete;
  FileStorage& operator=(FileStorage&&) = delete;

private:
  std::unique_ptr<TFile> file;
};
