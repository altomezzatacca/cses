#include "bits/stdc++.h"
using namespace std;

bool ask(int a, int b) {
    cout << "? " << a << " " << b << "\n";
    string s; cin >> s;
    return (s == "YES" ? 1 : 0);
}

void merge(vector<int> &v, int l, int m, int r) {
    int x = m - l + 1,
        y = r - m;
    vector<int> a(x), b(y);
    for (int i = 0; i < x; i++)
        a[i] = v[i + l];
    for (int i = 0; i < y; i++)
        b[i] = v[i + m + 1];
    int i = l, i_a = 0, i_b = 0;
    while (i_a < x && i_b < y) {
        if (ask(a[i_a], b[i_b]))
            v[i++] = a[i_a++];
        else
            v[i++] = b[i_b++];
    }
    while (i_a < x)
        v[i++] = a[i_a++];
    while (i_b < y)
        v[i++] = b[i_b++];
}

void solve(vector<int> &v, int l, int r) {
    if (l == r) return;
    int m = (l + r) >> 1;
    solve(v, l, m);
    solve(v, m + 1, r);
    merge(v, l, m, r);
}

int main() {
    int n; cin >> n;
    vector<int> p(n);
    iota(begin(p), end(p), 1);
    solve(p, 0, n - 1);
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++)
        ans[p[i]] = i + 1;
    cout << "! ";
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}
