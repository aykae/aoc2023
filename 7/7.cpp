#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

const std::string STRENGTH = "AKQJT98765432";

// Returns 1 if h1 > h2, else 0
int compare_hands(const std::string h1, const std::string h2) {

    std::unordered_map<char, int> card_counts1;
    for (char c : h1) {
        card_counts1[c] += 1;
    }

    // sort by count and then card in decreasing order
    std::vector<std::pair<char, int>> ordered_counts1(card_counts1.begin(), card_counts1.end());
    std::sort(ordered_counts1.begin(), ordered_counts1.end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        else {
            return STRENGTH.find(a.first) < STRENGTH.find(b.first);
        }
    });

    int type1;
    std::string details1 = "";


    std::unordered_map<char, int> card_counts2;
    for (char c : h2) {
        card_counts2[c] += 1;
    }

    return 1;

}

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::vector<std::string> hands;
    std::vector<int> bids;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string parsed;
        std::getline(iss, parsed, ' ');
        hands.push_back(parsed);
        std::getline(iss, parsed, ' ');
        bids.push_back(std::stoi(parsed));
    }

    compare_hands(hands[0], hands[1]);

    file.close();
    return 0;
}