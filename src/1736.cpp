#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct segtree{
    int sz = 1;
    struct node{
        ll sum;
        ll start, step;
    };
    vector<node> t;
    segtree(){}
    segtree(int n, vector<ll> v){
        while(sz < n) sz <<= 1;
        t.resize(2 * sz);
        for(int i = 0; i < n; i++)
            t[sz + i].sum = v[i];
        for(int i = n; i < sz; i++)
            t[sz + i].sum = 0;
        for(int i = sz - 1; i > 0; i--)
            t[i].sum = t[2 * i].sum + t[2 * i + 1].sum;
    }
    void propagate(int node, int nl, int nr){
        if(t[node].step){
            ll len = nr - nl;
            ll start = t[node].start;
            ll step = t[node].step;
            t[node].sum += start * len + step * (((len - 1) * len) >> 1);
            if(node < sz){
                int nm = (nl + nr) >> 1;
                ll len1 = nm - nl;
                t[2 * node].start += start;
                t[2 * node].step += step;
                t[2 * node + 1].start += start + len1 * step;
                t[2 * node + 1].step += step;
            }
            t[node].start = 0;
            t[node].step = 0;
        }
    }
    ll get_sum(int node, int nl, int nr, int ql, int qr){
        propagate(node, nl, nr);
        if(qr <= nl || nr <= ql) return 0;
        if(ql <= nl && nr <= qr) return t[node].sum;
        int nm = (nl + nr) >> 1;
        return get_sum(2 * node, nl, nm, ql, qr) + get_sum(2 * node + 1, nm, nr, ql, qr);
    }
    void add_range(int node, int nl, int nr, int ql, int qr){
        propagate(node, nl, nr);
        if(qr <= nl || nr <= ql) return;
        if(ql <= nl && nr <= qr){
            t[node].start += nl - ql + 1;
            t[node].step++;
            propagate(node, nl, nr);
            return;
        }
        int nm = (nl + nr) >> 1;
        add_range(2 * node, nl, nm, ql, qr);
        add_range(2 * node + 1, nm, nr, ql, qr);
        t[node].sum = t[2 * node].sum + t[2 * node + 1].sum;
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
            int a, b; cin >> a >> b;
            a--;
            seg.add_range(1, 0, seg.sz, a, b);
        } else if (x == 2) {
            int a, b; cin >> a >> b;
            a--;
            cout << seg.get_sum(1, 0, seg.sz, a, b) << "\n";
        }
    }
}
