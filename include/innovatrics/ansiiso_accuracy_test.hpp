/**
 * @file ansiiso_accuracy_test.hpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 *
 */

#pragma once

#include <string>

#include <config.hpp>

namespace Innovatrics {

class AnsiIsoAccuracyTest
{

public:
  static const std::string GetProductString() { return ANSSIISO_ACCURACY_TEST_PRODUCT_STRING; }
};
}
