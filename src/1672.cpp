#include "bits/stdc++.h"
using namespace std;
using ll = long long;
 
int main(){
    ll N, M, Q; cin >> N >> M >> Q;
    vector<vector<ll>> adj(N, vector<ll> (N, 1e15));
    for(int i = 0; i < M; i++){
        ll a, b, c; cin >> a >> b >> c; a--; b--;
        adj[a][b] = min(adj[a][b], c);
        adj[b][a] = min(adj[b][a], c);
    }
    for(int i = 0; i < N; i++)
        adj[i][i] = 0;
    for(int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    for(int i = 0; i < Q; i++){
        int a, b; cin >> a >> b; a--; b--;
        cout << (adj[a][b] == 1e15 ? -1 : adj[a][b]) << "\n";
    }
}
