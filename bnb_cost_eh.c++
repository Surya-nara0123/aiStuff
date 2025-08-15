#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

unordered_map<string, vector<pair<string,int>>> graph;
unordered_map<string,int> heuristic;

struct HeuristicNode {
    vector<string> path;
    int g,h;
    bool operator>(const HeuristicNode &other) const {
        return (g+h) > (other.g+other.h);
    }
};

void loadGraphWithHeuristic(const string &filename){
    ifstream infile(filename);
    int numNodes,numEdges; infile>>numNodes>>numEdges;
    for(int i=0;i<numEdges;i++){
        string u,v;int w; infile>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    for(int i=0;i<numNodes;i++){
        string node; int h; infile>>node>>h;
        heuristic[node]=h;
    }
    infile.close();
}

void branchAndBoundHeuristic(const string &start,const string &goal){
    priority_queue<HeuristicNode,vector<HeuristicNode>,greater<HeuristicNode>> pq;
    pq.push({{start},0,heuristic[start]});

    while(!pq.empty()){
        auto current = pq.top(); pq.pop();
        string node=current.path.back();
        cout<<"Expanding (g="<<current.g<<", h="<<current.h<<") ";
        for(auto &n: current.path) cout<<n<<" ";
        cout<<"\n";

        if(node==goal){
            cout<<"Goal found! Cost="<<current.g<<"\nPath: ";
            for(size_t i=0;i<current.path.size();i++)
                cout<<current.path[i]<<(i+1<current.path.size()?" -> ":"");
            cout<<"\n"; return;
        }

        for(auto &neighbor: graph[node]){
            auto newPath=current.path;
            newPath.push_back(neighbor.first);
            pq.push({newPath,current.g+neighbor.second,heuristic[neighbor.first]});
        }
    }
    cout<<"No path found.\n";
}

int main(){
    loadGraphWithHeuristic("graph_weighted.txt");
    branchAndBoundHeuristic("S","G");
    return 0;
}
