/**
 * @file Biometric.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 19.08.2020
 *
 */

#pragma once

#include <Storage/BiometricStorage.hpp>
#include <Record/BiometricRecord.hpp>

namespace biometric {
        using Data = std::vector<unsigned char>;

        enum StorageType
        {
            Cached,
            Filesystem
        };
}

template<class TDerived, class TStorage>
class Biometric
{
    public:
    std::unique_ptr<TStorage> createStorage(biometric::StorageType storageType) const {
                return static_cast<TDerived*>(createStorage(storageType));
        };
        std::unique_ptr<BiometricRecord> createRecord(const int id, const FData& data) const{
                return static_cast<TDerived*>(createRecord(id, data));
        };

        virtual ~Biometric() = default;

        Biometric(const Biometric&) = delete;
        Biometric(Biometric&&) = delete;
        Biometric& operator=(const Biometric&) = delete;
        Biometric& operator=(Biometric&&) = delete;

protected:
        Biometric() = default;
};
