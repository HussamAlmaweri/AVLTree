#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

	// Constructor
	Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
	Node* root;
	// Helper functions
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    Node* insert(Node* node, int key);
    void printTree(Node* node, int space);

public:
	AVLTree() : root(nullptr) {}

    void insert(int key) {
        root = insert(root, key);
    }

    void display() {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
        }
        else {
            cout << "AVL Tree: " << endl;
            printTree(root, 0);
        }
    }
   
};

// Function implementations
int AVLTree::getHeight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVLTree::getBalance(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return x;
}

Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* AVLTree::insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    else {
        return node; // Duplicate keys not allowed
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
void AVLTree::printTree(Node* node, int space) {
    if (node == nullptr)
        return;

    space += 10;
    printTree(node->right, space);

    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << node->key << "(" << getBalance(node) << ")" << endl;

    printTree(node->left, space);
}



int main() {
    AVLTree tree;
    int choice, value;

    while (true) {
		cout << "\nAVL Tree Menu:\n";
		cout << "1. Insert\n";
		cout << "2. Display\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;


        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            cout << "Inserted " << value << " into the AVL Tree.\n";
	        break;

        case 2:
            tree.display();
            break;

        case 3:
			cout << "Exiting program.\n";
			return 0;
        default:
			cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;  
}
