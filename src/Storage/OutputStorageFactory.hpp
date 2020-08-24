/**
 * @file OutputStorageFactory.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include "StorageFactory.hpp"

/**
 * @brief OutputStorageFactory
 *
 * Simple factory for creating instances of Output Storage.
 */
template<class TFileSystem, class TConfiguration, class TStorage>
class OutputStorageFactory final : public StorageFactory<OutputStorageFactory<TFileSystem, TConfiguration, TStorage>,TStorage>
{
public:
  std::unique_ptr<TStorage> create(storage::Identifier const& fileName) const
  {
    auto file = _filesystem.createOutputFile(fileName,filesystem::WriteMode::Truncate);
    return std::make_unique<TStorage>(std::move(file));
  }

  OutputStorageFactory(const TConfiguration& cfg, TFileSystem& fs) :
    _configuration(cfg),
    _filesystem(fs)
{}

  virtual ~OutputStorageFactory() = default;

  OutputStorageFactory(const OutputStorageFactory&) = delete;
  OutputStorageFactory(OutputStorageFactory&&) = delete;
  OutputStorageFactory& operator=(const OutputStorageFactory&) = delete;
  OutputStorageFactory& operator=(OutputStorageFactory&&) = delete;

protected:
  OutputStorageFactory() = default;
private:
  const TConfiguration& _configuration;
  TFileSystem&  _filesystem;
};
