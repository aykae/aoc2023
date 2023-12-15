#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string dirs;
    std::getline(file, dirs);
    std::string line;
    std::getline(file, line);


    std::unordered_map<std::string, std::pair<std::string, std::string>> map;
    while (std::getline(file, line)) {
        std::istringstream iss(line);


        std::pair<std::string, std::string> p;
        p.first = line.substr(7, 3);
        p.second = line.substr(12, 3);
        map[line.substr(0, 3)] = p;
    }

    std::string curr = "AAA";

    int di = 0;
    while (curr != "ZZZ") {
        char dir = dirs[di % dirs.length()];
        if (dir == 'L') {
            curr = map[curr].first;
        }
        else if (dir == 'R') {
            curr = map[curr].second;
        }

        di++;
    }

    std::cout << di << std::endl;

    file.close();
    return 0;
}