/**
 * @file TestBase.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */
#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <innovatrics/ansiiso.hpp>
#include <innovatrics/ansiiso_accuracy_test.hpp>

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