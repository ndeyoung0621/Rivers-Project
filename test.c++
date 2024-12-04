#include <iostream>
#include <cassert>

#include "main.c++"  // Include the implementation file or header if separate

// Test function to check the river tree structure
void testAddRiver() {
    RiverBinaryTree riverTree;

    // Adding rivers
    riverTree.addRiver("Columbia", "", 1, 1); // Root river with dams
    riverTree.addRiver("Snake", "Columbia", 0, 1); // Tributary without dams
    riverTree.addRiver("Willamette", "Columbia", 1, 1); // Tributary with dams
    riverTree.addRiver("Clearwater", "Snake", 1, 1); // Tributary of Snake without dams

    // Check if the root is correctly set
    assert(riverTree.getRoot()->name == "Columbia");
    
    // Check if tributaries are correctly added
    assert(riverTree.getRoot()->numTributaries == 2);
    assert(riverTree.getRoot()->left->name == "Snake");
    assert(riverTree.getRoot()->right->name == "Willamette");

    // Check nested tributaries
    assert(riverTree.getRoot()->left->numTributaries == 1);
    assert(riverTree.getRoot()->left->left->name == "Clearwater");

    std::cout << "testAddRiver passed." << std::endl;
}

void testInvalidParent() {
    RiverBinaryTree riverTree;

    try {
        // Attempt to add a river with a non-existent parent
        riverTree.addRiver("NewRiver", "NonExistentRiver", 0, 0);
        std::cerr << "testInvalidParent failed: Exception not thrown." << std::endl;
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Parent river 'NonExistentRiver' not found for 'NewRiver'.");
        std::cout << "testInvalidParent passed." << std::endl;
    }
}

void testMultipleRoots() {
    RiverBinaryTree riverTree;

    try {
        // Adding multiple root rivers (this should throw an exception)
        riverTree.addRiver("Columbia", "", 1, 1);
        riverTree.addRiver("Missouri", "", 0, 1);
        std::cerr << "testMultipleRoots failed: Exception not thrown." << std::endl;
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Multiple root rivers are not allowed.");
        std::cout << "testMultipleRoots passed." << std::endl;
    }
}

    int testRun() {
    // Run the tests
    testAddRiver();
    testInvalidParent();
    testMultipleRoots();

    return 0;
}