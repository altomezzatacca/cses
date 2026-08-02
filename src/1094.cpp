#include "bits/stdc++.h"
using namespace std;
using ll = long long;

int main(){
    int n; cin >> n;
    vector<int> v(n);
    for(auto &u: v) cin >> u;
    ll ans = 0;
    for(int i = 1; i < n; i++)
        if(v[i] < v[i - 1]){
            ll x = v[i - 1] - v[i];
            ans += x;
            v[i] += x;
        }
    cout << ans;
}
