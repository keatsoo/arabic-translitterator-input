#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "AlifKeyCore/ArabicModel.hpp"

using namespace std;

string sentence{};
vector<string> corpus{};

ArabicModel model{};

vector<string> loadCorpus(const vector<string> &files);

int main(int argc, char *argv[]) {
  if (argc == 2)
    sentence = argv[1];
  else {
    cout << "Enter the word to search: ";
    cin >> sentence;
  }

  vector<string> filenames{"./data/corpuses/chat-gpt-sample-poem.txt"};

  corpus = loadCorpus(filenames);

  for (string word : corpus) {
    model.addWord(word);
  }

  unordered_map<string, float> candidates = model.findSuggestions(sentence);

  vector<pair<string, float>> vec{};
  for (const pair<const string, float> &myPair : candidates) {
    vec.push_back(myPair);
  }

  sort(vec.begin(), vec.end(),
       [](const pair<string, float> &a, const pair<string, float> &b) {
         return a.second < b.second;
       });

  for (int i = 0; i < (int)vec.size(); ++i) {
    cout << i + 1 << ". " << vec[i].first << " (" << vec[i].second << ")\n";
  }

  return EXIT_SUCCESS;
}

vector<string> loadCorpus(const vector<string> &files) {
  string tempCorpus{};
  char corpusChar{};

  vector<string> outWords{};

  ifstream file;
  for (string fileName : files) {
    file.open(fileName);

    while (file >> noskipws >> corpusChar) {
      if (corpusChar == ' ' || corpusChar == '\n') {
        outWords.push_back(tempCorpus);
        tempCorpus.clear();
        continue;
      }
      tempCorpus += corpusChar;
    }

    file.close();
  }

  return outWords;
}
