#include <iostream>
#include <cassert>
#include "main.c++"  // Include the implementation file

using namespace std;

// Helper function to test adding rivers
void testAddRiver() {
    RiverBinaryTree tree;

    try {
        tree.addRiver("Columbia", "", 10, 5);
        tree.addRiver("Snake", "Columbia", 8, 3);
        tree.addRiver("Yakima", "Columbia", 4, 2);

        auto root = tree.getRoot();
        assert(root->name == "Columbia");
        assert(root->numDams == 10);
        assert(root->numTributaries == 5);

        assert(root->left->name == "Snake");
        assert(root->left->numDams == 8);

        assert(root->left->right->name == "Yakima");
        cout << "testAddRiver passed!" << endl;
    } catch (const exception& e) {
        cout << "testAddRiver failed: " << e.what() << endl;
    }
}

// Helper function to test reading from CSV
void testReadFromCSV() {
    RiverBinaryTree tree;

    try {
        tree.readFromCSV("test_data.csv"); // Replace with a test CSV file
        auto root = tree.getRoot();
        assert(root != nullptr);
        assert(root->name == "Columbia");
        assert(root->left->name == "Snake");

        cout << "testReadFromCSV passed!" << endl;
    } catch (const exception& e) {
        cout << "testReadFromCSV failed: " << e.what() << endl;
    }
}

// Helper function to test searching rivers
void testSearchRiver() {
    RiverBinaryTree tree;

    tree.addRiver("Columbia", "", 10, 5);
    tree.addRiver("Snake", "Columbia", 8, 3);

    try {
        tree.searchRiver("Columbia");
        tree.searchRiver("Snake");
        tree.searchRiver("Nonexistent");  // Should handle gracefully

        cout << "testSearchRiver passed!" << endl;
    } catch (const exception& e) {
        cout << "testSearchRiver failed: " << e.what() << endl;
    }
}

// Helper function to test tree traversal
void testTraverseTree() {
    RiverBinaryTree tree;

    tree.addRiver("Columbia", "", 10, 5);
    tree.addRiver("Snake", "Columbia", 8, 3);
    tree.addRiver("Yakima", "Snake", 4, 2);

    try {
        tree.traverseTree(tree.getRoot());
        cout << "testTraverseTree passed!" << endl;
    } catch (const exception& e) {
        cout << "testTraverseTree failed: " << e.what() << endl;
    }
}

// Main test runner function
void runTests() {
    cout << "Running tests..." << endl;
    testAddRiver();
    testReadFromCSV();
    testSearchRiver();
    testTraverseTree();
    cout << "All tests completed." << endl;
}
/*
int main() {
    runTests();
    return 0;
}
*/