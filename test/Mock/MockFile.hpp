/**
 * @file MockFile.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include <Filesystem/File.hpp>
#include <algorithm>
#include <boost/filesystem/path.hpp>

/**
 * @brief MockFile
 *
 * @ingroup g_File
 *
 * Mock implementation of File operations.
 *
 */
template<typename TPath>
class MockFile final : public File<MockFile<TPath>>
{
public:
  TPath _path;
  std::string _content;
  int _mode;

  bool isOpen() const noexcept
  {
    return 0 < (_openCalledCount - _closeCalledCount);
  }

  mutable int _getPathCalledCount = 0;
  const TPath& getPath() const noexcept
  {
    ++_getPathCalledCount;

    return _path;
  }

  int _openCalledCount = 0;
  void open() { ++_openCalledCount; }

  int _closeCalledCount = 0;
  void close() { ++_closeCalledCount; }

  int _writeCalledCount = 0;
  bool _isWriteException = false;
  void write(std::string const&)
  {
    ++_writeCalledCount;

    if (_isWriteException) {
      throw std::runtime_error("MockFile::Write");
    }
  }

  mutable bool _isReadToException = false;
  mutable int _readCalledCount = 0;
  void readTo(std::vector<uint8_t>& output) const// TODO return value
  {
    ++_readCalledCount;

    if (_isReadToException) {
      throw std::runtime_error("MockFile::ReadTo");
    }

    std::copy(_content.cbegin(), _content.cend(), std::back_inserter(output));
  }

  unsigned int readTo(std::vector<uint8_t>& v,
                      unsigned int from,
                      unsigned int len) const// TODO remove
  {
    ++_readCalledCount;

    if (_isReadToException) {
      throw std::runtime_error("MockFile::ReadTo partial");
    }

    auto b = _content.begin() + from;

    if (b > _content.end()) {
      b = _content.end();
    }

    auto e = b + len;

    if (e > _content.end()) {
      e = _content.end();
    }

    std::copy(b, e, std::back_inserter(v));

    return e - b;
  }

  explicit MockFile(const std::string& path, int mode)
    : _path(path)
    , _mode(mode){};

  ~MockFile() = default;

  MockFile(const MockFile&) = delete;
  MockFile(MockFile&&) = delete;
  MockFile& operator=(const MockFile&) = delete;
  MockFile& operator=(MockFile&&) = delete;
};