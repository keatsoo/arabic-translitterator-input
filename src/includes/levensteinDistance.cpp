#include "levensteinDistance.hpp"


int levensteinDistance(const std::string &s1, const std::string &s2) {
    std::vector<std::vector<int>> distances(s1.size() + 1, std::vector<int>(s2.size() + 1));

  int size_1 = (int)s1.size();
  int size_2 = (int)s2.size();

  // Initializing the matrix for the distances
  for (int i = 0; i < size_1; i++) {
    distances[i][0] = 0;
  }
  for (int j = 0; j < size_2; j++) {
    distances[0][j] = 0;
  }

  // Calculating the distances
  for (int i = 1; i <= size_1; i++) {
    for (int j = 1; j <= size_2; j++) {
      if (s1[i - 1] == s2[j - 1]) {
        distances[i][j] = distances[i - 1][j - 1];
      } else {
        int substitution = distances[i - 1][j - 1] + 1;
        int insertion = distances[i][j - 1] + 1;
        int suppression = distances[i - 1][j] + 1;
        distances[i][j] =
            (substitution < insertion
                 ? substitution
                 : (insertion < suppression ? insertion : suppression));
      }
    }
  }

  return distances[size_1][size_2];
}

