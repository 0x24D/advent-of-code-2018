#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

int main() {
    std::ifstream inputFile;
    std::vector<std::string> fileStrings;
    inputFile.open("../inputs/day2.txt");
    std::istream_iterator<std::string> input(inputFile);
    std::copy (input, std::istream_iterator<std::string>(), std::back_inserter(fileStrings));

    std::vector<char> alphabet(26);
    std::iota(alphabet.begin(), alphabet.end(), 'a');

    int twoLetters = 0;
    int threeLetters = 0;

    for (std::string str : fileStrings) {
        bool twoChars = false;
        bool threeChars = false;
        std::sort(str.begin(), str.end());
        for (char aToZ : alphabet) {
            int count = std::count(str.begin(), str.end(), aToZ);
            if (count == 2)
                twoChars = true;
            else if (count == 3)
                threeChars = true;
            if (twoChars && threeChars)
                break;
        }

        if (twoChars)
            ++twoLetters;
        if (threeChars)
            ++threeLetters;
    }

    std::cout << twoLetters << " * " << threeLetters << " = " << twoLetters * threeLetters << "\n";

    return 0;
}
