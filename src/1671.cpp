#include "bits/stdc++.h"
using namespace std;
using ll = long long;
 
int main(){
    ll N, M; cin >> N >> M;
    vector<vector<pair<ll, ll>>> adj(N);
    for(int i = 0; i < M; i++){
        ll a, b, w; cin >> a >> b >> w; a--; b--;
        adj[a].push_back({w, b});
    }
    vector<bool> visited (N);
    vector<ll> dist(N, -1);
    dist[0] = 0;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, 0});
    while(!pq.empty()){
        auto [d, node] = pq.top(); pq.pop();
        if(visited[node]) continue;
        visited[node] = 1;
        for (auto [w, u] : adj[node])
        if (dist[u] > dist[node] + w || dist[u] == -1)
            pq.push({dist[u] = dist[node] + w, u});
    }
    for(auto u: dist) cout << u << " ";
}
