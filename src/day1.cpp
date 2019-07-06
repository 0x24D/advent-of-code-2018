#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::ifstream inputFile;
  std::vector<int> fileIntegers;
  inputFile.open("../inputs/day1.txt");
  std::istream_iterator<int> input(inputFile);
  std::copy(input, std::istream_iterator<int>(),
            std::back_inserter(fileIntegers));

  // part 1
  int totalResult = 0;
  totalResult =
      std::accumulate(fileIntegers.begin(), fileIntegers.end(), totalResult);
  std::cout << "Resulting frequency is: " << totalResult << "\n";

  // part 2
  bool duplicateNumber = false;
  int duplicateFrequency = 0;
  std::vector<int> pastFrequencies;
  do {
    for (int i : fileIntegers) {
      duplicateFrequency += i;
      if (std::find(pastFrequencies.begin(), pastFrequencies.end(),
                    duplicateFrequency) != pastFrequencies.end()) {
        duplicateNumber = true;
        break;
      } else {
        pastFrequencies.push_back(duplicateFrequency);
      }
    }
  } while (!duplicateNumber);
  std::cout << "Got duplicate frequency: " << duplicateFrequency << "\n";
  return 0;
}
