#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;
    int sum = 0;
    while (std::getline(file, line)) {
        int lInt = -1;
        int rInt = -1; 

        int i = 0;
        int j = line.length() - 1;
        while (lInt < 0 || rInt < 0) {
            if (lInt < 0 && std::isdigit(line[i])) {
                lInt = line[i] - '0';
            }
            if (rInt < 0 && std::isdigit(line[j])) {
                rInt = line[j] - '0';
            }

            i += 1;
            j -= 1;
        }

        sum += (lInt * 10 + rInt);
    }

    std::cout << sum << std::endl;

    file.close();
    return 0;
}