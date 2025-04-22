#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {
    string key;
    string meaning;
    TreeNode* left;
    TreeNode* right;
    int height;
    TreeNode(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    void updateHeight(TreeNode* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    int getBalanceFactor(TreeNode* node) {
        return height(node->left) - height(node->right);
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    TreeNode* rebalance(TreeNode* node) {
        updateHeight(node);
        int balance = getBalanceFactor(node);
        
        if (balance > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
            }
            return rightRotate(node);
        }

        if (balance < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
            }
            return leftRotate(node);
        }
        return node;
    }

    TreeNode* insert(TreeNode* node, const string& key, const string& meaning) {
        if (!node) return new TreeNode(key, meaning);
        if (key < node->key) {
            node->left = insert(node->left, key, meaning);
        } else if (key > node->key) {
            node->right = insert(node->right, key, meaning);
        } else {
            node->meaning = meaning;
            return node;
        }
        return rebalance(node);
    }

    TreeNode* getMinNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    TreeNode* deleteNode(TreeNode* root, const string& key) {
        if (!root) return root;
        if (key < root->key) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNode(root->right, key);
        } else {
            if (!root->left || !root->right) {
                TreeNode* temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            } else {
                TreeNode* temp = getMinNode(root->right);
                root->key = temp->key;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        return rebalance(root);
    }

    void inorder(TreeNode* node) {
        if (node) {
            inorder(node->left);
            cout << node->key << " : " << node->meaning << endl;
            inorder(node->right);
        }
    }

    void reverseInorder(TreeNode* node) {
        if (node) {
            reverseInorder(node->right);
            cout << node->key << " : " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const string& key, const string& meaning) {
        root = insert(root, key, meaning);
    }

    void deleteKeyword(const string& key) {
        root = deleteNode(root, key);
    }

    void updateMeaning(const string& key, const string& newMeaning) {
        root = insert(root, key, newMeaning);
    }

    void displayAscending() {
        inorder(root);
    }

    void displayDescending() {
        reverseInorder(root);
    }

    int findMaxComparisons() {
        return height(root);
    }

    string search(const string& key) {
        TreeNode* current = root;
        while (current) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return current->meaning;
            }
        }
        return "Keyword not found";
    }
};

int main() {
    AVLTree dictionary;
    string key, meaning, newMeaning;
    int choice;

    while (true) {
        cout << "\nDictionary Menu:\n";
        cout << "1. Insert a new keyword\n";
        cout << "2. Delete a keyword\n";
        cout << "3. Update meaning of a keyword\n";
        cout << "4. Search for a keyword\n";
        cout << "5. Display dictionary (Ascending Order)\n";
        cout << "6. Display dictionary (Descending Order)\n";
        cout << "7. Find maximum comparisons needed for lookup\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.insert(key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                dictionary.deleteKeyword(key);
                break;
            case 3:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, newMeaning);
                dictionary.updateMeaning(key, newMeaning);
                break;
            case 4:
                cout << "Enter keyword to search: ";
                getline(cin, key);
                cout << "Meaning: " << dictionary.search(key) << endl;
                break;
            case 5:
                cout << "Dictionary in Ascending Order:\n";
                dictionary.displayAscending();
                break;
            case 6:
                cout << "Dictionary in Descending Order:\n";
                dictionary.displayDescending();
                break;
            case 7:
                cout << "Maximum comparisons needed for lookup: " << dictionary.findMaxComparisons() << endl;
                break;
            case 8:
                cout << "Exiting the program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
