/**
 * @file AnsiIso.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#include "AnsiIso.hpp"

AnsiIso::AnsiIso(
  AnsiIsoNativeInterface& ansiisointerface,
  BoostLogger& logger,
  const ProgramConfiguration<TFilesystem, TOptions>& configuration)
  : _ansiisointerface(ansiisointerface)
  , _logger(logger)
  , _configuration(configuration)
{
  _ansiisointerface.IEngine_Init();
}

AnsiIso::~AnsiIso()
{
  _ansiisointerface.IEngine_Terminate();
}

std::string
AnsiIso::getVersion() const
{
  return _ansiisointerface
    .IEngine_GetVersionString(); // TODO regex extract semantic version
}

void
AnsiIso::throwOnError(int result, const std::string& text)
{
  if (result != 0) {
    throw std::runtime_error(text + " " + std::to_string(result));
  }
}
