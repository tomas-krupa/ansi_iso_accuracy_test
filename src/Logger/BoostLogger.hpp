/**
 * @file BoostLogger.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include "Logger.hpp"
#include <boost/log/trivial.hpp>

/**
 * @brief BoostLogger
 *
 * @ingroup g_Logger
 *
 * Boost Log v2 -based logger.
 * Writes messages to console using BOOST_LOG_TRIVIAL.
 */
class BoostLogger final : public Logger<BoostLogger>
{
public:
  /**
   * Writes to stdout using BOOST_LOG_TRIVIAL.
   */
  void log(std::string const& line) const noexcept
  {
    BOOST_LOG_TRIVIAL(info) << line;
  }

  void log(std::stringstream const& line) const noexcept
  {
    BOOST_LOG_TRIVIAL(info) << line.str();
  }

  BoostLogger()
    : loglevel(boost::log::v2s_mt_posix::trivial::info){};

  ~BoostLogger() override = default;

  BoostLogger(const BoostLogger&) = delete;
  BoostLogger(BoostLogger&&) = delete;
  BoostLogger& operator=(const BoostLogger&) = delete;
  BoostLogger& operator=(BoostLogger&&) = delete;

private:
  boost::log::v2s_mt_posix::trivial::severity_level loglevel;
};
