#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <memory>
#include <iomanip>
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
    // Add a river to the binary tree
    void addRiver(const string& name, const string& parent, int numDams, int numTributaries) {
        auto riverNode = make_shared<RiverNode>(name, numDams, numTributaries);
        nodes[name] = riverNode;

        if (parent.empty()) {
            if (!root) {
                root = riverNode;  // Assign root if not already assigned
            } else {
                throw runtime_error("Multiple root rivers are not allowed.");
            }
        } else {
            auto parentNode = nodes.find(parent);
            if (parentNode != nodes.end()) {
                // Assign the new river as a left child or right sibling
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

    // Read data from a CSV file and build the binary tree
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

    // Recursive function to print the binary tree vertically
    void printTree(shared_ptr<RiverNode> node, const string& prefix = "", bool isLeft = true) {
        if (!node) return;

        // Print the current node
        cout << prefix << (isLeft ? "└── " : "├── ") << node->name
             << " (Dams: " << node->numDams << ", Tributaries: " << node->numTributaries << ")" << endl;

        // Recursively print left and right children
        printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
        printTree(node->right, prefix + (isLeft ? "    " : "│   "), false);
    }

    // Function to start printing the tree
    void printTreeTopDown() {
        if (!root) {
            cout << "The tree is empty." << endl;
            return;
        }

        printTree(root);
    }

    // Getter for root
    shared_ptr<RiverNode> getRoot() const {
        return root;
    }
};

int main() {
    RiverBinaryTree riverTree;

    try {
        riverTree.readFromCSV("columbiaInformation.csv");
        riverTree.printTreeTopDown();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}