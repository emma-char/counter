#pragma once

#include <iostream>
#include <unordered_set>  
#include <cstdint>

#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/search/views/minimiser_hash.hpp>
#include <seqan3/core/debug_stream.hpp>

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/archives/xml.hpp>

#include <configuration.hpp>
#include <get_shape.hpp>
#include <get_kmer_from_hash.hpp>

struct kmer_index
{
    std::unordered_set<uint64_t> set;
    seqan3::shape shape;


    kmer_index(std::filesystem::path const & input)
    {
        read(input);    
    }

    explicit kmer_index(seqan3::shape const & s) : shape(s) {} 


    template <class Archive>
    void save( Archive & ar ) const
    {
        ar( set, shape.to_string() );
    }
        
    template <class Archive>
    void load( Archive & ar )
    {
        std::string kmer_string;
        ar( set, kmer_string);
        shape = get_shape(kmer_string);
    }

    void write(std::filesystem::path const & output)//wiederverwenden
    {
        std::ofstream os(output);
        cereal::XMLOutputArchive archive( os );
        save(archive);
    }

    void read(std::filesystem::path const & input)//wiederverwenden
    {
        std::ifstream is(input);
        cereal::XMLInputArchive archive(is);
        load(archive);
    }

};