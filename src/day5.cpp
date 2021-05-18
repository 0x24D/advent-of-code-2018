#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>

void processChar(std::deque<char> &processedUnits, const int unit) {
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

int main() {
    std::deque<char> processedUnits;
    std::ifstream inputFile;
    inputFile.open("inputs/day5.txt");
    if (inputFile.is_open()) {
        char unit;
        while (inputFile.get(unit)) {
            processChar(processedUnits, unit);
        }
        inputFile.close();
    } else {
        std::cerr
            << "Couldn't find input file, expected to run from root directory: e.g. ./bin/day-5\n";
        return 1;
    }

    std::cout << "Number of units remaining: " << processedUnits.size() << "\n";

    // part 2
    std::deque<int> numberOfUnits(26, 0);
    for (int i = 0; i < numberOfUnits.size(); ++i) {
        processedUnits.clear();
        inputFile.open("inputs/day5.txt");
        if (inputFile.is_open()) {
            char unit;
            while (inputFile.get(unit)) {
                auto charToEmit = static_cast<char>(i + 97);
                if (std::tolower(unit) != charToEmit) {
                    processChar(processedUnits, unit);
                }
            }
        }
        inputFile.close();
        numberOfUnits[i] = processedUnits.size();
    }

    auto smallestPolymer = std::min_element(numberOfUnits.begin(), numberOfUnits.end());
    std::cout << "Smallest polymer: " << *smallestPolymer << "\n";

    return 0;
}
