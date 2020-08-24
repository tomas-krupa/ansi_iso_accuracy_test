/**
 * @file BiometricRecord.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 19.08.2020
 *
 */

#pragma once

#include <string>
#include "Record.hpp"
#include <Biometric/BiometricResult.hpp>
#include <vector>

/**
 * @brief BiometricRecord
 *
 * BiometricRecord is a simple interface to hold and provide biometric data.
 */
class BiometricRecord final : public Record<BiometricRecord,BiometricResult<BiometricRecord>>
{
public:
    BiometricResult<BiometricRecord> match(const BiometricRecord&){

    };
    int getId() const { return id; };

    BiometricRecord(const int i, std::vector<unsigned char>&& d) : id(i), data(std::forward<std::vector<unsigned char>>(d)) {

    };

    virtual ~BiometricRecord() = default;

  BiometricRecord(const BiometricRecord&) = delete;
  BiometricRecord(BiometricRecord&&) = delete;
  BiometricRecord& operator=(const BiometricRecord&) = delete;
  BiometricRecord& operator=(BiometricRecord&&) = delete;

protected:
    const std::vector<unsigned char> data;
    const int id;
  BiometricRecord() = default;
};
