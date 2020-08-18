/**
 * @file MockDirectory.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 11.08.2020
 *
 */

#pragma once

#include <Filesystem/Directory.hpp>
#include <algorithm>
#include <boost/filesystem/path.hpp>

/**
 * @brief MockDirectory
 *
 * @ingroup g_Directory
 *
 * Mock implementation of basic operations over directories.
 *
 */
template<typename TPath>
class MockDirectory final : public Directory<MockDirectory<TPath>>
{
public:
  TPath _path;
  std::string _content;

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
      throw std::runtime_error("MockDirectory::Write");
    }
  }

  bool _isReadToException = false;
  int _readCalledCount = 0;
  void readTo(std::vector<uint8_t>& output) // TODO return value
  {
    ++_readCalledCount;

    if (_isReadToException) {
      throw std::runtime_error("MockDirectory::ReadTo");
    }

    std::copy(_content.cbegin(), _content.cend(), std::back_inserter(output));
  }

  unsigned int readTo(std::vector<uint8_t>& v,
                      unsigned int from,
                      unsigned int len) // TODO remove
  {
    ++_readCalledCount;

    if (_isReadToException) {
      throw std::runtime_error("MockDirectory::ReadTo partial");
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

  explicit MockDirectory(std::string path, int mode)
    : _path(std::move(path)){};

  /*
    void Reset() // TODO unncesery? so remove
    {
      _getPathCalledCount = 0;
      _openCalledCount = 0;
      _closeCalledCount = 0;
      _writeCalledCount = 0;
      _isWriteException = false;
      _isReadToException = false;
      _readCalledCount = 0;
    }
  */

  ~MockDirectory() = default;

  MockDirectory(const MockDirectory&) = delete;
  MockDirectory(MockDirectory&&) = delete;
  MockDirectory& operator=(const MockDirectory&) = delete;
  MockDirectory& operator=(MockDirectory&&) = delete;
};
/*

class UniqueMockFile : public InputFile, public OutputFile
{
    public:
        const Path& GetPath() const noexcept
        {
            return file->GetPath();
        }

        void Open()
        {
            return file->Open();
        }

        void Close()
        {
            return file->Close();
        }

        void Write(const std::string& s)
        {
            return file->Write(s);
        }

        void ReadTo(std::vector<uint8_t>& v)
        {
            return file->ReadTo(v);
        }

        unsigned int ReadTo(std::vector<uint8_t>& data, unsigned int from,
unsigned int len)
        {
            return file->ReadTo(data, from, len);
        }

        explicit UniqueMockFile(const std::shared_ptr<MockDirectory>& f) :
        file(f)
        {}

        virtual ~UniqueMockFile() = default;

    private:
        std::shared_ptr<MockDirectory> file;

        UniqueMockFile(const UniqueMockFile&) = delete;
        UniqueMockFile(UniqueMockFile&&) = delete;
        UniqueMockFile& operator=(const UniqueMockFile&) = delete;
        UniqueMockFile& operator=(UniqueMockFile&&) = delete;
};*/