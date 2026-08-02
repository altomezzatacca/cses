#include "bits/stdc++.h"
using namespace std;

int grey(int n){
    return n ^ (n >> 1);
}

int rmv(int n, vector<stack<int>> s){
    if(!s[0].empty() && s[0].top() == n) return 0;
    else if(!s[1].empty() && s[1].top() == n) return 1;
    else return 2;
}

int main(){
    int n; cin >> n;
    int k = (1 << n) - 1;
    cout << k << "\n";
    int last = grey(0);
    vector<stack<int>> a(3);
    for(int i = n; i > 0; i--)
        a[0].push(i);
    array<int, 3> cycle;
    cycle[0] = 0;
    cycle[1] = (n & 1 ? 2 : 1);
    cycle[2] = 3 - cycle[1];
    int ix = 0;
    for(int i = 1; i <= k; i++){
        int g = grey(i);
        int nxt = log2(last ^ g) + 1;
        last = g;
        if(nxt == 1){
            cout << cycle[ix] + 1 << " ";
            a[cycle[ix]].pop();
            ix++;
            ix %= 3;
            a[cycle[ix]].push(nxt);
            cout << cycle[ix] + 1<< "\n";
        } else {
            int x = rmv(nxt, a);
            cout << x + 1<< " ";
            a[x].pop();
            int y;
            if((x != 0 && a[0].empty()) || (x != 0 && a[0].top() > nxt)) y = 0;
            else if ((x != 1 && a[1].empty()) || (x != 1 && a[1].top() > nxt)) y = 1;
            else y = 2;
            a[y].push(nxt);
            cout << y + 1 << "\n";
        }
    }
}
