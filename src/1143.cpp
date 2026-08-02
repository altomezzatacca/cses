#include "bits/stdc++.h"
using namespace std;
 
struct SegTree {
    int sz; vector<int> tree;
    SegTree(int N, vector<int> &V){
        sz = 1;
        while(sz < N) sz <<= 1;
        tree.resize(2 * sz);
        for(int i = 0; i < N; i++) tree[sz + i] = V[i];
        for(int i = N; i < sz; i++) tree[sz + i] = -1e9; //elemento neutro del massimo
        for(int i = sz - 1; i >= 1; i--) tree[i] = max(tree[2 * i], tree[2 * i + 1]);
    }
    void update(int node, int l, int r, int ix, int val){
        if(ix < l || r <= ix) return;
        if(r - l == 1) return;
        int m = (l + r) / 2;
        update(2 * node,     l, m, ix, val);
        update(2 * node + 1, m, r, ix, val);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }
    int query(int node, int q){
        if(node >= sz && tree[node] >= q) {
            tree[node] -= q;
            update(1, 0, sz, node - sz, q);
            return node;
        }
        else if(tree[2 * node] >= q) return query(2 * node, q);
        else return query(2 * node + 1, q);
    }
};
 
int main(){
    int N, M; cin >> N >> M;
    vector<int> H(N);
    for(auto &u: H) cin >> u;
    SegTree st(N, H);
    for(int i = 0; i < M; i++){
        int q; cin >> q;
        if(q > st.tree[1]) cout << 0 << " ";
        else cout << st.query(1, q) - st.sz + 1 << " ";
    } cout << "\n";
    
    return 0;
}
