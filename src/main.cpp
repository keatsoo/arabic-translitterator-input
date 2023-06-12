#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "includes/fuzzySearch.hpp"
#include "includes/transliterateNaively.hpp"

using namespace std;

string sentence{};
string corpusString{};
string corpusLine{};
vector<string> corpus{};

int main(int argc, char *argv[]) {
  cout << "Loading the corpus...\n";

  fstream corpusFile;
  corpusFile.open("data/corpuses/quran-simple-plain.txt");

  if (!corpusFile) {
    cerr << "No such file!\n";
    return 1;
  }

  while (getline(corpusFile, corpusLine)) {
    cout << corpusLine;
    corpusString += corpusLine;
  }

  corpusFile.close();

  string temp{};
  for (char c : corpusString) {
    if (c == ' ' || c == '\n') {
      if (temp.size() >= 4) corpus.push_back(temp);
      cout << "temp = " << temp << '\n';
      temp = "";
      continue;
    }
    temp += c;
  }

  cout << "Corpus loaded!\n"
       << "Please enter a word to search : ";
  cin >> sentence;

  cout << "Searching " << sentence << "...\n";

  string naiveTransliterated = transliterateNaively(sentence);
  string closestFound = fuzzySearch(naiveTransliterated, corpus);

  cout << "Closest word found is : " << closestFound << endl;

  return 0;
}
