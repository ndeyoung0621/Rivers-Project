#include <iostream>
#include <cassert>

#include "main.c++"  // Include the implementation file or header if separate

// Test function to check the river tree structure
void testAddRiver() {
    RiverTree riverTree;

    // Adding rivers
    riverTree.addRiver("Columbia", "", true); // Root river with dams
    riverTree.addRiver("Snake", "Columbia", false); // Tributary without dams
    riverTree.addRiver("Willamette", "Columbia", true); // Tributary with dams
    riverTree.addRiver("Clearwater", "Snake", false); // Tributary of Snake without dams

    // Check if the root is correctly set
    assert(riverTree.getRoot()->name == "Columbia");
    
    // Check if tributaries are correctly added
    assert(riverTree.getRoot()->tributaries.size() == 2);
    assert(riverTree.getRoot()->tributaries[0]->name == "Snake");
    assert(riverTree.getRoot()->tributaries[1]->name == "Willamette");

    // Check nested tributaries
    assert(riverTree.getRoot()->tributaries[0]->tributaries.size() == 1);
    assert(riverTree.getRoot()->tributaries[0]->tributaries[0]->name == "Clearwater");

    std::cout << "testAddRiver passed." << std::endl;
}

void testInvalidParent() {
    RiverTree riverTree;

    try {
        // Attempt to add a river with a non-existent parent
        riverTree.addRiver("NewRiver", "NonExistentRiver", false);
        std::cerr << "testInvalidParent failed: Exception not thrown." << std::endl;
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Parent river 'NonExistentRiver' not found for 'NewRiver'.");
        std::cout << "testInvalidParent passed." << std::endl;
    }
}

void testMultipleRoots() {
    RiverTree riverTree;

    try {
        // Adding multiple root rivers (this should throw an exception)
        riverTree.addRiver("Columbia", "", true);
        riverTree.addRiver("Missouri", "", false);
        std::cerr << "testMultipleRoots failed: Exception not thrown." << std::endl;
    } catch (const std::exception& e) {
        assert(std::string(e.what()) == "Multiple root rivers are not allowed.");
        std::cout << "testMultipleRoots passed." << std::endl;
    }
}

int main() {
    // Run the tests
    testAddRiver();
    testInvalidParent();
    testMultipleRoots();

    return 0;
}