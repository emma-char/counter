#pragma once

#include <sharg/all.hpp>
#include <filesystem>
#include <unordered_map>
#include "counting_index.hpp"

// Push/Pull Operationen
int run_git_pull(sharg::parser & parser);
struct pull_arguments
{
    std::string repository{};
    std::string branch{};
    bool progress{false};
};
int run_git_push(sharg::parser & parser);
struct push_arguments
{
    std::string repository{};
    std::vector<std::string> branches{};
    bool push_all{false};
};

// Set Operations
int run_set_union(sharg::parser & parser);

struct union_arguments
{
    std::string index_file1{};
    std::string index_file2{};
};

int run_set_intersection(sharg::parser & parser);

struct intersection_arguments
{
    std::string index_file1{};
    std::string index_file2{};
};

int run_set_difference(sharg::parser & parser);

struct difference_arguments
{
    std::string index_file1{};
    std::string index_file2{};
};