#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <unordered_map>

std::unordered_map<std::string, std::vector<int>> map;

int is_symbol(int i, int j, const std::vector<std::string>& schem) {
    if (schem[i][j] == '*') {
        return 2;
    }

    if (!std::isdigit(schem[i][j]) && schem[i][j] != '.') {
        return 1;
    }
    return 0;
}

int is_digit_adjacent(int i, int j, const std::vector<std::string>& schem) {

    if (i < schem.size()-1 && is_symbol(i+1, j, schem)) { is_symbol(i+1, j, schem); }

    if (i > 0 && is_symbol(i-1, j, schem)) { is_symbol(i-1, j, schem); }

    if (j < schem[0].length()-1 && is_symbol(i, j+1, schem)) { is_symbol(i, j+1, schem); }

    if (j > 0 && is_symbol(i, j-1, schem)) { is_symbol(i, j-1, schem); }

    if (i < schem.size()-1 && j < schem[0].length()-1 && is_symbol(i+1, j+1, schem)) { is_symbol(i+1, j+1, schem); }

    if (i > 0 && j < schem[0].length()-1 && is_symbol(i-1, j+1, schem)) { is_symbol(i-1, j+1, schem); }

    if (i < schem.size()-1 && j > 0 && is_symbol(i+1, j-1, schem)) { is_symbol(i+1, j-1, schem); }

    if (i > 0 && j > 0 && is_symbol(i-1, j-1, schem)) { is_symbol(i-1, j-1, schem); }

    return 0;
}

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    //get input dimensions
    std::vector<std::string> schem;
    std::string line;
    while (std::getline(file, line)) {
        schem.push_back(line);
    }

    int sum = 0;

    int building_num = 0;
    int is_adjacent = 0;
    int is_gear = 0;
    int num = 0;

    for (int i = 0; i < schem.size(); i++) {
        for (int j = 0; j < schem[i].length(); j++) {
            if (std::isdigit(schem[i][j])) {
                if (!building_num) { building_num = 1; }

                int adj_resp = is_digit_adjacent(i, j, schem);
                if (!is_adjacent && adj_resp) {
                    is_adjacent = 1;
                }
                if (adj_resp == 2) {
                    is_gear = 1;
                }
                num = num * 10 + (schem[i][j] - '0');
            }
            else if (building_num) {
                if (is_adjacent) { sum += num; }

                if (is_gear) {

                }
                
                num = 0;
                is_adjacent = 0;
                building_num = 0;
            }
        }
    }

    std::cout << sum << std::endl;

    file.close();
    return 0;
}