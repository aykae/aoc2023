#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::vector<std::vector<int>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<int> history;
        std::string num;
        while (std::getline(iss, num, ' ')) {
            history.push_back(std::stoi(num));
        }
        data.push_back(history);
    }

    int extrap = 0;
    int all_zeroes = 0;
    for (int h = 0; h < data.size(); h++) {
        all_zeroes = 0;
        int end = data[h].size()-1;
        while (!all_zeroes) {
            all_zeroes = 1;
            int temp = data[h][end];
            extrap += temp;
            for (int i = end; i > 0; i--) {
                data[h][i-1] = temp - data[h][i-1];
                temp = temp - data[h][i-1];
                all_zeroes = all_zeroes && data[h][i-1] == 0;
            }
            end--;
        }
    }

    std::cout << extrap << std::endl;

    file.close();
    return 0;
}