#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr static ll inf = 1e18;

int main() {
    int n; cin >> n;
    ll sum = 0, ans = inf;
    vector<ll> v(n);
    for (auto &u: v) cin >> u, sum += u;
    for (int k = 0; k < 1 << n; k++) {
        ll cur = 0;
        for (int bit = 0; bit < n; bit++)
            if (k & (1 << bit))
                cur += v[bit];
        ans = min(ans, abs(sum - 2 * cur));
    }
    cout << ans << "\n";
}
