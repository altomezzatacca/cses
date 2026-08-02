#include "bits/stdc++.h"
using namespace std;
constexpr static int mod = 1e9 + 7;
// Burnside's Lemma
 
int gcd (int a, int b){
    if(b == 0) return a;
    return gcd(b, a % b);
}
 
int fastexp (long long b, int e){
    long long ans = 1;
    while(e){
        if(e & 1)
            ans = (ans * b) % mod;
        e >>= 1;
        b = (b * b) % mod;
    }
    return ans;
}
 
int main(){
    int n, m; cin >> n >> m;
    long long ans = 0;
    for(int i = 0; i < n; i++)
        ans = (ans + fastexp(m, gcd(i, n))) % mod;
    ans = (ans  * fastexp(n, mod - 2)) % mod; // ans /= n
    cout << ans << "\n";
}
