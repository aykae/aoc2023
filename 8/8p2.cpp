#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

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
    std::vector<std::string> nodes;
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (line[2] == 'A') {
            nodes.push_back(line.substr(0, 3));
        }

        std::pair<std::string, std::string> p;
        p.first = line.substr(7, 3);
        p.second = line.substr(12, 3);
        map[line.substr(0, 3)] = p;
    }

    std::vector<int> steps(nodes.size(), 0);

    // TODO: find least common multiple (multiply all node di's together) of all ways to reach z 
    int found_zs = 0;
    int di = 0;
    while (found_zs < nodes.size()) {
        char dir = dirs[di % dirs.length()];
        for (int i = 0; i < nodes.size(); i++) {
            if (dir == 'L') {
                nodes[i] = map[nodes[i]].first;
            }
            else if (dir == 'R') {
                nodes[i] = map[nodes[i]].second;
            }

            if (nodes[i][2] == 'Z' && !steps[i]) {
                steps[i] = di;
                found_zs++;
            }
        }
        di++;
    }

    std::cout << di << std::endl;

    file.close();
    return 0;
}