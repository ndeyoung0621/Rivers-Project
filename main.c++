#include "river_binary_tree.h"

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
        getline(cin, userInput);

        if (userInput == "exit") {
            break;
        } else if (userInput == "traverse") {
            riverTree.traverseTree(riverTree.getRoot());
        } else if (userInput == "view map") {
            riverTree.printTreeTopDown();
        } else {
            riverTree.searchRiver(userInput);
        }
    }

    return 0;
}