#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

#define PART2

std::vector<int> stringToPriority(std::string inputString) {
    std::vector<int> ret;
    for (char c : inputString) {
        if ((int) c >= (int) 'a') { // Check if lowercase
            ret.push_back((int) c - (int) 'a' + 1);
        } else {
            ret.push_back((int) c - (int) 'A' + 27);
        }
    }
    return ret;
}

int findCommon(std::vector<int> a, std::vector<int> b) {
    // First sort vectors
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int i = 0;
    int j = 0;
    while (true) {
        if (a[i] == b[j]) {
            return a[i];
        } else if (a[i] < b[j]) {
            i++;
        } else if (a[i] > b[j]) {       // TODO: No default else
            j++;
        }

        // Check bounds
        if (i >= a.size() or j >= b.size()) {
            return 0;
        }
    }
}


int findCommon(std::vector<int> a, std::vector<int> b, std::vector<int> c) {
    // First sort vectors
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());
    int i = 0;
    int j = 0;
    int k = 0;
    while (true) {
        if (a[i] == b[j] and b[j] == c[k]) {
            return a[i];
        } else if (a[i] <= b[j] and a[i] <= c[k]) {
            i++;
        } else if (b[j] <= a[i] and b[j]  <= c[k]) {
            j++;
        } else if (c[k] <= a[i] and c[k]  <= b[j]) {    // TODO: No default else
            k++;
        }

        // Check bounds
        if (i >= a.size() or j >= b.size() or k >= c.size()) {
            return 0;
        }
    }
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

    // Create strings for each compartment
    std::string firstCompartment;
    std::string secondCompartment;
    int sum = 0;
    int line = 0;
    std::vector<int> triple[3];

    while(std::getline(iss, s)) {
        #ifndef PART2

        if (s.length() % 2 == 1) {
            return 1;   //the two compartemnts have different amounts of items
        }
        firstCompartment = s.substr(0, s.length()/2);
        secondCompartment = s.substr(s.length()/2, s.length()/2);
        std::vector<int> firstCompartment_Prio = stringToPriority(firstCompartment);
        std::vector<int> secondCompartment_Prio = stringToPriority(secondCompartment);
        sum += findCommon(firstCompartment_Prio, secondCompartment_Prio);
        
        #else

        // keep track in which line we are
        triple[line] = stringToPriority(s);
        line++;
        if (line > 2) {    // triple complete
            line = 0;       // reset line
            // Now we find the common element
            sum += findCommon(triple[0], triple[1], triple[2]);
        }
        
        #endif
    }

    std::cout << "Sum: " << sum << std::endl;
}