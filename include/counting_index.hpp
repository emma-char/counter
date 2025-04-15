#pragma once

#include <iostream>
#include <unordered_map>

#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <cereal/types/unordered_map.hpp>
#include <cereal/archives/xml.hpp>

#include <configuration.hpp>
#include <get_shape.hpp>
#include <get_kmer_from_hash.hpp>

struct counting_index
{
    std::unordered_map< uint64_t, uint64_t > u;
    seqan3::shape shape;

    counting_index(build_arguments const & config){
        shape = config.shape;
        seqan3::sequence_file_input fin_from_filename{config.fasta_input};

        for (auto & record : fin_from_filename)
        {
            seqan3::debug_stream << "ID:  " << record.id() << '\n';
            seqan3::debug_stream << "SEQ: " << record.sequence() << '\n';

            auto minimisers = record.sequence() | seqan3::views::minimiser_hash(seqan3::shape{config.shape}, seqan3::window_size{8});
            seqan3::debug_stream << minimisers << '\n';

            // Get hash values
            // uint64_t seed = 0x8F'3F'73'B5'CF'1C'9A'DE; // The default seed from minimiser_hash

            // Use XOR on all minimiser values
            /*auto hash_values = minimisers | std::views::transform
                ([seed](uint64_t i)
                {
                    return i ^ seed;
                });
            */

            for (uint64_t i : minimisers){
                u[i]++; //counting
                
                std::string kmer = get_kmer_from_hash(shape, i); // Convert hash to k-mer
                
                seqan3::debug_stream << "k-mer hash: " << i << " -> Count: " << u[i] 
                                    << " -> k-mer: " << kmer << '\n';
            }   
            
            
        }
    }

    counting_index(std::filesystem::path const & input)
    {
        read(input);    
    }

    template <class Archive>
    void save( Archive & ar ) const
    {
        ar( u, shape.to_string() );
    }
        
    template <class Archive>
    void load( Archive & ar )
    {
        std::string kmer_string;
        ar( u, kmer_string);
        shape = get_shape(kmer_string);
    }

    void write(std::filesystem::path const & output)
    {
        std::ofstream os(output);
        cereal::XMLOutputArchive archive( os );
        save(archive);
    }

    void read(std::filesystem::path const & input)
    {
        std::ifstream is(input);
        cereal::XMLInputArchive archive(is);
        load(archive);
    }


};
