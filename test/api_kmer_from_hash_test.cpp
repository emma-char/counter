// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <gtest/gtest.h>

#include <get_kmer_from_shape.hpp>

#include "app_test.hpp"

// To prevent issues when running multiple API tests in parallel, give each API test unique names:
struct hash_to_kmer : public app_test
{};

TEST_F(hash_to_kmer, ungapped)
{
    uint64_t len{28};

    std::string expected{"CTA"};
    seqan3::shape shape{seqan3::ungapped{3}};
    auto actual = get_kmer_from_hash(shape, str);

    EXPECT_EQ(expected, actual);
}
