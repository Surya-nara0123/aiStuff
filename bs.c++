#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

unordered_map<string, vector<pair<string, int>>> graph;
unordered_map<string, int> heuristic;

void loadWeightedGraphWithHeuristics(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open file " << filename << endl;
        exit(1);
    }

    int numNodes, numEdges;
    infile >> numNodes >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        string u, v;
        int w;
        infile >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    for (int i = 0; i < numNodes; i++) {
        string node;
        int h;
        infile >> node >> h;
        heuristic[node] = h;
    }

    infile.close();

    for (auto &p : graph) {
        sort(p.second.begin(), p.second.end(),
             [](auto &a, auto &b) { return a.first < b.first; });
    }
}

void beamSearch(const string &start, const string &goal, int beamWidth) {
    vector<string> frontier = {start};
    unordered_map<string, bool> visited;
    visited[start] = true;

    cout << "Starting Beam Search from " << start << "\n";

    while (!frontier.empty()) {
        vector<pair<string, int>> candidates;

        // Expand all nodes in frontier
        for (auto &node : frontier) {
            cout << "Expanding: " << node << "\n";
            if (node == goal) {
                cout << "Goal found!\n";
                return;
            }
            for (auto &neighbor : graph[node]) {
                if (!visited[neighbor.first]) {
                    candidates.push_back({neighbor.first, heuristic[neighbor.first]});
                    visited[neighbor.first] = true;
                }
            }
        }

        // Sort by heuristic
        sort(candidates.begin(), candidates.end(),
             [](auto &a, auto &b) {
                 if (a.second == b.second)
                     return a.first < b.first;
                 return a.second < b.second;
             });

        // Select top beamWidth nodes
        frontier.clear();
        for (int i = 0; i < (int)candidates.size() && i < beamWidth; i++) {
            frontier.push_back(candidates[i].first);
        }
    }

    cout << "Goal not found.\n";
}

int main() {
    loadWeightedGraphWithHeuristics("graph_weighted.txt");

    string start = "S";
    string goal = "G";
    int beamWidth = 2; // adjust as needed

    beamSearch(start, goal, beamWidth);

    return 0;
}
