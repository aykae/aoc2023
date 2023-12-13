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

    std::vector<long> candidate_seeds;
    for (int k = 0; k < mappings[mappings.size()-1].size(); k+=3) {
        long lower = mappings[mappings.size()-1][k];
        // long upper = 0;
        long upper = lower;
        int convcount = 0;
        for (int i = mappings.size()-1; i >= 0; i--) {
            // long min_dest = __LONG_MAX__;
            for (int j = 0; j < mappings[i].size(); j+=3) {
                // if (mappings[i][j] < min_dest && mappings[i][j] >= lower && mappings[i][j] <= upper) {
                if (lower >= mappings[i][j] && lower <= mappings[i][j] + mappings[i][j+2]) {
                    // min_dest = mappings[i][j];
                    lower = mappings[i][j+1] + (lower-mappings[i][j]);
                    upper = mappings[i][j+1] + mappings[i][j+2];
                    convcount += 1;
                    break;
                }
                else if (upper >= mappings[i][j] && upper <= mappings[i][j] + mappings[i][j+2]) {
                    lower = mappings[i][j+1];
                    upper = mappings[i][j+1] + (upper-mappings[i][j]);
                    convcount += 1;
                    break;
                }
            }
        }
        std::cout << k/3 << std::endl;
        std::cout << lower << std::endl;
        for (int s = 0; s < seeds.size(); s+=2){
            if (lower >= seeds[s] && lower <= seeds[s] + seeds[s+1]) {
                candidate_seeds.push_back(lower);
                std::cout << lower << std::endl; //find seed
            }
            else if (upper >= seeds[s] && upper <= seeds[s] + seeds[s+1]) {
                candidate_seeds.push_back(seeds[s]);
                std::cout << upper << std::endl; //find seed
            }
        }
        std::cout << convcount << "\n" << std::endl;
    }

    //convert candidate seeds back into locations
    seeds.clear();
    seeds = candidate_seeds;
    // seeds.push_back(2668361194);
    long min_dest = __LONG_MAX__;
    for (int i = 0; i < seeds.size(); i++) {
        long curr = seeds[i];
        for (int j = 0; j < mappings.size(); j++) {
            for (int k = 0; k < mappings[j].size(); k+=3) {
                if (seeds[i] >= mappings[j][k+1] && seeds[i] <= (mappings[j][k+1] + mappings[j][k+2])) { //src is in range
                    seeds[i] = mappings[j][k] + (seeds[i] - mappings[j][k+1]);
                    break;
                }
            }
        }
        min_dest = std::min(min_dest, seeds[i]);
    }

    std::cout << min_dest << std::endl;


    file.close();
    return 0;
}