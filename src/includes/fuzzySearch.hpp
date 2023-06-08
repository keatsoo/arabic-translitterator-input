#ifndef FUZZYSEARCH_H
#define FUZZYSEARCH_H

#include <string>
#include <map>
#include "levensteinDistance.hpp"

std::string fuzzySearch(const std::string &word, const std::map<std::string, std::string> words);

#endif
