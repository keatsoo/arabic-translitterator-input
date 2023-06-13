#include <iostream>
#include <stdexcept>
#include <string>

#include "ArabicModel.hpp"

ArabicModel::ArabicModel() {
  latinToArabic["A"] = "ا";
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
  latinToArabic["a"] = "ى";
  latinToArabic["2a"] = "آ";
  latinToArabic["2i"] = "ئ";
  latinToArabic["2u"] = "ؤ";
  latinToArabic["tah marbutah"] = "ة";
}

void ArabicModel::addWord(const std::string &word) {
  if (std::find(wordCorpus.begin(), wordCorpus.end(), word) == wordCorpus.end()) wordCorpus.push_back(word); 
}

bool ArabicModel::isWord(const std::string &word) {
  return std::find(wordCorpus.begin(), wordCorpus.end(), word) != wordCorpus.end();
}

bool ArabicModel::lettersEqual(const std::wstring &a, const std::wstring &b) {
  return a == b;  // PLACEHOLDER: make it will return if the letters are
                  // similar or not but for now they'll have to be equal
}

std::string ArabicModel::naiveTransliterate(const std::string &word) {
  std::string arabicWord{};
  std::string currentArabiziLetter{};
  std::vector<std::string> arabizis{};

  for (int i = 0; i < word.size(); ++i) {
    std::string letter{word[i], word[i + 1]};

    if ((letter == "ah" || letter == "eh" || letter[1] == 'a' ||
         letter[1] == 'e') &&
        (i == word.size() - 2)) {
      arabizis.push_back("tah marbutah");
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

float ArabicModel::jaroWinklerDistance(const std::string &word1,
                                       const std::string &word2) {
  float l1 = (float)word1.size();
  float l2 = (float)word2.size();

  if (l1 == l2 == 0) return 1.0f;

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

  for (const std::string candidate : wordCorpus) {
    float jwSimilarityCandidate = jaroWinklerDistance(candidate, naiveTransliterated);

    std::cerr << "Distance between " << candidate << " & " << naiveTransliterated << " is " << jwSimilarityCandidate << "\n";

    if (jwSimilarityCandidate > 1.0f)
      throw std::range_error("Jaro-Winkler Distance is over 1!");

    if ((int)candidates.size() < 3) {
      candidates.insert({candidate, jwSimilarityCandidate});
    }

    if ((int)candidates.size() == 3) {
      float minFloat = 2.0f;
      std::string minKey{};

      for (const std::pair<std::string, float> &candPair : candidates) {
        if (candPair.second < minFloat) {
          minFloat = candPair.second;
          minKey = candPair.first;
        }
      }

      if (minFloat <= jwSimilarityCandidate) {
        candidates[candidate] = jwSimilarityCandidate;
      }
    }

    if ((int)candidates.size() > 3) {

      float minFloat = 2.0f;
      std::string minKey{};

      for (const std::pair<std::string, float> &candPair : candidates) {
        if (candPair.second < minFloat) {
          minFloat = candPair.second;
          minKey = candPair.first;
        }
      }

      candidates.erase(minKey);

    }
  }


  return candidates;
}
