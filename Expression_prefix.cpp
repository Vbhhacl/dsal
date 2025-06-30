#include <iostream>
using namespace std;

// Structure for Node
struct Node {
    char data;
    Node* left;
    Node* right;

    // Constructor to initialize the Node
    Node(char val) : data(val), left(nullptr), right(nullptr) {}
};

// ExpressionTree Class Definition
class ExpressionTree {
public:
    Node* root;

    // Constructor
    ExpressionTree() : root(nullptr) {}

    // Build the tree from the prefix expression
    void buildTree(const char prefix[]) {
        Node* stack[50];  // Stack for nodes
        int top = -1;
        int length = 0;

        // Calculate length of the prefix expression
        while (prefix[length] != '\0') length++;

        for (int i = length - 1; i >= 0; i--) {
            char current = prefix[i];

            // If it's an operand, create a node and push it to stack
            if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z')) {
                Node* node = new Node(current);
                stack[++top] = node;
            }
            // If it's an operator, pop two operands from the stack and create a new node
            else if (current == '+' || current == '-' || current == '*' || current == '/') {
                Node* node = new Node(current);
                if (top < 1) {
                    clear(); // Clean up if invalid expression
                    cout << "Error: Invalid prefix expression!" << endl;
                    return;
                }
                node->left = stack[top--];  // Pop the left operand
                node->right = stack[top--]; // Pop the right operand
                stack[++top] = node;  // Push the new node back to the stack
            }
            // Ignore whitespace
            else if (current == ' ' || current == '\t') {
                continue;
            }
            else {
                clear(); // Clean up if invalid character found
                cout << "Error: Invalid character '" << current << "' in expression!" << endl;
                return;
            }
        }

        // The last element in the stack will be the root of the tree
        if (top == 0) {
            root = stack[top];
        } else {
            clear();
            cout << "Error: Invalid prefix expression!" << endl;
        }
    }

    // Non-recursive Post-order Traversal
    void postOrderTraversal() const {
        if (!root) {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node* stack1[50], *stack2[50];  // Two stacks
        int top1 = -1, top2 = -1;

        stack1[++top1] = root;

        // Traverse the tree
        while (top1 >= 0) {
            Node* temp = stack1[top1--];
            stack2[++top2] = temp;

            // Push left and right children to stack1
            if (temp->left) stack1[++top1] = temp->left;
            if (temp->right) stack1[++top1] = temp->right;
        }

        // Output the post-order traversal
        cout << "Post-order Traversal: ";
        while (top2 >= 0) {
            cout << stack2[top2--]->data << " ";
        }
        cout << endl;
    }

    // Non-recursive In-order Traversal
    void inOrderTraversal() const {
        if (!root) {
            cout << "Tree is empty!" << endl;
            return;
        }

        Node* stack[50];
        int top = -1;
        Node* current = root;

        cout << "In-order Traversal: ";
        while (current != nullptr || top >= 0) {
            // Reach the left most Node of the current Node
            while (current != nullptr) {
                stack[++top] = current;
                current = current->left;
            }

            // Current must be nullptr at this point
            current = stack[top--];
            cout << current->data << " ";

            // Now visit the right subtree
            current = current->right;
        }
        cout << endl;
    }

    // Clear the entire tree
    void clear() {
        clearTree(root);
        root = nullptr;
    }

private:
    // Recursive function to delete the tree (post-order deletion)
    void clearTree(Node* node) {
        if (node == nullptr) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
};

int main() {
    ExpressionTree tree;
    char prefixExpression[50];
    int choice;

    while (true) {
        cout << "\n----------------------------" << endl;
        cout << "Expression Tree Menu" << endl;
        cout << "----------------------------" << endl;
        cout << "1. Build Expression Tree" << endl;
        cout << "2. Post-order Traversal (Non-recursive)" << endl;
        cout << "3. In-order Traversal (Non-recursive)" << endl;
        cout << "4. Clear Tree" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the prefix expression: ";
                cin.ignore(); // Clear input buffer
                cin.getline(prefixExpression, 50);
                tree.buildTree(prefixExpression);
                break;

            case 2:
                tree.postOrderTraversal();
                break;

            case 3:
                tree.inOrderTraversal();
                break;

            case 4:
                tree.clear();
                cout << "Tree cleared successfully!" << endl;
                break;

            case 5:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again!" << endl;
        }
    }

    return 0;
}