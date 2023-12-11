#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;
    std::getline(file, line);


    std::istringstream iss1(line);
    std::vector<long> seeds;
    std::string seed;
    std::getline(iss1, seed, ' ');
    while(std::getline(iss1, seed, ' ')) {
        std::cout << seed << std::endl;
        seeds.push_back(std::stol(seed));
    }

    std::vector<std::vector<long>> mappings;
    int mapIdx = -1;
    while (std::getline(file, line)) {
        if (std::isdigit(line[0])) {
            std::istringstream iss2(line);

            std::string num;
            std::getline(iss2, num, ' ');
            mappings[mapIdx].push_back(std::stol(num));
            std::getline(iss2, num, ' ');
            mappings[mapIdx].push_back(std::stol(num));
            std::getline(iss2, num, ' ');
            mappings[mapIdx].push_back(std::stol(num));
        }
        else if (std::isalpha(line[0])) {
            stdA::asdfkkkj
            mapIdx += 1;
        }
        std::cout << line << std::endl;
    }

    file.close();
    return 0;
}