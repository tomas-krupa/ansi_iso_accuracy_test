/**
 * @file ansiiso.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <string>

#include <iengine_ansi_iso.h>
#include <innovatrics/config.hpp>

namespace Innovatrics {
class AnsiIso
{

public:
  static const std::string GetProductString() noexcept
  {
    return IEngine_GetVersionString();
  }
};
}