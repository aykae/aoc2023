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
            std::vector<long> newmap;
            mappings.push_back(newmap);
            mapIdx += 1;
        }
    }

    long min_dest = __LONG_MAX__;

    //TODO: work backwards from location ranges

    // for (int i = 0; i < seeds.size(); i+=2) {
    //     for (int offset = 0; offset < seeds[i+1]; offset++){ // seed ranges
    //         long curr = seeds[i] + offset;
    //         for (int j = 0; j < mappings.size(); j++) {
    //             for (int k = 0; k < mappings[j].size(); k+=3) {
    //                 if (curr >= mappings[j][k+1] && curr <= (mappings[j][k+1] + mappings[j][k+2])) { //src is in range
    //                     curr = mappings[j][k] + (curr - mappings[j][k+1]);
    //                     break;
    //                     // if (i == 0) {std::cout << j << " " << k/3 << std::endl;}
    //                 }
    //             }
    //         }
    //         min_dest = std::min(min_dest, curr);

    //         //optimize by only testing smallest of seed to seed+range values (actually dont think so)
    //         //or just work backwards
    //     }
    // }

    std::cout << min_dest << std::endl;

    file.close();
    return 0;
}