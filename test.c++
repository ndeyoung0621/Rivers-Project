#include <iostream>
#include <cassert>
#include "river_binary_tree.h"




void testAddRiver() {
    RiverBinaryTree riverTree;

    // Add a root river
    riverTree.addRiver("Columbia", "", 2, 2);
    assert(riverTree.getRoot()->name == "Columbia");

    // Add tributaries to the root river
    riverTree.addRiver("Snake", "Columbia", 1, 1);
    riverTree.addRiver("Willamette", "Columbia", 1, 0);
    assert(riverTree.getRoot()->left->name == "Snake");
    assert(riverTree.getRoot()->right->name == "Willamette");

    // Add tributary to a tributary
    riverTree.addRiver("Clearwater", "Snake", 0, 0);
    assert(riverTree.getRoot()->left->left->name == "Clearwater");

    // Test adding a river with a non-existent parent
    try {
        riverTree.addRiver("NonExistentTributary", "NonExistentRiver", 0, 0);
        assert(false); // Fail the test if no exception is thrown
    } catch (const std::exception& e) {
        assert(string(e.what()) == "Parent river 'NonExistentRiver' not found for 'NonExistentTributary'.");
    }

    // Test adding multiple roots
    try {
        riverTree.addRiver("Missouri", "", 0, 0);
        assert(false); // Fail the test if no exception is thrown
    } catch (const std::exception& e) {
        assert(string(e.what()) == "Multiple root rivers are not allowed.");
    }

    std::cout << "testAddRiver passed." << std::endl;
}

void testReadFromCSV() {
    RiverBinaryTree riverTree;
    
    try {
        riverTree.readFromCSV("non_existent_file.csv");
        assert(false); // Fail the test if no exception is thrown
    } catch (const std::exception& e) {
        assert(string(e.what()).find("Unable to open file: non_existent_file.csv") != string::npos);
    }

    // Assuming a valid CSV "rivers.csv" exists
    riverTree.readFromCSV("columbiaInformation.csv");

    // Check if root and its children are correctly loaded
    assert(riverTree.getRoot()->name == "Columbia River");
    assert(riverTree.getRoot()->right->name == "Kootenai");

    std::cout << "testReadFromCSV passed." << std::endl;
}

void testPrintTreeTopDown() {
    RiverBinaryTree riverTree;

    // Test empty tree
    riverTree.printTreeTopDown();

    // Test populated tree
    riverTree.addRiver("Columbia", "", 2, 2);
    riverTree.addRiver("Snake", "Columbia", 1, 1);
    riverTree.addRiver("Willamette", "Columbia", 1, 0);
    riverTree.addRiver("Clearwater", "Snake", 0, 0);
    riverTree.printTreeTopDown(); // Manual check to ensure output is correct

    std::cout << "testPrintTreeTopDown passed (manual check required)." << std::endl;
}

void testSearchRiver() {
    RiverBinaryTree riverTree;

    // Setup tree
    riverTree.addRiver("Columbia", "", 2, 2);
    riverTree.addRiver("Snake", "Columbia", 1, 1);
    riverTree.addRiver("Willamette", "Columbia", 1, 0);
    riverTree.addRiver("Clearwater", "Snake", 0, 0);

    // Test search for existing rivers
    riverTree.searchRiver("Snake");
    riverTree.searchRiver("Willamette");
    riverTree.searchRiver("Clearwater");

    // Test search for a non-existent river
    riverTree.searchRiver("NonExistentRiver");

    std::cout << "testSearchRiver passed (manual check required)." << std::endl;
}

void testTraverseTree() {
    RiverBinaryTree riverTree;

    // Setup tree
    riverTree.addRiver("Columbia", "", 2, 2);
    riverTree.addRiver("Snake", "Columbia", 1, 1);
    riverTree.addRiver("Willamette", "Columbia", 1, 0);
    riverTree.addRiver("Clearwater", "Snake", 0, 0);

    // Call traverseTree (manual interaction required)
    std::cout << "Begin manual traversal test. Please follow the prompts." << std::endl;
    riverTree.traverseTree(riverTree.getRoot());

    std::cout << "testTraverseTree passed (manual check required)." << std::endl;
}

void testGetRoot() {
    RiverBinaryTree riverTree;

    // Check root of an empty tree
    assert(riverTree.getRoot() == nullptr);

    // Add a root river
    riverTree.addRiver("Columbia", "", 2, 2);
    assert(riverTree.getRoot() != nullptr);
    assert(riverTree.getRoot()->name == "Columbia");

    std::cout << "testGetRoot passed." << std::endl;
}



    int main() {
    
    testPrintTreeTopDown();
    testSearchRiver();
    testTraverseTree();
    testGetRoot();

    std::cout << "All tests passed." << std::endl;
    return 0;
}