#include <iostream>
using namespace std;

class Graph {
public:
    int x; // Number of nodes
    int top, f, r;
    int **adjList;
    int data[30], data1[30];
    int visit[20];
    int g[10][10];

    Graph() {
        top = -1;
        f = r = -1;
        adjList = NULL;
    }

    // Stack functions for DFS
    void push(int t) {
        data[++top] = t;
    }

    int pop() {
        return (top != -1) ? data[top--] : -1;
    }

    // Queue functions for BFS
    void enqueue(int t) {
        if (f == -1 && r == -1)
            f = r = 0;
        else
            r++;
        data1[r] = t;
    }

    int dequeue() {
        if (f == -1)
            return -1;
        int val = data1[f];
        if (f == r)
            f = r = -1;
        else
            f++;
        return val;
    }

    void createMatrix() {
        cout << "Number of nodes: ";
        cin >> x;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < x; j++) {
                cout << "Enter link status from node " << i << " to " << j << ": ";
                cin >> g[i][j];
            }
        }
    }

    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n  ";
        for (int i = 0; i < x; i++)
            cout << i << " ";
        cout << "\n";
        for (int i = 0; i < x; i++) {
            cout << i << " ";
            for (int j = 0; j < x; j++)
                cout << g[i][j] << " ";
            cout << "\n";
        }
    }

    void createList() {
        cout << "Number of nodes: ";
        cin >> x;
        adjList = new int*[x];
        for (int i = 0; i < x; ++i) {
            adjList[i] = new int[x]{0};
        }

        for (int i = 0; i < x; i++) {
            int connected, node;
            cout << "\nEnter number of nodes connected to node " << i << ": ";
            cin >> connected;
            cout << "Enter the nodes: ";
            for (int j = 0; j < connected; j++) {
                cin >> node;
                adjList[i][node] = 1;
            }
        }
    }

    void displayList() {
        cout << "\nAdjacency List:";
        for (int i = 0; i < x; i++) {
            cout << "\nNode " << i << " is connected to: ";
            for (int j = 0; j < x; j++) {
                if (adjList[i][j] == 1)
                    cout << j << " ";
            }
        }
        cout << "\n";
    }

    void dfs() {
        for (int i = 0; i < x; i++) visit[i] = 0;
        Graph s;
        int start;
        cout << "Enter starting node for DFS: ";
        cin >> start;
        s.push(start);
        cout << "DFS Traversal: ";
        while (s.top != -1) {
            int v = s.pop();
            if (!visit[v]) {
                cout << v << " ";
                visit[v] = 1;
                for (int i = x - 1; i >= 0; i--) {
                    if (g[v][i] == 1 && !visit[i])
                        s.push(i);
                }
            }
        }
        cout << "\n";
    }

    void bfs() {
        for (int i = 0; i < x; i++) visit[i] = 0;
        Graph s;
        int start;
        cout << "Enter starting node for BFS: ";
        cin >> start;
        s.enqueue(start);
        cout << "BFS Traversal: ";
        while (s.f != -1) {
            int v = s.dequeue();
            if (!visit[v]) {
                cout << v << " ";
                visit[v] = 1;
                for (int i = 0; i < x; i++) {
                    if (adjList[v][i] == 1 && !visit[i])
                        s.enqueue(i);
                }
            }
        }
        cout << "\n";
    }
};

int main() {
    Graph obj;
    int choice;
    while (true) {
        cout << "\n*** MENU ***";
        cout << "\n1. Create Graph (Matrix)";
        cout << "\n2. DFS Traversal (Using Matrix)";
        cout << "\n3. Create Graph (List)";
        cout << "\n4. BFS Traversal (Using List)";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                obj.createMatrix();
                obj.displayMatrix();
                break;
            case 2:
                obj.dfs();
                break;
            case 3:
                obj.createList();
                obj.displayList();
                break;
            case 4:
                obj.bfs();
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
