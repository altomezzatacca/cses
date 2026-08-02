#include "bits/stdc++.h"
using namespace std;

int main(){
    string s; cin >> s;
    int n = s.size();
    if(n == 1){
        cout << 1;
        return 0;
    }
    int best = (s[0] == s[1] ? 1 : 0), cur = best;
    for(int i = 1; i < n; i++){
        if(s[i] == s[i - 1]) cur++;
        else {
            best = max(best, cur);
            cur = 1;
        }
    }
    best = max(best, cur);
    cout << best;
}
