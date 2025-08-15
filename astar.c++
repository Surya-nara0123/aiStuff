#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

unordered_map<string, vector<pair<string,int>>> graph;
unordered_map<string,int> heuristic;

struct State{
    vector<string> path;
    int g,h;
    bool operator>(const State &other) const {
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

void aStar(const string &start,const string &goal){
    priority_queue<State,vector<State>,greater<State>> pq;
    pq.push({{start},0,heuristic[start]});

    unordered_map<string,int> bestG;
    bestG[start]=0;

    while(!pq.empty()){
        auto current=pq.top(); pq.pop();
        string node=current.path.back();

        cout<<"Expanding "<<node<<" (g="<<current.g<<", h="<<current.h<<")\n";

        if(node==goal){
            cout<<"A* found goal! Cost="<<current.g<<"\nPath: ";
            for(size_t i=0;i<current.path.size();i++)
                cout<<current.path[i]<<(i+1<current.path.size()?" -> ":"");
            cout<<"\n"; return;
        }

        for(auto &neighbor: graph[node]){
            int newG=current.g+neighbor.second;
            if(!bestG.count(neighbor.first) || newG<bestG[neighbor.first]){
                bestG[neighbor.first]=newG;
                auto newPath=current.path;
                newPath.push_back(neighbor.first);
                pq.push({newPath,newG,heuristic[neighbor.first]});
            }
        }
    }
    cout<<"No path found.\n";
}

int main(){
    loadGraphWithHeuristic("graph_weighted.txt");
    aStar("S","G");
    return 0;
}
