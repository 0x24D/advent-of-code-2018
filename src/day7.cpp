#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

int main() {
    std::map<char, std::set<char>> stepsNeeded;
    std::ifstream inputFile;
    inputFile.open("../inputs/day7.txt");
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            auto preIndex = line.find("Step");
            auto postIndex = line.find("step");
            auto preStep = line.substr(preIndex + 5, 1).c_str()[0];
            auto postStep = line.substr(postIndex + 5, 1).c_str()[0];
            stepsNeeded[postStep].insert(preStep);
        }
        inputFile.close();
    }
    
    std::string steps;
    std::set<char> nextSteps;
    // Get initial step
    for (auto p : stepsNeeded) {
        for (auto c : p.second) {
            if (stepsNeeded.find(c) == stepsNeeded.end()) {
                nextSteps.insert(c);
            }
        }
    }
    // Calculate steps to end
    while (!nextSteps.empty()) {
        const auto ch = nextSteps.begin();
        steps += *ch;
        std::set<char> followingSteps;
        for (auto it = stepsNeeded.begin(); it != stepsNeeded.end(); ++it) {
            if (it->second.find(*ch) != it->second.end()) {
                if (std::all_of(stepsNeeded[it->first].begin(), stepsNeeded[it->first].end(), 
                [&steps](auto c) {  return steps.find(c) != std::string::npos; })) { 
                    nextSteps.insert(it->first);
                }
            }
        }
        nextSteps.erase(ch);
    }

    std::cout << "Steps to take: " << steps << "\n";
    return 0;
}
