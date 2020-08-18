/**
 * @file Test_CLIconfiguration.cpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 12.08.2020
 *
 */
#define CATCH_CONFIG_MAIN

#include <Configuration/CLIConfiguration.hpp>
#include <Configuration/Options.hpp>
#include <Mock/MockFilesystem.hpp>
#include <Mock/MockLogger.hpp>
#include <catch2/catch.hpp>
#include <memory>

/**
 * @brief Test_CLIconfiguration
 *
 * Unit test suite for Command-line Configuration operations using mocked
 * filesystem and mocked logger.
 */
TEST_CASE("Test_CommandLine")
{

  using CLI =
    CLIConfiguration<MockFileSystem,
                     Options<boost::program_options::options_description>>;

  SECTION("Output")
  {
    SECTION("When_output_has_existing_path_then_it_is_provided")
    {

      auto fs = std::make_shared<MockFileSystem>();
      fs->CreateDirectory("tmp/some/dir");
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      CLI cfg{ fs };
      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--output-directory",
                             "tmp/some/dir",
                             "--max-rotation",
                             "180" };
      cfg.parse(5, argv);

      const auto var = cfg.getData().find("output-directory")->second;
      CHECK("tmp/some/dir" == boost::get<std::string>(var));
    }

    SECTION("When_output_has_non_existing_path_then_invalid_option_is_thrown")
    {

      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--output-directory",
                             "/home/privateuser/result",
                             "--max-rotation",
                             "180" };

      CHECK_THROWS_AS(cfg.parse(5, argv), configuration::InvalidOption);
    }

    SECTION("When_no_output_given_then_default_is_provided")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--template-format",
                             "iso",
                             "--dpi",
                             "1000",
                             "--max-rotation",
                             "180" };
      cfg.parse(7, argv);

      CHECK("_result" == boost::get<std::string>(
                           cfg.getData().find("output-directory")->second));
    }

    SECTION("When_output_has_no_existing_directory_then_exception_is_thrown")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = {
        "ansi_iso_accuracy_test",
        "--output-directory",
        "/not/existing/dir",
      };
      CHECK_THROWS_AS(cfg.parse(3, argv), configuration::InvalidOption);
    }
  }
  SECTION("Input")
  {
    SECTION("When_no_default_input_pairs_given_then_exception_is_thrown")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };

      const char* argv[] = { "ansi_iso_accuracy_test", "-v" };
      cfg.parse(1, argv);
      CHECK_THROWS_AS(cfg.parse(2, argv), configuration::InvalidOption);
    }
    SECTION("When_no_input_genuine_pairs_given_then_default_is_provided")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("nonmatches.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--impostors",
                             "nonmatches.txt" };
      cfg.parse(3, argv);
      CHECK("match.txt" ==
            boost::get<std::string>(cfg.getData().find("genuines")->second));
    }

    SECTION("When_no_input_impostor_pairs_given_then_default_is_provided")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("matches.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--genuines",
                             "matches.txt" };
      cfg.parse(3, argv);
      CHECK("match2.txt" ==
            boost::get<std::string>(cfg.getData().find("impostors")->second));
    }
  }
  SECTION("Max_rotation")
  {

    SECTION("When_max_rotation_is_outside_then_exception_is_thrown")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--template-format",
                             "iso",
                             "--max-rotation",
                             "260" };

      CHECK_THROWS_AS(cfg.parse(5, argv), configuration::InvalidOption);
    }
    SECTION("When_max_rotation_is_is_not_specified_then_default_is_provided")
    {
      auto fs = std::make_shared<MockFileSystem>();
      CLI cfg{ fs };
      fs->CreateFile("match.txt");
      fs->CreateFile("match2.txt");

      const char* argv[] = { "ansi_iso_accuracy_test",
                             "--template-format",
                             "iso" };
      cfg.parse(3, argv);
      CHECK(180 == boost::get<int>(cfg.getData().find("max-rotation")->second));
    }
  }

  SECTION("Help")
  {
    auto fs = std::make_shared<MockFileSystem>();
    CLI cfg{ fs }; // TODO
    fs->CreateFile("match.txt");
    fs->CreateFile("match2.txt");

    const char* argv[] = { "ansi_iso_accuracy_test", "--help" };
    cfg.parse(2, argv);

    MockLogger logger;
    cfg.logHelp(logger);

    CHECK(true == cfg.needHelp);
    // CHECK(std::string::npos !=
    // logger.logs[0].find(ansi_iso_accuracy_test_VERSION));
    CHECK(std::string::npos != logger.logs[0].find("--output-directory"));
    CHECK(std::string::npos != logger.logs[0].find("--max-rotation"));
    std::cout << logger.logs[0] << std::endl;
  }

  SECTION("When_unknown_option_is_used_then_invalid_option_is_thrown")
  { // TODO and help should be shown
    auto fs = std::make_shared<MockFileSystem>();
    CLI cfg{ fs };
    fs->CreateFile("match.txt");
    fs->CreateFile("match2.txt");

    const char* argv[] = { "ansi_iso_accuracy_test",
                           "--unrecognized",
                           "--otherUnrecognised" };
    CHECK_THROWS_AS(cfg.parse(3, argv), configuration::InvalidOption);
  }
}