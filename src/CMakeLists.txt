# SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: CC0-1.0

cmake_minimum_required (VERSION 3.25)

# An object library (without main) to be used in multiple targets.
# You can add more external include paths of other projects that are needed for your project.
add_library (counter_lib STATIC get_shape.cpp get_kmer_from_hash.cpp commands.cpp save_set_opp.cpp save_kmer_counts.cpp)
target_include_directories (counter_lib PUBLIC "${counter_SOURCE_DIR}/include")
target_link_libraries (counter_lib PUBLIC seqan3::seqan3 sharg::sharg seqan::hibf
                                                    fmindex-collection::fmindex-collection
)

target_compile_options (counter_lib PUBLIC "-pedantic" "-Wall" "-Wextra")

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Disable warning about std::hardware_destructive_interference_size not being ABI-stable.
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
        target_compile_options (counter_lib PUBLIC "-Wno-interference-size")
    endif ()

    # Warn about failed return value optimization.
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14)
        target_compile_options (counter_lib PUBLIC "-Wnrvo")
    endif ()
endif ()

# Add the application.
add_executable (counter main.cpp)
target_link_libraries (counter PRIVATE counter_lib)
