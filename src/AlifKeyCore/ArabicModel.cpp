#include <iostream>
#include <stdexcept>
#include <string>

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
    std::string m_word = stripWord(word);
    if (wordCorpus.find(m_word) == wordCorpus.end())
        wordCorpus.insert({m_word, stemWord(m_word)});
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

    std::cout << "Created that awkward vector!!!\n";

    for (int i = 0; i <= l1; ++i)
        d[i][0] = i;
    for (int j = 0; j <= l2; ++j)
        d[0][j] = j;

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

ArabicModel::textType ArabicModel::checkType(const std::string &word) {
    std::cout << "Checking type" << std::endl;
    /*
    if (std::regex_match(word, std::regex("[0-9]+"))) return
    textType::DIGITS_ONLY; if (std::regex_match(word,
    std::regex("[\\u0600-\\u06FF]+"))) return textType::ARABIC_ONLY; if
    (std::regex_match(word, std::regex("[[:punct:]]+"))) return
    textType::PUNCTUATION_ONLY;
  */
    return textType::ARABIZI_ONLY;
}

std::unordered_map<std::string, float>
ArabicModel::convertDigits(const std::string &word) {
    std::string output{};
    for (char c : word) {
        if (c >= '0' && c <= '9') {
            output.push_back(c - '0' + 0x0600);
        }
    }
    std::unordered_map<std::string, float> outMap{{output, 0.0}};
    return outMap;
}

std::unordered_map<std::string, float>
ArabicModel::findSuggestions(const std::string &word) {

    std::unordered_map<std::string, float> candidates{};
    std::vector<std::string> candidatesAfterComparingStems{};

    textType wordType = checkType(word);

    if (wordType == textType::DIGITS_ONLY)
        return convertDigits(word);
    if (wordType == textType::PUNCTUATION_ONLY ||
        wordType == textType::ARABIC_ONLY) {
        candidates[word] = 0.0f;
        return candidates;
    }

    std::string naiveTransliterated = naiveTransliterate(word);

    std::string stemmed = stemWord(naiveTransliterated);

    for (const std::pair<const std::string, std::string> &corpusWordPair :
         wordCorpus) {
        std::string stemmedCorpus = corpusWordPair.second;
        if (levensteinDistance(stemmedCorpus, stemmed) < 3) {
            candidatesAfterComparingStems.push_back(corpusWordPair.first);
        }
    }

    for (const std::pair<const std::string, std::string> &candidatePair :
         wordCorpus) {
        std::string candidate = candidatePair.first;
        float levensteinSimilarityScore =
            levensteinDistance(candidate, naiveTransliterated);

        std::cout << "no levenstein Distance?\n";

        float stemFactor =
            std::find(candidatesAfterComparingStems.begin(),
                      candidatesAfterComparingStems.end(),
                      candidate) != candidatesAfterComparingStems.end()
                ? 2.0f
                : 1;

        if (levensteinSimilarityScore < 4)
            std::cerr << "Distance between " << candidate << " & "
                      << naiveTransliterated << " is "
                      << levensteinSimilarityScore << "\n";

        if ((int)candidates.size() < 3) {
            candidates.insert({candidate, levensteinSimilarityScore});
        }

        if ((int)candidates.size() == 3) {
            float maxFloat = 0.0f;
            std::string maxKey;

            for (const std::pair<const std::string, float> &candPair :
                 candidates) {
                if (candPair.second > maxFloat) {
                    maxFloat = candPair.second;
                    maxKey = candPair.first;
                }
            }

            if (levensteinSimilarityScore < maxFloat) {
                candidates.erase(maxKey);
                candidates[candidate] = levensteinSimilarityScore / stemFactor;
            }
        }
    }

    return candidates;
}

std::string ArabicModel::stripWord(const std::string &word) {
    std::cout << "Stripping word" << std::endl;
    return std::regex_replace(word, std::regex("[[:punct:]]"), "");
}

std::string ArabicModel::stemWord(const std::string &word) {
    std::cout << "Stemming word" << std::endl;

    std::string output = std::regex_replace(
        word, std::regex("[\\u064B-\\u0652\\u0670\\u0629]"), "");

    if (output.length() <= std::string("ااا").length()) {
        return output;
    }

    std::vector<std::pair<std::regex, std::string>> patterns = {
        // Prefixes
        {std::regex("^ال"), ""}, // Al-
        {std::regex("^و"), ""},  // Wa-
        {std::regex("^ب"), ""},  // Bi-
        {std::regex("^ف"), ""},  // Fa-
        {std::regex("^ل"), ""},  // Li-
        {std::regex("^ك"), ""},  // Ka-
        {std::regex("^م"), ""},  // Ma-
        {std::regex("^ن"), ""},  // Na-
        {std::regex("^س"), ""},  // Sa-
        {std::regex("^ي"), ""},  // Ya-
        {std::regex("^ت"), ""},  // Ta-
        {std::regex("^أ"), ""},  // Alef with Hamza above
        {std::regex("^إ"), ""},  // Alef with Hamza below
        {std::regex("^آ"), ""},  // Alef with Madda above

        // Suffixes
        {std::regex("ات$"), ""},  // Feminine plural
        {std::regex("اتي$"), ""}, // My feminine plural
        {std::regex("ان$"), ""},  // Dual
        {std::regex("ون$"), ""},  // Masculine plural
        {std::regex("ين$"), ""},  // Masculine plural
        {std::regex("ة$"), ""},   // Feminine singular
        {std::regex("ها$"), ""},  // Her
        {std::regex("ه$"), ""},   // Her
        {std::regex("نا$"), ""},  // Us
        {std::regex("ي$"), ""},   // My
        {std::regex("ى$"), ""},   // My
        {std::regex("يا$"), ""},  // O
        {std::regex("ا$"), ""},   // Alef
        {std::regex("تما$"), ""}, // Both of them
        {std::regex("تم$"), ""},  // Both
        {std::regex("تن$"), ""},  // Their
        {std::regex("وا$"), ""},  // They

        {std::regex("([اوي])\\1"), "$1"}};

    for (std::pair<std::regex, std::string> &pair : patterns) {
        output = std::regex_replace(output, pair.first, pair.second);

        if (output.length() <= std::string("ااا").length()) {
            return output;
        }
    }

    return output;
}
