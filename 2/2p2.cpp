#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::ifstream file("input.txt"); // replace with your file name
    if (!file) {
        std::cerr << "Unable to open file\n";
        return 1; // return with error code 1
    }

    int sum = 0;

    std::string line;

    //for each line in the input file
    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string token;
        std::getline(iss, token, ':');
        std::getline(iss, token, ':');
        std::string game = token;

        std::istringstream iss_game(game);

        int least_red = 0, least_green = 0, least_blue = 0;

        while (std::getline(iss_game, token, ';')) {
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

                if (color == "red" && count > least_red) {
                    least_red = count;
                }
                if (color == "green" && count > least_green) {
                    least_green = count;
                }
                if (color == "blue" && count > least_blue) {
                    least_blue = count;
                }
            }
        }
        sum += (least_red * least_blue * least_green);
    }

    std::cout << sum << std::endl;

    file.close();
    return 0;
}