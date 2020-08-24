/**
 * @file BiometricStorage.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include <string>
#include <Record/BiometricRecord.hpp>
#include "FileStorage.hpp"

struct IdPathPair{
    const int id;
    const std::string path;
};

/**
 * @brief BiometricStorage
 *
 * BiometricStorage providing a simple interface to hold and provide biometric records.
 */
using TResult = BiometricResult<BiometricRecord>;
template<class TFile>
class BiometricStorage final : public Storage<BiometricStorage<TFile>, BiometricRecord, TResult>
{
public:

  void store(const BiometricRecord &record)  {
//        const auto file = fs.createInputFile(std::to_string(record.id)); //TODO move to filestorage
//        FileStorage<TFile>{file}.store(record.data);
        _records.emplace_back(record.id,record.data);
  }

  std::shared_ptr<BiometricRecord> load(const int &id){ //TOOD rename to get
      auto compareRecords = [&id](BiometricRecord const& rec) {
          return id == rec.getId();
      };
      const auto recordAtId = _records.at(id);
      if(compareRecords(recordAtId)){
          return recordAtId;
      }
      const auto it = std::find(_records.cbegin(), _records.cend(), compareRecords);
      if ( _records.cend() != it ){
          return *it;
      }
          return nullptr;
      }
      BiometricStorage( ) = default;
  virtual ~BiometricStorage() = default;

  BiometricStorage(const BiometricStorage&) = delete;
  BiometricStorage(BiometricStorage&&) = delete;
  BiometricStorage& operator=(const BiometricStorage&) = delete;
  BiometricStorage& operator=(BiometricStorage&&) = delete;
private:
    std::vector<BiometricRecord> _records;
};
