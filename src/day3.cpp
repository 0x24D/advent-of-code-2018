#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

int main() {
    std::vector<std::vector<int>> claims(1336);
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

            claims.push_back({ leftInches, topInches, rectWidth, rectHeight });

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

    // part 2
    for (auto fab : fabric) {
        std::fill(fab.begin(), fab.end(), 0);
    }

    for (int c = 0; c < claims.size(); ++c) {
        auto vec = claims[c];
        for (int v = 0; v < vec.size(); ++v) {
            int leftInches = vec[0];
            int topInches = vec[1];
            int rectWidth = vec[2];
            int rectHeight = vec[3];
            for (int i = leftInches + rectWidth; i > leftInches; --i) {
                for (int j = topInches + rectHeight; j > topInches; --j) {
                    if (fabric[i][j] != 0) { // incorrect
                        fabric[i][j] = -1;
                    } else {
                        fabric[i][j] = (i + 1);
                    }
                }
            }
        }
    }

    std::pair<int, int> topLeftIndex, topRightIndex, bottomLeftIndex, bottomRightIndex;

    for (int i = 0; i < fabric.size(); ++i) {
        auto vec = fabric[i];
        for (int j = 0; j < vec.size(); ++j) {
            int element = vec[j];
            if (element != 0 && element != -1) {
                topLeftIndex = {i, j};
            }
        }
    }

    for (int i = 0; i < fabric.size(); ++i) {
        auto vec = fabric[i];
        for (int j = vec.size(); j > 0; --j) {
            int element = vec[j];
            if (element != 0 && element != -1) {
                topRightIndex = {i, j};
            }
        }
    }

    for (int i = fabric.size() - 1; i >= 0; --i) {
        auto vec = fabric[i];
        for (int j = 0; j < vec.size(); ++j) {
            int element = vec[j];
            if (element != 0 && element != -1) {
                bottomLeftIndex = {i, j};
            }
        }
    }

    for (int i = fabric.size() - 1; i >= 0; --i) {
        auto vec = fabric[i];
        for (int j = vec.size(); j > 0; --j) {
            int element = vec[j];
            if (element != 0 && element != -1) {
                bottomRightIndex = {i, j};
            }
        }
    }

    std::cout << "[" << topLeftIndex.first << "," << topLeftIndex.second << "]\n";
    std::cout << "[" << topRightIndex.first << "," << topRightIndex.second << "]\n";
    std::cout << "[" << bottomLeftIndex.first << "," << bottomLeftIndex.second << "]\n";
    std::cout << "[" << bottomRightIndex.first << "," << bottomRightIndex.second << "]\n";

    return 0;
}
