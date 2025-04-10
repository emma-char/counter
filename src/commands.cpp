#include "commands.hpp"
#include <iostream>
#include "configuration.hpp" 
#include "counting_index.hpp"
#include <sharg/all.hpp>

// =====================================================================================================================
// Push/Pull Implementierungen
// =====================================================================================================================

int run_git_pull(sharg::parser & parser)
{
    pull_arguments args{};
 
    parser.add_positional_option(args.repository, sharg::config{.description = "The repository name to pull from."});
    parser.add_positional_option(args.branch, sharg::config{.description = "The branch name to pull from."});
 
    try
    {int run_git_pull(sharg::parser & parser);
        struct pull_arguments
        {
            std::string repository{};
            std::string branch{};
            bool progress{false};
        };
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error git pull] " << ext.what() << "\n";
        return -1;
    }
 
    std::cerr << "Git pull with repository " << args.repository << " and branch " << args.branch << '\n';
 
    return 0;
}

int run_git_push(sharg::parser & parser)
{
    push_arguments args{};
 
    parser.add_positional_option(args.repository, sharg::config{.description = "The repository name to push to."});
    parser.add_positional_option(args.branches, sharg::config{.description = "The branch names to push."});
 
    try
    {
        parser.parse();
    }
    catch (sharg::parser_error const & ext)
    {
        std::cerr << "[Error git push] " << ext.what() << "\n";
        return -1;
    }
 
    std::cerr << "Git push with repository " << args.repository << " and branches ";
    for (auto && branch : args.branches)
        std::cerr << branch << ' ';
    std::cerr << '\n';
 
    return 0;
}

// =====================================================================================================================
// Mengenoperationen Implementierungen
// =====================================================================================================================

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

    std::unordered_map<uint64_t, uint64_t> index1;
    std::unordered_map<uint64_t, uint64_t> index2;

    
    //counting_index idx1 = load(args.index_file1);

    std::unordered_map<uint64_t, uint64_t> result = index1;

    for (auto &[k, v] : index2)
        result[k] += v;

    std::cout << "Union result has " << result.size() << " unique minimizers.\n";

    return 0;
}

/*int run_set_intersection(sharg::parser & parser)
{
    //set_arguments args;

    parser.add_positional_option(args.input_files, sharg::config{.description = "FASTA files to index and intersect."});
    
    try { parser.parse(); }
    catch (sharg::parser_error const & e)
    {
        std::cerr << "[Set Intersection Error] " << e.what() << '\n';
        return -1;
    }

    std::unordered_map<uint64_t, uint64_t> result;
    bool first_file = true;
    
    // Iteriere über die Dateien und berechne die Intersection
    for (auto const & file : args.input_files)
    {
        configuration cfg{.fasta_input = file, .shape = seqan3::ungapped{16}};
        auto idx = build_index(cfg);

        if (first_file)
        {
            result = std::move(idx); // Das erste Index übernehmen
            first_file = false;
        }
        else
        {
            // Intersection durch den Vergleich der beiden Indizes
            for (auto it = result.begin(); it != result.end();)
            {
                auto idx_it = idx.find(it->first);
                if (idx_it == idx.end())
                    it = result.erase(it); // Element entfernen, wenn es nicht im zweiten Index ist
                else
                {
                    // Minimale Häufigkeit beider Indizes
                    it->second = std::min(it->second, idx_it->second);
                    ++it;
                }
            }
        }
    }

}


int run_set_difference(sharg::parser & parser)
{
    // Implementierung für Difference
}
*/