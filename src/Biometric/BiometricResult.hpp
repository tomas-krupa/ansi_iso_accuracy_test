/**
 * @file BiometricResult.hpp
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 19.08.2020
 *
 */

#pragma once

/**
 * @brief BiometricResult
 *
 * BiometricResult is a simple holder of score and records.
 */
 template <class TRecord>
struct BiometricResult
{
    const int score;
    const std::shared_ptr<TRecord> probe;
    const std::shared_ptr<TRecord> reference;
};
