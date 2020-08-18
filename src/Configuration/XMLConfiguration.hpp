/**
 * @file XMLConfiguration.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <Filesystem/Filesystem.hpp>

#include "Configuration.hpp"
#include "Options.hpp"

/**
 * @brief ProgramConfiguration
 *
 * @ingroup g_Configuration
 *
 * Provides input configuration parsed from XML configuration file.
 *
 */
template<typename TFilesystem, typename TOptions>
class XMLConfiguration final
  : Configuration<XMLConfiguration<TFilesystem, TOptions>>
{
public:
  /**
   * @brief parse
   *
   * Parses configuration from XML configuration file and stores the Options.
   *
   */
  void parse(std::string const& path) { return; };

  /**
   * @brief getOptions
   *
   * @return common-interface options.
   *
   */
  const TOptions& getOptions() const { return _options; };

  /*  *//**
   * @brief getXmlPath
   *
   * @return path to XML configuration file.
   *
   *//*
  std::string getXmlPath() const;*/
  explicit XMLConfiguration(std::shared_ptr<TFilesystem>& fs)
    : _fs(fs){};

  ~XMLConfiguration() = default;

  XMLConfiguration(const XMLConfiguration&) = delete;
  XMLConfiguration(XMLConfiguration&&) = delete;
  XMLConfiguration& operator=(const XMLConfiguration&) = delete;
  XMLConfiguration& operator=(XMLConfiguration&&) = delete;

private:
  TOptions _options;
  const std::string _xmlFile;
  const std::shared_ptr<TFilesystem> _fs;
};