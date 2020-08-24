/**
 * @file CSVReader.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 20.08.2020
 *
 */

#pragma once

/**
 * @brief CSVReader
 *
 * Defines basic file operations and attributes.
 */

template <class TFileStorage, typename TFirst,typename TSecond>
class CSVReader final //: public Reader<CSVReader>
{
public:
  std::map<TFirst,TSecond> readToMap() const { return {};
  }

  explicit CSVReader(const TFileStorage& fileStorage):_fileStorage(fileStorage){};

  virtual ~CSVReader() = default;

  CSVReader(const CSVReader&) = delete;
  CSVReader(CSVReader&&) = delete;
  CSVReader& operator=(const CSVReader&) = delete;
  CSVReader& operator=(CSVReader&&) = delete;

protected:
  CSVReader() = default;
private:
   const TFileStorage& _fileStorage;
};