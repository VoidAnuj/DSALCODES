#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// Tree node structure
struct TreeNode {
    char data;
    TreeNode *left, *right;

    TreeNode(char val) {
        data = val;
        left = right = nullptr;
    }
};

// Function to check if character is operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Construct expression tree from prefix
TreeNode* constructTreeFromPrefix(string prefix) {
    stack<TreeNode*> st;

    // Scan from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char ch = prefix[i];

        TreeNode* node = new TreeNode(ch);

        if (isOperator(ch)) {
            // Pop two operands
            TreeNode* left = st.top(); st.pop();
            TreeNode* right = st.top(); st.pop();
            node->left = left;
            node->right = right;
        }
        // Push the new node
        st.push(node);
    }

    // Final node is root
    return st.top();
}

// Non-recursive postorder traversal using two stacks
void postOrderNonRecursive(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        TreeNode* node = s1.top(); s1.pop();
        s2.push(node);

        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }

    cout << "Postorder Traversal: ";
    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
    cout << endl;
}

// Function to delete tree using postorder
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    string prefix;
    cout << "Enter prefix expression: ";
    cin >> prefix;

    TreeNode* root = constructTreeFromPrefix(prefix);

    postOrderNonRecursive(root);

    deleteTree(root);
    cout << "Tree deleted successfully.\n";

    return 0;
}
