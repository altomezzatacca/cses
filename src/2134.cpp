#include "bits/stdc++.h"
using namespace std;
vector<vector<int>> adj;
vector<int> parent, depth, heavy, head, pos;

struct segtree {
    int sz = 1;
    vector<int> v;
    segtree(){}
    segtree(int n, vector<int> a) {
        while (sz < n) sz <<= 1;
        v.resize(2 * sz);
        for (int i = 0; i < n; i++)
            v[i + sz] = a[i];
        for (int i = n; i < sz; i++)
            v[i + sz] = -1;
        for (int i = sz - 1; i > 0; i--)
            v[i] = max(v[2 * i], v[2 * i + 1]);
    }
    inline void update(int ix, int x) {
        ix += sz;
        v[ix] = x;
        while (ix >> 1) {
            ix >>= 1;
            v[ix] = max(v[2 * ix], v[2 * ix + 1]);
        }
    }
    inline int query(int l, int r) {
        int ans = -1;
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(ans, v[l++]);
            if (r & 1) ans = max(ans, v[--r]);
        }
        return ans;
    }
};

segtree seg = segtree();

inline int query_path(int a, int b) {
    int ans = -1;
    while (head[a] != head[b]) {
        if (depth[head[a]] < depth[head[b]])
            swap(a, b);
        ans = max(ans, seg.query(pos[head[a]], pos[a] + 1));
        a = parent[head[a]];
    }
    if (depth[a] > depth[b])
        swap(a, b);
    ans = max(ans, seg.query(pos[a], pos[b] + 1));
    return ans;
}

inline int dfs(int node) {
    int sz = 1;
    int best = 0;
    for (int u: adj[node]) {
        if (u != parent[node]) {
            parent[u] = node;
            depth[u] = depth[node] + 1;
            int sz_u = dfs(u);
            sz += sz_u;
            if (sz_u > best)
                best = sz_u, heavy[node] = u;
        }
    }
    return sz;
}

inline void decompose(int node, int h, int &cur_pos) {
    head[node] = h;
    pos[node] = cur_pos++;
    if (heavy[node] != -1)
        decompose(heavy[node], h, cur_pos);
    for (int u: adj[node])
        if (u != parent[node] && u != heavy[node])
            decompose(u, u, cur_pos);
}

int main() {

    cin.tie(NULL);
    ios_base::sync_with_stdio(0);

    int n, q; cin >> n >> q;
    vector<int> v(n);

    for (auto &u: v) cin >> u;
    adj.resize(n);
    parent.resize(n);
    depth.resize(n);
    heavy.assign(n, -1);
    head.resize(n);
    pos.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }

    dfs(0);
    int cur_pos = 0;
    decompose(0, 0, cur_pos);
    vector<int> tmp(n);
    for (int i = 0; i < n; i++)
        tmp[pos[i]] = v[i];
    seg = segtree(n, tmp);

    for (int i = 0; i < q; i++) {
        int c; cin >> c;
        if (c == 1) {
            int s, x; cin >> s >> x;
            s--;
            seg.update(pos[s], x);
        } else {
            int a, b; cin >> a >> b;
            a--, b--;
            cout << query_path(a, b) << " ";
        }
    }
    cout << "\n";
}
