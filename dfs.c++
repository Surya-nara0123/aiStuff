#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

unordered_map<string, vector<string>> graph;
vector<string> path;
unordered_map<string, bool> visited;
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
    if (goalFound) return; // stop if goal already found

    visited[current] = true;
    cout << current << " -> ";
    path.push_back(current);

    if (current == goal) {
        // Found the goal → print path
        cout << "Goal found\nPath found: ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i] << (i + 1 < path.size() ? " -> " : "");
        }
        cout << "\n";
        goalFound = true;
    } else {
        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor]) {
                dfs(neighbor, goal);
                cout << current << " -> ";
            }
        }
    }

    path.pop_back(); // backtrack
    visited[current] = false;
}

int main() {
    string filename = "graph_unweighted.txt";
    loadGraph(filename);

    string start = "S";
    string goal = "G";

    dfs(start, goal);

    if (!goalFound) {
        cout << "No path found from " << start << " to " << goal << ".\n";
    }

    return 0;
}
