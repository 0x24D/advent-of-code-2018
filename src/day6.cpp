#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <utility>

int main() {
    std::deque<std::pair<int, int>> coords;
    std::ifstream inputFile;
    inputFile.open("../inputs/day6.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            auto comma = std::find(line.begin(), line.end(), ',');
            auto index = std::distance(line.begin(), comma);
            auto xCoord = std::stoi(line.substr(0, index));
            auto yCoord = std::stoi(line.substr(index + 2));
            coords.emplace_back(std::make_pair(xCoord, yCoord));
        }
        inputFile.close();
    }

    // Calculate Manhattan distances
    auto xMax = (*std::max_element(coords.begin(), coords.end(), 
        [](std::pair<int, int> a, std::pair<int, int> b) { return a.first < b.first; }
                )).first;
    auto yMax = (*std::max_element(coords.begin(), coords.end(), 
        [](std::pair<int, int> a, std::pair<int, int> b) { return a.second < b.second; }
                )).second;
    int distanceMap[xMax + 1][yMax + 1] = {};
    for (auto x = 0; x <= xMax; ++x) {
        for (auto y = 0; y <= yMax; ++y) {
            auto coord = std::find(coords.begin(), coords.end(), std::make_pair(x, y));
            if (coord != coords.end()) {
                distanceMap[x][y] = std::distance(coords.begin(), coord) + 1;
                continue;
            }
            std::deque<int> distances;
            for (auto c : coords) {
                auto dist = (std::abs(x - c.first) + std::abs(y - c.second));
                distances.emplace_back(dist);
            }
            auto m = std::min_element(distances.begin(), distances.end());
            if (std::count(distances.begin(), distances.end(), *m) == 1) {
                distanceMap[x][y] = std::distance(distances.begin(), m) + 1;
            }
        }
    }

    // Get finite areas
    std::set<int> infiniteAreas;
    for (auto x = 0; x <= xMax; ++x) {
        if (x == 0 || x == xMax) {
            // Get all values in row
            for (auto y = 0; y <= yMax; ++y) {
                infiniteAreas.emplace(distanceMap[x][y]);
            }
        } else {
            // Only get first and last value in row
            infiniteAreas.emplace(distanceMap[x][0]);
            infiniteAreas.emplace(distanceMap[x][yMax]);
        }
    }
    
    auto largestFiniteArea = 0;
    for (auto i = 1; i <= coords.size(); ++i) {
        if (std::find(infiniteAreas.begin(), infiniteAreas.end(), i) != infiniteAreas.end()) {
            continue;
        }
        auto total = 0;
        for (auto x = 0; x <= xMax; ++x) {
            for (auto y = 0; y <= yMax; ++y) {
                total += (distanceMap[x][y] == i) ? 1 : 0;
            }
        }
        if (total > largestFiniteArea) {
            largestFiniteArea = total;
        }
    }
    std::cout << "Largest finite area size: " << largestFiniteArea << "\n";
    return 0;
}
    

