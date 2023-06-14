#ifndef ARABIC_MODEL_HPP
#define ARABIC_MODEL_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class ArabicModel {
    
public:
    ArabicModel();

    void addWord(const std::string &word);
    bool isWord(const std::string &word);
    std::unordered_map<std::string, float> findSuggestions(const std::string &word);

private:
    std::vector<std::string> wordCorpus;
    std::unordered_map<std::string, std::string> latinToArabic;
    std::unordered_map<std::wstring, std::string> equalLetters;

    float jaroWinklerDistance(const std::string &word1, const std::string &word2);
    int levensteinDistance(const std::string &s1, const std::string &s2);
    std::string naiveTransliterate(const std::string &word);
    bool lettersEqual(const std::wstring &a, const std::wstring &b);
    std::string stripWord(const std::string &word);
};

#endif
