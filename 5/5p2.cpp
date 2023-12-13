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


    //TODO: work backwards from location ranges
    // 1. iterate through mappings, bottom up
    //      1. find lowest dest that is geq (lower_bound) prev src and (upper_bound) leq src+range
    //      2. set new lower_bound to new_src+(lowest_dest-prev_src) and upper_bound to new_src + new_range

    long min_dest = __LONG_MAX__;
    // long lower = 0;
    for (int k = 0; k < mappings[mappings.size()-1].size(); k+=3) {
    long lower = mappings[mappings.size()-1][k];
    // long upper = 0;
    long upper = lower;
    int convcount = 0;
    for (int i = mappings.size()-1; i >= 0; i--) {
        // long min_dest = __LONG_MAX__;
        for (int j = 0; j < mappings[i].size(); j+=3) {
            // if (mappings[i][j] < min_dest && mappings[i][j] >= lower && mappings[i][j] <= upper) {
            if (mappings[i][j] >= lower && mappings[i][j] <= upper) {
                // min_dest = mappings[i][j];
                // lower = mappings[i][j+1] + (mappings[i][j]-lower);
                lower = mappings[i][j+1];
                upper = mappings[i][j+1] + mappings[i][j+2];
                convcount += 1;
                break;
            }
        }
    }
    std::cout << lower << std::endl;
    std::cout << convcount << std::endl;

    if (convcount == mappings.size()-1) {
        for (int s = 0; s < seeds.size(); s+=2){
            if (seeds[s] >= lower && seeds[s] <= upper) {
                std::cout << seeds[s] << std::endl;
            }
        }
    }

    }


    file.close();
    return 0;
}