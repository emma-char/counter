// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "configuration.hpp"
#include "get_shape.hpp"
#include "counting_index.hpp"
#include "save_kmer_counts.hpp"
#include "commands.hpp"

#include <seqan3/alphabet/nucleotide/dna4.hpp>
#include <seqan3/core/debug_stream.hpp>
#include <sharg/all.hpp>

#include <iostream>

using namespace seqan3::literals;

int main(int argc, char ** argv)
{

    sharg::parser top_level_parser{"counter", argc, argv, sharg::update_notifications::on, {"build", "union", "intersection", "difference"}};
 
 
    // Add information and flags, but no (positional) options to your top-level parser.
    // Because of ambiguity, we do not allow any (positional) options for the top-level parser.
    top_level_parser.info.description.push_back("....");

 
    try
    {
        top_level_parser.parse(); // trigger command line parsing
    }
    catch (sharg::parser_error const & ext) // catch user errors
    {
        std::cerr << "[Error] " << ext.what() << "\n"; // customise your error message
        return -1;
    }
 
 
    // hold a reference to the sub_parser
    sharg::parser & sub_parser = top_level_parser.get_sub_parser();
 
    if (sub_parser.info.app_name == std::string_view{"counter-build"})
        return run_build(sub_parser);
    else if (sub_parser.info.app_name == std::string_view{"counter-union"})
        return run_set_union(sub_parser);
    else if (sub_parser.info.app_name == std::string_view{"counter-intersection"})
        return run_set_intersection(sub_parser);
    else if (sub_parser.info.app_name == std::string_view{"counter-diffrence"})
        return run_set_difference(sub_parser);
    else
        std::cout << "Unhandled subparser named " << sub_parser.info.app_name << '\n';
    // Note: Arriving in this else branch means you did not handle all sub_parsers in the if branches above.

    return 0;
}
