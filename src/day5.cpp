#include <deque>
#include <fstream>
#include <iostream>

int main() {
  std::deque<char> processedUnits;
  std::ifstream inputFile;
  inputFile.open("../inputs/day5.txt");
  if (inputFile.is_open()) {
    char unit;
    while (inputFile.get(unit)) {
      if (processedUnits.empty()) {
        processedUnits.emplace_back(unit);
      } else {
        auto lastUnit = processedUnits.back();
        if ((tolower(lastUnit) == tolower(unit)) &&
            ((std::isupper(lastUnit) && std::islower(unit)) ||
             (std::islower(lastUnit) && std::isupper(unit)))) {
          processedUnits.pop_back();
        } else {
          processedUnits.push_back(unit);
        }
      }
    }
    inputFile.close();
  }

  std::cout << "Number of units remaining: " << processedUnits.size() << "\n";

  return 0;
}
