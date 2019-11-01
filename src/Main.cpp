/**
 * @file Main.cpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 *
 */

#include <innovatrics/ansiiso_accuracy_test.hpp>
#include <iostream>

int
main(int argc, const char* argv[])
{

  std::cout << Innovatrics::AnsiIsoAccuracyTest::GetProductString() << std::endl;

  return 0;
}
