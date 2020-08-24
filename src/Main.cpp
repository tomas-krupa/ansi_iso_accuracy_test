/**
 * @file Main.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#include <AnsiIso/AnsiIso.hpp>
#include <Application.hpp>
#include <Biometric/AnsiIsoBiometric.hpp>
#include <Configuration/ProgramConfiguration.hpp>
#include <Logger/BoostLogger.hpp>
#include <innovatrics/ansiiso_accuracy_test.hpp>

void
Run(AnsiIsoNativeInterface& ansiIsoNative,
    BoostLogger& log,
    int argc,
    const char** argv);

/**
 * @mainpage
 *
 * Initializes logger and native library and run application's main function.
 */
int
main(int argc, const char* argv[])
{
  BoostLogger logger;
  AnsiIsoNativeInterface ansiIsoNative;

  const std::string productString =
    Innovatrics::AnsiIsoAccuracyTest::GetProductString();

  logger.log(productString);
  try {
    Run(ansiIsoNative, logger, argc, argv);
  } catch (const std::exception& e) {
    logger.log(e.what());
    return 1;
  } catch (...) {
    logger.log("Unknown exception thrown");
    return 1;
  }
}

/**
 * @brief Run
 *
 * Application's main function. Initializes filesystem handler, reads program
 * configuration, prepares native library and run Application's core function.
 *
 * @param ansiIsoNative instance of native library tested by the application
 * @param logger instance of a Boost-derived logger
 */
void
Run(AnsiIsoNativeInterface& ansiIsoNative,
    BoostLogger& logger,
    int argc,
    const char** const argv)
{
  Application::TFilesystem fileSystem;

  ProgramConfiguration<Application::TFilesystem, Application::TOptions> cfg(fileSystem, argc, argv);

  if (cfg.needHelp()) {
    cfg.logHelp(logger);
    return;
  }

  using TConf = decltype(cfg);
  using TLogger = decltype(logger);
  using TFilesystem = decltype(fileSystem);

  AnsiIso ansiiso(ansiIsoNative, logger, cfg);

  //Biometric<AnsiIsoBiometric<Application::TFile,TLogger,TConf>,Application::TBiometricStorage> biometric(ansiiso, logger, cfg);
  AnsiIsoBiometric<Application::TBiometricStorage, BoostLogger, Application::TConfiguration> biometric(ansiiso, logger, cfg);

  OutputStorageFactory<TFilesystem,TConf,Application::TFileStorage> storageFactory{cfg,fileSystem};

  Application app(cfg, fileSystem, logger, storageFactory,biometric);

  app.Run();
}