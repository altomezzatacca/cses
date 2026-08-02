#include "bits/stdc++.h"
using namespace std;
using ll = long long;

int main(){
    int n; cin >> n;
    ll nn = (1LL * n * (n + 1)) >> 1;
    if(nn & 1){
        cout << "NO";
        return 0;
    }
    cout << "YES\n";
    ll sum_a = 0, sum_b = 0;
    vector<int> a, b;
    for(int i = n; i > 0; i--){
        if(sum_a + i <= (nn) >> 1){
            sum_a += i;
            a.emplace_back(i);
        } else {
            sum_b += i;
            b.emplace_back(i);
        }
    }
    cout << (int)a.size() << "\n";
    for(auto u: a) cout << u << " ";
    cout << "\n" << (int)b.size() << "\n";
    for(auto u: b) cout << u << " ";
}
