// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include "get_shape.hpp"

seqan3::shape get_shape(std::string const & shape_str)
{
    uint64_t bin_shape{};
    std::from_chars(shape_str.data(), shape_str.data() + shape_str.size(), bin_shape, 2);
    return seqan3::shape(seqan3::bin_literal{bin_shape});
}
