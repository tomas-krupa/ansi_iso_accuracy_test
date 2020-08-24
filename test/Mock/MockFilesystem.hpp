/**
 * @file MockFilesystem.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 12.08.2020
 *
 */

#pragma once

#include "MockDirectory.hpp"
#include "MockFile.hpp"

#include <Filesystem/BoostMMFile.hpp>
#include <Filesystem/Filesystem.hpp>
#include <map>
#include <memory>
#include <vector>

/**
 * @brief MockFilesystem
 *
 * @ingroup g_Filesystem
 *
 * Mock implementation of Filesystem operations.
 *
 */
using TPath = boost::filesystem::path;
using TMockFile = MockFile<TPath>;
using TMockDirectory = MockDirectory<TPath>;

class MockFileSystem final
  : public Filesystem<MockFileSystem, TMockFile, TMockDirectory>
{
public:
  mutable std::map<std::string, std::vector<std::string>> _directories;
  mutable std::map<std::string, std::shared_ptr<TMockFile>> _files;
  mutable std::map<std::string, std::shared_ptr<TMockDirectory>> _mockDirectories;
  mutable std::map<std::string, std::string> _filesContent;
  mutable std::map<std::string, bool> _existsAttributes;
  mutable std::map<std::string, bool> _browseExceptions;
  mutable std::map<std::string, bool> _browseNonStdExceptions;

  std::unique_ptr<TMockFile> createInputFile(const std::string& path) const  noexcept
  {
    return std::unique_ptr<TMockFile>(
      new TMockFile{ path, (int)filesystem::WriteMode::Read });
  }

  std::unique_ptr<TMockFile> createFile(const std::string& path) const noexcept
  {
    return createMockFile(path);
  }

  //        std::unique_ptr<Path> createPath(const std::string& path) noexcept
  //        {
  //            return std::make_unique<MockPath>(path);
  //        }

  std::unique_ptr<TMockDirectory> createDirectory (
    std::string const& path) const noexcept
  {
    return createMockDirectory(path);
  }

  bool exists(const std::string& path) const
  {
    if (_existsAttributes.find(path) != _existsAttributes.end()) {
      return _existsAttributes[path];
    }

    return false;
  }

  MockFileSystem() = default;
  virtual ~MockFileSystem() = default;
  MockFileSystem(const MockFileSystem&) = delete;
  MockFileSystem& operator=(const MockFileSystem&) = delete;

private:
  bool isDirectory(const std::string& path) const
  {
    return (_directories.find(path) != _directories.end());
  }

  bool isFile(const std::string& path)const { return not isDirectory(path); }

  bool isExists(const std::string& path)const
  {
    if (_existsAttributes.find(path) != _existsAttributes.end()) {
      return _existsAttributes[path];
    }

    return true;
  }

  bool isBrowseException(const std::string& path) const
  {
    if (_browseExceptions.find(path) != _browseExceptions.end()) {
      return _browseExceptions[path];
    }

    return false;
  }

  bool isBrowseNonStdException(const std::string& path) const
  {
    if (_browseNonStdExceptions.find(path) != _browseNonStdExceptions.end()) {
      return _browseNonStdExceptions[path];
    }

    return false;
  }

  std::unique_ptr<TMockFile> createMockFile(const std::string& path) const
  {
    auto file = std::unique_ptr<TMockFile>();
    // _files[path] = file;
    _existsAttributes[path] = true;

    //            file->_path.path = path;
    //            file->_path.isFile = isFile(path);
    //            file->_path.isExists = isExists(path);

    if (_filesContent.find(path) != _filesContent.end()) {
      file->_content = _filesContent[path];
    }

    return std::move(file);
  }

  std::unique_ptr<TMockDirectory> createMockDirectory(const std::string& path) const
  {
    auto dir = std::unique_ptr<TMockDirectory>();
    //_mockDirectories[path] = dir;
    _existsAttributes[path] = true;
    //            dir->path.path = path;
    //            dir->path.isFile = isFile(path);
    //            dir->path.isExists = isExists(path);
    //            dir->_isBrowseException = isBrowseException(path);
    //          dir->_isBrowseNonStdException = isBrowseNonStdException(path);

    return std::move(dir);
  }
};
