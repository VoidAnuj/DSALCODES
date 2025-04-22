// Code by Anuj Gholve

#include <iostream>
#include <cstring>
using namespace std;

class Node {
public:
    string name;
    Node *firstChild;
    Node *sibling;

    Node(string s) {
        name = s;
        firstChild = NULL;
        sibling = NULL;
    }

    void create(Node *root, Node *child) {
        if (root == NULL) {
            root = child;
        } else {
            if (root->firstChild == NULL) {
                root->firstChild = child;
            } else {
                Node *sib = root->firstChild;
                while (sib->sibling != NULL) {
                    sib = sib->sibling;
                }
                sib->sibling = child;
            }
        }
    }

    void print(Node *root, int level = 0) {
        if (root == NULL) return;

        for (int i = 0; i < level; i++) {
            cout << "  ";
        }
        cout << root->name << endl;

        print(root->firstChild, level + 1);
        print(root->sibling, level);
    }

    void addChapter(Node *root) {
        string chapterName;
        cout << "Enter Chapter Name: ";
        getline(cin, chapterName);
        Node *chapter = new Node(chapterName);
        create(root, chapter);

        int sectionChoice;
        cout << "Do you want to add Sections to this Chapter? (1 for Yes, 0 for No): ";
        cin >> sectionChoice;
        cin.ignore();

        if (sectionChoice == 1) {
            addSection(chapter);
        }
    }

    void addSection(Node *root) {
        string sectionName;
        cout << "Enter Section Name: ";
        getline(cin, sectionName);
        Node *section = new Node(sectionName);
        create(root, section);

        int subsectionChoice;
        cout << "Do you want to add Subsections to this Section? (1 for Yes, 0 for No): ";
        cin >> subsectionChoice;
        cin.ignore();

        if (subsectionChoice == 1) {
            addSubsection(section);
        }
    }

    void addSubsection(Node *root) {
        string subsectionName;
        cout << "Enter Subsection Name: ";
        getline(cin, subsectionName);
        Node *subsection = new Node(subsectionName);
        create(root, subsection);

        int moreSubsections;
        cout << "Do you want to add more Subsections to this Section? (1 for Yes, 0 for No): ";
        cin >> moreSubsections;
        cin.ignore();

        if (moreSubsections == 1) {
            addSubsection(root);  // Recursive call to allow multiple subsections
        }
    }
};

int main() {
    Node *book = new Node("Book Structure:");

    int chapterChoice;
    do {
        book->addChapter(book);
        cout << "Do you want to add another Chapter? (1 for Yes, 0 for No): ";
        cin >> chapterChoice;
        cin.ignore();
    } while (chapterChoice == 1);

    cout << "\nFinal Book Structure:\n";
    book->print(book);

    return 0;
}
