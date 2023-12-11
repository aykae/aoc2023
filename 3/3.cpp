#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

int is_symbol(int i, int j, const std::vector<std::string>& schem) {
    if (!std::isdigit(schem[i][j]) && schem[i][j] != '.') {
        return 1;
    }
    return 0;

}

int is_digit_adjacent(int i, int j, const std::vector<std::string>& schem) {

    if (i < schem.size()-1 && is_symbol(i+1, j, schem)) { return 1; }

    if (i > 0 && is_symbol(i-1, j, schem)) { return 1; }

    if (j < schem[0].length()-1 && is_symbol(i, j+1, schem)) { return 1; }

    if (j > 0 && is_symbol(i, j-1, schem)) { return 1; }

    if (i < schem.size()-1 && j < schem[0].length()-1 && is_symbol(i+1, j+1, schem)) { return 1; }

    if (i > 0 && j < schem[0].length()-1 && is_symbol(i-1, j+1, schem)) { return 1; }

    if (i < schem.size()-1 && j > 0 && is_symbol(i+1, j-1, schem)) { return 1; }

    if (i > 0 && j > 0 && is_symbol(i-1, j-1, schem)) { return 1; }

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
    int num = 0;

    for (int i = 0; i < schem.size(); i++) {
        for (int j = 0; j < schem[i].length(); j++) {
            if (std::isdigit(schem[i][j])) {
                if (!building_num) { building_num = 1; }

                if (!is_adjacent && is_digit_adjacent(i, j, schem)) {
                    is_adjacent = 1;
                }
                num = num * 10 + (schem[i][j] - '0');
            }
            else if (building_num) {
                if (is_adjacent) { sum += num; }

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