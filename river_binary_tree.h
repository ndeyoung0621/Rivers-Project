#ifndef RIVER_BINARY_TREE_H
#define RIVER_BINARY_TREE_H

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
    shared_ptr<RiverNode> left;  
    shared_ptr<RiverNode> right; 

    RiverNode(const string& riverName, int dams, int tributariesCount);
};

class RiverBinaryTree {
private:
    shared_ptr<RiverNode> root;
    map<string, shared_ptr<RiverNode>> nodes;

public:
    void addRiver(const string& name, const string& parent, int numDams, int numTributaries);
    void readFromCSV(const string& filename);
    void printTree(shared_ptr<RiverNode> node, const string& prefix = "", bool isLeft = true);
    void printTreeTopDown();
    void searchRiver(const string& riverName) const;
    void traverseTree(shared_ptr<RiverNode> node);
    shared_ptr<RiverNode> getRoot() const;
};

#endif // RIVER_BINARY_TREE_H