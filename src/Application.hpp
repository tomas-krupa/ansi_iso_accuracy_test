/**
 * @file Application.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <AnsiIso/AnsiIso.hpp>
#include <Configuration/ProgramConfiguration.hpp>
#include <Filesystem/BoostDirectory.hpp>
#include <Filesystem/BoostFilesystem.hpp>
#include <Logger/Logger.hpp>
#include <Biometric/AnsiIsoBiometric.hpp>
#include <Storage/BiometricStorage.hpp>
#include <Storage/OutputStorageFactory.hpp>

class AnsiIso;
class AnsiIsoNativeInterface;

/**
 * @brief Application
 *
 * Facade class covering the core logic of the application.
 *
 */
class Application
{
public:
  using TPath = boost::filesystem::path;
  using TFile = BoostMMFile<TPath>;
  using TFilesystem = BoostFilesystem<BoostDirectory<TPath>, TFile>;
  using TOptions = Options<boost::program_options::options_description>;
  using TConfiguration = ProgramConfiguration<TFilesystem, TOptions>;
  using TBiometricStorage = BiometricStorage<TFile>;
  using TFileStorage = FileStorage<TFile>;
  using TOutputStorageFactory = OutputStorageFactory<TFilesystem, TConfiguration, TFileStorage>;
  using TStorageFactory = StorageFactory<TOutputStorageFactory,TFileStorage>;
  using TBiometric = AnsiIsoBiometric<TBiometricStorage,BoostLogger,TConfiguration>;

  Application(const TConfiguration &configuration,
                            const TFilesystem &filesystem,
                            const BoostLogger &logger,
                            const TStorageFactory& storageFactory,
                           const TBiometric &biometric );
  /**
   * @brief Run
   *
   * Application's core function. Initializes filesystem handler, reads program
   * configuration, prepares native library and run Application's main function.
   *
   * @param ansiIsoNative instance of native library tested by the application
   * @param logger instance of a Boost-derived logger
   */
  void Run();

private:
  const TFilesystem& _filesystem;
  const TConfiguration& _configuration;
  const BoostLogger& _logger;
  const TBiometric& _biometric;
  const std::unique_ptr<TBiometricStorage> _biometricStorage;
  const std::unique_ptr<TFileStorage> _templateListStorage;
  const std::unique_ptr<TFileStorage> _genuinesStorage;
  const std::unique_ptr<TFileStorage> _impostorsStorage;

  const CSVReader<TFileStorage,int,std::string> _templateListReader;
  const CSVReader<TFileStorage,int,int> _genuinesReader;
  const CSVReader<TFileStorage,int,int> _impostorsReader;

  std::map<int,std::string> _templatesMap;
  std::map<int,int> _genuinesPairs;
  std::map<int,int> _impostorsPairs;
  using TBiometricResult = BiometricResult<BiometricRecord>;
  std::vector<TBiometricResult> _genuinesResults;
  std::vector<TBiometricResult> _impostorsResults;

    /**
   * @brief measureMatches
   *
   * Match all input pairs and assigns them matching score.
     *
     * @return vector of match results
   */
  static std::vector<Application::TBiometricResult> measureMatches(const std::map<int,int>& pairs);

  /**
   * @brief loadStorage
   *
   * Load input text files and templates from filesystem to storage.
   */
  void loadStorages();

  /**
   * @brief measureResults
   *
   * Performs test scenario with recording accuracy and performance.
   */
  void measureResults();

  /**
   * @brief storeResults
   *
   * Stores raw accuracy scores and API call performace in the filesystem.
   */
  void storeResults();

  /**
   * @brief generateStatistics
   *
   * Generates various accuracy statistics (FARatFRR, ERR, DET) and performance
   * summary.
   */
  void generateStatistics();

  /**
   * @brief storeStatistics
   *
   * Stores accuracy and performance summary in the filesystem.
   */
  void storeStatistics();
};