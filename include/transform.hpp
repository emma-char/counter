#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <seqan3/search/kmer_index/shape.hpp>

/*int transform_base4(int x){
    
    int num = 0;
    int i = 0;

    while(x > 0)
    {
        int b = x % 4; // Rest
        num = (b * pow(10, i)) + num;
        x /= 4; // Ganzzahldivision
        i++;
    }
    return num;

}
*/

std::string transform_to_dna(int x) {

    std::string dna{};
    std::string mapping = "ACGT";  // 0 → A, 1 → C, 2 → G, 3 → T

    if (x == 0) return "A";

    while (x > 0) {
        int rest = x % 4;  
        dna += mapping[rest];
        x /= 4;
    }

    std::reverse(dna.begin(), dna.end());
    return dna;
}