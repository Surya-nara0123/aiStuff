#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string>> graph;
unordered_map<string, bool> visited;
vector<string> path;
vector<string> history; // stores the full traversal history
bool goalFound = false;

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

void dfs(const string &current, const string &goal) {
    if (goalFound) return;

    visited[current] = true;
    path.push_back(current);
    history.push_back(current); // record visiting this node

    if (current == goal) {
        cout << "Goal found!\nPath to goal: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
        goalFound = true;
    } else {
        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor]) {
                dfs(neighbor, goal);
                history.push_back(current); // record backtracking step
            }
        }
    }

    path.pop_back();
    visited[current] = false; // so we can see backtracking clearly in history
}

int main() {
    string filename = "graph_unweighted.txt";
    loadGraph(filename);

    string start = "S";
    string goal = "G";

    dfs(start, goal);

    cout << "\nDFS traversal history:\n";
    for (size_t i = 0; i < history.size(); i++) {
        cout << history[i] << (i + 1 < history.size() ? " -> " : "");
    }
    cout << "\n";

    return 0;
}
