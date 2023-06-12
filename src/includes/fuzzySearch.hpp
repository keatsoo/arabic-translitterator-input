#ifndef FUZZYSEARCH_H
#define FUZZYSEARCH_H

#include <string>
#include <vector>
#include "levensteinDistance.hpp"

std::string fuzzySearch(const std::string &word, std::vector<std::string> corpus);

#endif
