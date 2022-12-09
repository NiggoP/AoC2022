#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <utility>

#define NUMBER_OF_KNOTS 10


class knot {
    public:

    knot(knot *n) {
        next = n;
        pos = {0,0};
        pastPositions.insert({0,0});
    }

    void moveHead(char dir) {
        switch (dir) {
            case 'R':
                pos.first++;
                break;
            case 'L':
                pos.first--;
                break;
            case 'U':
                pos.second++;
                break;
            case 'D':
                pos.second--;
                break;
            
            default:
                break;
        }
        next->update(pos);
    }

    std::set<std::pair<int, int>> get_pastPositions() {
        return pastPositions;
    }

    private:
    std::pair<int, int> pos;
    knot *next = nullptr;
    std::set<std::pair<int, int>> pastPositions;

    void update(std::pair<int, int> pos_prev) {
        // calc vector between previous and current knot
        std::pair<int, int> vec = {0,0};
        vec.first = pos_prev.first - pos.first;
        vec.second = pos_prev.second - pos.second;

        // check if knots touch
        if (abs(vec.first) > 1 or abs(vec.second) > 1) {
            // they don't touch -> update tail positon
            switch (vec.first) {
                case -2:
                    vec.first++;
                    break;
                
                case 2:
                    vec.first--;
                    break;
                
                default:
                    break;
            }
            switch (vec.second) {
                case -2:
                    vec.second++;
                    break;
                
                case 2:
                    vec.second--;
                    break;
                
                default:
                    break;
            }
            pos.first += vec.first;
            pos.second += vec.second;
            pastPositions.insert(pos);

            if (next != nullptr) {
                next->update(pos);
            }
        }
    }
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

    // init rope
    knot tail(nullptr);
    knot *temp =&tail;
    for (int i = 2; i < NUMBER_OF_KNOTS; i++) {
        temp = new knot(temp);
    }
    knot head(temp);

    // Read commands
    while(std::getline(iss, s)) {
        for (int i = 0; i < stoi(s.substr(1)); i++) {
            head.moveHead(s.at(0));
        }
    }

    std::cout <<"Visited positions: " << tail.get_pastPositions().size() << std::endl;
}