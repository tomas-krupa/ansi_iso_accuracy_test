/**
 * @file BoostDirectory.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 18.08.2020
 *
 */

#pragma once

#include "Directory.hpp"
#include <boost/filesystem.hpp>
#include <functional>
#include <memory>
/**
 * @brief BoostDirectory
 *
 * @ingroup g_Directory
 *
 * Defines basic operations over directories.
 */
template<typename TPath>
class BoostDirectory final : public Directory<BoostDirectory<TPath>>
{
public:
  bool exists() const { return _path.exists(); };
  void create() { boost::filesystem::create_directory(_path.string()); }

  BoostDirectory(TPath const& path)
    : _path(path){};
  ~BoostDirectory() = default;

  BoostDirectory(const BoostDirectory&) = delete;
  BoostDirectory(BoostDirectory&&) = delete;
  BoostDirectory& operator=(const BoostDirectory&) = delete;
  BoostDirectory& operator=(BoostDirectory&&) = delete;

private:
  const TPath _path;
};
