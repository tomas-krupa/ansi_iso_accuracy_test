/**
 * @file TestBase.cpp
 *
 * @copyright Copyright (c) 2019 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 07.08.2019
 *
 */
#include <catch2/catch.hpp>

TEST_CASE("Product string are readable")
{
  SECTION("Product string of ANSI&ISO library os non-empty")
  {
    CHECK_EQUAL(false, Innovatrics::AnsiIso::GetProductString().empty());
  }

  SECTION("Product string of ANSI&ISO Accuracy test is non-empty")
  {
    CHECK_EQUAL(false,
                Innovatrics::AnsiIsoAccuracyTest::GetProductString().empty());
  }
}