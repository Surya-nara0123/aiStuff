#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Graph: node -> list of (neighbor, weight)
unordered_map<string, vector<pair<string, int>>> graph;
// Heuristics: node -> estimated distance to goal
unordered_map<string, int> heuristic;

void loadWeightedGraphWithHeuristics(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    int numNodes, numEdges;
    infile >> numNodes >> numEdges;

    // Read edges
    for (int i = 0; i < numEdges; i++) {
        string u, v;
        int w;
        infile >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // undirected
    }

    // Read heuristics
    for (int i = 0; i < numNodes; i++) {
        string node;
        int h;
        infile >> node >> h;
        heuristic[node] = h;
    }

    infile.close();

    // Sort adjacency lists for lexicographic order (used in ties)
    for (auto &p : graph) {
        sort(p.second.begin(), p.second.end(),
             [](const pair<string, int> &a, const pair<string, int> &b) {
                 return a.first < b.first; // lexicographic order
             });
    }
}

bool hillClimb(const string &start, const string &goal) {
    unordered_map<string, bool> visited;
    string current = start;
    visited[current] = true;

    cout << "Starting at " << current << "\n";

    while (current != goal) {
        string bestNode = "";
        int bestH = numeric_limits<int>::max();

        // Look for neighbor with smallest heuristic
        for (auto &neighbor : graph[current]) {
            if (!visited[neighbor.first]) {
                int hVal = heuristic[neighbor.first];
                if (hVal < bestH || (hVal == bestH && neighbor.first < bestNode)) {
                    bestH = hVal;
                    bestNode = neighbor.first;
                }
            }
        }

        if (bestNode.empty()) {
            cout << "No better move found. Stuck at " << current << "\n";
            return false; // stuck, failure
        }

        cout << "Moving to " << bestNode << " (h=" << bestH << ")\n";
        current = bestNode;
        visited[current] = true;
    }

    cout << "Reached goal " << goal << "\n";
    return true;
}

int main() {
    string filename = "graph_weighted.txt";
    loadWeightedGraphWithHeuristics(filename);

    string start = "S";
    string goal = "G";

    hillClimb(start, goal);

    return 0;
}
