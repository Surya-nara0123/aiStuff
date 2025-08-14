#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

unordered_map<string, vector<string>> graph;
int shortestDist = -1;
vector<string> path;
vector<vector<string>> allShortestPaths;

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

int bfsShortestDistance(const string &start, const string &goal) {
    unordered_map<string, int> dist;
    queue<string> q;

    for (auto &p : graph) {
        dist[p.first] = -1;
    }

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        string current = q.front();
        q.pop();

        if (current == goal) {
            return dist[current];
        }

        for (auto &neighbor : graph[current]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                q.push(neighbor);
            }
        }
    }
    return -1; // no path
}

void dfsPaths(const string &current, const string &goal, unordered_map<string, bool> &visited) {
    visited[current] = true;
    path.push_back(current);

    if (current == goal && path.size() - 1 == shortestDist) {
        allShortestPaths.push_back(path);
    } else {
        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor]) {
                dfsPaths(neighbor, goal, visited);
            }
        }
    }

    path.pop_back();
    visited[current] = false;
}

int main() {
    string filename = "graph_unweighted.txt";
    loadGraph(filename);

    string start = "S";
    string goal = "G";

    // Step 1: BFS to get shortest distance
    shortestDist = bfsShortestDistance(start, goal);

    if (shortestDist == -1) {
        cout << "No path found from " << start << " to " << goal << ".\n";
        return 0;
    }

    cout << "Shortest path length: " << shortestDist << "\n";

    // Step 2: DFS to find all shortest paths
    unordered_map<string, bool> visited;
    dfsPaths(start, goal, visited);

    cout << "All shortest paths:\n";
    for (auto &p : allShortestPaths) {
        for (size_t i = 0; i < p.size(); i++) {
            cout << p[i] << (i + 1 < p.size() ? " -> " : "");
        }
        cout << "\n";
    }

    return 0;
}
