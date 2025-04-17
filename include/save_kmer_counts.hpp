#pragma once

#include <string>
#include <filesystem>
#include "counting_index.hpp"

void save_kmer_counts(counting_index const & index, std::filesystem::path const & output_path);



