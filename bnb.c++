#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

unordered_map<string, vector<pair<string,int>>> graph;

struct PathNode {
    vector<string> path;
    int cost;
    bool operator>(const PathNode &other) const {
        return cost > other.cost;
    }
};

void loadGraph(const string &filename) {
    ifstream infile(filename);
    int numNodes, numEdges;
    infile >> numNodes >> numEdges;

    for (int i = 0; i < numEdges; i++) {
        string u,v; int w;
        infile >> u >> v >> w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    infile.close();
}

void branchAndBoundWithCost(const string &start,const string &goal){
    priority_queue<PathNode,vector<PathNode>,greater<PathNode>> pq;
    pq.push({{start},0});

    while(!pq.empty()){
        auto current = pq.top(); pq.pop();
        string node = current.path.back();
        cout<<"Expanding path (cost="<<current.cost<<"): ";
        for(auto &n: current.path) cout<<n<<" ";
        cout<<"\n";

        if(node==goal){
            cout<<"Goal found! Path cost="<<current.cost<<"\nPath: ";
            for(size_t i=0;i<current.path.size();i++)
                cout<<current.path[i]<<(i+1<current.path.size()?" -> ":"");
            cout<<"\n";
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
    branchAndBoundWithCost("S","G");
    return 0;
}
