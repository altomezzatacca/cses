#include "bits/stdc++.h"
using namespace std;
using ll = long long;
// x pari, 1 -> (x - 1)^2 + 1
// x dispari, 1 -> x^2
// 1, y pari -> y^2
// 1, y dispari -> (y - 1)^2 + 1

void solve(){
    ll x, y; cin >> y >> x;
    ll xx = (x % 2 == 0 ? ((x - 1) * (x - 1)) + 1 : x * x);
    ll yy = (y % 2 == 0 ? y * y : ((y - 1) * (y - 1)) + 1);
    ll var = max(xx, yy), par = (var == xx ? x : y);
    cout << var + ((par == x && x % 2 == 1) || (par == y && y % 2 == 0) ? -1 : 1) * (x + y - par - 1) << "\n";
}

int main(){
    int t; cin >> t;
    while(t--)
        solve();
}
