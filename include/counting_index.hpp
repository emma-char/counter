#pragma once

#include <iostream>
#include <unordered_map>

#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <configuration.hpp>




struct counting_index
{
    std::unordered_map< uint64_t, uint64_t > u;

    counting_index(configuration const & config){

        seqan3::sequence_file_input fin_from_filename{config.fasta_input};


        for (auto & record : fin_from_filename)
        {
            seqan3::debug_stream << "ID:  " << record.id() << '\n';
            seqan3::debug_stream << "SEQ: " << record.sequence() << '\n';

            auto minimisers = record.sequence() | seqan3::views::minimiser_hash(seqan3::shape{config.shape}, seqan3::window_size{8});
            seqan3::debug_stream << minimisers << '\n';


            for (uint64_t i : minimisers){
                u.insert(std::make_pair(i, 1));
                seqan3::debug_stream << i << '\n';

            }
               
        }

    }
};