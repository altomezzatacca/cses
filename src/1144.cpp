#include "bits/stdc++.h"
using namespace std;
 
struct SegTree{
    int sz; vector<int> tree;
    SegTree(vector<int> &V){
        int N = size(V);
        sz = 1;
        while(sz < N) sz *= 2;
        tree.resize(2 * sz);
        for(int i = 0; i < N; i++) tree[sz + i] = V[i];
        for(int i = N; i < sz; i++) tree[sz + i] = 0;
        for(int i = sz - 1; i >= 1; i--) tree[i] = tree[2 * i] + tree[2 * i + 1];
    }
    int query(int node, int nl, int nr, int ql, int qr){
        if(qr <= nl || nr <= ql) return 0;
        if(ql <= nl && nr <= qr) return tree[node];
        int nm = (nr + nl) / 2;
        return query(2 * node,     nl, nm, ql, qr) +
               query(2 * node + 1, nm, nr, ql, qr);
    }
    void update(int node, int nl, int nr, int ix){
        if(ix < nl || nr <= ix) return;
        if(nr - nl == 1) return;
        int nm = (nl + nr) / 2;
        update(2 * node,     nl, nm, ix);
        update(2 * node + 1, nm, nr, ix);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
};
 
int main(){
    int N, Q; cin >> N >> Q;
    vector<int> V (N);
    for(auto &u: V) cin >> u;
    vector<tuple<char, int, int>> query(Q);
    vector<int> sorted(begin(V), end(V));
    for(auto &[q, a, b] : query){
        cin >> q >> a >> b;
        if(q == '!') sorted.push_back(b);
    }
    sort(begin(sorted), end(sorted));
    vector<int> mapping;
    mapping.push_back(sorted[0]);
    vector<int> frequences (1, 0);
    for(int i = 1; i < (int)sorted.size(); i++){
        if(sorted[i] != mapping.back()){
            mapping.push_back(sorted[i]);
            frequences.push_back(0);
        }
    }
    for(auto u: V)
        frequences[lower_bound(begin(mapping), end(mapping), u) - mapping.begin()]++;
    assert(size(frequences) == size(mapping));
    SegTree st(frequences);
    for(auto [q, a, b] : query){
        if(q == '!'){
            int k = lower_bound(begin(mapping), end(mapping), V[a - 1]) - mapping.begin();
            int x = lower_bound(begin(mapping), end(mapping), b) - mapping.begin();
            st.tree[st.sz + k]--;
            st.update(1, 0, st.sz, k);
            st.tree[st.sz + x]++;
            st.update(1, 0, st.sz, x);
            V[a - 1] = b;
        } else {
            a = lower_bound(begin(mapping), end(mapping), a) - mapping.begin();
            b = upper_bound(begin(mapping), end(mapping), b) - mapping.begin();
            cout << st.query(1, 0, st.sz, a, b) << "\n";
        }
    }
}
