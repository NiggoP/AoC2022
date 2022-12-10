#include <iostream>
#include <string>
#include <sstream>
#include <vector>


// Input:
// addx V   add V to x, 2 ticks
// noop     do nothing, 1 tick

int calcSigStrength(std::vector<int> *reg, int cycle) {
    return cycle * reg->at(cycle-1);
}


int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    std::istringstream iss(input_string);
    std::string s;

    int x = 1;
    std::vector<int> register_over_time;
    register_over_time.push_back(x);

    while(std::getline(iss, s)) {
        if (s.substr(0,4) == "addx") {
            // add x to v after 2 cycles
            register_over_time.push_back(x);
            x += std::stoi(s.substr(5));
            register_over_time.push_back(x);
        } else if (s.substr(0,4) == "noop") {
            // do nothing
            register_over_time.push_back(x);
        } else {
            std::cout << "ERROR: Unknown command" << std::endl;
        }
    }

    int cycles_to_calc[] = {20, 60, 100, 140, 180, 220};
    int sum = 0;
    for (int cycle : cycles_to_calc) {
        sum += calcSigStrength(&register_over_time, cycle);
    }

    std::cout << "Signal Strength: " << sum << std::endl;

    // Part 2
    int i = 0;
    for (auto r : register_over_time) {
        if (i == 40) {
            // New line
            std::cout << std::endl;
            i = 0;
        }
        if (abs(i - r) <= 1) {
            std::cout << "#";
        } else {
            std::cout << ".";
        }
        i++;
    }
}