#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "includes/fuzzySearch.hpp"

using namespace std;

string sentence{};
vector<string> words{};
map<string, string> dictionary{{"marhaban", "MAR7ABN"},
                               {"ahlan", "AHLN"},
                               {"fadaa'", "FAD.AA2"}};

int main(int argc, char *argv[]) {
  getline(cin, sentence);

  string s{};
  for (int i = 0; i < (int)sentence.size(); i++) {
    if (sentence[i] == ' ') {
      words.push_back(s);
      s = "";
    } else {
      s += sentence[i];
    }
  }
  words.push_back(s);

  cout << "closest word is : " << fuzzySearch(words[0], dictionary) << endl;

  return 0;
}

