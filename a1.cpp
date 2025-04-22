// Code by Anuj Gholve

#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 10;

int hashFunction(string key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash + c) % TABLE_SIZE;
    }
    return hash;
}

class HashTableChaining {
    list<pair<string, string>>* table;
public:
    HashTableChaining() {
        table = new list<pair<string, string>>[TABLE_SIZE];
    }

    void insert(string name, string phone) {
        int index = hashFunction(name);
        table[index].push_back({name, phone});
    }

    string search(string name, int &comparisons) {
        int index = hashFunction(name);
        comparisons = 0;
        for (auto& entry : table[index]) {
            comparisons++;
            if (entry.first == name) {
                return entry.second;
            }
        }
        return "Not found";
    }

    ~HashTableChaining() {
        delete[] table;
    }
};

class HashTableLinearProbing {
    vector<pair<string, string>> table;
public:
    HashTableLinearProbing() {
        table.resize(TABLE_SIZE, {"", ""});
    }

    void insert(string name, string phone) {
        int index = hashFunction(name);
        int originalIndex = index;
        while (table[index].first != "" && table[index].first != name) {
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                cout << "Hash table is full!" << endl;
                return;
            }
        }
        table[index] = {name, phone};
    }

    string search(string name, int &comparisons) {
        int index = hashFunction(name);
        int originalIndex = index;
        comparisons = 0;
        while (table[index].first != "" && table[index].first != name) {
            comparisons++;
            index = (index + 1) % TABLE_SIZE;
            if (index == originalIndex) {
                return "Not found";
            }
        }
        comparisons++;
        return table[index].second;
    }
};

void interactWithUser() {
    int choice;
    HashTableChaining* hashTableChaining = nullptr;
    HashTableLinearProbing* hashTableLinearProbing = nullptr;

    do {
        cout << "Choose collision resolution method: \n";
        cout << "1. Chaining\n";
        cout << "2. Linear Probing\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            hashTableChaining = new HashTableChaining();
        } else if (choice == 2) {
            hashTableLinearProbing = new HashTableLinearProbing();
        } else if (choice == 3) {
            cout << "\nExiting...\n";
            return;
        } else {
            cout << "Invalid choice! Please try again.\n";
            continue;
        }

        int insertChoice;
        do {
            string name, phone;
            cout << "Enter client name: ";
            getline(cin, name);
            cout << "Enter phone number for " << name << ": ";
            getline(cin, phone);

            if (choice == 1) {
                hashTableChaining->insert(name, phone);
            } else {
                hashTableLinearProbing->insert(name, phone);
            }

            cout << "Do you want to add another client? (1 for Yes, 0 for No): ";
            cin >> insertChoice;
            cin.ignore();
        } while (insertChoice == 1);

        string searchName;
        int comparisons = 0;
        cout << "Enter the name of the client you want to search: ";
        getline(cin, searchName);

        string result;
        if (choice == 1) {
            result = hashTableChaining->search(searchName, comparisons);
        } else {
            result = hashTableLinearProbing->search(searchName, comparisons);
        }

        if (result != "Not found") {
            cout << "Phone number for " << searchName << ": " << result << endl;
        } else {
            cout << searchName << " not found!" << endl;
        }

        cout << "Number of comparisons: " << comparisons << endl;

        if (choice == 1) {
            delete hashTableChaining;
        } else {
            delete hashTableLinearProbing;
        }

    } while (choice != 3);
}

int main() {
    interactWithUser();
    return 0;
}
