#include "bits/stdc++.h"
using namespace std;

int main() {
    int l = 0, r = 1e9 + 1;
    while (r > l) {
        int m = (l + r) >> 1;
        cout << "? " << m << "\n";
        string s; cin >> s;
        if (s == "YES")
            l = m + 1;
        else
            r = m;
    }
    cout << "! " << l << "\n";
}
