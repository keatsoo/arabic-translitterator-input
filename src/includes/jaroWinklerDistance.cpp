#include "jaroWinklerDistance.hpp"

float jaroWinklerDistance(std::string str1, std::string str2) {
  int len1 = (int)str1.size();
  int len2 = (int)str2.size();

  int matchRange = (int)(std::max(len1, len2) / 2) - 1;
  std::vector<char> matches1{};
  std::vector<char> matches2{};

  for (int i = 0; i < len1; i++) {
    for (int j = std::max(0, i - matchRange);
         j < std::min(i + matchRange + 1, len2); j++) {
      if (str1[i] == str2[j]) {
        matches1.push_back(str1[i]);
        matches2.push_back(str2[i]);
        break;
      }
    }
  }

  int numMatches = matches1.size();
  if (numMatches == 0) return 0.0f;

  int transpositions{0};
  for (int i = 0; i < numMatches; i++) {
    if (matches1[i] != matches2[i]) {
      transpositions++;
    }
  }

  float similarity = ((float)numMatches / len1 + (float)numMatches / len2 +
                      (float)(numMatches - transpositions) / numMatches) /
                     3;

  float jaroDist = similarity;

  float prefixLength = 0;
  int maxPrefixLength = std::min(4, std::min(len1, len2));

  for (int i = 0; i < maxPrefixLength; i++) {
    if (str1[i] != str2[i]) break;
    prefixLength++;
  }

  float jaroWinklerDistance = jaroDist + 0.1 * prefixLength * (1 - jaroDist);

  return jaroWinklerDistance;
}
