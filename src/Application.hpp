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
  using TFilesystem =
    BoostFilesystem<BoostDirectory<TPath>, BoostMMFile<TPath>>;
  using TOptions = Options<boost::program_options::options_description>;

  Application(const AnsiIso&,
              std::shared_ptr<TFilesystem>&,
              const ProgramConfiguration<TFilesystem, TOptions>&,
              BoostLogger&);
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
  const AnsiIso& _ansiiso;
  const std::shared_ptr<TFilesystem>& _fs;
  const ProgramConfiguration<TFilesystem, TOptions>& _configuration;
  const BoostLogger& _logger;

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