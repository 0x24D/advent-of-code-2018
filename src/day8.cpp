#include <fstream>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

struct Node {
    std::vector<Node> children;
    std::vector<unsigned int> metadata;
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
    node.children.reserve(numChildren);
    node.metadata.reserve(numMetadata);
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
    for (size_t i = 0; i < node.children.size(); ++i) {
        sum += getMetadataSum(node.children[i]);
    }
    return sum;
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

    auto sum = getMetadataSum(node);
    std::cout << "Sum of all metadata entries: " << std::to_string(sum) << '\n';

    return 0;
}
