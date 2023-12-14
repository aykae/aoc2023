#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

const std::string STRENGTH = "AKQJT98765432";

std::vector<std::pair<char, int>>* sort_counts(const std::string &hand) {
    std::unordered_map<char, int> card_counts1;
    for (char c : hand) {
        card_counts1[c] += 1;
    }

    std::vector<std::pair<char, int>>* ordered_counts;
    ordered_counts = new std::vector<std::pair<char, int>>(card_counts1.begin(), card_counts1.end());

    std::sort(ordered_counts->begin(), ordered_counts->end(), [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        else {
            return STRENGTH.find(a.first) < STRENGTH.find(b.first);
        }
    });

    return ordered_counts;
}

int get_hand_type(std::vector<std::pair<char, int>>& counts) {
    if (counts[0].second == 5) { // Five of a kind
        return 6;
    }
    else if (counts[0].second == 4) { // Four of a kind
        return 5;
    }
    else if (counts[0].second == 3 && counts[1].second == 2) { // Full house
        return 4;
    }
    else if (counts[0].second == 3) { // Three of a kind
        return 3;
    }
    else if (counts[0].second == 2 && counts[1].second == 2) { // Two pairs
        return 2;
    }
    else if (counts[0].second == 2) { // Two pairs
        return 1;
    }

    return 0; // High Card
}

// Returns 1 if h1 > h2, else 0
int tiebreaker(const std::string& h1, const std::string& h2) {
    int i = 0;
    while (STRENGTH.find(h1[i]) == STRENGTH.find(h2[i])) {
        i++;
    }

    return STRENGTH.find(h1[i]) < STRENGTH.find(h2[i]);
}

// Returns 1 if h1 > h2, else 0
int compare_hands(const std::string& h1, const std::string& h2) {

    std::vector<std::pair<char, int>>* counts1;
    counts1 = sort_counts(h1);
    int type1 = get_hand_type(*counts1);

    std::vector<std::pair<char, int>>* counts2;
    counts2 = sort_counts(h2);
    int type2 = get_hand_type(*counts2);
    
    if (type1 == type2) {
        return tiebreaker(h1, h2);
    }

    return type1 > type2;
}

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::vector<std::pair<std::string, int>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string parsed;
        std::pair<std::string, int> p;
        std::getline(iss, parsed, ' ');
        p.first = parsed;
        std::getline(iss, parsed, ' ');
        p.second = std::stoi(parsed);
        data.push_back(p);
    }

    std::sort(data.begin(), data.end(), [](const std::pair<std::string, int> p1, const std::pair<std::string, int> p2) {
        return compare_hands(p1.first, p2.first);
    });

    long long answer = 0;
    for (int i = 0; i < data.size(); i++) {
        answer += data[i].second * (data.size() - i);
    }

    std::cout << answer << std::endl;

    file.close();
    return 0;
}