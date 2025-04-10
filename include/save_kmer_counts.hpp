#pragma once

#include <iostream>
#include <counting_index.hpp>
#include <configuration.hpp>
#include <get_kmer_from_hash.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <unordered_map>


/*
void save_kmer_counts(const std::unordered_map<uint64_t, size_t>& save, seqan3::shape const & shape) {
    std::ofstream ot("output.txt");

    for (const auto& [hash, count] : save) {
        std::string kmer = get_kmer_from_hash(shape, hash); // <- shape must be passed in
        ot << kmer << " " << count << "\n";
    }
}
*/

