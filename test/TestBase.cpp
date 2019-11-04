/**
 * @file TestBase.cpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 *
 */
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <innovatrics/ansiiso_accuracy_test.hpp>
#include <innovatrics/ansiiso.hpp>

TEST_CASE("Product string are readable")
{
  SECTION("Product string of ANSI&ISO library os non-empty")
  {
    CHECK(false == Innovatrics::AnsiIso::GetProductString().empty());
  }

  SECTION("Product string of ANSI&ISO Accuracy test is non-empty")
  {
    CHECK(false ==
                Innovatrics::AnsiIsoAccuracyTest::GetProductString().empty());
  }
}