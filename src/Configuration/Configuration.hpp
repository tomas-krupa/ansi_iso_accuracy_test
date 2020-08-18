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

class FOptions;
class FData;

#include "Options.hpp"
#include <Logger/Logger.hpp>
#include <string>

/**
 * @brief Configuration
 *
 * @ingroup g_Configuration
 *
 * Provides configuration interface.
 *
 */
template<class TDerived>
class Configuration
{
public:
  void parse(const int argc, const char** argv)
  {
    static_cast<TDerived*>(this)->parse(argc, argv);
  }

  const FOptions& getOptions() const
  {
    return static_cast<TDerived*>(this)->getOptions();
  }

  const FData& getData() const
  {
    return static_cast<TDerived*>(this)->getData();
  }

  virtual ~Configuration() = default;

  Configuration(const Configuration&) = delete;
  Configuration(Configuration&&) = delete;
  Configuration& operator=(const Configuration&) = delete;
  Configuration& operator=(Configuration&&) = delete;

protected:
  Configuration() = default;
};

namespace configuration {
/**
 * @brief InvalidOption
 *
 * Decorates standard runtime exception with custom error message.
 *
 */
struct InvalidOption : std::runtime_error
{
  explicit InvalidOption(const char* msg) noexcept
    : std::runtime_error(msg)
  {}
  explicit InvalidOption(std::string const& msg) noexcept
    : std::runtime_error(msg)
  {}
};
}