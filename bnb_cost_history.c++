#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

unordered_map<string, vector<pair<string,int>>> graph;

struct PathNode {
    vector<string> path;   // current path
    int cost;              // total path cost
    bool operator>(const PathNode &other) const {
        return cost > other.cost;
    }
};

// Load weighted graph (no heuristic needed here)
void loadGraph(const string &filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Error: Could not open " << filename << "\n";
        exit(1);
    }

    int numNodes, numEdges;
    infile >> numNodes >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        string u,v; int w;
        infile >> u >> v >> w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w}); // undirected
    }
    infile.close();
}

void branchAndBoundWithHistory(const string &start,const string &goal){
    priority_queue<PathNode,vector<PathNode>,greater<PathNode>> pq;
    pq.push({{start},0});

    vector<vector<string>> history; // store all explored paths

    while(!pq.empty()){
        auto current = pq.top(); pq.pop();
        string node = current.path.back();

        // save history
        history.push_back(current.path);

        cout<<"Expanding path (cost="<<current.cost<<"): ";
        for(auto &n: current.path) cout<<n<<" ";
        cout<<"\n";

        if(node==goal){
            cout<<"\n✅ Goal found!\n";
            cout<<"Path cost = "<<current.cost<<"\n";
            cout<<"Final path: ";
            for(size_t i=0;i<current.path.size();i++)
                cout<<current.path[i]<<(i+1<current.path.size()?" -> ":"");
            cout<<"\n";

            // Print history of explored paths
            cout<<"\n📜 History of expansions:\n";
            for(size_t i=0;i<history.size();i++){
                cout<<i+1<<": ";
                for(auto &n: history[i]) cout<<n<<" ";
                cout<<"\n";
            }
            return;
        }

        for(auto &neighbor: graph[node]){
            auto newPath=current.path;
            newPath.push_back(neighbor.first);
            pq.push({newPath,current.cost+neighbor.second});
        }
    }
    cout<<"No path found.\n";
}

int main(){
    loadGraph("graph_weighted.txt");
    branchAndBoundWithHistory("S","G");
    return 0;
}
