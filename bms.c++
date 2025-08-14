#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

unordered_map<string, vector<string>> graph;
vector<vector<string>> allPaths;

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
        graph[v].push_back(u); // Undirected
    }
    infile.close();
}

void bmsDFS(const string &current, const string &goal, 
            unordered_map<string, bool> &visited, vector<string> &path) {
    visited[current] = true;
    path.push_back(current);

    if (current == goal) {
        // Save this path
        allPaths.push_back(path);
    } else {
        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor]) {
                bmsDFS(neighbor, goal, visited, path);
            }
        }
    }

    // Backtrack
    path.pop_back();
    visited[current] = false;
}

int main() {
    string filename = "graph_unweighted.txt";
    loadGraph(filename);

    // Identify start (S) and goal (G)
    string start = "S";
    string goal = "G";

    unordered_map<string, bool> visited;
    vector<string> path;

    bmsDFS(start, goal, visited, path);

    // Output all found paths
    cout << "All paths from " << start << " to " << goal << ":\n";
    for (const auto &p : allPaths) {
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i] << (i + 1 < p.size() ? " -> " : "");
        }
        cout << "\n";
    }

    cout << "Total paths found: " << allPaths.size() << "\n";

    return 0;
}
