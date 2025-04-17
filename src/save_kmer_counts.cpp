#include "save_kmer_counts.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "get_kmer_from_hash.hpp" // for the hash -> kmer conversion

void save_kmer_counts(counting_index const & index, std::filesystem::path const & output_path)
{
    std::ofstream out_file(output_path);

    if (!out_file)
    {
        std::cerr << "Failed to open output file: " << output_path << "\n";
        return;
    }

    for (auto const & [hash, count] : index.u)
    {
        std::string kmer = get_kmer_from_hash(index.shape, hash);
        out_file << kmer << ":" << count <<'\n';
    }

    out_file.close();
}