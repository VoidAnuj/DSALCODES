#include <iostream>
#include <string.h>
using namespace std;

struct node {
    int data, prior;
    char pnm[10], name[10];
    struct node* next;
} *front, *rear;

class Queue {
public:
    int isempty();
    void pq_insert(int prior, char name[10]);
    void display();
    void p_delete();
};

int Queue::isempty() {
    if (front == NULL) {
        return 1;
    }
    return 0;
}

struct node* createnode(int prior, char name[10]) {
    struct node* temp;
    temp = new node;
    strcpy(temp->pnm, name);
    temp->prior = prior;
    temp->next = NULL;
    return temp;
}

void Queue::pq_insert(int prior, char name[10]) {
    struct node* temp;
    temp = createnode(prior, name);
    if (isempty()) {
        front = rear = temp;
    } else if (front->prior > temp->prior) {
        temp->next = front;
        front = temp;
    } else {
        rear = front;
        while (rear->next != NULL && temp->prior >= rear->next->prior) {
            rear = rear->next;
        }
        temp->next = rear->next;
        rear->next = temp;
    }
}

void Queue::display() {
    struct node* temp;
    cout << "Priority \t Name \t\t Patient Name" << endl;
    for (temp = front; temp != NULL; temp = temp->next) {
        if (temp->prior == 1)
            cout << temp->prior << "\t\t Serious \t\t" << temp->pnm << endl;
        if (temp->prior == 2)
            cout << temp->prior << "\t\t Medium \t\t" << temp->pnm << endl;
        if (temp->prior == 3)
            cout << temp->prior << "\t\t Normal \t\t" << temp->pnm << endl;
    }
}

void Queue::p_delete() {
    struct node* temp;
    temp = front;
    front = front->next;
    temp->next = NULL;
    cout << "\n" << temp->pnm << " patient checked successfully\n" << endl;
    delete temp;
    display();
}

int main() {
    int priority, i, ch, n, ans;
    char name[10];
    Queue q;
    do {
        cout << "\nHospital History";
        cout << "\n1. Enter the record you want";
        cout << "\n2. Display";
        cout << "\n3. Delete";
        cout << "\nEnter your choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "\n1. Serious";
                cout << "\n2. Medium";
                cout << "\n3. Normal";
                cout << "\nEnter number of patients: ";
                cin >> n;
                for (i = 0; i < n; i++) {
                    cout << "\nEnter severity: ";
                    cin >> priority;
                    cout << "\nEnter patient name: ";
                    cin >> name;
                    q.pq_insert(priority, name);
                }
                break;

            case 2:
                q.display();
                break;

            case 3:
                q.p_delete();
                break;

            case 4:
                cout << "\nWrong choice!";
                break;
        }

        cout << "\nDo you want to continue? (1 for Yes, 0 for No): ";
        cin >> ans;
    } while (ans == 1);

    return 0;
}
