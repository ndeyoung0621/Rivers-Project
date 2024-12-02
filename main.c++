#include <std>
#include <iostream>
#include <queue>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;

    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
    private:
    Node<T>* root;
    
    Node<T>* recursiveDel(Node<T>* current, T value)
    {
        if (current == nullptr)
            return nullptr;
        if (current->data == value)
        {
            if (current->left == nullptr && current->right == nullptr)
            {
                delete current;
                return nullptr;
            }
            if (current->left == nullptr)
            {
                Node<T>* temp = current->right;
                delete current;
                return temp;
            }
            if (current->right == nullptr)
            {
                Node<T>* temp = current->left;
                delete current;
                return temp;
            }
            Node<T>* successor = findMin(current->right);
            current->data = successor->data;
            current->right = recursiveDel(current->right, succesor->data);
        }
        else
        {
            current->left = recursiveDel(current->left, value);
            current->right = recursiveDel(current->right, value);
        }
        return current;
    }

    Node<T>* findMin(Node<T>* node)
    {
        while (node->left != nullptr)
        {
            node = node->left;
            return node;
        }
    }

    bool recursiveSearch(Node<T>* current, T value)
    {
        if (current == nullptr)
            return false;
        if (current->data == value)
            return true;
        return recursiveSearch(current->left, value) || recursiveSearch(current->right, value);
    }

    void inorderRecusrsion(Node<T>* node)
    {
        if (node != nullptr)
        {
            inorderRecusrsion(node->left);
            cout << node->data << ", ";
            inorderRecusrsion(node->right);
        }
    }

    void preorderRecursion(Node<T>* node)
    {
        if (node != nullptr)
        {
            cout << node->data << ", ";
            preorderRecusrsion(node->left);
            preorderRecusrsion(node->right);
        }
    }

    void postorderRecursion(Node<T>* node)
    {
        if (node != nullptr)
        {
            preorderRecusrsion(node->left);
            preorderRecusrsion(node->right);
            cout << node->data << ", ";
        }
    }
    public:

    BinaryTree() : root(nullptr) {}

    void insertNode(T value)
    {
        Node<T>* newNode = new Node<T>(value);

        if (root == nullptr)
        {
            root = newNode;
            return;
        }

        queue<Node<T>*> q;
        q.push(root);

        while (!q.empty())
        {
            Node<T>* current = q.front();
            q.pop();

            if (current->left == nullptr)
            {
                current->left = newNode;
                return;
            }
            else
            {
                q.push(current->left);
            }

            if (current->right == nullptr)
            {
                current->right = newNode;
                return;
            }
            else
            {
                q.push(current->right);
            }
        }
    }

    void deleteNode(T value)
    {
        root = recursiveDel(root, value);
    }

    bool search(T value)
    {
        return recursiveSearch(root, value);
    }

    void inorder()
    {
        inorderRecusrsion(root);
        cout << endl;
    }

    void preorder()
    {
        preorderRecursion(root);
        cout << endl;
    }

    void postorder()
    {
        postorderRecursion(root);
        cout << endl;
    }
}

int main()
{
    
}

