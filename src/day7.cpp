#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>

int main() {
    std::map<char, std::set<char>> stepsNeeded;
    std::ifstream inputFile;
    inputFile.open("inputs/day7.txt");
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
    } else {
        std::cerr
            << "Couldn't find input file, expected to run from root directory: e.g. ./bin/day-7\n";
        return 1;
    }
    std::string steps = "";
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
        const auto ch = *nextSteps.begin();
        steps += ch;
        std::set<char> followingSteps;
        for (auto it = stepsNeeded.begin(); it != stepsNeeded.end(); ++it) {
            if (it->second.find(ch) != it->second.end()) {
                if (std::all_of(stepsNeeded[it->first].begin(), stepsNeeded[it->first].end(),
                        [&steps](auto c) {
                            return steps.find(c) != std::string::npos;
                        })) {
                    nextSteps.insert(it->first);
                }
            }
        }
        nextSteps.erase(ch);
    }

    std::cout << "Steps to take: " << steps << "\n";

    // TODO: This works for the example but the answer is incorrect for the full input.
    // Part 2
    struct WorkerData {
        unsigned int time = 0;
        char step = '.';
    };

    constexpr auto STEP_DURATION = 60;
    constexpr auto NUM_WORKERS = 5;
    std::array<WorkerData, NUM_WORKERS> dataArr;
    std::set<char> unblockedSteps{};
    unsigned int clock = 0;

    do {
        for (auto i = 0; i < NUM_WORKERS; ++i) {
            if (dataArr[i].time == 0) {
                if (dataArr[i].step != '.') {
                    for (auto& [step, prevSteps] : stepsNeeded) {
                        prevSteps.erase(dataArr[i].step);
                    }
                }
                if (unblockedSteps.empty()) {
                    std::string newSteps{};
                    for (const auto step : steps) {
                        const auto& stepMap = stepsNeeded.find(step);
                        if (stepMap == stepsNeeded.end() || stepMap->second.size() == 0) {
                            if (stepMap != stepsNeeded.end()) {
                                stepsNeeded.erase(stepMap);
                            }
                            newSteps += step;
                            unblockedSteps.insert(step);
                        }
                    }
                    for (const auto& step : newSteps) {
                        steps.erase(steps.find(step), 1);
                    }
                }
                if (unblockedSteps.empty()) {
                    dataArr[i].step = '.';
                    // dataArr[i].time is already 0
                } else {
                    dataArr[i].step = *unblockedSteps.begin();
                    unblockedSteps.erase(dataArr[i].step);
                    dataArr[i].time = STEP_DURATION + (dataArr[i].step - 'A') + 1;
                }
            }
            if (dataArr[i].time != 0) {
                --dataArr[i].time;
            }
        }
        if (std::any_of(dataArr.cbegin(), dataArr.cend(), [](const auto& w) {
                return w.step != '.';
            })) {
            ++clock;
        }
    } while (std::any_of(dataArr.cbegin(), dataArr.cend(), [](const auto& w) {
        return w.step != '.';
    }));
    std::cout << "Time taken to complete all steps: " << clock << "\n";
    return 0;
}
