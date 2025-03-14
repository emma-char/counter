// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "get_kmer_from_hash.hpp"

std::string get_kmer_from_hash(seqan3::shape const & shape, uint64_t const hash)
{
    size_t kmer_weight = shape.count();
    constexpr uint8_t alphabet_size{4};

    std::string kmer_str{};
    std::unordered_map<uint8_t, char> alphabet_rank_map{
        {0, 'A'},
        {1, 'C'},
        {2, 'G'},
        {3, 'T'}
    };

    uint64_t hash_rest{hash};
    // iteriere über die positionen im k-mer
    for (size_t n{kmer_weight}; n > 0; n--)
    {
        // iteriere über die möglichen Buchstaben im DNA4 Alphabet
        for (uint8_t base_rank{alphabet_size - 1}; base >= 0; base--) 
        {
            if (hash_rest > (base_rank * alphabet_size**n))
            {
                hash =- hash_rest;
                kmer_str += alphabet_rank_map{base_rank};

                break;
            }
        }
    }
}
