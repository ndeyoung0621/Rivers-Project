#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

using namespace std;

struct RiverNode {
    string name;
    int numDams;
    int numTributaries;
    shared_ptr<RiverNode> left;  // Primary tributary (or first child)
    shared_ptr<RiverNode> right; // Continuation or sibling

    RiverNode(const string& riverName, int dams, int tributariesCount)
        : name(riverName), numDams(dams), numTributaries(tributariesCount), left(nullptr), right(nullptr) {}
};

class RiverBinaryTree {
private:
    shared_ptr<RiverNode> root;
    map<string, shared_ptr<RiverNode>> nodes;

public:
    void addRiver(const string& name, const string& parent, int numDams, int numTributaries) {
        auto riverNode = make_shared<RiverNode>(name, numDams, numTributaries);
        nodes[name] = riverNode;

        if (parent.empty()) {
            if (!root) {
                root = riverNode;
            } else {
                throw runtime_error("Multiple root rivers are not allowed.");
            }
        } else {
            auto parentNode = nodes.find(parent);
            if (parentNode != nodes.end()) {
                if (!parentNode->second->left) {
                    parentNode->second->left = riverNode;
                } else {
                    auto sibling = parentNode->second->left;
                    while (sibling->right) {
                        sibling = sibling->right;
                    }
                    sibling->right = riverNode;
                }
            } else {
                throw runtime_error("Parent river '" + parent + "' not found for '" + name + "'.");
            }
        }
    }

    void readFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + filename);
        }

        string line;
        getline(file, line);  // Skip the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string name, parent, numDamsStr, numTributariesStr;

            getline(ss, name, ',');
            getline(ss, parent, ',');
            getline(ss, numDamsStr, ',');
            getline(ss, numTributariesStr, ',');

            int numDams = stoi(numDamsStr);
            int numTributaries = stoi(numTributariesStr);
            addRiver(name, parent, numDams, numTributaries);
        }
        file.close();
    }

    void printTree(shared_ptr<RiverNode> node, const string& prefix = "", bool isLeft = true) {
        if (!node) return;

        cout << prefix << (isLeft ? "└── " : "├── ") << node->name
             << " (Dams: " << node->numDams << ", Tributaries: " << node->numTributaries << ")" << endl;

        printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
        printTree(node->right, prefix + (isLeft ? "    " : "│   "), false);
    }

    //Just a catch method
    void printTreeTopDown() {
        if (!root) {
            cout << "The tree is empty." << endl;
            return;
        }
        printTree(root);
    }

    void searchRiver(const string& riverName) const {
    // Check if the river exists in the map
    auto it = nodes.find(riverName);

    if (it == nodes.end()) {
        cout << "River '" << riverName << "' not found in the tree." << endl;
        return;
    }

    // Retrieve the river node
    auto riverNode = it->second;

    // Find the parent by searching all nodes (basic binary search-like logic)
    string parentName = "None";
    for (const auto& pair : nodes) {
        auto parent = pair.second;
        if (parent->left == riverNode || parent->right == riverNode) {
            parentName = parent->name;
            break;
        }
    }

    // Print the river details
    cout << "River: " << riverNode->name << endl;
    cout << "Parent: " << parentName << endl;
    cout << "Number of Dams: " << riverNode->numDams << endl;
    cout << "Number of Tributaries: " << riverNode->numTributaries << endl;
}

    void traverseTree(shared_ptr<RiverNode> node) {
        if (!node) {
            cout << "The tree is empty." << endl;
            return;
        }

        shared_ptr<RiverNode> current = node;

        while (current) {
            cout << "You are at: " << current->name << " (Dams: " << current->numDams
                 << ", Tributaries: " << current->numTributaries << ")" << endl;

            if (current->left) {
                cout << "Press 'L' to go to this river's tributary: " << current->left->name << endl;
            }
            if (current->right) {
                cout << "Press 'R' to continue down the river: " << current->right->name << endl;
            }
            cout << "Press 'B' to go back to root or 'E' to exit traversal." << endl;

            char choice;
            cin >> choice;

            if (choice == 'L' || choice == 'l') {
                if (current->left) {
                    current = current->left;
                } else {
                    cout << "No left tributary." << endl;
                }
            } else if (choice == 'R' || choice == 'r') {
                if (current->right) {
                    current = current->right;
                } else {
                    cout << "No right tributary." << endl;
                }
            } else if (choice == 'B' || choice == 'b') {
                cout << "Returning to root." << endl;
                current = root; // Reset to root for simplicity
            } else if (choice == 'E' || choice == 'e') {
                cout << "Exiting traversal." << endl;
                break;
            } else {
                cout << "Invalid input. Try again." << endl;
            }
        }
    }

    shared_ptr<RiverNode> getRoot() const {
        return root;
    }
};

int main() {
    RiverBinaryTree riverTree;

    try {
        riverTree.readFromCSV("columbiaInformation.csv");
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    while (true) {
        cout << "Enter a command (\"traverse\", \"view map\", a river name, or \"exit\"): ";
        string userInput;
        getline(cin, userInput);  // Use getline to handle full river names with spaces

        if (userInput == "exit") {
            cout << "Exiting program. Goodbye!" << endl;
            break;
        } else if (userInput == "traverse") {
            riverTree.traverseTree(riverTree.getRoot());
        } else if (userInput == "view map") {
            riverTree.printTreeTopDown();
        } else {
            // Assume user entered a river name
            try {
                riverTree.searchRiver(userInput);
            } catch (const exception& e) {
                cout << "Error during search: " << e.what() << endl;
            }
        }
    }

    return 0;
}
