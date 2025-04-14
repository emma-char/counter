#include "commands.hpp"
#include <iostream>
#include "configuration.hpp" 
#include "counting_index.hpp"
#include <sharg/all.hpp>

// =====================================================================================================================
// Mengenoperationen Implementierungen
// =====================================================================================================================
counting_index set_union(counting_index const & a, counting_index const & b)
{
    counting_index result = a;
    for (auto const & [k, v] : b.u) // <-- use b.u here
        result.u[k] += v;
    return result;
}

int run_set_union(sharg::parser & parser)
{
    union_arguments args{};

    parser.add_positional_option(args.index_file1, sharg::config{.description = "The first index file to merge."});
    parser.add_positional_option(args.index_file2, sharg::config{.description = "The second index file to merge."});

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error set union] " << ext.what() << "\n";
        return -1;
    }

    
    counting_index idx1(args.index_file1);
    counting_index idx2(args.index_file2);
    
    counting_index set_union(counting_index const & idx1, counting_index const & idx2);
    return 0;

}

int run_build(sharg::parser & parser)
{
        // Configuration
        build_arguments config{};

        // Parser
        //sharg::parser parser{"K-mer-Counter", argc, argv};
    
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

int run_set_intersection(sharg::parser & parser)
{
    (void)parser;
    std::cerr << "run_set_intersection is not implemented yet.\n";
    return 1;

}


int run_set_difference(sharg::parser & parser)
{
    (void)parser;
    std::cerr << "run_set_difference is not implemented yet.\n";
    return 1;
}
