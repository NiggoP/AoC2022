#include <iostream>
#include <string>
#include <sstream>
#include <vector>


bool check_for_common(char *from, char *to) {
    int size = to - from;
    int i = 0;
    while (i < size) {
        for (int j = 1; j <= size-i; j++) {
            if (*(from + i) == *(from + i + j)) {
                //std::cout << " found 2: " << *(from + i) << std::endl;
                return false;
            }
        }
        i++;
    }

    return true;
}

int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    int var = 14;

    for (int i = var-1; i < input_string.size(); i++) {
        if (check_for_common(&input_string.at(i-var+1), &input_string.at(i))) {
            std::cout << "Result: " << i+1 << std::endl;
            break;
        }
    }
}
//mjqjpqmgbljsphdztnvjfqwrcgsmlb