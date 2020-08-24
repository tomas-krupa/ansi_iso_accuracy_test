/**
 * @file AnsiIsoBiometric.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 19.08.2020
 *
 */

#pragma once

#include <Configuration/ProgramConfiguration.hpp>
#include "Biometric.hpp"

template<class TBiometricStorage, class TLogger, class TConfiguration>
class AnsiIsoBiometric final : public Biometric<AnsiIsoBiometric<TBiometricStorage, TLogger, TConfiguration>,TBiometricStorage>
{
    public:
        std::unique_ptr<TBiometricStorage> createStorage( biometric::StorageType storage) const{
            switch (storage){
                case  biometric::StorageType::Filesystem:
                    return std::make_unique<TBiometricStorage>();
                case  biometric::StorageType::Cached:
                default:
                    return nullptr;
            }

        };
        std::unique_ptr<BiometricRecord> createRecord(const int id, const FData& data) const{
            return std::make_unique<BiometricRecord>(id,data);
        };

        AnsiIsoBiometric(AnsiIso& a, TLogger& l, TConfiguration const& c):
            ansiIso(a),
            logger(l),
            configuration(c){        };

        virtual ~AnsiIsoBiometric() = default;

        AnsiIsoBiometric(const AnsiIsoBiometric&) = delete;
        AnsiIsoBiometric(AnsiIsoBiometric&&) = delete;
        AnsiIsoBiometric& operator=(const AnsiIsoBiometric&) = delete;
        AnsiIsoBiometric& operator=(AnsiIsoBiometric&&) = delete;

private:
    AnsiIso& ansiIso;
    TLogger& logger;
    TConfiguration const& configuration;
};
