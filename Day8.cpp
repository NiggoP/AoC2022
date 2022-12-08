#include <iostream>
#include <string>
#include <sstream>
#include <vector>

/*
Two approaches come to mind:
1.  Check for each tree wheather it is visible in any direction
+ No additional memory required
- Time Complexity O(n²)

2.  Check for each direction and remember visible trees
+ One must only check once in each direction -> Time Complexity O(4n)
- One must check for duplicates, for example if a tree is visible from multiple
  directions. Therefore 2nd tree matrix to keep track -> Space Complexity O(n)
*/

int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '$');

    std::istringstream iss(input_string);
    std::string s;
    
    std::vector<std::vector<int>> forest;

    // Read input into a 2dim vector
    while(std::getline(iss, s)) {
        std::vector<int> line;
        for (auto c : s) {
            line.push_back(atoi(&c));
        }
        forest.push_back(line);
    }

    // Create a duplicate of forest to track visible trees
    int xlength = forest.at(0).size();
    int ylength = forest.size();
    int *visibleTreeMap = new int[xlength * ylength] {} ;
    // x->
    // y
    // |
    // v


    // Look from top
    for (int x = 0; x < xlength; x++) {
        int highest = -1;
        for (int y = 0; y < ylength; y++) {
            if (forest.at(y).at(x) > highest) {
                // this tree is visible
                visibleTreeMap[y*xlength + x] = 1;
                highest = forest.at(y).at(x);
            }
        }
    }

    // Look from bottom
    for (int x = 0; x < xlength; x++) {
        int highest = -1;
        for (int y = ylength-1; y >= 0; y--) {
            if (forest.at(y).at(x) > highest) {
                // this tree is visible
                visibleTreeMap[y*xlength + x] = 1;
                highest = forest.at(y).at(x);
            }
        }
    }

    // Look from left
    for (int y = 0; y < ylength; y++) {
        int highest = -1;
        for (int x = 0; x < xlength; x++) {
            if (forest.at(y).at(x) > highest) {
                // this tree is visible
                visibleTreeMap[y*xlength + x] = 1;
                highest = forest.at(y).at(x);
            }
        }
    }

    // Look from right
    for (int y = 0; y < ylength; y++) {
        int highest = -1;
        for (int x = xlength-1; x >= 0; x--) {
            if (forest.at(y).at(x) > highest) {
                // this tree is visible
                visibleTreeMap[y*xlength + x] = 1;
                highest = forest.at(y).at(x);
            }
        }
    }

    // Count visible trees
    int sumOfVisibleTrees = 0;
    for (int i = 0; i < xlength*ylength; i++) {
        sumOfVisibleTrees += visibleTreeMap[i];
    }

    // Print visible trees
    std::cout << "#visible trees: " << sumOfVisibleTrees << std::endl;

    // Part 2
    // Calculate scenic score for each tree
    // Time Complexity O(n²)
    // Space Complexity O(n)

    int highestScenicScore = 0;

    // ignore outer ring of trees since one viewing direction will always be 0
    // scenic score will also be 0
    for (int x = 1; x < xlength-1; x++) {
        for (int y = 1; y < ylength-1; y++) {
            // 4 indices corresponding to each direction
            int t = y - 1;
            int b = y + 1;
            int l = x - 1;
            int r = x + 1;
            int score[4];

            // explore top
            // while tree < house : continue
            // if tree is edge : break;
            while (forest.at(t).at(x) < forest.at(y).at(x)) {
                if (t <= 0) {
                    // we reached the edge
                    break;
                } else {
                    t--;
                }
            }
            score[0] = y - t;

            // explore bot
            while (forest.at(b).at(x) < forest.at(y).at(x)) {
                if (b >= ylength-1) {
                    // we reached the edge
                    break;
                } else {
                    b++;
                }
            }
            score[1] = b - y;

            // explore left
            while (forest.at(y).at(l) < forest.at(y).at(x)) {
                if (l <= 0) {
                    // we reached the edge
                    break;
                } else {
                    l--;
                }
            }
            score[2] = x - l;

            // explore right
            while (forest.at(y).at(r) < forest.at(y).at(x)) {
                if (r >= xlength-1) {
                    // we reached the edge
                    break;
                } else {
                    r++;
                }
            }
            score[3] = r - x;

            // Now calc score and check if new highest
            int scenicScore = score[0] * score[1] * score[2] * score[3];
            highestScenicScore =  std::max(highestScenicScore, scenicScore);
        }
    }

    std::cout << "Highest scenic score: " << highestScenicScore << std::endl;
}