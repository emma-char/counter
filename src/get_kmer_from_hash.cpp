// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "get_kmer_from_hash.hpp"

#include <seqan3/core/debug_stream.hpp>

#include <unordered_map>

/*std::string get_kmer_from_hash(seqan3::shape const & shape, uint64_t const hash)
{
    uint8_t kmer_weight = shape.count();
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
    for (uint8_t n{kmer_weight}; n > 0; n--)
    {
        // iteriere über die möglichen Buchstaben im DNA4 Alphabet
        for (int8_t base_rank{alphabet_size - 1}; base_rank >= 0; base_rank--) 
        {
            auto base_int = (base_rank * std::pow(alphabet_size, n - 1));
            if (hash_rest >= base_int)
            {
                hash_rest -= base_int;
                kmer_str += alphabet_rank_map[base_rank];

                break;
            }
        }
    }
    
    return kmer_str;
}*/


std::string get_kmer_from_hash(seqan3::shape const & shape, uint64_t const hash)
{
    uint8_t kmer_size = shape.size();  // Use `size()` instead of `count()`
    constexpr uint8_t alphabet_size{4};

    std::string kmer_str(kmer_size, 'A'); // Initialize k-mer with 'A's

    std::unordered_map<uint8_t, char> alphabet_rank_map{
        {0, 'A'}, {1, 'C'}, {2, 'G'}, {3, 'T'}
    };

    uint64_t hash_rest = hash;

    // Convert hash to DNA sequence from right to left
    for (int8_t i = kmer_size - 1; i >= 0; --i)
    {
        uint8_t base = hash_rest % alphabet_size;  // Extract last 2 bits
        kmer_str[i] = alphabet_rank_map[base];     // Map to DNA character
        hash_rest /= alphabet_size;                // Shift to next base
    }

    return kmer_str;
}