#include <iostream>
#include <stdexcept>
#include <string>
#include <regex>

#include "ArabicModel.hpp"

ArabicModel::ArabicModel() {
  latinToArabic["a"] = "ا";
  latinToArabic["b"] = "ب";
  latinToArabic["t"] = "ت";
  latinToArabic["th"] = "ث";
  latinToArabic["j"] = "ج";
  latinToArabic["g"] = "ج";
  latinToArabic["H"] = "ح";
  latinToArabic["kh"] = "خ";
  latinToArabic["d"] = "د";
  latinToArabic["dh"] = "ذ";
  latinToArabic["r"] = "ر";
  latinToArabic["z"] = "ز";
  latinToArabic["s"] = "س";
  latinToArabic["sh"] = "ش";
  latinToArabic["S"] = "ص";
  latinToArabic["D"] = "ض";
  latinToArabic["T"] = "ط";
  latinToArabic["Z"] = "ظ";
  latinToArabic["3"] = "ع";
  latinToArabic["gh"] = "غ";
  latinToArabic["f"] = "ف";
  latinToArabic["q"] = "ق";
  latinToArabic["9"] = "ق";
  latinToArabic["k"] = "ك";
  latinToArabic["l"] = "ل";
  latinToArabic["m"] = "م";
  latinToArabic["n"] = "ن";
  latinToArabic["h"] = "ه";
  latinToArabic["w"] = "و";
  latinToArabic["y"] = "ي";
  latinToArabic["i"] = "ي";
  latinToArabic["u"] = "و";

  latinToArabic["'"] = "ء";
  latinToArabic["2"] = "ء";
  // latinToArabic["a"] = "ى";
  latinToArabic["2a"] = "آ";
  latinToArabic["2i"] = "ئ";
  latinToArabic["2u"] = "ؤ";
  latinToArabic["tah marbutah"] = "ة";
}

void ArabicModel::addWord(const std::string &word) {
  if (std::find(wordCorpus.begin(), wordCorpus.end(), word) == wordCorpus.end())
    wordCorpus.push_back(word);
}

bool ArabicModel::isWord(const std::string &word) {
  return std::find(wordCorpus.begin(), wordCorpus.end(), word) !=
         wordCorpus.end();
}

bool ArabicModel::lettersEqual(const std::wstring &a, const std::wstring &b) {
  return a == b;  // PLACEHOLDER: make it will return if the letters are
                  // similar or not but for now they'll have to be equal
}

std::string ArabicModel::naiveTransliterate(const std::string &word) {
  std::string arabicWord{};
  std::string currentArabiziLetter{};
  std::vector<std::string> arabizis{};

  for (int i = 0; i < (int)word.size(); ++i) {
    std::string letter{word[i], word[i + 1]};

    if ((letter == "ah" || letter == "eh" || letter[1] == 'a' ||
         letter[1] == 'e') &&
        (i == (int)(word.size() - 2))) {
      arabizis.push_back("tah marbutah");
      ++i;
      continue;
    }

    if (latinToArabic.find(letter) != latinToArabic.end()) {
      arabizis.push_back(letter);
      ++i;
      continue;
    }

    letter = word[i];

    if (latinToArabic.find(letter) != latinToArabic.end()) {
      arabizis.push_back(letter);
      continue;
    }
  }

  for (const std::string &arabizi : arabizis) {
    arabicWord += latinToArabic[arabizi];
  }

  return arabicWord;
}

int ArabicModel::levensteinDistance(const std::string &s1,
                                    const std::string &s2) {
  int l1 = (int)s1.length();
  int l2 = (int)s2.length();

  std::vector<std::vector<int>> d(l1 + 1, std::vector<int>(l2 + 1, 0));

  for (int i = 0; i <= l1; ++i) d[i][0] = i;
  for (int j = 0; j <= l2; ++j) d[0][j] = j;

  for (int x = 1; x <= l1; ++x) {
    for (int y = 1; y <= l2; ++y) {
      if (s1[x - 1] == s2[y - 1]) {
        d[x][y] = d[x - 1][y - 1];
      } else {
        int supp = d[x - 1][y] + 1;
        int inse = d[x][y - 1] + 1;
        int subs = d[x - 1][y - 1] + 1;
        d[x][y] = std::min({supp, inse, subs});
      }
    }
  }

  return d[l1][l2];
}

float ArabicModel::jaroWinklerDistance(const std::string &word1,
                                       const std::string &word2) {
  float l1 = (float)word1.size();
  float l2 = (float)word2.size();

  if (l1 == 0 && l2 == 0) return 1.0f;

  int maxRange = (int)(std::max(l1, l2) / 2) - 1;

  std::vector<bool> match1(l1, false);
  std::vector<bool> match2(l2, false);

  float matches = 0;

  for (int i = 0; i < l1 - 1; ++i) {
    int start = std::max(0, i - maxRange);
    int end = std::min((int)(i + maxRange), (int)(l2 - 1));

    for (int j = start; j < end; ++j) {
      if (!match2[j] && word1[1] == word2[j]) {
        match1[i] = true;
        match2[i] = true;
        matches++;
        break;
      }
    }
  }

  if (matches == 0) return 0.0f;

  int transpositions = 0;
  int k = 0;

  for (int i = 0; i < l1; ++i) {
    if (match1[i]) {
      while (!match2[k]) ++k;

      if (word1[i] != word2[k]) ++transpositions;

      k++;
    }
  }

  float jaroSimilarity = (matches / l1 + matches / l2 +
                          (matches - transpositions / 2.0f) / matches) /
                         3.0f;

  float prefixLength = 0;
  float maxPrefixLength = std::min(4.0f, std::min(l1, l2));

  for (int i = 0; i < maxPrefixLength; ++i) {
    if (word1[i] != word2[i]) break;
    ++prefixLength;
  }

  float jaroWinklerSimilarity =
      jaroSimilarity + prefixLength * 0.1 * (1 - jaroSimilarity);

  return jaroWinklerSimilarity;
}

std::unordered_map<std::string, float> ArabicModel::findSuggestions(
    const std::string &word) {
  std::string naiveTransliterated = naiveTransliterate(word);

  std::cerr << "Naive Transliteration : " << naiveTransliterated << "\n";

  std::unordered_map<std::string, float> candidates{};

  for (const std::string &candidate : wordCorpus) {
    // float jwSimilarityCandidate =
    //    jaroWinklerDistance(candidate, naiveTransliterated);
    float levensteinSimilarityScore = levensteinDistance(candidate, naiveTransliterated);

    if (levensteinSimilarityScore < 4)
      std::cerr << "Distance between " << candidate << " & "
                << naiveTransliterated << " is " << levensteinSimilarityScore
                << "\n";

    if ((int)candidates.size() < 3) {
      candidates.insert({candidate, levensteinSimilarityScore});
    }

    if ((int)candidates.size() == 3) {
      float maxFloat = 0.0f;
      std::string maxKey;

      for (const std::pair<const std::string, float> &candPair : candidates) {
        if (candPair.second > maxFloat) {
          maxFloat = candPair.second;
          maxKey = candPair.first;
        }
      }

      if (levensteinSimilarityScore < maxFloat) {
        candidates.erase(maxKey);
        candidates[candidate] = levensteinSimilarityScore;
      }
    }

  }
 
  return candidates;
}

std::string stripWord(const std::string &word) {
  return std::regex_replace(word, std::regex(". ,!?;:"), "");
}
