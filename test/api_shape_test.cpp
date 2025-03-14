// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <gtest/gtest.h>

#include <get_shape.hpp>

#include "app_test.hpp"

// To prevent issues when running multiple API tests in parallel, give each API test unique names:
struct string_to_shape : public app_test
{};

TEST_F(string_to_shape, ungapped)
{
    uint8_t len{8};
    std::string str(len, '1');
    auto const expected = seqan3::shape{seqan3::ungapped{len}};
    auto actual = get_shape(str);

    EXPECT_EQ(expected.count(), actual.count());
    EXPECT_EQ(expected.size(), actual.size());
    EXPECT_EQ(expected.to_string(), actual.to_string());
}

TEST_F(string_to_shape, gapped)
{
    std::string str{"1001"};
    auto const expected = seqan3::shape{seqan3::bin_literal{0b1001}};
    auto actual = get_shape(str);

    EXPECT_EQ(expected.count(), actual.count());
    EXPECT_EQ(expected.size(), actual.size());
    EXPECT_EQ(expected.to_string(), actual.to_string());
}
