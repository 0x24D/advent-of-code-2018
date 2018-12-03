#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main() {

    std::vector<std::vector<int>> fabric(1000, std::vector<int>(1000, 0));
    std::ifstream inputFile;
    inputFile.open("../inputs/day3.txt");
    int numberOfClaims = 0;
    if (inputFile.is_open()) {
        std::string inches, rect;
        while (inputFile >> inches >> inches >> inches >> rect) {
            auto commaDelimiter = inches.find(",");
            auto colonDelimiter = inches.find(":");
            auto xDelimiter = rect.find("x");
            int leftInches = std::atoi(inches.substr(0, commaDelimiter).c_str());
            int topInches = std::atoi(inches.substr(commaDelimiter + 1, colonDelimiter - commaDelimiter - 1).c_str());
            int rectWidth = std::atoi(rect.substr(0, xDelimiter).c_str());
            int rectHeight = std::atoi(rect.substr(xDelimiter + 1).c_str());
            for (int i = leftInches + rectWidth; i > leftInches; --i) {
                for (int j = topInches + rectHeight; j > topInches; --j) {
                    ++fabric[i][j];
                }
            }
        }
        inputFile.close();
    }
    for (int i = 0; i < fabric.size(); ++i) {
        numberOfClaims += (std::count_if(fabric[i].begin(), fabric[i].end(), [](int n) { return n >= 2; }));
    }
    std::cout << "Number of inches with two or more claims: " << numberOfClaims << "\n";
    return 0;
}
