#include <gtest/gtest.h>
#include "main.c++"  // Include the implementation file

// Test the addition of rivers
TEST(RiverTreeTest, AddRiver) {
    RiverBinaryTree riverTree;

    // Adding rivers
    riverTree.addRiver("Columbia", "", 1, 1);          // Root river with dams
    riverTree.addRiver("Snake", "Columbia", 0, 1);    // Tributary without dams
    riverTree.addRiver("Willamette", "Columbia", 1, 0); // Tributary with dams
    riverTree.addRiver("Clearwater", "Snake", 0, 0);   // Tributary of Snake with dams

    // Validate the root
    ASSERT_NE(riverTree.getRoot(), nullptr);
    EXPECT_EQ(riverTree.getRoot()->name, "Columbia");

    // Validate tributaries of the root
    auto root = riverTree.getRoot();
    ASSERT_EQ(root->NumTributaries, 2);
    EXPECT_EQ(root->left->name, "Snake");
    EXPECT_EQ(root->right->name, "Willamette");

    // Validate nested tributaries
    auto snake = root->tributaries[0];
    ASSERT_EQ(snake->tributaries.size(), 1);
    EXPECT_EQ(snake->tributaries[0]->name, "Clearwater");
}

// Test adding a river with a non-existent parent
TEST(RiverTreeTest, InvalidParent) {
    RiverBinaryTree riverTree;

    // Attempt to add a river with a non-existent parent and expect an exception
    EXPECT_THROW(riverTree.addRiver("NewRiver", "NonExistentRiver", 0, 0), std::runtime_error);
}

// Test adding multiple root rivers
TEST(RiverTreeTest, MultipleRoots) {
    RiverBinaryTree riverTree;

    // Add the first root river
    riverTree.addRiver("Columbia", "", 1, 1);

    // Attempt to add another root river and expect an exception
    EXPECT_THROW(riverTree.addRiver("Missouri", "", 1, 1), std::runtime_error);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
