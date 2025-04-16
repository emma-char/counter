// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <filesystem>
#include <seqan3/search/kmer_index/shape.hpp>

struct build_arguments
{
    std::filesystem::path fasta_input{};
    std::filesystem::path output{"output_index"};
    bool verbose{}; // Default is false.
    std::string shape_input{"1111"};
    uint8_t shape_size;
    seqan3::shape shape;
    uint8_t window_input{8};

};

struct union_arguments
{
    std::string index_file1{};
    std::string index_file2{};
    std::filesystem::path output{"union_result"};
    std::filesystem::path txt_output{"union_result.txt"}; 
};

struct intersection_arguments
{
    std::string index_file1{};
    std::string index_file2{};
    std::filesystem::path output{"intersection_result"};
    std::filesystem::path txt_output{"intersection_result.txt"}; 
};

struct difference_arguments
{
    std::string index_file1{};
    std::string index_file2{};
    std::filesystem::path output{"difference_result"};
    std::filesystem::path txt_output{"difference_result.txt"}; 
};
