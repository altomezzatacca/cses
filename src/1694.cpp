#include "bits/stdc++.h"
using namespace std;
constexpr static long long INF = 1e15;
 
long long bfs(int source, int sink, vector<vector<long long>> &adj, vector<vector<long long>> &C, vector<int> &parent) {
	fill(begin(parent), end(parent), -1);
    queue<pair<long long, long long>> q;
    parent[source] = source;
    q.emplace(source, INF);
    while(!q.empty()){
        auto [u, flow] = q.front(); q.pop();
        for(auto v: adj[u]){
            long long _new = min((long long)C[u][v], flow);
            if(_new > 0 && parent[v] == -1){
                parent[v] = u;
                if(v == sink)
                    return _new;
                q.emplace(v, _new);
            }
        }
    }
    return 0;
}
 
long long maxflow(int source, int sink, vector<vector<long long>> &adj, vector<vector<long long>> &C) {
	long long flow = 0;
	long long _new;
    vector<int> parent((int)adj.size());
    while((_new = bfs(source, sink, adj, C, parent))){
        flow += _new;
        int current = sink;
        while(current != source){
            int prev = parent[current];
            C[prev][current] -= _new;
            C[current][prev] += _new;
            current = prev;
        }
    }
	return flow;
}
 
int main(){
    int N, M; cin >> N >> M;
    vector<vector<long long>> adj(N + 1);
    vector<vector<long long>> C(N + 1, vector<long long> (N + 1, 0));
    for(int i = 0, a, b, w; i < M; i++){
        cin >> a >> b >> w;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
        C[a][b] += w;
    }
    cout << maxflow(1, N, adj, C) << "\n";
}
