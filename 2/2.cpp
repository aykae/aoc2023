#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int RED = 12;
const int GREEN = 13;
const int BLUE = 14;

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    std::string line;

    //for each line in the input file
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string token;
        std::getline(iss, token, ':');
        int id = std::stoi(token.substr(5));
        //std::cout << id << std::endl << std::endl;

        std::getline(iss, token, ':');
        std::string game = token;

        std::istringstream iss_game(game);

        while (std::getline(iss_game, token, ';')) {
            std::istringstream iss_set(token);
            std::string set;

            while (std::getline(iss_set, set, ',')) {
                std::istringstream iss_balls(set);
                std::string num_balls;
                std::getline(iss_balls, num_balls, ' ');
                int count = std::stoi(num_balls);
                std::string color;
                std::getline(iss_balls, color, ' ');
                if (color == "RED") {
                    std::cout << "RED" << std::endl;
                }
            }
        }

        //for each set in a particular game

    }

    file.close();
    return 0;
}