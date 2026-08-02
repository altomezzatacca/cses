#include "bits/stdc++.h"
using namespace std;
using ll = long long;

ll solve(int n){
    if(n == 1) return 0;
    if(n == 2) return 6;
    if(n == 3) return 28;
    return (1LL * (n - 1) * (n + 4) * (n * n - 3 * n + 4)) >> 1;
}

int main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++)
        cout << solve(i + 1) << "\n";
}
