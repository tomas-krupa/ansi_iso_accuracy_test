/**
 * @file CLIConfiguration.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include "Configuration.hpp"
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

/**
 * @ingroup g_Configuration
 *
 * Parses Configuration from command line.
 * The ``boost::program_options`` are used to parse command line and providing
 * help.
 */
template<typename TFilesystem, typename TOptions>
class CLIConfiguration final
  : Configuration<CLIConfiguration<TFilesystem, TOptions>>
{
private:
  const std::string kConfigFileDefault = "config.xml";
  const std::string kOutDirectoryDefault = "_result";
  const std::string kGenuinesDefault = "match.txt";
  const std::string kImpostorsDefault = "match2.txt";
  std::string _programName{};
  boost::program_options::positional_options_description _podesc;

public:
  explicit CLIConfiguration(const std::shared_ptr<TFilesystem> filesystem)
    : _filesystem(filesystem)
  {
    namespace po = boost::program_options;
    _options.getOptions().add_options()("help,h", "display help message")(
      "verification,v", "perform verification benchmark")( // TODO test
      "max-rotation,r",
      po::value<int>()->default_value(180),
      "maximum rotation of fingerprints (verification parameter)")(
      "output-directory,o",
      po::value<std::string>()->default_value(
        kOutDirectoryDefault), // TODO add test
      "input xml file with application configuration")(
      "config-file,c",
      po::value<std::string>()->default_value(kConfigFileDefault),
      "output directory for storing results")(
      "genuines,g",
      po::value<std::string>()->default_value(kGenuinesDefault),
      "input text file with genuine fingerprint pairs")(
      "impostors,i",
      po::value<std::string>()->default_value(kImpostorsDefault),
      "input text file with impostor fingerprint pairs")(
      "template-format,f",
      po::value<std::string>()->default_value("ansi"),
      "fingerprint template format")(
      "dpi,d",
      po::value<int>()->default_value(500),
      "DPI of fingerprint images (extraction parameter)");
  };

  virtual ~CLIConfiguration() = default;

  /**
   * @brief parse
   *
   * Parses input arguments from command-line, i.e. passed from main.
   *
   * @return parsed common-interface options.
   *
   */
  void parse(int argc, const char** argv)
  {
    namespace po = boost::program_options;
    namespace fs = boost::filesystem;

    _programName = std::string(argv[0]);
    try {
      po::variables_map vm;

      po::parsed_options parsed = po::command_line_parser(argc, argv)
                                    .options(_options.getOptions())
                                    .positional(_podesc)
                                    .run();
      po::store(parsed, vm);

      if (vm.count("help") != 0 or argc == 1) {
        needHelp = true;
        return;
      }

      po::notify(vm);

      auto pathParamValidator = [&](const std::string& option,
                                    const std::string& defaultValue = "") {
        const auto path = vm[option].as<std::string>();
        if (defaultValue != path &&
            not _filesystem->exists(
              path)) { // skips existence check if default value is used
          throw configuration::InvalidOption(
            "the value '" + path + "' for option  '--" + option +
            "' does not contain existing path");
        }
        return path;
      };

      auto intParamValidator =
        [&](const std::string& option, int lowerBound, int upperBound) {
          const int val = vm[option].as<int>();
          if (lowerBound > val || upperBound < val) {
            const auto errorMsg = "only <" + std::to_string(lowerBound) + ";" +
                                  std::to_string(upperBound) +
                                  "> values allowed for option '--" + option +
                                  "'";
            throw configuration::InvalidOption(errorMsg);
          }
          return val;
        };

      auto listParamValidator =
        [&](const std::string& option,
            const std::vector<std::string>& list_of_possible_values) {
          const std::string val = vm[option].as<std::string>(); // TODO tolower
          if (std::find(list_of_possible_values.cbegin(),
                        list_of_possible_values.cend(),
                        val) == list_of_possible_values.cend()) {
            std::stringstream ss;
            for (const auto& possible_value : list_of_possible_values) {
              ss << " " << possible_value << ',';
            }
            throw std::runtime_error("only [" + ss.str() +
                                     " ] values allowed for option '--" +
                                     option + "'");
          }
          return val;
        };

      auto boolParamValidator = [&](const std::string& option) {
        return static_cast<bool>(not vm[option].empty());
      };
      _options.getData()["config-file"] =
        pathParamValidator("config-file", kConfigFileDefault);
      _options.getData()["verifications"] = boolParamValidator("verifications");
      _options.getData()["help"] = boolParamValidator("help");
      _options.getData()["output-directory"] =
        pathParamValidator("output-directory", kOutDirectoryDefault);
      _options.getData()["impostors"] = pathParamValidator("impostors");
      _options.getData()["genuines"] = pathParamValidator("genuines");
      _options.getData()["max-rotation"] =
        intParamValidator("max-rotation", 0, 180);
      _options.getData()["dpi"] = intParamValidator("max-rotation", 50, 2000);
      _options.getData()["template-format"] =
        listParamValidator("template-format", { "ansi", "iso" });
    } catch (boost::program_options::unknown_option& e) {
      throw configuration::InvalidOption(e.what());
    } catch (boost::program_options::required_option& e) {
      throw configuration::InvalidOption(e.what());
    } catch (boost::program_options::invalid_option_value& e) {
      throw configuration::InvalidOption(e.what());
    } catch (boost::program_options::invalid_bool_value& e) {
      throw configuration::InvalidOption(e.what());
    }
  }

  /**
   * @brief getOptions
   *
   * @return common-interface options.
   *
   */
  const typename TOptions::Options& getOptions() const { return _options; }

  /**
   * @brief getData
   *
   * @return options data.
   *
   */
  const typename TOptions::Data& getData() { return _options.getData(); }

  /**
   * @brief getXmlPath
   *
   * @return path to XML configuration file (read from command-line, otherwise a
   * default).
   *
   */
  std::string getXmlPath() const
  {
    return boost::get<std::string>(
      _options.getData().find("config-file")->second);
  };

  /**
   * @brief logHelp
   *
   * prints help message using logger interface.
   *
   */
  template<class TLogger>
  void logHelp(TLogger const& logger) const
  {
    logger.log(getHelp(_programName));
  }

  CLIConfiguration(const CLIConfiguration&) = delete;

  CLIConfiguration(CLIConfiguration&&) = delete;

  CLIConfiguration& operator=(const CLIConfiguration&) = delete;

  CLIConfiguration& operator=(CLIConfiguration&&) = delete;

  bool needHelp = false;

private:
  mutable TOptions _options;
  const std::shared_ptr<TFilesystem> _filesystem;
  /**
   * @brief logHelp
   *
   * @return help message string.
   *
   */
  std::stringstream getHelp(std::string const& programName) const
  {
    std::stringstream ss;

    ss << "Usage:" << std::endl;

    boost::filesystem::path p(programName);
    ss << "  " << p.filename().string();

    ss << " [options]";

    for (int i = 0; i < _podesc.max_total_count(); ++i) {
      ss << " " << _podesc.name_for_position(i);
    }
    ss << std::endl << std::endl;
    ss << _options.getOptions() << std::endl;
    return ss;
  }
};