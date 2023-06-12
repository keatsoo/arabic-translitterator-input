#include <algorithm>
#include <iostream>

#include "fuzzySearch.hpp"
#include "jaroWinklerDistance.hpp"

std::string removeCharacters(const std::string& input,
                             const std::string& charactersToRemove) {
  std::string result = input;
  result.erase(std::remove_if(result.begin(), result.end(),
                              [&charactersToRemove](char c) {
                                return charactersToRemove.find(c) !=
                                       std::string::npos;
                              }),
               result.end());
  return result;
}

std::string fuzzySearch(const std::string& word,
                        std::vector<std::string> corpus) {
  std::string closest{};
  float biggestSimilarity{0};

  for (std::string proposition : corpus) {
    if (proposition == "") continue;
    float distance = jaroWinklerDistance(
        removeCharacters(
            proposition,
            "\u064B\u064C\u064D\u064E\u064F\u0650\u0651\u0652\u0653\u0654\u0655"
            "\u0656\u0657\u0658\u0659\u065A\u065B\u065C\u065D\u065E\u065F"
        ),
        word);

    if (distance > 0.95) return proposition;
    if (distance > biggestSimilarity) {
      biggestSimilarity = distance;
      closest = proposition;
      std::cout << "Distance for " << proposition << " and " << word << " is " << distance << "\n";
    }
  }

  return closest;
}
