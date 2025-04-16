#pragma once

#include <sharg/all.hpp>
#include <filesystem>
#include <unordered_map>
#include "counting_index.hpp"


// Set Operations
int run_set_union(sharg::parser & parser);


int run_set_intersection(sharg::parser & parser);


int run_set_difference(sharg::parser & parser);

int run_build(sharg::parser & parser);