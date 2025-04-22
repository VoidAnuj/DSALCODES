#include <iostream>
#include <vector>
#include <cstdint>
#define MAX_NUM_CITIES 10
using namespace std;

struct Edge {
    int start, end, weight;
};

class Graph {
    int adj_mat[MAX_NUM_CITIES][MAX_NUM_CITIES];
    string city_names[MAX_NUM_CITIES];
    int city_count;
    Edge mst[MAX_NUM_CITIES - 1];
    int cost;

    void add_to_list(vector<Edge>& list, Edge e);

public:
    Graph();
    void prims_algo(int start);
    void display_mst();
};

Graph::Graph() {
    cost = 0;

    cout << "Number of cities (1-" << MAX_NUM_CITIES << "): ";
    cin >> city_count;
    city_count = (city_count > MAX_NUM_CITIES) ? MAX_NUM_CITIES : city_count;

    for (int i = 0; i < city_count; i++) {
        cout << "Enter name for city " << i << ": ";
        cin >> city_names[i];
    }

    for (int i = 0; i < city_count; i++)
        for (int j = 0; j < city_count; j++)
            adj_mat[i][j] = INT32_MAX;

    int num_pairs;
    cout << "Number of connections: ";
    cin >> num_pairs;

    cout << "\nCity codes:\n";
    for (int i = 0; i < city_count; i++)
        cout << i << " - " << city_names[i] << endl;

    for (int i = 0; i < num_pairs; i++) {
        int x, y, wt;
        cout << "\nEnter connection " << i + 1 << " (city1 city2 cost): ";
        cin >> x >> y >> wt;
        adj_mat[x][y] = adj_mat[y][x] = wt;
    }
}

void Graph::add_to_list(vector<Edge>& list, Edge e) {
    list.push_back(e);
    for (int i = list.size() - 1; i > 0; i--) {
        if (list[i].weight < list[i - 1].weight)
            swap(list[i], list[i - 1]);
        else
            break;
    }
}

void Graph::prims_algo(int start) {
    bool visited[MAX_NUM_CITIES] = {false};
    int visited_count = 1;
    visited[start] = true;

    vector<Edge> adj;
    for (int i = 0; i < city_count; i++) {
        if (adj_mat[start][i] != INT32_MAX) {
            Edge e = {start, i, adj_mat[start][i]};
            add_to_list(adj, e);
        }
    }

    while (visited_count < city_count) {
        Edge min_edge = adj.front();
        adj.erase(adj.begin());

        if (!visited[min_edge.end]) {
            mst[visited_count - 1] = min_edge;
            cost += min_edge.weight;

            for (int i = 0; i < city_count; i++) {
                if (adj_mat[min_edge.end][i] != INT32_MAX && !visited[i]) {
                    Edge e = {min_edge.end, i, adj_mat[min_edge.end][i]};
                    add_to_list(adj, e);
                }
            }

            visited[min_edge.end] = true;
            visited_count++;
        }
    }
}

void Graph::display_mst() {
    cout << "\nMost efficient network (Minimum Spanning Tree):\n";
    for (int i = 0; i < city_count - 1; i++) {
        cout << city_names[mst[i].start] << " -> "
             << city_names[mst[i].end] << " (Cost: " << mst[i].weight << ")\n";
    }
    cout << "\nTotal cost of network: " << cost << endl;
}

int main() {
    Graph g;
    int start;
    cout << "\nEnter starting city code (0-" << MAX_NUM_CITIES - 1 << "): ";
    cin >> start;
    if (start >= MAX_NUM_CITIES) start = 0;
    g.prims_algo(start);
    g.display_mst();
    return 0;
}
