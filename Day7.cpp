#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#define MAXFILESYSTEM 70000000
#define SPACENEEDED 30000000

class Node {
    private:
        std::string name;
        int size;
        Node *parent;
        std::vector<Node*> children;

    public:
        Node(std::string n, Node *p, int s = 0) {
            name = n;
            size = s; 
            parent = p;
        }

        int getSize () {
            return size;
        }

        std::string getName() {
            return name;
        }

        void addChild(Node* c) {
            children.push_back(c);
        }

        Node* getParent() {
            return parent;
        }

        Node* findChildByName(std::string n) {
            for (auto child : children) {
                if (child->name == n) {
                    return child;
                }
            }
            return nullptr;
        }

        int calcSize() {
            if (children.size() == 0) {
                return size;
            } else {
                size = 0;
                for (auto child : children) {
                    size += child->calcSize();
                }
                return size;
            }
        }

        int sumDirUnderX(int x) {
            if (children.size() == 0) {
                return 0;   // This is a file
            }
            
            int sum = 0;
            if (size <= x) {
                sum += size;
            }
            for (auto child : children) {
                sum += child->sumDirUnderX(x);
            }
            return sum;
        }

        Node* smallestDirOverX(int x) {
            if (children.size() == 0) {
                return nullptr; // This is a file
            }

            if (size < x) {
                return nullptr; // Dir to small
            }
            Node *ret = this;
            for (auto child : children) {
                child = child->smallestDirOverX(x);
                if (child != nullptr) {
                    if (child->getSize() < ret->getSize()) {
                        ret = child;
                    }
                }
            }
            return ret;
        }
};

int main()
{
    // Get input from console
    // in order to accept multiple lines aswell as empty lines,
    // we use $ character as EOF
    std::string input_string;
    std::getline(std::cin, input_string, '%');

    std::istringstream iss(input_string);
    std::string s;
    Node root("/", &root);
    Node *current_node;
    std::string command[3];

    while(std::getline(iss, s)) {
        //std::cout << "Line: " << s << std::endl;
        if (s.at(0) == '$') {
            // The line is a command
            if (s.substr(2,2) == "cd") {
                // cd
                if (s.substr(5) == "..") {
                    // cd ..
                    current_node = current_node->getParent();
                } else if (s.substr(5) == "/") {
                    // cd /
                    current_node = &root;
                } else {
                    // cd dir
                    current_node = current_node->findChildByName(s.substr(5));
                }
            } else if (s.substr(2,2) == "ls") {
                // ls
                continue;
            } else {
                // error
                std::cout << "Unknown command" << std::endl;
                continue;
            }
        } else {
            // The line is part of ls output
            // Create new node
            if (current_node == nullptr) {
                std::cout << "ERROR" << std::endl;
                return 0;
            }
            int indexWhitespace = s.find(' ');
            if (s.substr(0, indexWhitespace) == "dir") {
                // dir
                Node *n = new Node(s.substr(indexWhitespace + 1), current_node);
                current_node->addChild(n);
            } else {
                // file
                Node *n = new Node(s.substr(indexWhitespace + 1), current_node, std::stoi(s.substr(0, indexWhitespace)));
                current_node->addChild(n);
            }
        }
    }

    // Traverse through tree and sum directory with size <= 100000
    #define MAXDIRSIZE 100000

    root.calcSize();
    std::cout << "Sum of Dir under X: " << root.sumDirUnderX(MAXDIRSIZE) << std::endl;
    int spaceToFreeUp = SPACENEEDED + root.getSize() - MAXFILESYSTEM;
    std::cout << "Space to free up: " <<spaceToFreeUp << std::endl;
    std::cout << "Dir to delete: " << root.smallestDirOverX(spaceToFreeUp)->getName() << std::endl;
    std::cout << "Dir Size: " << root.smallestDirOverX(spaceToFreeUp)->getSize() << std::endl;
}