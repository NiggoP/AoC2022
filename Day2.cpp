#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>

#define PART2

enum RPS {  // Different Choices with their attributed points
    rock = 1,
    paper = 2,
    scissors = 3,
};

enum RPS_Result {
    lose = 2,
    draw = 0,
    win = 1,
};

class Strategy {
    public:
        Strategy(RPS opponentsChoice, RPS myChoice) {
            me = myChoice;
            opponent = opponentsChoice;
        };

        Strategy(RPS opponentsChoice, RPS_Result desiredResult) {
            opponent = opponentsChoice;
            gameResult = desiredResult;
        };

        int getResult() {
            int result;
            if (me == opponent) {
                // Draw
                result = 3;
            } else {
                // Determine wheter I won
                // Use the acredited point as a model
                // If I lose: me % 3 = opponent - 1
                // For example: 1 (rock) % 3 = 2 (paper) - 1; If opponent has 2 (paper), he wins
                if (static_cast<int>(me) % 3 == static_cast<int>(opponent) - 1) {
                    // I lose
                    result = 0;
                } else {
                    result = 6;
                }
            }
            return result + static_cast<int>(me);
        }

        void pickHand() {
            // my choice = opponent-1 + result % 3 + 1
            me = static_cast<RPS>(((int) opponent - 1 + (int) gameResult) % 3 + 1);
        }
        
    private:
        RPS me;
        RPS opponent;
        RPS_Result gameResult;
};

int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    std::istringstream iss(input_string);
    std::string s;

    std::map<char, RPS> InputToRPS {
        {'A', RPS::rock},
        {'X', RPS::rock},
        {'B', RPS::paper},
        {'Y', RPS::paper},
        {'C', RPS::scissors},
        {'Z', RPS::scissors},
    };

    std::map<char, RPS_Result> InputToRPS_Result {
        {'X', RPS_Result::lose},
        {'Y', RPS_Result::draw},
        {'Z', RPS_Result::win},
    };

    int myScore = 0;
    // Loop through each line
    while(std::getline(iss, s)) {
        #ifndef PART2
        // Part 1:
        Strategy strat = Strategy(InputToRPS[s.at(0)], InputToRPS[s.at(2)]);
        #else
        // Part 2:
        Strategy strat = Strategy(InputToRPS[s.at(0)], InputToRPS_Result[s.at(2)]);
        strat.pickHand();
        #endif        

        //std::cout << strat.getResult() << std::endl;
        myScore += strat.getResult();
    }
    
    std::cout << "My Score: " << myScore << std::endl;
    
    return 0;
}