#include "bits/stdc++.h"
using namespace std;
constexpr static int logN = 20;
 
int main(){
    int N, Q; cin >> N >> Q;
    vector<vector<int>> up(N, vector<int> (logN));
    up[0][0] = -1;
    for(int i = 1; i < N; i++){
        cin >> up[i][0];
        up[i][0]--;
    }
    for(int j = 1; j < logN; j++)
        for(int i = 0; i < N; i++)
            up[i][j] = (up[i][j - 1] == -1 ? -1 : up[up[i][j - 1]][j - 1]);
    for(int q = 0; q < Q; q++){
        int node, k; cin >> node >> k; node--;
        for(int j = logN - 1; j >= 0 && node != -1; j--)
            if(k & (1 << j))
                node = up[node][j];
        cout << (node == -1 ? -1 : node + 1) << "\n";
    }
}
