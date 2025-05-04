#include <iostream>
#include <vector>
#include <string>
using namespace std;

class TreeNode {
public:
    string name;
    vector<TreeNode*> children;

    TreeNode(string name) {
        this->name = name;
    }

    void addChild(TreeNode* child) {
        children.push_back(child);
    }

    void printTree(int level = 0) {
        for (int i = 0; i < level; i++) cout << "\t";
        cout << name << endl;
        for (TreeNode* child : children) {
            child->printTree(level + 1);
        }
    }
};

int main() {
    TreeNode* book = new TreeNode("Book");

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;

    for (int i = 0; i < numChapters; i++) {
        string chapName;
        cout << "Enter name of chapter " << i + 1 << ": ";
        cin.ignore();
        getline(cin, chapName);
        TreeNode* chapter = new TreeNode(chapName);

        int numSections;
        cout << "Enter number of sections in " << chapName << ": ";
        cin >> numSections;

        for (int j = 0; j < numSections; j++) {
            string secName;
            cout << "Enter name of section " << j + 1 << ": ";
            cin.ignore();
            getline(cin, secName);
            TreeNode* section = new TreeNode(secName);

            int numSubsections;
            cout << "Enter number of subsections in " << secName << ": ";
            cin >> numSubsections;

            for (int k = 0; k < numSubsections; k++) {
                string subsecName;
                cout << "Enter name of subsection " << k + 1 << ": ";
                cin.ignore();
                getline(cin, subsecName);
                TreeNode* subsection = new TreeNode(subsecName);
                section->addChild(subsection);
            }

            chapter->addChild(section);
        }

        book->addChild(chapter);
    }

    cout << "\nTree Structure of Book:\n";
    book->printTree();

    return 0;
}
