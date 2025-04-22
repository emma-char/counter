#include "commands.hpp"
#include <iostream>
#include "configuration.hpp" 
#include "counting_index.hpp"
#include "kmer_index.hpp"
#include "save_set_opp.hpp"
#include "save_kmer_counts.hpp"
#include "filter.hpp"
#include <sharg/all.hpp>


kmer_index set_union(counting_index const & a, counting_index const & b)
{
    kmer_index result(a.shape);

    for (auto const & [k, _] : a.u)
        result.set.insert(k);

    for (auto const & [k, _] : b.u)
        result.set.insert(k);

    return result;
}

int run_set_union(sharg::parser & parser)
{
    union_arguments args{};

    // Output file. Default: print to terminal 
    parser.add_option(args.output,
        sharg::config{.short_id = 'o',
                      .long_id = "output",
                      .description = "The output file with union.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});

    parser.add_option(args.txt_output,
        sharg::config{.short_id = 't',
                      .long_id = "txt-output",
                      .description = "The output txt file with union.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});

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
    
    kmer_index result = set_union(idx1, idx2);
 
    result.write(args.output);
    save_set_opp(result, args.txt_output);

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
                                        
        parser.add_option(config.txt_output,
                            sharg::config{.short_id = 't',
                                        .long_id = "txt-output",
                                        .description = "The output txt file with kmere and counts.",
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

        parser.add_option(config.count_threshold,
                            sharg::config{ .short_id = 'c',
                                           .long_id = "count-threshold",
                                           .description = "Filter out k-mers that appear less than or equal to this threshold.",
                                           .default_message = "0 (no filtering)"});
    
                                       
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

    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error build] " << ext.what() << "\n";
        return -1;
    }


    counting_index index(config);

    if (config.count_threshold > 0)
    {
        filter_counts(index, config.count_threshold);

    if (config.verbose)
        std::cerr << "Applied count threshold: " << config.count_threshold << '\n';
    }

    index.write(config.output);
    save_kmer_counts(index, config.txt_output);

    if (config.verbose) // If flag is set.
    	std::cerr << "Counting was a success. Congrats!\n";

    
    return 0;
        
}

kmer_index set_intersection(counting_index const & a, counting_index const & b)
{
    kmer_index result(a.shape); // assumes shape is the same

    for (auto const & [k, _] : a.u)
    {
        if (b.u.contains(k))
        {
            result.set.insert(k);
        }
    }
    return result;
}


int run_set_intersection(sharg::parser & parser)
{
    union_arguments args{};

    parser.add_option(args.output,
        sharg::config{.short_id = 'o',
                      .long_id = "output",
                      .description = "The output file with union.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});

    parser.add_option(args.txt_output,
        sharg::config{.short_id = 't',
                      .long_id = "txt-output",
                      .description = "The output txt file with intersection.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});



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
    
    kmer_index result = set_intersection(idx1, idx2);
    save_set_opp(result, args.txt_output);

    result.write(args.output);

    return 0;

}

kmer_index set_difference(counting_index const & a, counting_index const & b)
{
    kmer_index result(a.shape); // assumes same shape in both a and b

    for (auto const & [k, _] : a.u)
    {
        if (!b.u.contains(k))
            result.set.insert(k);
    }
    return result;
}

int run_set_difference(sharg::parser & parser)
{
    union_arguments args{};

    parser.add_option(args.output,
        sharg::config{.short_id = 'o',
                      .long_id = "output",
                      .description = "The output file with union.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});

    parser.add_option(args.txt_output,
        sharg::config{.short_id = 't',
                      .long_id = "txt-output",
                      .description = "The output txt file with difference.",
                      .default_message = "Print to terminal (stdout)",
                      .validator = sharg::output_file_validator{}});



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
    
    kmer_index result = set_difference(idx1, idx2);

    result.write(args.output);
    save_set_opp(result, args.txt_output);

    return 0;
}
