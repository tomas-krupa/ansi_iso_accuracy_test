/**
 * @file test_package.cpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 */

#include <innovatrics/ansiiso_accuracy_test.hpp>
#include <iostream>
#include <string>

void
check_eternity()
{
  return Innovatrics::AnsiIsoAccuracyTest::GetProductString().find("ANSI") !=
         std::npos;
}

int
main()
{
  return check_eternity();
}
