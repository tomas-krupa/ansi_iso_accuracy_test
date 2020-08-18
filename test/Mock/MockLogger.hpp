/**
 * @file MocLogger.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 12.08.2020
 *
 */

#pragma once

#include <Logger/Logger.hpp>
/**
 * @brief MockLogger
 *
 * @ingroup g_Logger
 *
 * Mock implementation of logging interface.
 *
 */
class MockLogger final : public Logger<MockLogger>
{
public:
  mutable std::vector<std::string> logs;

  void log(std::string const& msg) const { logs.emplace_back(msg); }

  void log(std::stringstream const& msg) const { logs.emplace_back(msg.str()); }

  MockLogger() = default;
  virtual ~MockLogger() = default;

private:
  MockLogger(const MockLogger&) = delete;
  MockLogger(MockLogger&&) = delete;
  MockLogger& operator=(const MockLogger&) = delete;
  MockLogger& operator=(MockLogger&&) = delete;
};