#include "fuzzySearch.hpp"
#include <iostream>

std::string fuzzySearch(const std::string &word, const std::map<std::string, std::string> words) {
    std::string closest {};
    int smallestDistance{100};

    for (std::map<std::string, std::string>::const_iterator iter = words.begin(); iter != words.end(); ++iter) {
        std::string proposition = iter->first;
        //std::cout << "what? yeah " << proposition << "\n";
        int distance = levensteinDistance(proposition, word);
        if (distance < smallestDistance) {
            smallestDistance = distance;
            closest = iter->second;
        }
    }

    return closest;
}

