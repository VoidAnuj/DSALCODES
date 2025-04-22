#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

Node* constructTree(vector<vector<int>>& root, vector<int>& keys, int i, int j) {
    if (i > j) return nullptr;
    int r = root[i][j]; 
    Node* node = new Node(keys[r]); 

    node->left = constructTree(root, keys, i, r - 1);
    node->right = constructTree(root, keys, r + 1, j);

    return node;
}

Node* optimalBST(vector<int>& keys, vector<int>& freq, int n) {
    vector<vector<int>> cost(n, vector<int>(n, 0));
    vector<vector<int>> root(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        cost[i][i] = freq[i];
        root[i][i] = i;
    }

    for (int L = 2; L <= n; L++) {
        for (int i = 0; i <= n - L; i++) {
            int j = i + L - 1;
            cost[i][j] = INT_MAX;
            int freqSum = 0;

            for (int k = i; k <= j; k++) freqSum += freq[k];

            for (int r = i; r <= j; r++) {
                int leftCost = (r > i) ? cost[i][r - 1] : 0;
                int rightCost = (r < j) ? cost[r + 1][j] : 0;
                int totalCost = leftCost + rightCost + freqSum;

                if (totalCost < cost[i][j]) {
                    cost[i][j] = totalCost;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "Optimal BST Cost: " << cost[0][n - 1] << endl;
    return constructTree(root, keys, 0, n - 1);
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void printTree(Node* root, int space = 0, int height = 10) {
    if (!root) return;
    space += height;
    printTree(root->right, space);
    cout << endl;
    for (int i = height; i < space; i++) cout << " ";
    cout << root->key << endl;
    printTree(root->left, space);
}

int main() {
    vector<int> keys = {10, 20, 30};      
    vector<int> freq = {3, 2, 4};          
    int n = keys.size();

    Node* root = optimalBST(keys, freq, n);

    cout << "\nInorder Traversal of the Optimal BST: ";
    inorder(root);
    cout << "\n\nTree Structure:\n";
    printTree(root);

    return 0;
}
