#include "save_set_opp.hpp"

#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include "get_kmer_from_hash.hpp" // for the hash -> kmer conversion

void save_set_opp(kmer_index const & index, std::filesystem::path const & output_path)
{
    std::ofstream out_file(output_path);

    if (!out_file)
    {
        std::cerr << "Failed to open output file: " << output_path << "\n";
        return;
    }

    for (auto const & hash : index.set)
    {
        std::string kmer = get_kmer_from_hash(index.shape, hash);
        out_file << kmer << '\n';
    }

    out_file.close();
}
