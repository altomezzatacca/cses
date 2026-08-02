#include "bits/stdc++.h"
using namespace std;
using ll = long long;
// n! contiene tanti trailing zeros quanti fattori 5 che ha (i fattori 2 sono più comuni)
// cerco v_5(n!) = floor(n/5^1) + floor(n/5^2) + floor(n/5^3) + ...

int main(){
    ll n; cin >> n;
    ll ans = 0, x = 5;
    while(x <= n){
        ans += n / x;
        x *= 5;
    }
    cout << ans << "\n";
}
