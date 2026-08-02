#include "bits/stdc++.h"
using namespace std;
using ll = long long;
 
void dfs(int node, vector<bool> &visited, vector<vector<ll>> &adj){
    for(auto u: adj[node])
        if(!visited[u]){
            visited[u] = 1;
            dfs(u, visited, adj);
        }
    return;
}
 
int main(){
    ll N, M; cin >> N >> M;
    vector<vector<ll>> adj2(N);
    vector<vector<ll>> inverse_adj(N);
    vector<tuple<ll, ll, ll>> adj(M);
    for(int i = 0; i < M; i++){
        ll a, b, c; cin >> a >> b >> c; a--; b--;
        adj[i] = {a, b, c};
        adj2[a].push_back(b);
        inverse_adj[b].push_back(a);
    }
    vector<ll> dist (N, -1e15);
    dist[0] = 0;
    for(int i = 0; i < N - 1; i++)
        for(auto [a, b, w]: adj)
            dist[b] = max(dist[b], dist[a] + w);
    vector<ll> prev = dist;
    for(int i = 0; i < N; i++)
        for(auto [a, b, w]: adj)
            dist[b] = max(dist[b], dist[a] + w);
    vector<bool> reach_from_N(N);
    reach_from_N[N - 1] = 1;
    dfs(N - 1, reach_from_N, inverse_adj);
    vector<bool> reach_from_0(N);
    reach_from_0[0] = 1;
    dfs(0, reach_from_0, adj2);
    bool b = 1;
    for(int i = 0; i < N && b; i++)
        if(reach_from_N[i] && reach_from_0[i])
            if(dist[i] != prev[i]) b = 0;
    cout << (b == 1 ? dist[N - 1] : -1);
    return 0;
}
