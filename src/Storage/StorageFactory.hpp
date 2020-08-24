/**
 * @file StorageFactory.hpp
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

namespace storage{
    using Identifier = std::string;
}
/**
 * @brief StorageFactory
 *
 * Simple factory for creating instances of Storage.
 */
template<class TDerived, class TStorage>
class StorageFactory
{
public:
  std::unique_ptr<TStorage> create(storage::Identifier const& fileName) const
  {
    return static_cast<const TDerived*>(this)->create(fileName);
  }

  virtual ~StorageFactory() = default;

  StorageFactory(const StorageFactory&) = delete;
  StorageFactory(StorageFactory&&) = delete;
  StorageFactory& operator=(const StorageFactory&) = delete;
  StorageFactory& operator=(StorageFactory&&) = delete;

protected:
  StorageFactory() = default;
};
