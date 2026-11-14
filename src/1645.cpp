#include "bits/stdc++.h"
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> v(n);
    for (auto &u: v) cin >> u;
    stack<int> s;
    vector<int> prv(n);
    for (int i = 0; i < n; i++) {
        while (!s.empty() && v[s.top()] >= v[i])
            s.pop();
        if (s.empty())
            prv[i] = -1;
        else
            prv[i] = s.top();
        s.emplace(i);
    }
    for (auto u: prv)
        cout << u + 1 << " ";
    cout << "\n";
}
