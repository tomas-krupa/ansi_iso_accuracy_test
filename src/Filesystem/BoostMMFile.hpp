/**
 * @file BoostMMFile.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <istream>
#include <string>

#include "File.hpp"
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>

/**
 * @brief BoostMMFile
 *
 * Provides real interface to Boost Memory-mapped file.
 */

template<typename TPath>
class BoostMMFile final : public File<BoostMMFile<TPath>>
{
public:
  void open(){};

  void close(){};

  void write(const std::string&){};

  void readTo(std::vector<uint8_t>&){};

  unsigned int readTo(std::vector<uint8_t>&,
                      unsigned int from,
                      unsigned int len){};

  bool isOpen() const noexcept { return _file.is_open(); };

  const TPath& getPath() const noexcept {};

  explicit BoostMMFile(const std::string& path, int mode)
    : _file(createFileParams(path, mode))
    , bstream(_file)
  {}

  std::istream readToStream() { return std::istream{ bstream.rdbuf() }; };

  std::vector<unsigned char> readToVector()
  {
    return { _file.data(), _file.data() + _file.size() };
  };

  ~BoostMMFile() = default;

  BoostMMFile(const BoostMMFile&) = delete;

  BoostMMFile(BoostMMFile&&) = delete;

  BoostMMFile& operator=(const BoostMMFile&) = delete;

  BoostMMFile& operator=(BoostMMFile&&) = delete;

private:
  boost::iostreams::mapped_file_params createFileParams(const std::string& path,
                                                        int mode)
  {
    namespace io = boost::iostreams;

    const auto modeToMapmode =
      [](const int mode) -> io::mapped_file_base::mapmode {
      enum boost_mapmode
      {
        readonly = 1,
        readwrite = 2,
        priv = 4
      };
      switch (mode) {
        case readonly:
          return io::mapped_file_base::mapmode::readonly;
        case readwrite:
          return io::mapped_file_base::mapmode::readonly;
        default:
          return io::mapped_file_base::mapmode::priv;
      }
    };
    io::mapped_file_params fparams{ path };
    fparams.flags = modeToMapmode(mode);
    return fparams;
  }

  TPath _path;
  boost::iostreams::mapped_file_source _file;
  boost::iostreams::stream<
    boost::iostreams::mapped_file_source,
    BOOST_IOSTREAMS_CHAR_TRAITS(
      BOOST_DEDUCED_TYPENAME boost::iostreams::char_type_of<
        boost::iostreams::mapped_file_source>::type),
    std::allocator<BOOST_DEDUCED_TYPENAME boost::iostreams::char_type_of<
      boost::iostreams::mapped_file_source>::type>>
    bstream; // TODO simplify!!
  std::ios_base::openmode _openMode;
  std::size_t _length;
};