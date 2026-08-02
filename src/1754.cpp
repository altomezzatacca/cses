#include "bits/stdc++.h"
using namespace std;
using ll = long long;

string solve(){
    ll a, b; cin >> a >> b;
    if(a < b) swap(a, b);
    if(a > 2 * b) return "NO"; 
    if((a + b) % 3 != 0) return "NO";
    return "YES";
}

int main(){
    int t; cin >> t;
    while(t--)
        cout << solve() << "\n";
}
