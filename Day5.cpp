#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

#define PART2

// input:
/*
    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

move 1 from 2 to 1
move 3 from 1 to 3
move 2 from 2 to 1
move 1 from 1 to 2

*/

void moveCrane(int numberOfCrates, std::vector<char> *from, std::vector<char> *to) {
    #ifndef PART2
    for (int i = 0; i < numberOfCrates; i++) {
        to->push_back(from->back());
        from->pop_back();
    }
    #else
    std::vector<char> temp;
    for (int i = 0; i < numberOfCrates; i++) {
        temp.push_back(from->back());
        from->pop_back();
    }
    for (int i = 0; i < numberOfCrates; i++) {
        to->push_back(temp.back());
        temp.pop_back();
    }
    #endif
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

    std::vector<std::string> linesWithBoxes;
    std::vector<std::vector<char>> vectorOfStacks;

    while(std::getline(iss, s)) {
        if (s.find('1') != std::string::npos) {
            // found stack row
            break;
        }
        // Add line to linesWithBoxes
        linesWithBoxes.push_back(s);
    }

    // reverse 
    std::reverse(linesWithBoxes.begin(), linesWithBoxes.end());

    int colIndex = 0;
        std::regex regexp_rows("[0-9]");
        std::smatch m;
    while (std::regex_search(s, m, regexp_rows)) {
        // Create the corresponding stack
        std::vector<char> stack;
        colIndex += s.find(m[0]);

        for (std::string line : linesWithBoxes) {
            try {
                if (line.at(colIndex) != ' ') {
                    // add to respective stack
                    stack.push_back(line.at(colIndex));
                } else {
                    continue;
                }
            } catch(const std::exception& e) {
                std::cerr << e.what() << '\n';
                continue;
            }
        }

        vectorOfStacks.push_back(stack);

        // Search the rest of the string
        s = m.suffix();
        colIndex++;
    }

    std::cout << "last element of 4: " << vectorOfStacks.at(3).back() << std::endl;

    // Now do the crane operations
    std::regex regexp_command(".* ([0-9]+) .* ([0-9]+) .* ([0-9]+)");
    while(std::getline(iss, s)) {
        if (std::regex_search(s, m, regexp_command)) {
            moveCrane(stoi(m[1]), &vectorOfStacks.at(stoi(m[2])-1), &vectorOfStacks.at(stoi(m[3])-1));
        }
    }

    // print tops
    for (int i = 0; i < vectorOfStacks.size(); i++) {
        std::cout << vectorOfStacks.at(i).back();
    }
    std::cout << std::endl;
}