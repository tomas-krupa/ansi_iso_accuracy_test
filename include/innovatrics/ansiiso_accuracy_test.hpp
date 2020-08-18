/**
 * @file ansiiso_accuracy_test.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <string>

#include <innovatrics/config.hpp>

namespace Innovatrics {

class AnsiIsoAccuracyTest
{

public:
  static const std::string GetProductString()
  {
    return ANSSIISO_ACCURACY_TEST_PRODUCT_STRING;
  }
};
}
