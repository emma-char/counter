// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "app_test.hpp"

// To prevent issues when running multiple CLI tests in parallel, give each CLI test unique names:
struct counter : public app_test
{};

TEST_F(counter, no_options)
{
    app_test_result const result = execute_app("counter");
    std::string_view const expected{"counter\n=======\n"
                                    "    Try -h or --help for more information.\n"};

    EXPECT_SUCCESS(result);
    EXPECT_EQ(result.out, expected);
    EXPECT_EQ(result.err, "");
}

TEST_F(counter, fail_no_argument)
{
    app_test_result const result = execute_app("counter","build", "-v");
    std::string_view const expected{"[Error build] Not enough positional arguments provided (Need at least 1). See -h/--help for more information.\n"};

    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, expected);
}

TEST_F(counter, with_argument)
{
    app_test_result const result = execute_app("counter","build", data("seq.fasta"));

    EXPECT_SUCCESS(result);
    //EXPECT_EQ(result.out, "");
    //EXPECT_EQ(result.err, "");
}

TEST_F(counter, with_argument_verbose)
{
    app_test_result const result = execute_app("counter", "build", data("seq.fasta"), "-v");

    EXPECT_SUCCESS(result);
    //EXPECT_EQ(result.out, "");
    //EXPECT_EQ(result.err, "");
}

TEST_F(counter, missing_path)
{
    app_test_result const result = execute_app("counter", "build", data("missing.fasta"), "-o", "");

    EXPECT_FAILURE(result);
    EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err, "[Error build] Missing value for option -o\n");
}

TEST_F(counter, invalid_path)
{
    app_test_result const result = execute_app("counter", "build", data("seq.fasta"), "-o", "does_not_exist/out.fasta");

    EXPECT_FAILURE(result);
    //EXPECT_EQ(result.out, "");
    EXPECT_EQ(result.err,
              "[Error build] Validation failed for option -o/--output: Cannot write \"does_not_exist/out.fasta\"!\n");
}
