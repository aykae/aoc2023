#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <cmath>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    int sum = 0;
    std::string line;
    std::unordered_map<std::string, int> cardmap;
    while (std::getline(file, line)) {
        std::istringstream iss1(line);

        std::string token;
        std::getline(iss1, token, ':');
        std::getline(iss1, token, ':');

        std::istringstream iss2(token);
        std::string nums;
        std::getline(iss2, nums, '|');

        //parse winning numbers
        int num = 0; 
        for (int i = 0; i < nums.length(); i++) {
            if (std::isdigit(nums[i])) {
                num *= 10;
                num += (nums[i] - '0');
            }
            else if (num) {
                cardmap[std::to_string(num)] = 1;
                num = 0;
            }
        }

        //parse my numbers
        // std::cout << cardmap.size() << std::endl;

        std::getline(iss2, nums, '|');
        nums += " "; //so that last number in line is parsed
        num = 0; 
        int score = 0;
        for (int i = 0; i < nums.length(); i++) {
            if (std::isdigit(nums[i])) {
                num *= 10;
                num += (nums[i] - '0');
            }
            else {
                if (cardmap[std::to_string(num)] == 1) {
                    score += 1;
                    cardmap[std::to_string(num)] = 2; //no repeat counts
                }
                num = 0;
            }
        }

        if (score) {
            sum += std::pow(2, score-1);
        }
        cardmap.clear();
    }

    std::cout << sum << std::endl;

    file.close();
    return 0;
}