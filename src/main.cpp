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
    // Configuration
    configuration config{};

    // Parser
    sharg::parser parser{"K-mer-Counter", argc, argv};

    // General information.
    parser.info.author = "SeqAn-Team";
    parser.info.version = "1.0.0";

    // Positional option: The FASTQ file to convert.
    parser.add_positional_option(config.fasta_input,
                                 sharg::config{.description = "The FASTA file with sequences to count.",
                                               .validator = sharg::input_file_validator{{"fa", "fasta"}}});
    
    
    // Output file. Default: print to terminal 
    parser.add_option(config.output,
                      sharg::config{.short_id = 'o',
                                    .long_id = "output",
                                    .description = "The output file with counted Kmere.",
                                    .default_message = "Print to terminal (stdout)",
                                    .validator = sharg::output_file_validator{}});

    //Validator for Kmer shape
    sharg::regex_validator shape_validator{"[0-1]"}; //!does not work

    //Kmer shape
    parser.add_option(config.shape_input,
                        sharg::config{.short_id = 's', 
                                      .long_id = "shape", 
                                      .description = "The shape of the Kmer.",
                                      .validator = shape_validator});
    


    //Window size input
    parser.add_option(config.window_input, 
                        sharg::config{.short_id = 'w',
                                      .long_id = "window", 
                                      .description = "The window size for the Kmer"});

                                   
    // Flag: Verose output.
    parser.add_flag(
        config.verbose,
        sharg::config{.short_id = 'v', .long_id = "verbose", .description = "Give more detailed information."});
    

    try
    {
        parser.parse(); // Trigger command line parsing.
    }
    catch (sharg::parser_error const & ext) // Catch user errors.
    {
        std::cerr << "Parsing error. " << ext.what() << '\n'; // Give error message.
        return -1;
    }



    sharg::parser top_level_parser{"mygit", argc, argv, sharg::update_notifications::on, {"push", "pull"}};
 
 
    // Add information and flags, but no (positional) options to your top-level parser.
    // Because of ambiguity, we do not allow any (positional) options for the top-level parser.
    top_level_parser.info.description.push_back("You can push or pull from a remote repository.");
    bool flag{false};
    top_level_parser.add_flag(flag, sharg::config{.short_id = 'f', .long_id = "flag", .description = "some flag"});
 
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
 
    std::cout << "Proceed to sub parser.\n";
 
    if (sub_parser.info.app_name == std::string_view{"mygit-pull"})
        return run_git_pull(sub_parser);
    else if (sub_parser.info.app_name == std::string_view{"mygit-push"})
        return run_git_push(sub_parser);
    else
        std::cout << "Unhandled subparser named " << sub_parser.info.app_name << '\n';
    // Note: Arriving in this else branch means you did not handle all sub_parsers in the if branches above.




    

    //auto sequence_size  ...
    config.shape = get_shape(config.shape_input);
    config.shape_size = config.shape.size();

    //Validating Window Input
    if(config.window_input <= config.shape_size){
        throw std::runtime_error("Window size to big");

    }

    counting_index kmer_index(config);

    kmer_index.write(config.output);

    if (config.verbose) // If flag is set.
    	std::cerr << "Counting was a success. Congrats!\n";

    

    return 0;
}
