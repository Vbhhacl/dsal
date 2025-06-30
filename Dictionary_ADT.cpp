#include <iostream>
#include <cstring>
using namespace std;

struct Node {
    char keyword[50];
    char meaning[200];
    Node* left;
    Node* right;
    int height;

    Node(const char* k, const char* m) : left(nullptr), right(nullptr), height(1) {
        strcpy(keyword, k);
        strcpy(meaning, m);
    }
};

class Dictionary {
private:
    Node* root;

    // Helper function to get height of a node
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Helper function to get balance factor
    int getBalance(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Helper function to update height
    void updateHeight(Node* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Insert a node
    Node* insert(Node* node, const char* keyword, const char* meaning) {
        if (!node) return new Node(keyword, meaning);

        int cmp = strcmp(keyword, node->keyword);
        if (cmp < 0)
            node->left = insert(node->left, keyword, meaning);
        else if (cmp > 0)
            node->right = insert(node->right, keyword, meaning);
        else {
            cout << "Keyword already exists! Updating meaning instead." << endl;
            strcpy(node->meaning, meaning);
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && strcmp(keyword, node->left->keyword) < 0)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && strcmp(keyword, node->right->keyword) > 0)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && strcmp(keyword, node->left->keyword) > 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && strcmp(keyword, node->right->keyword) < 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Find node with minimum value
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    // Delete a node
    Node* deleteNode(Node* root, const char* keyword) {
        if (!root) return root;

        int cmp = strcmp(keyword, root->keyword);
        if (cmp < 0)
            root->left = deleteNode(root->left, keyword);
        else if (cmp > 0)
            root->right = deleteNode(root->right, keyword);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                strcpy(root->keyword, temp->keyword);
                strcpy(root->meaning, temp->meaning);
                root->right = deleteNode(root->right, temp->keyword);
            }
        }

        if (!root) return root;

        updateHeight(root);

        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Search for a keyword
    Node* search(Node* root, const char* keyword, int& comparisons) {
        if (!root) return nullptr;

        comparisons++;
        int cmp = strcmp(keyword, root->keyword);
        if (cmp == 0) return root;
        if (cmp < 0) return search(root->left, keyword, comparisons);
        return search(root->right, keyword, comparisons);
    }

    // Display in ascending order (inorder)
    void displayAscending(Node* node) {
        if (node) {
            displayAscending(node->left);
            cout << node->keyword << ": " << node->meaning << endl;
            displayAscending(node->right);
        }
    }

    // Display in descending order (reverse inorder)
    void displayDescending(Node* node) {
        if (node) {
            displayDescending(node->right);
            cout << node->keyword << ": " << node->meaning << endl;
            displayDescending(node->left);
        }
    }

public:
    Dictionary() : root(nullptr) {}

    void addKeyword() {
        char keyword[50], meaning[200];
        cout << "Enter keyword: ";
        cin.ignore();
        cin.getline(keyword, 50);
        cout << "Enter meaning: ";
        cin.getline(meaning, 200);
        root = insert(root, keyword, meaning);
        cout << "Keyword added successfully!" << endl;
    }

    void deleteKeyword() {
        char keyword[50];
        cout << "Enter keyword to delete: ";
        cin.ignore();
        cin.getline(keyword, 50);
        root = deleteNode(root, keyword);
        cout << "Keyword deleted successfully!" << endl;
    }

    void updateKeyword() {
        char keyword[50], newMeaning[200];
        cout << "Enter keyword to update: ";
        cin.ignore();
        cin.getline(keyword, 50);
        cout << "Enter new meaning: ";
        cin.getline(newMeaning, 200);
        root = deleteNode(root, keyword);
        root = insert(root, keyword, newMeaning);
        cout << "Keyword updated successfully!" << endl;
    }

    void searchKeyword() {
        char keyword[50];
        int comparisons = 0;
        cout << "Enter keyword to search: ";
        cin.ignore();
        cin.getline(keyword, 50);
        Node* result = search(root, keyword, comparisons);
        if (result) {
            cout << "Meaning: " << result->meaning << endl;
            cout << "Comparisons required: " << comparisons << endl;
            cout << "Maximum comparisons in AVL tree: " << getHeight(root) << endl;
            cout << "Complexity: O(log n)" << endl;
        } else {
            cout << "Keyword not found!" << endl;
        }
    }

    void display() {
        int choice;
        cout << "1. Display in ascending order\n2. Display in descending order\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            cout << "\nDictionary (Ascending order):\n";
            displayAscending(root);
        } else {
            cout << "\nDictionary (Descending order):\n";
            displayDescending(root);
        }
    }
};

int main() {
    Dictionary dict;
    int choice;

    while (true) {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Update Keyword\n";
        cout << "4. Search Keyword\n";
        cout << "5. Display Dictionary\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                dict.addKeyword();
                break;
            case 2:
                dict.deleteKeyword();
                break;
            case 3:
                dict.updateKeyword();
                break;
            case 4:
                dict.searchKeyword();
                break;
            case 5:
                dict.display();
                break;
            case 6:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
}