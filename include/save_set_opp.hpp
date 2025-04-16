#pragma once

#include <string>
#include <filesystem>
#include "kmer_index.hpp" // Make sure this includes your kmer_index definition

void save_set_opp(kmer_index const & index, std::filesystem::path const & output_path);