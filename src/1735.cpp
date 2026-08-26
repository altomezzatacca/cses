#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct segtree{
    int sz = 1;
    struct node{
        ll v_sum;
        bool sum_update, set_update;
        ll u_sum, u_set;
    };
    vector<node> t;
    segtree(){}
    segtree(int n, vector<ll> v){
        while(sz < n) sz <<= 1;
        t.resize(2 * sz);
        for(int i = 0; i < n; i++)
            t[sz + i].v_sum = v[i];
        for(int i = n; i < sz; i++)
            t[sz + i].v_sum = 0;
        for(int i = sz - 1; i > 0; i--)
            t[i].v_sum = t[2 * i].v_sum + t[2 * i + 1].v_sum;
    }
    void propagate(int node, int nl, int nr){
        if(t[node].set_update){
            t[node].v_sum = t[node].u_set * (nr - nl);
            if(node < sz){
                t[2 * node].set_update = 1;
                t[2 * node].sum_update = 0;
                t[2 * node].u_set = t[node].u_set;
                t[2 * node].u_sum = 0;
                t[2 * node + 1].set_update = 1;
                t[2 * node + 1].sum_update = 0;
                t[2 * node + 1].u_set = t[node].u_set;
                t[2 * node + 1].u_sum = 0;
            }
            t[node].u_set = 0;
            t[node].set_update = 0;
        }
        if(t[node].sum_update){
            t[node].v_sum += t[node].u_sum * (nr - nl);
            if(node < sz){
                t[2 * node].sum_update = 1;
                t[2 * node].u_sum += t[node].u_sum;
                t[2 * node + 1].sum_update = 1;
                t[2 * node + 1].u_sum += t[node].u_sum;
            }
            t[node].u_sum = 0;
            t[node].sum_update = 0;
        }
    }
    ll get_sum(int node, int nl, int nr, int ql, int qr){
        propagate(node, nl, nr);
        if(qr <= nl || nr <= ql) return 0;
        if(ql <= nl && nr <= qr) return t[node].v_sum;
        int nm = (nl + nr) >> 1;
        return get_sum(2 * node, nl, nm, ql, qr) + get_sum(2 * node + 1, nm, nr, ql, qr);
    }
    void add_range(int node, int nl, int nr, int ql, int qr, ll x){
        propagate(node, nl, nr);
        if(qr <= nl || nr <= ql) return;
        if(ql <= nl && nr <= qr){
            t[node].sum_update = 1;
            t[node].u_sum += x;
            propagate(node, nl, nr);
            return;
        }
        int nm = (nl + nr) >> 1;
        add_range(2 * node, nl, nm, ql, qr, x);
        add_range(2 * node + 1, nm, nr, ql, qr, x);
        t[node].v_sum = t[2 * node].v_sum + t[2 * node + 1].v_sum;
    }
    void set_range(int node, int nl, int nr, int ql, int qr, ll x){
        propagate(node, nl, nr);
        if(qr <= nl || nr <= ql) return;
        if(ql <= nl && nr <= qr){
            t[node].sum_update = 0;
            t[node].u_sum = 0;
            t[node].set_update = 1;
            t[node].u_set = x;
            propagate(node, nl, nr);
            return;
        }
        int nm = (nl + nr) >> 1;
        set_range(2 * node, nl, nm, ql, qr, x);
        set_range(2 * node + 1, nm, nr, ql, qr, x);
        t[node].v_sum = t[2 * node].v_sum + t[2 * node + 1].v_sum;
    }
};

int main(){
    int n, q; cin >> n >> q;
    vector<ll> t(n);
    for(auto &u: t) cin >> u;
    segtree seg = segtree(n, t);
    for (int i = 0, x; i < q; i++) {
        cin >> x;
        if (x == 1) {
            int a, b, c; cin >> a >> b >> c;
            a--;
            seg.add_range(1, 0, seg.sz, a, b, c);
        } else if (x == 2) {
            int a, b, c; cin >> a >> b >> c;
            a--;
            seg.set_range(1, 0, seg.sz, a, b, c);
        } else {
            int a, b; cin >> a >> b;
            a--;
            cout << seg.get_sum(1, 0, seg.sz, a, b) << "\n";
        }
    }
}
