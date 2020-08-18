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
#include <Logger/BoostLogger.hpp>

Application::Application(
  const AnsiIso& ansiiso,
  std::shared_ptr<TFilesystem>& fs,
  const ProgramConfiguration<TFilesystem, TOptions>& configuration,
  BoostLogger& logger)
  : _ansiiso(ansiiso)
  , _fs(fs)
  , _configuration(configuration)
  , _logger(logger)
{}

void
Application::Run()
{
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
Application::measureResults()
{}

void
Application::storeResults()
{}

void
Application::generateStatistics()
{}

void
Application::storeStatistics()
{}