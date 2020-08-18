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

#include <memory>
#include <string>

class Storage;

/**
 * @brief Storage
 *
 * Simple factory for creating instances of Storage.
 */
class StorageFactory
{
public:
  std::unique_ptr<Storage> create(std::string const& fileName)
  {
    static_cast<TDerived*>(this)->create(std::forward<std::string>(fileName));
  }

  virtual ~StorageFactory() = default;

  StorageFactory(const StorageFactory&) = delete;
  StorageFactory(StorageFactory&&) = delete;
  StorageFactory& operator=(const StorageFactory&) = delete;
  StorageFactory& operator=(StorageFactory&&) = delete;

protected:
  StorageFactory() = default;
};
