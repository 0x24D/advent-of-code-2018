#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <string>

int main() {
  std::deque<std::string> logLines;
  std::ifstream inputFile;
  inputFile.open("../inputs/day4.txt");
  if (inputFile.is_open()) {
    std::string line;
    while (std::getline(inputFile, line)) {
      logLines.emplace_back(line);
    }
    inputFile.close();
  }

  std::sort(logLines.begin(), logLines.end(), [](std::string a, std::string b) {
    std::string aTimestamp = a.substr(1, 16);
    std::string bTimestamp = b.substr(1, 16);
    return aTimestamp < bTimestamp;
  });

  std::deque<std::pair<int, std::deque<int>>> timesAsleep;
  int guardNumber;
  int timeAsleep = -1;
  for (std::string line : logLines) {
    std::string lineType = line.substr(19, 1);
    if (lineType == "G") {
      int hashIndex = line.find('#');
      int spaceIndex = line.find(' ', hashIndex);
      guardNumber = std::atoi(
          line.substr(hashIndex + 1, spaceIndex - hashIndex - 1).c_str());
      timesAsleep.push_back({guardNumber, std::deque<int>(60, 0)});
    } else if (lineType == "w") {
      auto el = std::find_if(timesAsleep.begin(), timesAsleep.end(),
                             [&guardNumber](std::pair<int, std::deque<int>> p) {
                               return p.first == guardNumber;
                             });
      if (el != timesAsleep.end()) {
        int timeAwake = std::atoi(line.substr(15, 2).c_str());
        for (int i = timeAsleep; timeAsleep != -1 && i < timeAwake; ++i) {
          el->second[i] += 1;
        }
      }
    } else {
      timeAsleep = std::atoi(line.substr(15, 2).c_str());
    }
  }
  std::map<int, int> guardsAsleep;
  for (auto pair : timesAsleep) {
    auto total = std::accumulate(pair.second.begin(), pair.second.end(), 0);
    guardsAsleep.insert({pair.first, total});
  }
  auto mostAsleep =
      std::max_element(guardsAsleep.begin(), guardsAsleep.end(),
                       [](std::pair<int, int> a, std::pair<int, int> b) {
                         return a.second < b.second;
                       });

  auto guardRecord = std::find_if(
      timesAsleep.begin(), timesAsleep.end(),
      [&mostAsleep](auto p) { return p.first == mostAsleep->first; });

  if (guardRecord != timesAsleep.end()) {
    auto maxEl = std::max_element(guardRecord->second.begin(),
                                  guardRecord->second.end());
    for (int i = 0; i < guardRecord->second.size(); ++i) {
      if (guardRecord->second[i] == *maxEl) {
        std::cout << (mostAsleep->first) << " * " << i << " = "
                  << (mostAsleep->first * i) << "\n";
        break;
      }
    }
  }

  return 0;
}
