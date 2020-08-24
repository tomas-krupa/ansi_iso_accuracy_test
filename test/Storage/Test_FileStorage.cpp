/**
 * @file Test_FileStorage.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */
#define CATCH_CONFIG_MAIN

#include <Mock/MockFile.hpp>
#include <Storage/FileStorage.hpp>
#include <catch2/catch.hpp>

using TPath = boost::filesystem::path;

/**
 * @brief Test_FileStorage
 *
 * Minimal unit test suite for Storage operations using mocked file.
 */
TEST_CASE("Test_FileStorage")
{
  //SECTION("Fileopen_is_performed_only_on_first_store") //TODO decide when to open
  SECTION("Fileopen_is_performed_on_filestorage_creation")
  {
    auto mockFile = std::make_unique<MockFile<TPath>>("mock/path", -1);
    auto mockFilePtr = mockFile.get(); // dirty hack
    FileStorage filesystem(std::move(mockFile));

    CHECK(1 == mockFilePtr->_openCalledCount);

    filesystem.store("whatever");

    CHECK(1 == mockFilePtr->_openCalledCount);

    filesystem.store("whaaateeever");

    CHECK(1 == mockFilePtr->_openCalledCount);
  }

  SECTION("When_filewrite_throws_then_exception_is_propagated")
  {
    auto mockFile = std::make_unique<MockFile<TPath>>("mock/path", -1);
    auto mockFilePtr = mockFile.get(); // dirty hack

    FileStorage filesystem(std::move(mockFile));

    mockFilePtr->_isWriteException = true;

    CHECK_THROWS_AS(filesystem.store("this should throw"), std::runtime_error);
  }
}