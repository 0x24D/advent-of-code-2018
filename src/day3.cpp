#include <deque>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <utility>

int main() {
    std::deque<std::deque<int>> claims;
    std::deque<std::deque<int>> fabric(1000, std::deque<int>(1000, 0));
    std::ifstream inputFile;
    inputFile.open("../inputs/day3.txt");
    int numberOfClaims = 0;
    int currentClaim = 0;
    if (inputFile.is_open()) {
        std::string inches, rect;
        while (inputFile >> inches >> inches >> inches >> rect) {
            ++currentClaim;
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
                  if (fabric[i][j] == 0) {
                    fabric[i][j] = currentClaim;
                  } else {
                    fabric[i][j] = -1;
                  }
                }
            }
        }
        inputFile.close();
    }
    for (int i = 0; i < fabric.size(); ++i) {
        numberOfClaims += (std::count_if(fabric[i].begin(), fabric[i].end(), [](int n) { return n == -1; }));
    }
    std::cout << "Number of inches with two or more claims: " << numberOfClaims << "\n";

    // part 2
    for (int c = 0; c < claims.size(); ++c) {
        auto leftInches = claims[c][0];
        auto topInches = claims[c][1];
        auto rectWidth = claims[c][2];
        auto rectHeight = claims[c][3];

        bool stop = false;
        for (int i = leftInches + rectWidth; i > leftInches; --i) {
            for (int j = topInches + rectHeight; j > topInches; --j) {
                if (fabric[i][j] == -1) {
                    stop = true;
                    break;
                }
            }
            if (stop) {
                break;
            }
        }
        if (!stop) {
            std::cout << "Claim " << c + 1 << " does not overlap\n";
        }
    }

    return 0;
}
