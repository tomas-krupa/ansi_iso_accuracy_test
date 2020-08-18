/**
 * @file test_package.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 */

#include <innovatrics/ansiiso_accuracy_test.hpp>
#include <iostream>
#include <string>

bool
check_eternity()
{
  const auto productString =
    Innovatrics::AnsiIsoAccuracyTest::GetProductString();
  std::cout << "Product string: " << productString << std::endl;

  return productString.find("ansi") == std::string::npos;
}

int
main()
{
  return check_eternity();
}
