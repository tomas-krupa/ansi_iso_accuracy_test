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
  ProgramConfiguration(const TFilesystem& fs,
                       int argc,
                       const char** argv)
    : _filesystem(fs),_cliCfg(_filesystem)
  {
    _cliCfg.parse(argc, argv);
    if (_cliCfg.needHelp) { // TODO move otside constructor
      return;
    }

    XMLConfiguration<TFilesystem, TOptions> xmlCfg{ _filesystem };
    xmlCfg.parse(_cliCfg.getXmlPath());

    _options += _cliCfg.getOptions();
    _options += xmlCfg.getOptions();

    createOutputDir(getOption<std::string>("output-directory"));
  };

  bool needHelp() const { return _cliCfg.needHelp; }
  bool doGenuines() const { return not getOption<bool>("exclude-genuines"); }
  bool doImpostors() const  { return not getOption<bool>("exclude-impostors"); }

  template <typename TReturn>
  TReturn getOption(std::string const& option) const { return _options.template getData<TReturn>(option); }

  template<class TLogger>
  void logHelp(TLogger const& logger) const
  {
    _cliCfg.logHelp(logger);
  }

  void createOutputDir(const std::string& path) const {
    auto outputDirectory = _filesystem.createDirectory(path);

    if (not _filesystem.exists(outputDirectory->getPath()))
    {
        outputDirectory->create();
    }
  }

  virtual ~ProgramConfiguration() = default;

  ProgramConfiguration(const ProgramConfiguration&) = delete;
  ProgramConfiguration(ProgramConfiguration&&) = delete;
  ProgramConfiguration& operator=(const ProgramConfiguration&) = delete;
  ProgramConfiguration& operator=(ProgramConfiguration&&) = delete;

private:
  TOptions _options;
  const TFilesystem& _filesystem;
  CLIConfiguration<TFilesystem, TOptions> _cliCfg;
};
