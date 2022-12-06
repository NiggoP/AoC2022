#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define PART2

int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    std::istringstream iss(input_string);
    std::string s;

    // Input:
    // 2-4,6-8
    // My variables:
    // a-b,c-d
    
    int index;
    std::string firstRange;
    std::string secondRange;
    int a;
    int b;
    int c;
    int d;

    int counter = 0;

    while(std::getline(iss, s)) {
        index = s.find_first_of(',');
        firstRange = s.substr(0, index);
        secondRange = s.substr(index+1, s.length()-index);
        index = firstRange.find_first_of('-');
        //int deb = index;
        a = stoi(firstRange.substr(0, index));
        b = stoi(firstRange.substr(index+1, firstRange.length()-index));
        //std::cout << "Deb: "  << firstRange.substr(index+1, firstRange.length()-index) << std::endl;
        index = secondRange.find_first_of('-');
        c = stoi(secondRange.substr(0, index));
        d = stoi(secondRange.substr(index+1, secondRange.length()-index));
        // DEBUG
        std::cout << "first: " << firstRange << " second: " << secondRange << std::endl;
        //std::cout << "Index: " << deb << std::endl;
        std::cout << "a: " << a << " b: " << b << " c: " << c << " d: " << d << std::endl;

        // Now lets check for fully containement
        if (a >= c and b <= d) {
            // first is contained in second
            counter++;
            continue;
        }
        if (a<= c and b >= d) {
            // second is contained in first
            counter++;
            continue;
        }

        #ifdef PART2

        if (a >= c and a <= d) {
            counter++;
            continue;
        }
        if (b >= c and b <= d) {
            counter++;
            continue;
        }

        #endif
    }

    // print result
    std::cout << "Counter: " << counter << std::endl;
}