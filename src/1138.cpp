#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct segtree {
    struct node {
        int l, r;
        ll x;
    };
    int sz = 1;
    vector<node> v;
    segtree (int n, vector<ll> a) {
        while (sz < n) sz <<= 1;
        v.resize(2 * sz);
        for (int i = 0; i < n; i++) {
            v[i + sz].x = a[i];
            v[i + sz].l = i;
            v[i + sz].r = i + 1;
        }
        for (int i = n; i < sz; i++) {
            v[i + sz].x = 0;
            v[i + sz].l = i;
            v[i + sz].r = i + 1;
        }
        for (int i = sz - 1; i > 0; i--) {
            v[i].x = v[2 * i].x + v[2 * i + 1].x;
            v[i].l = v[2 * i].l;
            v[i].r = v[2 * i + 1].r;
        }
    }
    void update(int ix, ll x) {
        ix += sz;
        while (ix > 0) {
            v[ix].x += x;
            ix >>= 1;
        }
    }
    ll query(int node, int ql, int qr) {
        int l = v[node].l, r = v[node].r;
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return v[node].x;
        ll ans = 0;
        ans += query(2 * node, ql, qr);
        ans += query(2 * node + 1, ql, qr);
        return ans;
    }
};

int main() {
    int n, q; cin >> n >> q;
    vector<ll> v(n);
    for (auto &u: v) cin >> u;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].emplace_back(b);
        adj[b].emplace_back(a);
    }
    vector<int> parent(n);
    vector<int> in(n), out(n); // tempo di entrata e uscita dal nodo i
    function <void(int, int&)> dfs = [&] (int node, int &t) -> void {
        in[node] = t;
        for (auto u: adj[node]) {
            if (u != parent[node]) {
                t++;
                parent[u] = node;
                dfs(u, t);
            }
        }
        out[node] = t;
    };
    int t = 0;
    dfs(0, t);
    assert(t + 1 == n);
    vector<ll> diff(n + 1); // d[i] = v[i] - v[i - 1]
    for (int i = 0; i < n; i++) {
        diff[in[i]] += v[i];
        diff[out[i] + 1] -= v[i];
    }
    segtree seg = segtree(n + 1, diff);
    for (int i = 0; i < q; i++) {
        int a; cin >> a;
        if (a & 1) {
            int s, x; cin >> s >> x;
            s--;
            ll delta = x - v[s];
            v[s] = x;
            seg.update(in[s], delta);
            seg.update(out[s] + 1, -delta);
        } else {
            int s; cin >> s;
            s--;
            cout << seg.query(1, 0, in[s] + 1) << "\n";
        }
    }
}
