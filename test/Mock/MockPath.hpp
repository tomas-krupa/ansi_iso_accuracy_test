/**
 * @file MockPath.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 13.08.2020
 *
 */

#pragma once

#include <FileSystem/Path.h>
#include <algorithm>

class MockPath
{
public:
  std::string _path;
  bool _exists;
  bool _isFile;

  mutable int _getCalledCount = 0;

  std::string get() const
  {
    _getCalledCount++;

    return _path;
  }

  mutable int getNameCalledCount;

  std::string GetName() const
  {
    getNameCalledCount++;

    size_t sep = _path.find_last_of("/");

    if (sep != std::string::npos) {
      return _path.substr(sep + 1, _path.size() - sep - 1);
    } else {
      return _path;
    }
  }

  std::string GetExtension() const
  {
    std::string fileName = GetName();

    size_t dot = fileName.find_last_of(".");

    if (dot != std::string::npos) {
      return fileName.substr(dot, fileName.length());
    } else {
      return "";
    }
  }

  bool isGetNameWithoutExtensionException;
  mutable int getNameWithoutExtensionCalledCount;

  std::string GetNameWithoutExtension() const
  {
    getNameWithoutExtensionCalledCount++;

    if (isGetNameWithoutExtensionException) {
      throw std::runtime_error("MockPath::GetNameWithoutExtension");
    }

    std::string fileName = GetName();

    size_t dot = fileName.find_last_of(".");

    if (dot != std::string::npos) {
      return fileName.substr(0, dot);
    } else {
      return fileName;
    }
  }

  mutable int getDirectoryCalledCount;

  std::string GetDirectory() const
  {
    getDirectoryCalledCount++;

    size_t sep = _path.find_last_of("/");
    return _path.substr(0, sep);
  }

  mutable int isExistsCalledCount;

  bool IsExists() const
  {
    isExistsCalledCount++;

    return _exists;
  }

  mutable int isFileCalledCount;

  bool IsFile() const
  {
    isFileCalledCount++;

    return _isFile;
  }

  mutable int isDirectoryCalledCount;

  bool IsDirectory() const
  {
    isDirectoryCalledCount++;

    return !IsFile();
  }

  explicit MockPath() { Reset(); }

  explicit MockPath(const char* p)
  {
    Reset();

    _path = p;
  }

  void Reset()
  {
    _exists = true;
    _isFile = true;
    _getCalledCount = 0;
    getNameCalledCount = 0;
    isGetNameWithoutExtensionException = false;
    getNameWithoutExtensionCalledCount = 0;
    getDirectoryCalledCount = 0;
    isExistsCalledCount = 0;
    isFileCalledCount = 0;
    isDirectoryCalledCount = 0;
  }

  virtual ~MockPath() = default;

private:
  MockPath(const MockPath&) = delete;
  MockPath(MockPath&&) = delete;
  MockPath& operator=(const MockPath&) = delete;
  MockPath& operator=(MockPath&&) = delete;
};

class UniqueMockPath : public Path
{
public:
  std::string Get() const noexcept { return _path->Get(); }

  std::string GetName() const { return _path->GetName(); }

  std::string GetExtension() const { return _path->GetExtension(); }

  std::string GetNameWithoutExtension() const
  {
    return _path->GetNameWithoutExtension();
  }

  std::string GetDirectory() const { return _path->GetDirectory(); }

  bool IsExists() const { return _path->IsExists(); }

  bool IsFile() const { return _path->IsFile(); }

  bool IsDirectory() const { return _path->IsDirectory(); }

  explicit UniqueMockPath(const std::shared_ptr<MockPath>& p)
    : _path(p)
  {}

  virtual ~UniqueMockPath() = default;

private:
  std::shared_ptr<MockPath> _path;

  UniqueMockPath(const UniqueMockPath&) = delete;
  UniqueMockPath(UniqueMockPath&&) = delete;
  UniqueMockPath& operator=(const UniqueMockPath&) = delete;
  UniqueMockPath& operator=(UniqueMockPath&&) = delete;
};

#endif
