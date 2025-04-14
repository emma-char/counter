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


int run_set_intersection(sharg::parser & parser);


int run_set_difference(sharg::parser & parser);

int run_build(sharg::parser & parser);