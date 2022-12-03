#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

int main()
{
    // Get input from consol
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    // Store the calories per elve in a vector since we don't know how many elves there are
    std::vector<int> caloriesPerElve;
    caloriesPerElve.push_back(0);

    // Use stringstream to convert the input to integers
    std::stringstream ss(input_string);
    int n;
    while(ss >> n) {
        // Add calories to the elve
        caloriesPerElve.back() += n;

        // This construction checks for 2 consecutive newline characters
        // indicating an empty line
        if (ss.peek() == '\n') {
            ss.get();
            if (ss.peek() == '\n') {
                // New elve, new entry
                caloriesPerElve.push_back(0);
            }
        }
    }
    // Convert the array to a max_heap to easily access the elve with the most calories
    std::make_heap(caloriesPerElve.begin(), caloriesPerElve.end());
    // Get the highest calories count
    std::cout << (int) caloriesPerElve.front() << '\n';
    
    // For part 2:
    // Sum up the three highest values
    int topThree = 0;
    for(int i = 0; i < 3; i++){
        topThree += caloriesPerElve.front();
        std::pop_heap(caloriesPerElve.begin(), caloriesPerElve.end());
        caloriesPerElve.pop_back();
    }
    // Print topThree
    std::cout << (int) topThree << '\n';
    return 0;
}