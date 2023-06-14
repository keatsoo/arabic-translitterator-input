#ifndef ARABIC_MODEL_HPP
#define ARABIC_MODEL_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>

class ArabicModel {
    
public:
    ArabicModel();

    void addWord(const std::string &word);
    std::unordered_map<std::string, float> findSuggestions(const std::string &word);

    enum textType {
      ARABIC_ONLY,
      ARABIZI_ONLY,
      PUNCTUATION_ONLY,
      DIGITS_ONLY
    };

private:
    std::unordered_map<std::string, std::string> wordCorpus;
    std::unordered_map<std::string, std::string> latinToArabic;
    std::unordered_map<std::wstring, std::string> equalLetters;
    std::unordered_map<std::string, float> convertDigits(const std::string &word);

    int levensteinDistance(const std::string &s1, const std::string &s2);
    std::string naiveTransliterate(const std::string &word);
    std::string stripWord(const std::string &word);
    std::string stemWord(const std::string &word);
    textType checkType(const std::string &word);
};

#endif
