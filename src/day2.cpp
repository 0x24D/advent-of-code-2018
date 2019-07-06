#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::ifstream inputFile;
  std::vector<std::string> fileStrings;
  inputFile.open("../inputs/day2.txt");
  std::istream_iterator<std::string> input(inputFile);
  std::copy(input, std::istream_iterator<std::string>(),
            std::back_inserter(fileStrings));
  std::sort(fileStrings.begin(), fileStrings.end());

  // part 1
  std::vector<char> alphabet(26);
  std::iota(alphabet.begin(), alphabet.end(), 'a');
  int twoLetters = 0;
  int threeLetters = 0;
  for (std::string str : fileStrings) {
    bool twoChars = false;
    bool threeChars = false;
    std::sort(str.begin(), str.end());
    for (char aToZ : alphabet) {
      int count = std::count(str.begin(), str.end(), aToZ);
      if (count == 2)
        twoChars = true;
      else if (count == 3)
        threeChars = true;
      if (twoChars && threeChars)
        break;
    }
    if (twoChars)
      ++twoLetters;
    if (threeChars)
      ++threeLetters;
  }
  std::cout << twoLetters << " * " << threeLetters << " = "
            << twoLetters * threeLetters << "\n";

  // part 2
  bool found = false;
  int lhsIndex = 0;
  int rhsIndex = 0;
  for (int i = 0; i < fileStrings.size(); ++i) {
    for (int j = (i + 1); j < fileStrings.size(); ++j) {
      int numOfDiffs = 0;
      std::string lhs = fileStrings[i];
      std::string rhs = fileStrings[j];
      for (int i = 0; i < lhs.length(); ++i) {
        if (lhs[i] != rhs[i])
          ++numOfDiffs;
        if (numOfDiffs == 2)
          break;
      }
      if (numOfDiffs == 1) {
        found = true;
        lhsIndex = i;
        rhsIndex = j;
        break;
      }
    }
    if (found)
      break;
  }

  std::string lhsString = fileStrings[lhsIndex];
  std::string rhsString = fileStrings[rhsIndex];
  std::string commonString = lhsString;
  for (int i = 0; i < lhsString.size(); ++i) {
    if (lhsString[i] != rhsString[i])
      commonString.erase(commonString.begin() + i);
  }
  std::cout << "Found common chars: " << lhsString << " " << rhsString << ": "
            << commonString << "\n";

  return 0;
}
