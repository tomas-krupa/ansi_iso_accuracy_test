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
#include <CSV/CSVReader.hpp>
#include <Filesystem/BoostMMFile.hpp>
#include <Filesystem/File.hpp>
#include <ciso646>
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Storage
 *
 * Simple implementation of storage facade.
 */
template<typename TFile>
class FileStorage final : public Storage<FileStorage<TFile>, std::vector<unsigned char>, std::string>
{
public:
  void store(std::vector<unsigned char>  const& data)
  {
    store({reinterpret_cast<const char*>(data.data()),reinterpret_cast<const char*>(data.data()) + data.size()}); //TODO optimize
  }

  void store(std::string const& data)
  {
          if (not file->isOpen()) {
      file->open();
    }
    file->write(data + '\n');
  }

    std::vector<unsigned char> load(std::string const& id)
  {
    if (not file->isOpen()) {
      file->open();
    }
    return file->readToVec();
  }
/*

  template<typename TRecord>
  void loadRecords(const std::map<int,std::string>& pairs) {
      std::vector<TRecord> records;
      records.reserve(pairs.size());
      for (const auto &pair : pairs) {
          records.emplace_back(pair.first, file.read());
      }
      return records;
  }

   std::map<int,std::string> loadPairs(const std::string& path){
            const auto fileStream = file.readToStream();

            CSVReader<int,std::string> csvReader{fileStream};
            return csvReader.readToMap();
  }
*/

  explicit FileStorage(std::unique_ptr<TFile>&& f)
    : file(std::forward<std::unique_ptr<TFile>>(f))
  {
      file->open(); //TODO check open file
  }

  ~FileStorage() { file->close(); }

  FileStorage(const FileStorage&) = delete;
  FileStorage(FileStorage&&) = delete;
  FileStorage& operator=(const FileStorage&) = delete;
  FileStorage& operator=(FileStorage&&) = delete;

private:
  std::unique_ptr<TFile> file;
};
