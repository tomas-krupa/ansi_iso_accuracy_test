/**
 * @file AnsiIso.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <AnsiIso/AnsiIsoInterface.hpp>
#include <AnsiIso/AnsiIsoNativeInterface.hpp>
#include <Configuration/ProgramConfiguration.hpp>
#include <Filesystem/BoostDirectory.hpp>
#include <Filesystem/BoostFilesystem.hpp>
#include <Logger/BoostLogger.hpp>

/**
 * @brief AnsiIso
 *
 * AnsiIso native interface adapter. Wraps all functionality of AnsiIso library,
 * feed it with configuration and monitor it using a logger.
 *
 * @param ansiIsoNative instance of native library tested by the application
 * @param logger instance of a Boost-derived logger
 */
class AnsiIso final
{
public:
  using TPath = boost::filesystem::path;
  using TFilesystem =
    BoostFilesystem<BoostDirectory<TPath>, BoostMMFile<TPath>>;
  using TOptions = Options<boost::program_options::options_description>;

  AnsiIso(AnsiIsoNativeInterface&,
          BoostLogger&,
          const ProgramConfiguration<TFilesystem, TOptions>&);

  ~AnsiIso();

  /**
   * @brief getVersion
   *
   * Provides semantic version of native library.
   *
   * @return version of native library
   */
  std::string getVersion() const;

  /**
   * @brief throwOnError
   *
   * Converts native error code to standard runtime exception.
   *
   * @param result code of native function
   * @param text to embed into the runtime exception
   */
  static void throwOnError(int result, const std::string& text);

private:
  const AnsiIsoNativeInterface& _ansiisointerface;
  const BoostLogger& _logger;
  const ProgramConfiguration<
    TFilesystem,
    Options<boost::program_options::options_description>>& _configuration;
};