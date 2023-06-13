#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ArabicModelCore/ArabicModel.hpp"

using namespace std;

string sentence{};
string tempCorpus{};
vector<string> corpus{};
char corpusChar{};

ArabicModel model{};

int main(int argc, char *argv[])
{
  if (argc == 2) sentence = argv[1];
  else {
    cout << "Enter the word to search: ";
    cin >> sentence;
  }

  ifstream file;
  file.open("./data/corpuses/chat-gpt-sample-poem.txt");

  while (file >> noskipws >> corpusChar) {
    if (tempCorpus == " " || tempCorpus == "\n") {
      corpus.push_back(tempCorpus);
      tempCorpus.clear();
      continue;
    }
    tempCorpus += corpusChar;
  }

  file.close();

  for (string word : corpus) {
    model.addWord(word);
  }

  unordered_map<string, float> candidates = model.findSuggestions(sentence);

  vector<pair<string, float>> vec{};
  for (const pair<string, float> &pair : candidates) {
    vec.push_back(pair);
  }

  sort(vec.begin(), vec.end(), [](const pair<string, float> &a, const pair<string, float> &b){
        return a.second > b.second;
  });

  for (int i = 0; i < vec.size(); ++i) {
    cout << i + 1 << ". " << vec[i].first << "\n";
  }

  return EXIT_SUCCESS;
}
