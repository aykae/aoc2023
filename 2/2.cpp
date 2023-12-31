#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const int MAX_RED = 12;
const int MAX_GREEN = 13;
const int MAX_BLUE = 14;

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    int sum = 0;

    int is_possible = 1;
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

        while (std::getline(iss_game, token, ';') && is_possible) {
            std::istringstream iss_set(token);
            std::string set;

            while (std::getline(iss_set, set, ',')) {

                //parse ball count
                std::istringstream iss_balls(set.substr(1));
                std::string num_balls;
                std::getline(iss_balls, num_balls, ' ');

                //parse color
                int count = std::stoi(num_balls);
                std::string color;
                std::getline(iss_balls, color, ' ');

                if (
                    color == "red" && count > MAX_RED ||
                    color == "green" && count > MAX_GREEN ||
                    color == "blue" && count > MAX_BLUE
                ) {
                    is_possible = 0;
                    break;
                }
            }
        }

        if (is_possible) {
            sum += id;
        }
        else {
            is_possible = 1;
        } 
    }

    std::cout << sum << std::endl;

    file.close();
    return 0;
}