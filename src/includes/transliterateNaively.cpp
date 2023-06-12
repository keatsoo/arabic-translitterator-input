#include "transliterateNaively.hpp"

std::string transliterateNaively(std::string string) {
  std::map<std::string, std::string> arabiziToArabic;

  // Add mappings for each Arabizi string to its corresponding Arabic character
  arabiziToArabic["a"] = "ا";
  arabiziToArabic["b"] = "ب";
  arabiziToArabic["t"] = "ت";
  arabiziToArabic["th"] = "ث";
  arabiziToArabic["j"] = "ج";
  arabiziToArabic["h"] = "ح";
  arabiziToArabic["7"] = "ح";
  arabiziToArabic["kh"] = "خ";
  arabiziToArabic["d"] = "د";
  arabiziToArabic["dh"] = "ذ";
  arabiziToArabic["r"] = "ر";
  arabiziToArabic["z"] = "ز";
  arabiziToArabic["s"] = "س";
  arabiziToArabic["sh"] = "ش";
  arabiziToArabic["s"] = "ص";
  arabiziToArabic["3"] = "ع";
  arabiziToArabic["gh"] = "غ";
  arabiziToArabic["f"] = "ف";
  arabiziToArabic["9"] = "ق";
  arabiziToArabic["q"] = "ق";
  arabiziToArabic["k"] = "ك";
  arabiziToArabic["l"] = "ل";
  arabiziToArabic["m"] = "م";
  arabiziToArabic["n"] = "ن";
  arabiziToArabic["h"] = "ه";
  arabiziToArabic["w"] = "و";
  arabiziToArabic["y"] = "ي";
  arabiziToArabic["i"] = "ي";

  std::string arabified{};

  for (int i = 0; i < string.size(); ++i) {
    std::string currentArabizi{string[i]};

    if (i < string.size() - 1 && string[i + 1] == 'h' &&
        arabiziToArabic.find(currentArabizi + 'h') != arabiziToArabic.end()) {
      currentArabizi = currentArabizi + 'h';
      ++i;
    }

    arabified += arabiziToArabic[currentArabizi];
  }

  return arabified;
}
