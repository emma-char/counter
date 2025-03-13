// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#pragma once

#include <string>
#include <charconv>

#include <seqan3/search/kmer_index/shape.hpp>

/*! \brief Function, converting a std::string to a seqan3::shape.
 *  \param std::string The string shape.
 *
 *  Simple function, converting fastq files to fasta files using the seqan3 library.
 *  For more information about the SeqAn Library functions see https://docs.seqan.de/seqan3/main_user.
 */
seqan3::shape get_shape(std::string const & shape_str);
