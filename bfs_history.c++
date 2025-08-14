#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

unordered_map<string, vector<string>> graph;
vector<string> history; // order of node visits

void loadGraph(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    int numNodes, numEdges;
    infile >> numNodes >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        string u, v;
        infile >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // undirected
    }
    infile.close();

    // Sort adjacency lists for lexicographic order
    for (auto &pair : graph) {
        sort(pair.second.begin(), pair.second.end());
    }
}

void bfs(const string &start, const string &goal) {
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;
    queue<string> q;

    visited[start] = true;
    q.push(start);

    bool goalFound = false;

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        history.push_back(current); // record visit

        if (current == goal) {
            goalFound = true;
            break; // stop BFS when goal is found
        }

        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    if (goalFound) {
        // reconstruct path
        vector<string> path;
        string node = goal;
        while (!node.empty()) {
            path.push_back(node);
            if (parent.find(node) == parent.end()) break;
            node = parent[node];
        }
        reverse(path.begin(), path.end());

        cout << "Path to goal: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
    } else {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }
}

int main() {
    string filename = "graph_unweighted.txt";
    loadGraph(filename);

    string start = "S";
    string goal = "G";

    bfs(start, goal);

    cout << "\nBFS traversal history:\n";
    for (size_t i = 0; i < history.size(); i++) {
        cout << history[i] << (i + 1 < history.size() ? " -> " : "");
    }
    cout << "\n";

    return 0;
}
