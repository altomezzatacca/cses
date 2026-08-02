#include "bits/stdc++.h"
using namespace std;
using ll = long long;
constexpr static int mod = 1e9 + 7;

ll fast_exp(ll b, ll e){
    ll ans = 1;
    while(e){
        if(e & 1) ans = (ans * b) % mod;
        b = (b * b) % mod;
        e >>= 1;
    }
    return ans;
}

ll solve(){
    ll a, b; cin >> a >> b;
    return fast_exp(a, b);
}

int main(){
    int q; cin >> q;
    while(q--)
        cout << solve() << "\n";
}
