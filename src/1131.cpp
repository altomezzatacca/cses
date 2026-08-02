#include "bits/stdc++.h"
using namespace std;
 
void dfs(int node, int parent, vector<int> &dist, vector<vector<int>> &adj){
    for(auto u: adj[node]){
        if(u != parent){
            dist[u] = dist[node] + 1;
            dfs(u, node, dist, adj);
        }
    }
}
 
int main(){
    int N; cin >> N;
    vector<vector<int>> adj (N);
    for(int i = 0; i < N - 1; i++){
        int a, b; cin >> a >> b; a--; b--;
        adj[a].push_back(b); adj[b].push_back(a);
    }
    vector<int> dist1 (N), dist2 (N);
    dfs(0, -1, dist1, adj);
    int far = 0;
    for(int i = 1; i < N; i++)
        if(dist1[i] > dist1[far]) far = i;
    dfs(far, -1, dist2, adj);
    for(int i = 0; i < N; i++)
        if(dist2[i] > dist2[far]) far = i;
    cout << dist2[far] << "\n";
    return 0;
}
