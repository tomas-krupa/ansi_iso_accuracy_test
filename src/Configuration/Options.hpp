/**
 * @file Options.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <boost/program_options/option.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/variant.hpp>
#include <list>
#include <string>

/**
 * @brief Options
 *
 * Program options wrapper. Provides simple interface for option manipulation
 * and holds all options in a map.
 *
 */
template<class TOptions>
class Options
{
public:
  using Data =
    std::map<std::string, boost::variant<int, float, bool, std::string>>;

  Options() = default;

  Options(const Options& other) noexcept
    : _options(other._options)
    , _data(other._data){};

  Options(Options&& other) noexcept
    : _options(std::forward<TOptions>(other._options))
    , _data(std::forward<Data>(other._data)){};

  Options& operator=(Options&& other) = delete; /* noexcept
  {
    if (this == &other) {
      return *this;
    }
    _options = std::move(other._options);
    return *this;
  };*/

  Options& operator=(const Options& other) = delete; /*noexcept
  {
    if (this == &other) {
      return *this;
    }
    _data = other._options;
    _options = other._data;
    return *this;
  };
*/

  Options& operator+=(const Options& other) noexcept
  {
    _data.insert(other._data.cbegin(), other._data.cend());
    _options.add(other._options);
    return *this;
  };

  TOptions& getOptions() { return _options; };
  template<typename TReturn>
  TReturn getData(std::string const& option) const { return  boost::get<TReturn>(_data[option]); };

  boost::variant<int, float, bool, std::string>& getDataVariant(std::string const& option) const { return  _data[option]; };

private:
  TOptions _options;
  mutable Data _data;
};