#include "bits/stdc++.h"
using namespace std;

struct Node
{
    string label;
    int n;
    struct Node *child[10];
} *root;

class GT
{
public:
    GT() {
        root = NULL;
    }
    void createTree()
    {
        root = new Node;
        cout << "Enter the name of the book :";
        getline(cin, root->label);

        cout << "Enter the number of chapters :";
        cin >> root->n;
        cin.ignore();

        for(int i = 0; i < root->n; i++) {
            root->child[i] = new Node;
            cout << "Enter the name of chapter " << i + 1 << " : ";
            getline(cin, root->child[i]->label);

            cout << "Enter the number of sections :";
            cin >> root->child[i]->n;
            cin.ignore();

            for(int j = 0; j < root->child[i]->n; j++)  {
                root->child[i]->child[j] = new Node;
                cout << " Enter the name of section " << j + 1 << " : ";
                getline(cin, root->child[i]->child[j]->label);

                cout << "Enter the number of subsections: ";
                cin >> root->child[i]->child[j]->n;
                cin.ignore();

                for(int k = 0; k < root->child[i]->child[j]->n; k++) {
                    root->child[i]->child[j]->child[k] = new Node;
                    cout << "Enter the name of the subsection " << k + 1 << ":";
                    getline(cin,root->child[i]->child[j]->child[k]->label);
                }
            }
        }
    }


    void display(struct Node*root) {
        if(root) {
            cout << "BOOK Name -> " << root->label << endl;
            for(int i = 0; i < root->n; i++) {
                cout << "\tChapter -> " << root->child[i]->label << endl;

                for(int j = 0; j < root->child[i]->n; j++) {
                    cout << "\t\t Section -> " << root->child[i]->child[j]->label << endl;

                    for(int k = 0; k < root->child[i]->child[j]->n;k++) {
                        cout << "\t\t\tSub-section -> " << root->child[i]->child[j]->child[k]->label << endl;
                    }
                }
            }
        }
    }
};

int main()
{
    int choice;
    GT gt;
    while (1)
    {
        cout << "---------------------" << endl;
        cout << " BOOK TREE CREATION " << endl;
        cout << "----------------------" << endl;
        cout << "1.Create" << endl;
        cout << "2.Display" << endl;
        cout << "3.Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            gt.createTree();
            break;
        case 2:
            gt.display(root);
            break;
        case 3:
            cout << " Thanks for using this program !";
            exit(1);
        default:
            cout << "Wrong Choice !!! " << endl;
        }
    }
    return 0;
}


