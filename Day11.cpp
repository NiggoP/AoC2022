#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>

#define PART2

// input
/*
Monkey 0:
  Starting items: 79, 98
  Operation: new = old * 19
  Test: divisible by 23
    If true: throw to monkey 2
    If false: throw to monkey 3
*/

using namespace std;

class Monkey {

    public:

    Monkey(vector<Monkey> *monkeys, int monkeyNr, vector<long> itemList, int testNumber, bool operationIsAdd,
            int operand, int nextMonkeyIfTrue, int nextMonkeyIfFalse) {
                this->monkeys = monkeys;
                this->monkeyNumber = monkeyNr;
                this->itemList = itemList;
                this->testNumber = testNumber;
                this->operationIsAdd = operationIsAdd;
                this ->operand = operand;
                this->nextMonkeyIfTrue = nextMonkeyIfTrue;
                this->nextMonkeyIfFalse = nextMonkeyIfFalse;
            }

    void inspect_items() {
        for (auto item : itemList) {
            // increase inspection counter
            monkeys->at(monkeyNumber).numberOfInspections++;

            // increase the worry level of item
            int tmp = operand;
            if (tmp == 0) {
                tmp = item;
            }

            if (operationIsAdd) {
                item += tmp;
            } else {
                item *= tmp;
            }

            // monkey gets bored
            #ifndef PART2
            item = item / 3;
            #else
            item = item % scd;  // modulo preserves modulo characteristic
            #endif

            // perform test
            if (item % testNumber == 0) {
                // True
                monkeys->at(nextMonkeyIfTrue).itemList.push_back(item);
            } else {
                monkeys->at(nextMonkeyIfFalse).itemList.push_back(item);
            }
        }

        // All items have been thrown
        monkeys->at(monkeyNumber).itemList.clear();
    }

    int getInspections() {
        return numberOfInspections;
    }

    int getNr() {
        return monkeyNumber;
    }


    int getTestNumber() {
        return testNumber;
    }

    void setSCD(int scd) {
        this->scd = scd;
    }

    private:
    
    int monkeyNumber;
    vector<long> itemList;
    int testNumber;
    bool operationIsAdd;
    int operand;
    int nextMonkeyIfTrue;
    int nextMonkeyIfFalse;

    int numberOfInspections = 0;
    vector<Monkey> *monkeys;

    int scd;    // smallest common divider
};


int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    string input_string;
    getline(cin, input_string, '$');

    istringstream iss(input_string);
    string s;

    regex pattern("Monkey (\\d+):\\n +Starting items: ([\\d, ]+)\\n +Operation: new = old (.) (.+)\\n +Test: divisible by (\\d+)\\n +If true: throw to monkey (\\d+)\\n +If false: throw to monkey (\\d+)");
    smatch match;

    vector<Monkey> monkeys;

    while (regex_search(input_string, match, pattern)) {
        int monkeyNumber = stoi(match[1]);

        string items_string = match[2];
        // Split the string of numbers into a vector
        regex split_pattern("\\d+");
        vector<long> items;
        for (sregex_iterator i = sregex_iterator(items_string.begin(), items_string.end(), split_pattern);
            i != sregex_iterator();
            ++i) {
            
            smatch split_match = *i;
            items.push_back(stoi(split_match.str()));
        }
        //char operation = (char) match[3];
        bool isOpAdd;
        if (match[3].compare("*") == 0) {
            isOpAdd = false;
        } else if (match[3].compare("+") == 0) {
            isOpAdd = true;
        } else {
            cout << "ERROR: Unknown operation" << endl;
            return 0;
        }
        int operand = 0;
        if (match[4].compare("old") != 0) {
            operand = stoi(match[4]);
        }
        int testNumber = stoi(match[5]);
        int nextMonkeyIfTrue = stoi(match[6]);
        int nextMonkeyIfFalse = stoi(match[7]);

        // Create Monkey
        Monkey *m = new Monkey(&monkeys, monkeyNumber, items, testNumber, isOpAdd, operand, nextMonkeyIfTrue, nextMonkeyIfFalse);
        monkeys.push_back(*m);

        if (input_string.find("\n\n") == string::npos) {
            break;
        }
        input_string = input_string.substr(input_string.find("\n\n") + 1);
    }

    // Lets play X rounds
    #ifndef PART2
    int x = 20;
    #else
    int x = 10000;
    // set scd
    int scd = 1;
    for (int i = 0; i < monkeys.size(); i++) {
        scd *= monkeys.at(i).getTestNumber();
    }

    for (int i = 0; i < monkeys.size(); i++) {
        monkeys.at(i).setSCD(scd);
    }
    #endif

    for (int i = 0; i < x; i++) {
        for (Monkey m : monkeys) {
            m.inspect_items();
        }
    }

    vector<int> inspections;
    for (Monkey m : monkeys) {
        cout << "Monkey " << m.getNr() << " inspected items: " << m.getInspections() << endl;
        inspections.push_back(m.getInspections());
    }

    sort(inspections.begin(), inspections.end());
    unsigned long a = inspections.at(inspections.size()-2);
    unsigned long b = inspections.back();
    unsigned long res = a*b;

    cout << "Res: " << res << endl;


}