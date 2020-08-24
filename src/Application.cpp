/**
 * @file Application.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#include "Application.hpp"
#include <Storage/StorageFactory.hpp>

Application::Application(   const TConfiguration &configuration,
                            const TFilesystem &filesystem,
                            const BoostLogger &logger,
                            const TStorageFactory& storageFactory,
                            const TBiometric &biometric ):
        _biometric(biometric),
        _filesystem(filesystem),
        _configuration(configuration),
        _logger(logger),
        _biometricStorage(_biometric.createStorage(biometric::StorageType::Cached)),
        _templateListStorage(storageFactory.create(_configuration.getOption<std::string>("templates"))),
        _genuinesStorage(storageFactory.create(_configuration.getOption<std::string>("genuines"))),
        _impostorsStorage(storageFactory.create(_configuration.getOption<std::string>("impostors"))),
        _templateListReader(*_templateListStorage),
        _genuinesReader(*_genuinesStorage),
        _impostorsReader(*_impostorsStorage)
{
}

void
Application::Run() {
    _logger.log("Loading storages");
    loadStorages();

    _logger.log("Measure results");
    measureResults();

    _logger.log("Storing results");
    storeResults();

    _logger.log("Generating statistics");
    generateStatistics();

    _logger.log("Storing statistics");
    storeStatistics();
}


void
Application::loadStorages() {

     const auto checkTemplatesAvailability = [](const std::map<int,int> pairs){
         //TODO check pairs or throw
     };

     _templatesMap = _templateListReader.readToMap();
    _logger.log("List of input templates loaded");

    if (_configuration.doGenuines()) {
        _genuinesPairs = _genuinesReader.readToMap();
        checkTemplatesAvailability(_genuinesPairs);
        _logger.log("List of genuine pairs loaded and checked");
    }
    if (_configuration.doImpostors()) {
        _impostorsPairs = _impostorsReader.readToMap();
        checkTemplatesAvailability(_impostorsPairs);
       _logger.log("List of impostor pairs loaded and checked");
    }
}

std::vector<Application::TBiometricResult>
Application::measureMatches(const std::map<int,int>& pairs) {
    for(const auto& pair : pairs){

    }
    return {};
}

void
Application::measureResults() {
    if (_configuration.doGenuines()) {
        _genuinesResults = measureMatches(_genuinesPairs);
    }
    if (_configuration.doImpostors()) {
        _impostorsResults = measureMatches(_impostorsPairs);
    }
}

void
Application::storeResults() {}

void
Application::generateStatistics() {}

void
Application::storeStatistics() {}