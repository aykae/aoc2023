#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream file("filename.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }

    file.close();
    return 0;
}