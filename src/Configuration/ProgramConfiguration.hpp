/**
 * @file Configuration.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include "CLIConfiguration.hpp"
#include "Options.hpp"
#include "XMLConfiguration.hpp"

/**
 * @brief ProgramConfiguration
 *
 * @ingroup g_Configuration
 *
 * Composite configuration provider. Contains command-line and XML file
 * configurations.
 *
 */
template<class TFilesystem, class TOptions>
class ProgramConfiguration
{
public:
  ProgramConfiguration(std::shared_ptr<TFilesystem>& fs,
                       int argc,
                       const char** argv)
    : _cliCfg(fs)
  {
    _cliCfg.parse(argc, argv);
    if (_cliCfg.needHelp) { // TODO move otside constructor
      return;
    }

    XMLConfiguration<TFilesystem, TOptions> xmlCfg{ fs };
    xmlCfg.parse(_cliCfg.getXmlPath());

    _options += _cliCfg.getOptions();
    _options += xmlCfg.getOptions();
  };

  bool needHelp() { return _cliCfg.needHelp; }

  template<class TLogger>
  void logHelp(TLogger const& logger)
  {
    _cliCfg.logHelp(logger);
  }

  const ProgramConfiguration& GetProgramConfiguration() const { return this; };

  virtual ~ProgramConfiguration() = default;

  ProgramConfiguration(const ProgramConfiguration&) = delete;
  ProgramConfiguration(ProgramConfiguration&&) = delete;
  ProgramConfiguration& operator=(const ProgramConfiguration&) = delete;
  ProgramConfiguration& operator=(ProgramConfiguration&&) = delete;

private:
  TOptions _options;
  CLIConfiguration<TFilesystem, TOptions> _cliCfg;
};
