#include "bits/stdc++.h"
using namespace std;
vector<int> cycle;
 
void dfs(int node, vector<int> &state, vector<vector<int>> &adj, int &last, vector<int> &parent){
    state[node] = 1;
    for(auto u: adj[node]){
        if(state[u] == 2) continue;
        if(state[u] == 0) {
            parent[u] = node;
            dfs(u, state, adj, last, parent);
        }
        if(u != parent[node] && state[u] == 1 && last == -1) {
            cycle.push_back(node);
            last = u;
        }
    }
    state[node] = 2;
    return;
}
 
int main(){
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> state (N); //0: unvisited, 1: in elaborazione, 2: visited
    vector<int> parent (N, -1);
    for(int i = 0; i < N && cycle.empty(); i++){
        int last = -1;
        if(state[i] == 0) dfs(i, state, adj, last, parent);
        if(!cycle.empty()){
            int current = cycle[0];
            while(current != last){
                current = parent[current];
                cycle.push_back(current);
            }
            reverse(cycle.begin(), cycle.end());
            cycle.push_back(cycle[0]);
            cout << (int)cycle.size() << "\n";
            for(auto u: cycle) cout << u + 1 << " ";
        }
    }
    if(cycle.empty()) cout << "IMPOSSIBLE";
}
