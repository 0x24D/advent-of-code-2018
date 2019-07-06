#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
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

  std::map<int, int> timesAsleep;
  int guardNumber;
  int lastTime;
  for (std::string line : logLines) {
    std::string lineType = line.substr(19, 1);
    if (lineType == "G") {
      int hashIndex = line.find('#');
      int spaceIndex = line.find(' ', hashIndex);
      guardNumber = std::atoi(line.substr(hashIndex + 1, spaceIndex - hashIndex - 1).c_str());
      timesAsleep.insert({guardNumber, 0});
    } else if (lineType == "w") {
      int timeAsleep = std::atoi(line.substr(15, 2).c_str()) - lastTime;
      timesAsleep[guardNumber] += timeAsleep;
    } else {
      lastTime = std::atoi(line.substr(15, 2).c_str());
    }
  }
  auto mostAsleep = std::max_element(timesAsleep.begin(), timesAsleep.end(), [](std::pair<int, int> a, std::pair<int, int> b) {
    return a.second < b.second;
  });
  std::cout << "Most asleep guard: " << (*mostAsleep).first << "\n";
  std::deque<std::pair<int, int>> startEndTimes;

  return 0;
}
