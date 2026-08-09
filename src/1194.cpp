#include "bits/stdc++.h"
using namespace std;

int main(){
    vector<int> vx = {0, 0, 1, -1};
    vector<int> vy = {1, -1, 0, 0};
    int n, m; cin >> n >> m;
    vector<vector<char>> v(n, vector<char> (m));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            cin >> v[i][j];
    queue<pair<int, char>> q;
    int startpos = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(v[i][j] == 'M')
                q.emplace(i * m + j, 'M');
            else if (v[i][j] == 'A')
                startpos = i * m + j;
    q.emplace(startpos, 'A');
    auto exists = [&] (int x, int y) -> bool {
        return x >= 0 && y >= 0 && x < n && y < m;
    };
    vector<vector<bool>> mosited(n, vector<bool> (m));
    vector<vector<bool>> visited(n, vector<bool> (m));
    visited[startpos / m][startpos % m] = 1;
    vector<vector<int>> parent(n, vector<int> (m));
    while(!q.empty()){
        auto [coord, typ] = q.front(); q.pop();
        int x = coord / m, y = coord % m;
        if(typ == 'M'){ 
            for(int k = 0; k < 4; k++)
                if(exists(x + vx[k], y + vy[k]) && v[x + vx[k]][y + vy[k]] != '#' && !mosited[x + vx[k]][y + vy[k]]){ 
                    v[x + vx[k]][y + vy[k]] = 'M';
                    q.emplace((x + vx[k]) * m + y + vy[k], 'M');
                    mosited[x + vx[k]][y + vy[k]] = 1;
                }
        } else { 
            for(int k = 0; k < 4; k++)
                if(exists(x + vx[k], y + vy[k]) && v[x + vx[k]][y + vy[k]] == '.' && !visited[x + vx[k]][y + vy[k]]){
                    visited[x + vx[k]][y + vy[k]] = 1;
                    q.emplace((x + vx[k]) * m + y + vy[k], 'A');
                    parent[x + vx[k]][y + vy[k]] = x * m + y;
                }
        }
    }
    int found = -1;
    for(int i = 0; i < n && found == -1; i++){
        if(visited[i][0]) found = i * m;
        if(visited[i][m - 1]) found = i * m + m - 1;
    }
    for(int i = 0; i < m && found == -1; i++){
        if(visited[0][i]) found = i;
        if(visited[n - 1][i]) found = (n - 1) * m + i;
    }
    if(found == -1){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    string ans;
    while(found != startpos){
        int x = found / m, y = found % m;
        int nxt = parent[x][y];
        int xx = nxt / m, yy = nxt % m;
        if(x - xx == 1) ans.push_back('D');
        if(xx - x == 1) ans.push_back('U');
        if(y - yy == 1) ans.push_back('R');
        if(yy - y == 1) ans.push_back('L');
        found = nxt;
    }
    reverse(begin(ans), end(ans));
    cout << (int)ans.size() << "\n" << ans << "\n";
}
