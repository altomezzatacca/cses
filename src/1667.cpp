#include "bits/stdc++.h"
using namespace std;
 
int main(){
    int N, M; cin >> N >> M;
    vector<vector<int>> adj(N);
    for(int i = 0; i < M; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> dist(N, 2e9);
    vector<int> parent(N, -1);
    dist[0] = 1;
    queue<int> q; q.push(0);
    while(!q.empty()){
        int node = q.front(); q.pop();
        for(auto u: adj[node]){
            if(dist[u] != 2e9) continue;
            parent[u] = node;
            dist[u] = dist[node] + 1;
            q.push(u);
        }
    }
    int d = dist[N - 1];
    if(d == 2e9) cout << "IMPOSSIBLE";
    else {
        cout << d << "\n";
        int node = N - 1;
        vector<int> seq;
        while(parent[node] != -1){
            seq.push_back(node + 1);
            node = parent[node];
        }
        seq.push_back(1);
        reverse(begin(seq), end(seq));
        for(auto u: seq) cout << u << " ";
    }
}
