#include <fstream>
#include <string>
#include <iostream>

int main() {
    std::ifstream inputFile;
    std::string readLine;
    int totalResult = 0;
    inputFile.open("../inputs/day1.txt");
    if (inputFile.is_open()) {
        while (getline(inputFile, readLine)) {
            totalResult += std::stoi(readLine);
        }
        inputFile.close();
    }
    std::cout << "Resulting frequency is: " << totalResult << "\n";
    return 0;
}
