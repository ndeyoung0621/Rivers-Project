#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iomanip>
#include <algorithm>

using namespace std;

struct RiverNode {
    string name;
    bool hasDams;
    vector<shared_ptr<RiverNode>> tributaries;

    RiverNode(const string& riverName, bool dams)
        : name(riverName), hasDams(dams) {}
};

class RiverTree {
private:
    shared_ptr<RiverNode> root;
    map<string, shared_ptr<RiverNode>> nodes;

public:
    // Add a river to the tree
    void addRiver(const string& name, const string& parent, bool hasDams) {
        auto riverNode = make_shared<RiverNode>(name, hasDams);
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
                parentNode->second->tributaries.push_back(riverNode);
            } else {
                throw runtime_error("Parent river '" + parent + "' not found for '" + name + "'.");
            }
        }
    }

    // Read data from a CSV file and build the tree
    void readFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Unable to open file: " + filename);
        }

        string line;
        getline(file, line);  // Skip the header line

        while (getline(file, line)) {
            stringstream ss(line);
            string name, parent, hasDamsStr;

            getline(ss, name, ',');
            getline(ss, parent, ',');
            getline(ss, hasDamsStr, ',');

            bool hasDams = (hasDamsStr == "true");
            addRiver(name, parent, hasDams);
        }
        file.close();
    }

    // Recursive function to print the tree vertically with symbols
    void printTreeVerticallyWithSymbols(shared_ptr<RiverNode> node, const string& prefix = "", bool isLast = true) {
        if (!node) return;

        // Print the current node with the appropriate prefix
        cout << prefix << (isLast ? "└── " : "├── ") << node->name
            << (node->hasDams ? " (D)" : "") << endl;

        // Update the prefix for the next level
        string newPrefix = prefix + (isLast ? "    " : "│   ");

        // Recursively print each tributary
        for (size_t i = 0; i < node->tributaries.size(); ++i) {
            printTreeVerticallyWithSymbols(node->tributaries[i], newPrefix, i == node->tributaries.size() - 1);
        }
    }

    // Function to initiate the vertical tree printing with symbols
    void printTreeTopDown() {
        if (!root) {
            cout << "The tree is empty." << endl;
            return;
        }

        printTreeVerticallyWithSymbols(root);
    }

    // Getter for root (public)
    shared_ptr<RiverNode> getRoot() const {
        return root;
    }
};

int main() {
    RiverTree riverTree;

    try {
        riverTree.readFromCSV("columbiaInformation.csv");
        riverTree.printTreeTopDown();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}