#include "river_binary_tree.h"

// RiverNode constructor
RiverNode::RiverNode(const string& riverName, int dams, int tributariesCount)
    : name(riverName), numDams(dams), numTributaries(tributariesCount), left(nullptr), right(nullptr) {}

// Adds a river to the tree
void RiverBinaryTree::addRiver(const string& name, const string& parent, int numDams, int numTributaries) {
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

// Reads a CSV file and adds rivers to the tree
void RiverBinaryTree::readFromCSV(const string& filename) {
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

// Print the tree structure
void RiverBinaryTree::printTree(shared_ptr<RiverNode> node, const string& prefix, bool isLeft) {
    if (!node) return;

    cout << prefix << (isLeft ? "└── " : "├── ") << node->name
         << " (Dams: " << node->numDams << ", Tributaries: " << node->numTributaries << ")" << endl;

    printTree(node->left, prefix + (isLeft ? "    " : "│   "), true);
    printTree(node->right, prefix + (isLeft ? "    " : "│   "), false);
}

void RiverBinaryTree::printTreeTopDown() {
    if (!root) {
        cout << "The tree is empty." << endl;
        return;
    }
    printTree(root);
}

// Search for a river in the tree
void RiverBinaryTree::searchRiver(const string& riverName) const {
    auto it = nodes.find(riverName);
    if (it == nodes.end()) {
        cout << "River '" << riverName << "' not found in the tree." << endl;
        return;
    }

    auto riverNode = it->second;
    string parentName = "None";
    for (const auto& pair : nodes) {
        auto parent = pair.second;
        if (parent->left == riverNode || parent->right == riverNode) {
            parentName = parent->name;
            break;
        }
    }

    cout << "River: " << riverNode->name << endl;
    cout << "Parent: " << parentName << endl;
    cout << "Number of Dams: " << riverNode->numDams << endl;
    cout << "Number of Tributaries: " << riverNode->numTributaries << endl;
}

void RiverBinaryTree::traverseTree(shared_ptr<RiverNode> node) {
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

shared_ptr<RiverNode> RiverBinaryTree::getRoot() const {
    return root;
}