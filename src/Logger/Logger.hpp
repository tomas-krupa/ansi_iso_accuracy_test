/**
 * @file Logger.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <sstream>
#include <string>

/**
 * @brief Logger
 *
 * @ingroup g_Logger
 *
 * Defines logging interface.
 *
 */
template<class TDerived>
class Logger
{
public:
  void log(std::string const& msg) const
  {
    static_cast<const TDerived*>(this)->log(msg);
  }

  void log(std::stringstream const& ss) const
  {
    static_cast<const TDerived*>(this)->log(ss);
  }

  virtual ~Logger() = default;

  Logger(const Logger&) = delete;
  Logger(Logger&&) = delete;
  Logger& operator=(const Logger&) = delete;
  Logger& operator=(Logger&&) = delete;

protected:
  Logger() = default;
};