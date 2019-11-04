/**
 * @file ansiiso.hpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 *
 */

#pragma once

#include <string>

#include <innovatrics/config.hpp>
#include <iengine_ansi_iso.h>

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