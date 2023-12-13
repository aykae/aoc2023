#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;
    std::vector<long> races;
    int race_count = 0;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
        line += " "; //to aid in parsing delimiter
        std::string num_str = "";
        long num = 0;
        for (int i = 0; i < line.length(); i++) {
            if (std::isdigit(line[i])) {
                num_str += line[i];
            }
        }
        num = std::stol(num_str);
        races.push_back(num);
    }
    race_count = races.size()/2;

    int margin = 0;
    int product = 1;

    for (int i = 0; i < race_count; i++) {
        for (int j = 0; j < races[i]; j++) {
            if (j * (races[i] - j) > races[race_count + i]) {
                margin += 1;
            }
        }
        product *= margin;
        margin = 0;
    }

    std::cout << product << std::endl;

    file.close();
    return 0;
}