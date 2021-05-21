#include <deque>
#include <fstream>
#include <iostream>
#include <numeric>
#include <utility>

struct Node {
    std::deque<Node> children{};
    std::deque<unsigned int> metadata{};
};

Node getNode(std::ifstream& inputFile) {
    if (inputFile.peek() == inputFile.eof()) {
        return {};
    }
    auto numChildren = 0;
    inputFile >> numChildren;
    auto numMetadata = 0;
    inputFile >> numMetadata;

    Node node{};
    for (auto i = 0; i < numChildren; ++i) {
        node.children.push_back(getNode(inputFile));
    }
    for (auto i = 0; i < numMetadata; ++i) {
        int metadata = 0;
        inputFile >> metadata;
        node.metadata.push_back(metadata);
    }
    return node;
}

unsigned int getMetadataSum(const Node& node) {
    unsigned int sum = std::accumulate(node.metadata.cbegin(), node.metadata.cend(), 0);
    for (const auto& child : node.children) {
        sum += getMetadataSum(child);
    }
    return sum;
}

unsigned int getNodeValue(const Node& node) {
    if (node.children.size() == 0) {
        return getMetadataSum(node);
    }
    unsigned int value = 0;
    for (auto m : node.metadata) {
        if (m != 0 && m <= node.metadata.size()) {
            value += getNodeValue(node.children[m - 1]);
        }
    }
    return value;
}

int main() {
    Node node{};
    std::ifstream inputFile;
    inputFile.open("inputs/day8.txt");
    if (inputFile.is_open()) {
        node = getNode(inputFile);
        inputFile.close();
    } else {
        std::cerr
            << "Couldn't find input file, expected to run from root directory: e.g. ./bin/day-8\n";
        return 1;
    }

    const auto sum = getMetadataSum(node);
    std::cout << "Sum of all metadata entries: " << std::to_string(sum) << '\n';

    // Part 2
    const auto value = getNodeValue(node);
    std::cout << "Value of root node: " << std::to_string(value) << '\n';
    return 0;
}
