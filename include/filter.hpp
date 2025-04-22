#pragma once

#include <iostream>
#include <counting_index.hpp>
#include <unordered_map>


void filter_counts(counting_index & index, uint64_t threshold)
{
    for (auto it = index.u.begin(); it != index.u.end(); )
    {
        if (it->second <= threshold)
            it = index.u.erase(it);
        else
            ++it;
    }
}