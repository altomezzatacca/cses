#include "bits/stdc++.h"
using namespace std;
vector<int> vx = {0, 0, 1, -1};
vector<int> vy = {1, -1, 0, 0,};

int main(){
    int n, m; cin >> n >> m;
    vector<vector<char>> v(n, vector<char> (m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> v[i][j];
    auto exixts = [&] (int x, int y) -> bool {
        return (x >= 0 && y >= 0 && x < n && y < m);
    };
    vector<vector<bool>> visited(n, vector<bool> (m));
    function<void(int, int)> bfs = [&] (int x, int y) -> void {
        if(!exixts(x, y)) return;
        if(visited[x][y] || v[x][y] == '#') return;
        visited[x][y] = 1;
        for(int k = 0; k < 4; k++)
            bfs(x + vx[k], y + vy[k]);
    };
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++){
            if(visited[i][j] || v[i][j] == '#') continue;
            ans++;
            bfs(i, j);
        }
    cout << ans << "\n";
}
